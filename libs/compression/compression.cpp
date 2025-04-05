#include "compression.h"
#include "lzokay.h"
#include "qlibrary.h"

QByteArray Compression::DecompressZLIB(const QByteArray &aCompressedData) {
    if (aCompressedData.isEmpty())
        return {};

    z_stream strm{};
    strm.next_in = reinterpret_cast<Bytef*>(const_cast<char*>(aCompressedData.data()));
    strm.avail_in = static_cast<uInt>(aCompressedData.size());

    if (inflateInit2(&strm, MAX_WBITS) != Z_OK) {
        qWarning() << "Failed to initialize zlib for decompression.";
        return {};
    }

    QByteArray decompressed;
    char buffer[4096];

    int ret;
    do {
        strm.next_out = reinterpret_cast<Bytef*>(buffer);
        strm.avail_out = sizeof(buffer);

        ret = inflate(&strm, Z_NO_FLUSH);

        if (ret != Z_OK && ret != Z_STREAM_END) {
            qWarning() << "Zlib decompression error:" << zError(ret);
            inflateEnd(&strm);
            return {};
        }

        decompressed.append(buffer, sizeof(buffer) - strm.avail_out);
    } while (ret != Z_STREAM_END);

    inflateEnd(&strm);
    return decompressed;
}

QByteArray Compression::CompressZLIB(const QByteArray &aData) {
    return CompressZLIBWithSettings(aData);
}

QByteArray Compression::CompressZLIBWithSettings(const QByteArray &aData, int aCompressionLevel, int aWindowBits, int aMemLevel, int aStrategy, const QByteArray &aDictionary) {
    if (aData.isEmpty())
        return {};

    z_stream strm{};
    if (deflateInit2(&strm, aCompressionLevel, Z_DEFLATED, aWindowBits, aMemLevel, aStrategy) != Z_OK) {
        qWarning() << "Failed to initialize compression with custom settings.";
        return {};
    }

    if (!aDictionary.isEmpty()) {
        deflateSetDictionary(&strm, reinterpret_cast<const Bytef*>(aDictionary.constData()), aDictionary.size());
    }

    strm.next_in = reinterpret_cast<Bytef*>(const_cast<char*>(aData.data()));
    strm.avail_in = aData.size();

    QByteArray compressed;
    char buffer[4096];

    int ret;
    do {
        strm.next_out = reinterpret_cast<Bytef*>(buffer);
        strm.avail_out = sizeof(buffer);

        ret = deflate(&strm, strm.avail_in ? Z_NO_FLUSH : Z_FINISH);
        if (ret != Z_OK && ret != Z_STREAM_END) {
            qWarning() << "Compression error:" << zError(ret);
            deflateEnd(&strm);
            return {};
        }

        compressed.append(buffer, sizeof(buffer) - strm.avail_out);
    } while (ret != Z_STREAM_END);

    deflateEnd(&strm);
    return compressed;
}

QByteArray Compression::DecompressDeflate(const QByteArray &aCompressedData) {
    if (aCompressedData.isEmpty())
        return {};

    z_stream strm{};
    strm.next_in = reinterpret_cast<Bytef*>(const_cast<char*>(aCompressedData.data()));
    strm.avail_in = static_cast<uInt>(aCompressedData.size());

    // Negative window bits (-MAX_WBITS) indicate raw DEFLATE data.
    if (inflateInit2(&strm, -MAX_WBITS) != Z_OK) {
        qWarning() << "Failed to initialize DEFLATE for decompression.";
        return QByteArray();
    }

    QByteArray decompressed;
    char buffer[4096];

    int ret;
    do {
        strm.next_out = reinterpret_cast<Bytef*>(buffer);
        strm.avail_out = sizeof(buffer);

        ret = inflate(&strm, Z_NO_FLUSH);

        if (ret != Z_OK && ret != Z_STREAM_END) {
            qWarning() << "DEFLATE decompression error:" << zError(ret);
            inflateEnd(&strm);
            return QByteArray();
        }

        decompressed.append(buffer, sizeof(buffer) - strm.avail_out);
    } while (ret != Z_STREAM_END);

    inflateEnd(&strm);
    return decompressed;
}

QByteArray Compression::CompressDeflate(const QByteArray &aData) {
    return CompressDeflateWithSettings(aData);
}

QByteArray Compression::CompressDeflateWithSettings(const QByteArray &aData, int aCompressionLevel, int aWindowBits, int aMemLevel, int aStrategy, const QByteArray &aDictionary) {
    if (aData.isEmpty())
        return QByteArray();

    z_stream strm{};

    // Negative window bits (-MAX_WBITS) indicate raw DEFLATE data.
    if (deflateInit2(&strm, aCompressionLevel, Z_DEFLATED, -aWindowBits, aMemLevel, aStrategy) != Z_OK) {
        qWarning() << "Failed to initialize DEFLATE for compression.";
        return QByteArray();
    }

    strm.next_in = reinterpret_cast<Bytef*>(const_cast<char*>(aData.data()));
    strm.avail_in = static_cast<uInt>(aData.size());

    QByteArray compressed;
    char buffer[4096];

    int ret;
    do {
        strm.next_out = reinterpret_cast<Bytef*>(buffer);
        strm.avail_out = sizeof(buffer);

        ret = deflate(&strm, strm.avail_in ? Z_NO_FLUSH : Z_FINISH);

        if (ret != Z_OK && ret != Z_STREAM_END) {
            qWarning() << "DEFLATE compression error:" << zError(ret);
            deflateEnd(&strm);
            return {};
        }

        compressed.append(buffer, sizeof(buffer) - strm.avail_out);
    } while (ret != Z_STREAM_END);

    deflateEnd(&strm);
    return compressed;

}

QByteArray Compression::DecompressOodle(const QByteArray &aCompressedData, quint32 aDecompressedSize) {
    return pDecompressOodle(aCompressedData, aCompressedData.length(), aDecompressedSize);
}

QByteArray Compression::CompressOodle(const QByteArray &aData) {

    quint32 maxSize = pGetOodleCompressedBounds(aData.length());
    QByteArray compressedData = pCompressOodle(aData, aData.length(),
                                  maxSize, OodleFormat::Kraken, OodleCompressionLevel::Optimal5);

    return compressedData.mid(0, maxSize);
}

quint32 Compression::pGetOodleCompressedBounds(quint32 aBufferSize) {
    return aBufferSize + 274 * ((aBufferSize + 0x3FFFF) / 0x400000);
}

QByteArray Compression::pCompressOodle(QByteArray aBuffer, quint32 aBufferSize, quint32 aOutputBufferSize, OodleFormat aformat, OodleCompressionLevel alevel) {
    QLibrary oodleLib("oo2core_8_win64");

    if (!oodleLib.load()) {
        qDebug() << "Failed to load DLL:" << oodleLib.errorString();
        return QByteArray();
    }

    OodleLZ_CompressFunc OodleLZ_Compress =
        (OodleLZ_CompressFunc)oodleLib.resolve("OodleLZ_Compress");

    if (!OodleLZ_Compress) {
        qDebug() << "Failed to resolve function:" << oodleLib.errorString();
        return QByteArray();
    }

    std::byte *outputBuffer = new std::byte[aOutputBufferSize];

    if (aBuffer.length() > 0 && aBufferSize > 0 && aOutputBufferSize > 0)
        OodleLZ_Compress(aformat, reinterpret_cast<std::byte*>(aBuffer.data()), aBufferSize, outputBuffer, alevel, 0, 0, 0);

    return QByteArray(reinterpret_cast<const char*>(outputBuffer), aOutputBufferSize);
}

QByteArray Compression::pDecompressOodle(QByteArray aBuffer, quint32 aBufferSize, quint32 aOutputBufferSize) {
    QLibrary oodleLib("oo2core_8_win64");

    if (!oodleLib.load()) {
        qDebug() << "Failed to load DLL:" << oodleLib.errorString();
        return QByteArray();
    }

    OodleLZ_DecompressFunc OodleLZ_Decompress =
        (OodleLZ_DecompressFunc)oodleLib.resolve("OodleLZ_Decompress");

    if (!OodleLZ_Decompress) {
        qDebug() << "Failed to resolve function:" << oodleLib.errorString();
        return QByteArray();
    }

    std::byte *outputBuffer = new std::byte[aOutputBufferSize];

    if (aBuffer.length() > 0 && aBufferSize > 0 && aOutputBufferSize > 0)
        OodleLZ_Decompress(reinterpret_cast<std::byte*>(aBuffer.data()), aBufferSize, outputBuffer, aOutputBufferSize, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

    return QByteArray(reinterpret_cast<const char*>(outputBuffer), aOutputBufferSize);
}

QByteArray Compression::DecompressLZO(const QByteArray &aCompressedData) {
    lzokay::EResult error;

    // Ensure the input QByteArray is valid
    if (aCompressedData.isEmpty()) {
        qDebug() << "Input QByteArray is empty.";
        return QByteArray();
    }

    // Step 1: Cast QByteArray to uint8_t*
    const uint8_t *compressedData = reinterpret_cast<const uint8_t *>(aCompressedData.constData());
    std::size_t compressedSize = static_cast<std::size_t>(aCompressedData.size());

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

QByteArray Compression::CompressLZO(const QByteArray &aData) {
    lzokay::EResult error;

    // Check input validity
    if (aData.isEmpty()) {
        qDebug() << "Input QByteArray is empty.";
        return QByteArray();
    }

    // Step 1: Cast QByteArray to uint8_t*
    const uint8_t *uncompressedData = reinterpret_cast<const uint8_t *>(aData.constData());
    std::size_t uncompressedSize = static_cast<std::size_t>(aData.size());

    // Step 2: Allocate output buffer with sufficient size (compressBound-like estimation)
    std::size_t maxCompressedSize = uncompressedSize + uncompressedSize / 16 + 64 + 3; // Safe estimation
    std::unique_ptr<uint8_t[]> compressed(new uint8_t[maxCompressedSize]);

    // Step 3: Compress data
    std::size_t compressedSize = 0;
    error = lzokay::compress(
        uncompressedData, uncompressedSize,   // Input data
        compressed.get(), maxCompressedSize,  // Output buffer
        compressedSize                        // Actual compressed size
        );

    // Step 4: Handle compression errors
    if (error != lzokay::EResult::Success) {
        qDebug() << "Compression failed with error code:" << static_cast<int>(error);
        return QByteArray();
    }

    // Step 5: Return compressed data as QByteArray
    return QByteArray(reinterpret_cast<const char *>(compressed.get()), compressedSize);
}

QByteArray Compression::DecompressLZX(const QByteArray &compressedData, uint32_t windowBits)
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
