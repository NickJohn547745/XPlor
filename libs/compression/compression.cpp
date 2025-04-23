#include "compression.h"
//#include "lzokay.h"

#define XBOXAPI __declspec(dllimport)
#include "xcompress.h"

#include <QLibrary>
#include <QDebug>
#include <QFile>
#include <QDataStream>

QByteArray Compression::CompressXMem(const QByteArray &data)
{
    XMEMCODEC_PARAMETERS_LZX lzxParams = {};
    lzxParams.Flags = 0;
    lzxParams.WindowSize = XCOMPRESS_LZX_BLOCK_SIZE;
    lzxParams.CompressionPartitionSize = XCOMPRESS_LZX_BLOCK_SIZE;

    XMEMCOMPRESSION_CONTEXT ctx = nullptr;
    if (FAILED(XMemCreateCompressionContext(XMEMCODEC_LZX, &lzxParams, 0, &ctx)) || !ctx)
        return QByteArray();

    SIZE_T estimatedSize = data.size() + XCOMPRESS_LZX_BLOCK_GROWTH_SIZE_MAX;
    QByteArray output(static_cast<int>(estimatedSize), 0);
    SIZE_T actualSize = estimatedSize;

    HRESULT hr = XMemCompress(ctx, output.data(), &actualSize, data.constData(), data.size());
    XMemDestroyCompressionContext(ctx);

    if (FAILED(hr))
        return QByteArray();

    output.resize(static_cast<int>(actualSize));
    return output;
}

QByteArray Compression::DecompressXMem(const QByteArray &data)
{
    XMEMCODEC_PARAMETERS_LZX lzxParams = {};
    lzxParams.Flags = 0;
    lzxParams.WindowSize = XCOMPRESS_LZX_BLOCK_SIZE;
    lzxParams.CompressionPartitionSize = XCOMPRESS_LZX_BLOCK_SIZE;

    XMEMDECOMPRESSION_CONTEXT ctx = nullptr;
    if (FAILED(XMemCreateDecompressionContext(XMEMCODEC_LZX, &lzxParams, 0, &ctx)) || !ctx)
        return QByteArray();

    QByteArray output(data.size(), 0);
    SIZE_T actualSize = data.size();

    HRESULT hr = XMemDecompress(ctx, output.data(), &actualSize, data.constData(), data.size());
    XMemDestroyDecompressionContext(ctx);

    if (FAILED(hr))
        return QByteArray();

    output.resize(static_cast<int>(actualSize));
    return output;
}

quint32 Compression::CalculateAdler32Checksum(const QByteArray &data) {
    // Start with the initial value for Adler-32
    quint32 adler = adler32(0L, Z_NULL, 0);

    // Calculate Adler-32 checksum
    adler = adler32(adler, reinterpret_cast<const Bytef *>(data.constData()), data.size());

    return adler;
}

QByteArray Compression::DecompressZLIB(const QByteArray &aCompressedData) {
    if (aCompressedData.isEmpty()) {
        return {};
    }

    z_stream strm{};
    strm.zalloc = Z_NULL;
    strm.zfree = Z_NULL;
    strm.opaque = Z_NULL;
    strm.avail_in = static_cast<uInt>(aCompressedData.size());
    strm.next_in = reinterpret_cast<Bytef*>(const_cast<char*>(aCompressedData.data()));

    if (inflateInit2(&strm, MAX_WBITS) != Z_OK) {
        qWarning() << "inflateInit2 failed";
        return {};
    }

    QByteArray decompressed;
    QByteArray buffer(fmin(strm.avail_in * 2, 4096), Qt::Uninitialized);

    int ret;
    do {
        strm.next_out = reinterpret_cast<Bytef*>(buffer.data());
        strm.avail_out = buffer.size();

        ret = inflate(&strm, Z_NO_FLUSH);

        if (strm.avail_out < buffer.size()) {  // Data has been written to the buffer
            decompressed.append(buffer.constData(), buffer.size() - strm.avail_out);
        }

        if (ret == Z_STREAM_END) {
            break;  // Proper end of the data stream
        }

        if (ret == Z_BUF_ERROR && strm.avail_out == 0) {
            // Buffer was completely used, resize it
            int newSize = buffer.size() * 2;  // Double the buffer size
            buffer.resize(newSize);
        } else if (ret != Z_OK) {
            qWarning() << "Zlib error:" << zError(ret);
            inflateEnd(&strm);
            return {};  // Return on other errors
        }
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
    Q_UNUSED(aDictionary);

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
