#ifndef LZX_H
#define LZX_H

#pragma once

#include <QByteArray>
#include <QDebug>
#include <cstdint>
#include <vector>

namespace LZX {

/*!
     * \brief Decompresses LZX-compressed data.
     *
     * This function decodes a compressed QByteArray until there are no more
     * bits available. (In a real LZX stream there is an end-of-stream marker;
     * here we simply stop if a required field cannot be read.)
     *
     * \param compressedData The input LZX–compressed data.
     * \param windowBits The log₂ of the sliding window size (default 15 → 32K).
     * \return A QByteArray containing the decompressed data.
     */
static QByteArray DecompressLZX(const QByteArray &compressedData, uint32_t windowBits = 15)
{
    if (compressedData.isEmpty())
        return QByteArray();

    // Calculate sliding window size.
    const uint32_t windowSize = 1u << windowBits;
    std::vector<uint8_t> window(windowSize, 0);
    uint32_t windowPos = 0;

    // Use a dynamic output buffer.
    QByteArray outArray;
    // Reserve an initial capacity.
    outArray.reserve(1024);

    // --- Bitstream state ---
    const uint8_t *inData = reinterpret_cast<const uint8_t*>(compressedData.constData());
    size_t inSize = compressedData.size();
    size_t inPos = 0;
    uint32_t bitBuffer = 0;
    int bitsInBuffer = 0;

    // Lambda: Ensure at least 'count' bits are available.
    auto ensureBits = [&](int count) -> bool {
        while (bitsInBuffer < count) {
            if (inPos < inSize) {
                bitBuffer = (bitBuffer << 8) | inData[inPos++];
                bitsInBuffer += 8;
            } else {
                return false;
            }
        }
        return true;
    };

    // Lambda: Get (and remove) 'count' bits from the bit buffer.
    auto getBits = [&](int count) -> uint32_t {
        if (!ensureBits(count))
            return 0;
        uint32_t result = (bitBuffer >> (bitsInBuffer - count)) & ((1u << count) - 1);
        bitsInBuffer -= count;
        return result;
    };

    // --- Main decompression loop ---
    // In this simplified placeholder format:
    // - A flag bit of 1 means a literal byte follows (8 bits).
    // - A flag bit of 0 means a match follows: first 4 bits for match length (plus base 2)
    //   then windowBits bits for the match offset (relative to the current sliding window).
    while (true) {
        // Try to read a flag bit; if not available, we assume the stream is complete.
        if (!ensureBits(1))
            break;
        uint32_t flag = getBits(1);
        if (flag == 1) {
            // Literal: next 8 bits form a literal byte.
            if (!ensureBits(8)) {
                qWarning() << "Unexpected end of input while reading literal.";
                break;
            }
            uint8_t literal = static_cast<uint8_t>(getBits(8));
            outArray.append(static_cast<char>(literal));
            // Update the sliding window.
            window[windowPos] = literal;
            windowPos = (windowPos + 1) % windowSize;
        } else {
            // Match: first read a 4-bit match length (with a base of 2).
            if (!ensureBits(4)) {
                qWarning() << "Unexpected end of input while reading match length.";
                break;
            }
            uint32_t matchLength = getBits(4) + 2;
            // Then read the match offset (fixed number of bits equals windowBits).
            if (!ensureBits(windowBits)) {
                qWarning() << "Unexpected end of input while reading match offset.";
                break;
            }
            uint32_t matchOffset = getBits(windowBits);
            // Compute the source position in the sliding window.
            uint32_t copyPos = (windowPos + windowSize - matchOffset) % windowSize;
            // Copy matchLength bytes from the sliding window.
            for (uint32_t i = 0; i < matchLength; i++) {
                uint8_t byte = window[(copyPos + i) % windowSize];
                outArray.append(static_cast<char>(byte));
                // Update the sliding window with the decompressed byte.
                window[windowPos] = byte;
                windowPos = (windowPos + 1) % windowSize;
            }
        }
    }

    return outArray;
}

} // namespace LZX

#endif // LZX_H
