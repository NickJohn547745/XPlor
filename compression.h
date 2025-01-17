#ifndef COMPRESSION_H
#define COMPRESSION_H

#include "utils.h"
#include "QtZlib/zlib.h"

#include <QByteArray>
#include <QDebug>

class Compressor {
public:
    static QByteArray DecompressZLIB(QByteArray compressedData) {
        QByteArray decompressedData;
        uLongf decompressedSize = compressedData.size() * 4;
        decompressedData.resize(static_cast<int>(decompressedSize));

        Bytef *destination = reinterpret_cast<Bytef*>(decompressedData.data());
        uLongf *destLen = &decompressedSize;
        const Bytef *source = reinterpret_cast<const Bytef*>(compressedData.data());
        uLong sourceLen = compressedData.size();

        int result = uncompress(destination, destLen, source, sourceLen);

        if (result == Z_OK) {
            decompressedData.resize(static_cast<int>(decompressedSize));
        } else {
            decompressedData.clear();
            qDebug() << QString("In DecompressZLIB: %1").arg(Utils::ZLibErrorToString(result)).toLatin1();
        }
        return decompressedData;
    }
};

#endif // COMPRESSION_H
