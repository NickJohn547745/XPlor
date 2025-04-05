#ifndef COMPRESSION_H
#define COMPRESSION_H

#include "QtZlib/zlib.h"

#include <stddef.h>
#include <QByteArray>
#include <QDebug>
#include <QDataStream>
#include <QVector>
#include <QCryptographicHash>
#include <QFile>

enum OodleFormat {
    LZH = 0,
    LZHLW = 1,
    LZNIB = 2,
    FormatNone = 3,
    LZB16 = 4,
    LZBLW = 5,
    LZA = 6,
    LZNA = 7,
    Kraken = 8,
    Mermaid = 9,
    BitKnit = 10,
    Selkie = 11,
    Hydra = 12,
    Leviathan = 13
};

enum OodleCompressionLevel {
    LevelNone = 0,
    SuperFast = 1,
    VeryFast = 2,
    Fast = 3,
    Normal = 4,
    Optimal1 = 5,
    Optimal2 = 6,
    Optimal3 = 7,
    Optimal4 = 8,
    Optimal5 = 9
};

typedef int (*OodleLZ_CompressFunc)(OodleFormat Format, std::byte *Buffer, long BufferSize, std::byte *OutputBuffer, OodleCompressionLevel Level, uint a, uint b, uint c);
typedef int (*OodleLZ_DecompressFunc)(std::byte* Buffer, long BufferSize, std::byte* OutputBuffer, long OutputBufferSize, uint a, uint b, uint c, uint d, uint e, uint f, uint g, uint h, uint i, int ThreadModule);

class Compression {
public:
    static QByteArray DecompressZLIB(const QByteArray &aCompressedData);
    static QByteArray CompressZLIB(const QByteArray &aData);
    static QByteArray CompressZLIBWithSettings(const QByteArray &aData,
                                               int aCompressionLevel = Z_BEST_COMPRESSION,
                                               int aWindowBits = MAX_WBITS,
                                               int aMemLevel = 8,
                                               int aStrategy = Z_DEFAULT_STRATEGY,
                                               const QByteArray &aDictionary = {});

    static QByteArray DecompressDeflate(const QByteArray &aCompressedData);
    static QByteArray CompressDeflate(const QByteArray &aData);
    static QByteArray CompressDeflateWithSettings(const QByteArray &aData,
                                               int aCompressionLevel = Z_BEST_COMPRESSION,
                                               int aWindowBits = MAX_WBITS,
                                               int aMemLevel = 8,
                                               int aStrategy = Z_DEFAULT_STRATEGY,
                                               const QByteArray &aDictionary = {});

    static QByteArray DecompressOodle(const QByteArray &aCompressedData, quint32 aDecompressedSize);
    static QByteArray CompressOodle(const QByteArray &aData);

    static QByteArray DecompressLZO(const QByteArray& aCompressedData);
    static QByteArray CompressLZO(const QByteArray& aData);

    static QByteArray DecompressLZX(const QByteArray &compressedData, uint32_t windowBits = 15);

private:
    static quint32 pGetOodleCompressedBounds(quint32 aBufferSize);
    static QByteArray pCompressOodle(QByteArray aBuffer, quint32 aBufferSize, quint32 aOutputBufferSize,
                                     OodleFormat aformat, OodleCompressionLevel alevel);
    static QByteArray pDecompressOodle(QByteArray aBuffer, quint32 aBufferSize, quint32 aOutputBufferSize);
};


#endif // COMPRESSION_H
