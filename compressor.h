#ifndef COMPRESSOR_H
#define COMPRESSOR_H

#include "utils.h"
#include "QtZlib/zlib.h"
#include "lzokay.hpp"
#include "lzx.h"

#include <stdint.h>
#include <stddef.h>
#include <QByteArray>
#include <QDebug>
#include <QDataStream>
#include <QVector>
#include <algorithm>

typedef enum {
    EResult_LookbehindOverrun = -4,
    EResult_OutputOverrun = -3,
    EResult_InputOverrun = -2,
    EResult_Error = -1,
    EResult_Success = 0,
    EResult_InputNotConsumed = 1,
} lzokay_EResult;

static_assert(EResult_LookbehindOverrun == lzokay_EResult(lzokay::EResult::LookbehindOverrun), "LookbehindOverrun mismatch");
static_assert(EResult_OutputOverrun == lzokay_EResult(lzokay::EResult::OutputOverrun), "OutputOverrun mismatch");
static_assert(EResult_InputOverrun == lzokay_EResult(lzokay::EResult::InputOverrun), "InputOverrun mismatch");
static_assert(EResult_Error == lzokay_EResult(lzokay::EResult::Error), "Error mismatch");
static_assert(EResult_Success == lzokay_EResult(lzokay::EResult::Success), "Success mismatch");
static_assert(EResult_InputNotConsumed == lzokay_EResult(lzokay::EResult::InputNotConsumed), "InputNotConsumed mismatch");

class Compressor {
public:
    static QByteArray DecompressZLIB(const QByteArray &compressedData) {
        if (compressedData.isEmpty())
            return QByteArray();

        // Set up the inflate stream.
        z_stream strm;
        memset(&strm, 0, sizeof(strm));
        // The inflate() function needs a non-const pointer; this is safe as we never modify the input.
        strm.next_in = reinterpret_cast<Bytef*>(const_cast<char*>(compressedData.data()));
        strm.avail_in = static_cast<uInt>(compressedData.size());

        // Use inflateInit(); if you want to support gzip streams, see note below.
        int ret = inflateInit(&strm);
        if (ret != Z_OK) {
            qWarning() << "inflateInit failed:" << zError(ret);
            return QByteArray();
        }

        QByteArray outArray;
        char buffer[4096];

        // Decompress until we reach the stream end.
        do {
            strm.next_out = reinterpret_cast<Bytef*>(buffer);
            strm.avail_out = sizeof(buffer);

            ret = inflate(&strm, Z_NO_FLUSH);
            // Handle a special case: if inflate() returns Z_BUF_ERROR without
            // having produced any output and with no further input, then we break out.
            if (ret == Z_BUF_ERROR && strm.avail_in == 0) {
                break;
            }
            if (ret != Z_OK && ret != Z_STREAM_END) {
                qWarning() << "Error: ZLib inflate failed:" << zError(ret);
                inflateEnd(&strm);
                return QByteArray();
            }

            // Calculate number of bytes produced in this iteration.
            int bytesProduced = sizeof(buffer) - strm.avail_out;
            if (bytesProduced > 0)
                outArray.append(buffer, bytesProduced);

        } while (ret != Z_STREAM_END);

        inflateEnd(&strm);
        return outArray;
    }

    static QByteArray DecompressLZO(const QByteArray& input) {
        lzokay::EResult error;

        // Ensure the input QByteArray is valid
        if (input.isEmpty()) {
            qDebug() << "Input QByteArray is empty.";
            return QByteArray();
        }

        // Step 1: Cast QByteArray to uint8_t*
        const uint8_t *compressedData = reinterpret_cast<const uint8_t *>(input.constData());
        std::size_t compressedSize = static_cast<std::size_t>(input.size());

        // Step 2: Allocate a sufficiently large decompression buffer
        // Use a large initial estimate if the decompressed size is unknown
        std::size_t initialBufferSize = compressedSize * 20; // Arbitrary multiplier for decompression
        std::unique_ptr<uint8_t[]> decompressed(new uint8_t[initialBufferSize]);

        // Step 3: Attempt decompression
        std::size_t decompressedSize = 0;
        error = lzokay::decompress(
            compressedData, compressedSize, // Input data and size
            decompressed.get(), initialBufferSize, // Output buffer and initial size
            decompressedSize // Actual decompressed size
            );

        // Step 4: Handle decompression errors
        if (error != lzokay::EResult::Success) {
            qDebug() << "Decompression failed with error code:" << static_cast<int>(error);
            return QByteArray();
        }

        // Step 5: Return the decompressed data as a QByteArray
        return QByteArray(reinterpret_cast<const char *>(decompressed.get()), decompressedSize);
    }

    static const int VECTOR_SIZE = 16;        // 16 32-bit words
    static const int NUM_OF_BLOCKS_PER_CHUNK = 8192;

    //--------------------------------------------------------------------
    // Helper functions (assuming little–endian order)

    static void Convert32BitTo8Bit(quint32 value, quint8* array) {
        array[0] = static_cast<quint8>(value >> 0);
        array[1] = static_cast<quint8>(value >> 8);
        array[2] = static_cast<quint8>(value >> 16);
        array[3] = static_cast<quint8>(value >> 24);
    }

    static quint32 ConvertArrayTo32Bit(const QByteArray &array) {
        return ((static_cast<quint32>(static_cast<uchar>(array[0])) << 0)  |
                (static_cast<quint32>(static_cast<uchar>(array[1])) << 8)  |
                (static_cast<quint32>(static_cast<uchar>(array[2])) << 16) |
                (static_cast<quint32>(static_cast<uchar>(array[3])) << 24));
    }

    static quint32 Rotate(quint32 value, quint32 numBits) {
        return (value << numBits) | (value >> (32 - numBits));
    }

    // Build the IV table from a 0x20–byte feed. The table is 0xFB0 bytes.
    static QByteArray InitIVTable(const QByteArray &feed) {
        const int tableSize = 0xFB0;
        QByteArray table;
        table.resize(tableSize);
        int ptr = 0;
        for (int i = 0; i < 200; ++i) {
            for (int x = 0; x < 5; ++x) {
                if (static_cast<uchar>(feed.at(ptr)) == 0x00)
                    ptr = 0;
                int base = i * 20 + x * 4;
                table[base]     = feed.at(ptr);
                table[base + 1] = feed.at(ptr);
                table[base + 2] = feed.at(ptr);
                table[base + 3] = feed.at(ptr);
                ++ptr;
            }
        }
        // Copy block numbers [1,0,0,0] into the last 16 bytes
        QByteArray oneBlock;
        oneBlock.append(char(1)); oneBlock.append(char(0)); oneBlock.append(char(0)); oneBlock.append(char(0));
        table.replace(0xFA0, 4, oneBlock);
        table.replace(0xFA4, 4, oneBlock);
        table.replace(0xFA8, 4, oneBlock);
        table.replace(0xFAC, 4, oneBlock);
        return table;
    }

    // "unk" function as in the C# code.
    static int unk(quint64 arg1, quint8 arg2) {
        if (arg2 >= 0x40)
            return 0;
        return static_cast<int>(arg1 >> arg2);
    }

    // Compute the IV for a given section index using the IV table.
    static QByteArray GetIV(const QByteArray &table, int index) {
        int num1 = 0xFA0 + index;
        int num2 = unk(0x51EB851FLL * num1, 0x20);
        int adjust = ((num2 >> 6) + (num2 >> 31));
        int startIndex = 20 * (num1 - 200 * adjust);
        // Return 8 bytes from that location.
        return table.mid(startIndex, 8);
    }

    // Update the IV table given the section's SHA1 hash.
    static void UpdateIVTable(QByteArray &table, int index, const QByteArray &sectionHash) {
        int blockNumIndex = index % 4;
        int baseOffset = 0xFA0 + blockNumIndex * 4;
        quint32 blockNumVal = (static_cast<uchar>(table.at(baseOffset))      ) |
                              (static_cast<uchar>(table.at(baseOffset + 1)) << 8 ) |
                              (static_cast<uchar>(table.at(baseOffset + 2)) << 16) |
                              (static_cast<uchar>(table.at(baseOffset + 3)) << 24);
        int blockNum = blockNumVal * 4 + index;
        int num2 = unk(0x51EB851FLL * blockNum, 0x20);
        int adjust = ((num2 >> 6) + (num2 >> 31));
        int startIndex = 20 * (blockNum - 200 * adjust) + 1;
        int hashIndex = 0;
        for (int x = 0; x < 4; ++x) {
            table[startIndex - 1] = table.at(startIndex - 1) ^ sectionHash.at(hashIndex);
            table[startIndex]     = table.at(startIndex)     ^ sectionHash.at(hashIndex + 1);
            table[startIndex + 1] = table.at(startIndex + 1) ^ sectionHash.at(hashIndex + 2);
            table[startIndex + 2] = table.at(startIndex + 2) ^ sectionHash.at(hashIndex + 3);
            table[startIndex + 3] = table.at(startIndex + 3) ^ sectionHash.at(hashIndex + 4);
            startIndex += 5;
            hashIndex += 5;
        }
    }

    static quint32 ToUInt32(const QByteArray &data, int offset) {
        // Converts 4 bytes (starting at offset) from data into a 32-bit unsigned integer (little-endian)
        return ((static_cast<quint32>(static_cast<uchar>(data[offset]))      ) |
                (static_cast<quint32>(static_cast<uchar>(data[offset+1])) << 8 ) |
                (static_cast<quint32>(static_cast<uchar>(data[offset+2])) << 16) |
                (static_cast<quint32>(static_cast<uchar>(data[offset+3])) << 24));
    }

    //--------------------------------------------------------------------
    // Salsa20 decryption for one section.
    // This function resets the counter for each section.
    static QByteArray salsa20DecryptSection(const QByteArray &sectionData, const QByteArray &key, const QByteArray &iv, int blockSize = 64)
    {
        // Choose the appropriate constant based on key length.
        QByteArray constants;
        if (key.size() == 32)
            constants = "expand 32-byte k";
        else if (key.size() == 16)
            constants = "expand 16-byte k";
        else {
            qWarning() << "Invalid key size:" << key.size() << "; expected 16 or 32 bytes.";
            return QByteArray();
        }

        QVector<quint32> state(VECTOR_SIZE);

        // Set state[0] using the first 4 bytes of the constant.
        state[0] = ConvertArrayTo32Bit(constants.mid(0, 4));

        // state[1] through state[4] come from the first 16 bytes of the key.
        state[1] = ToUInt32(key, 0);
        state[2] = ToUInt32(key, 4);
        state[3] = ToUInt32(key, 8);
        state[4] = ToUInt32(key, 12);

        // state[5] comes from the next 4 bytes of the constant.
        state[5] = ConvertArrayTo32Bit(constants.mid(4, 4));

        // state[6] and state[7] come from the IV (which must be 8 bytes).
        state[6] = ConvertArrayTo32Bit(iv.mid(0, 4));
        state[7] = ConvertArrayTo32Bit(iv.mid(4, 4));

        // state[8] and state[9] are the 64-bit block counter (start at 0).
        state[8] = 0;
        state[9] = 0;

        // state[10] comes from the next 4 bytes of the constant.
        state[10] = ConvertArrayTo32Bit(constants.mid(8, 4));

        // For state[11] through state[14]:
        // If the key is 32 bytes, use bytes 16..31; if 16 bytes, reuse the first 16 bytes.
        if (key.size() == 32) {
            state[11] = ToUInt32(key, 16);
            state[12] = ToUInt32(key, 20);
            state[13] = ToUInt32(key, 24);
            state[14] = ToUInt32(key, 28);
        } else { // key.size() == 16
            state[11] = ToUInt32(key, 0);
            state[12] = ToUInt32(key, 4);
            state[13] = ToUInt32(key, 8);
            state[14] = ToUInt32(key, 12);
        }

        // state[15] comes from the last 4 bytes of the constant.
        state[15] = ConvertArrayTo32Bit(constants.mid(12, 4));

        // Prepare the output buffer.
        QByteArray output(sectionData.size(), Qt::Uninitialized);
        int numBlocks = sectionData.size() / blockSize;
        int remainder = sectionData.size() % blockSize;

        // Process each full block.
        for (int blockIndex = 0; blockIndex < numBlocks; ++blockIndex) {
            QVector<quint32> x = state; // make a copy of the current state for this block

            // Run 20 rounds (10 iterations) of Salsa20.
            for (int round = 20; round > 0; round -= 2) {
                x[4]  ^= Rotate(x[0]  + x[12], 7);
                x[8]  ^= Rotate(x[4]  + x[0], 9);
                x[12] ^= Rotate(x[8]  + x[4], 13);
                x[0]  ^= Rotate(x[12] + x[8], 18);

                x[9]  ^= Rotate(x[5]  + x[1], 7);
                x[13] ^= Rotate(x[9]  + x[5], 9);
                x[1]  ^= Rotate(x[13] + x[9], 13);
                x[5]  ^= Rotate(x[1]  + x[13], 18);

                x[14] ^= Rotate(x[10] + x[6], 7);
                x[2]  ^= Rotate(x[14] + x[10], 9);
                x[6]  ^= Rotate(x[2]  + x[14], 13);
                x[10] ^= Rotate(x[6]  + x[2], 18);

                x[3]  ^= Rotate(x[15] + x[11], 7);
                x[7]  ^= Rotate(x[3]  + x[15], 9);
                x[11] ^= Rotate(x[7]  + x[3], 13);
                x[15] ^= Rotate(x[11] + x[7], 18);

                x[1]  ^= Rotate(x[0]  + x[3], 7);
                x[2]  ^= Rotate(x[1]  + x[0], 9);
                x[3]  ^= Rotate(x[2]  + x[1], 13);
                x[0]  ^= Rotate(x[3]  + x[2], 18);

                x[6]  ^= Rotate(x[5]  + x[4], 7);
                x[7]  ^= Rotate(x[6]  + x[5], 9);
                x[4]  ^= Rotate(x[7]  + x[6], 13);
                x[5]  ^= Rotate(x[4]  + x[7], 18);

                x[11] ^= Rotate(x[10] + x[9], 7);
                x[8]  ^= Rotate(x[11] + x[10], 9);
                x[9]  ^= Rotate(x[8]  + x[11], 13);
                x[10] ^= Rotate(x[9]  + x[8], 18);

                x[12] ^= Rotate(x[15] + x[14], 7);
                x[13] ^= Rotate(x[12] + x[15], 9);
                x[14] ^= Rotate(x[13] + x[12], 13);
                x[15] ^= Rotate(x[14] + x[13], 18);
            }

            // Produce the 64-byte keystream block by adding the original state.
            QVector<quint8> keyStreamBlock(blockSize);
            for (int i = 0; i < VECTOR_SIZE; ++i) {
                x[i] += state[i];
                Convert32BitTo8Bit(x[i], keyStreamBlock.data() + 4 * i);
            }

            // XOR the keystream block with the corresponding block of sectionData.
            const uchar* inBlock = reinterpret_cast<const uchar*>(sectionData.constData()) + blockIndex * blockSize;
            uchar* outBlock = reinterpret_cast<uchar*>(output.data()) + blockIndex * blockSize;
            for (int j = 0; j < blockSize; ++j) {
                outBlock[j] = inBlock[j] ^ keyStreamBlock[j];
            }
            // Increment the 64-bit block counter.
            state[8]++;
            if (state[8] == 0)
                state[9]++;
        }

        // Process any remaining bytes.
        if (remainder > 0) {
            QVector<quint32> x = state;
            for (int round = 20; round > 0; round -= 2) {
                x[4]  ^= Rotate(x[0]  + x[12], 7);
                x[8]  ^= Rotate(x[4]  + x[0], 9);
                x[12] ^= Rotate(x[8]  + x[4], 13);
                x[0]  ^= Rotate(x[12] + x[8], 18);

                x[9]  ^= Rotate(x[5]  + x[1], 7);
                x[13] ^= Rotate(x[9]  + x[5], 9);
                x[1]  ^= Rotate(x[13] + x[9], 13);
                x[5]  ^= Rotate(x[1]  + x[13], 18);

                x[14] ^= Rotate(x[10] + x[6], 7);
                x[2]  ^= Rotate(x[14] + x[10], 9);
                x[6]  ^= Rotate(x[2]  + x[14], 13);
                x[10] ^= Rotate(x[6]  + x[2], 18);

                x[3]  ^= Rotate(x[15] + x[11], 7);
                x[7]  ^= Rotate(x[3]  + x[15], 9);
                x[11] ^= Rotate(x[7]  + x[3], 13);
                x[15] ^= Rotate(x[11] + x[7], 18);

                x[1]  ^= Rotate(x[0]  + x[3], 7);
                x[2]  ^= Rotate(x[1]  + x[0], 9);
                x[3]  ^= Rotate(x[2]  + x[1], 13);
                x[0]  ^= Rotate(x[3]  + x[2], 18);

                x[6]  ^= Rotate(x[5]  + x[4], 7);
                x[7]  ^= Rotate(x[6]  + x[5], 9);
                x[4]  ^= Rotate(x[7]  + x[6], 13);
                x[5]  ^= Rotate(x[4]  + x[7], 18);

                x[11] ^= Rotate(x[10] + x[9], 7);
                x[8]  ^= Rotate(x[11] + x[10], 9);
                x[9]  ^= Rotate(x[8]  + x[11], 13);
                x[10] ^= Rotate(x[9]  + x[8], 18);

                x[12] ^= Rotate(x[15] + x[14], 7);
                x[13] ^= Rotate(x[12] + x[15], 9);
                x[14] ^= Rotate(x[13] + x[12], 13);
                x[15] ^= Rotate(x[14] + x[13], 18);
            }
            QVector<quint8> keyStreamBlock(blockSize);
            for (int i = 0; i < VECTOR_SIZE; ++i) {
                x[i] += state[i];
                Convert32BitTo8Bit(x[i], keyStreamBlock.data() + 4 * i);
            }
            const uchar* inBlock = reinterpret_cast<const uchar*>(sectionData.constData()) + numBlocks * blockSize;
            uchar* outBlock = reinterpret_cast<uchar*>(output.data()) + numBlocks * blockSize;
            for (int j = 0; j < remainder; ++j)
                outBlock[j] = inBlock[j] ^ keyStreamBlock[j];
        }

        return output;
    }
};


#endif // COMPRESSOR_H
