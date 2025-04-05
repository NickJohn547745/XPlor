#ifndef COMPRESSOR_H
#define COMPRESSOR_H

#include "QtZlib/zlib.h"
#include "lzokay.hpp"
#include "statusbarmanager.h"

#include <stdint.h>
#include <stddef.h>
#include <QByteArray>
#include <QDebug>
#include <QDataStream>
#include <QVector>
#include <QCryptographicHash>
#include <QFile>

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

        z_stream strm;
        memset(&strm, 0, sizeof(strm));
        strm.next_in = reinterpret_cast<Bytef*>(const_cast<char*>(compressedData.data()));
        strm.avail_in = static_cast<uInt>(compressedData.size());

        int ret = inflateInit(&strm);
        if (ret != Z_OK) {
            qWarning() << "inflateInit failed:" << zError(ret);
            return QByteArray();
        }

        QByteArray outArray;
        char buffer[4096];

        int compressedBytesConsumed = 0;
        int index = 0;
        int totalCompressedSize = compressedData.size();  // n in x/n progress

        do {
            strm.next_out = reinterpret_cast<Bytef*>(buffer);
            strm.avail_out = sizeof(buffer);

            int compressedBefore = strm.avail_in; // Track before calling inflate
            ret = inflate(&strm, Z_NO_FLUSH);
            int compressedAfter = strm.avail_in;  // Track after calling inflate

            if (ret == Z_BUF_ERROR && strm.avail_in == 0) {
                break;
            }
            if (ret != Z_OK && ret != Z_STREAM_END) {
                qWarning() << "Error: ZLib inflate failed:" << zError(ret);
                inflateEnd(&strm);
                return QByteArray();
            }

            int bytesProduced = sizeof(buffer) - strm.avail_out;
            int bytesConsumed = compressedBefore - compressedAfter;  // Track consumed compressed bytes
            compressedBytesConsumed += bytesConsumed;

            if (bytesProduced > 0) {
                outArray.append(buffer, bytesProduced);

                index++;

                StatusBarManager::instance().updateProgressStatus(
                    QString("Processing Decompressing ZLib Data (%1/%2 bytes)").arg(compressedBytesConsumed).arg(totalCompressedSize),
                    compressedBytesConsumed, totalCompressedSize);
            }

        } while (ret != Z_STREAM_END);

        StatusBarManager::instance().updateStatus("Finished decompression!");

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
};


#endif // COMPRESSOR_H
