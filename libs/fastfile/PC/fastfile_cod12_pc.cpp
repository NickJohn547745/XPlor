#include "fastfile_cod12_pc.h"
#include "zonefile_cod12_pc.h"

#include "utils.h"
#include "compression.h"
#include "encryption.h"

#include <QFile>
#include <QDebug>

FastFile_COD12_PC::FastFile_COD12_PC()
    : FastFile() {
    SetCompany(COMPANY_INFINITY_WARD);
    SetType(FILETYPE_FAST_FILE);
    SetSignage(SIGNAGE_UNSIGNED);
    SetMagic(0);
    SetVersion(0);
    SetGame("COD12");
    SetPlatform("PC");
}

FastFile_COD12_PC::FastFile_COD12_PC(const QByteArray& aData)
    : FastFile_COD12_PC() {

    if (!aData.isEmpty()) {
        Load(aData);
    }
}

FastFile_COD12_PC::FastFile_COD12_PC(const QString aFilePath)
    : FastFile_COD12_PC() {

    if (!aFilePath.isEmpty()) {
        Load(aFilePath);
    }
}

FastFile_COD12_PC::~FastFile_COD12_PC() {

}

QByteArray FastFile_COD12_PC::GetBinaryData() {
    return QByteArray();
}

bool FastFile_COD12_PC::Load(const QString aFilePath) {
    if (aFilePath.isEmpty()) {
        return false;
    }

    // Check fastfile can be read
    QFile *file = new QFile(aFilePath);
    if (!file->open(QIODevice::ReadOnly)) {
        qDebug() << QString("Error: Failed to open FastFile: %1!").arg(aFilePath);
        return false;
    }

    // Decompress fastfile and close
    const QString fastFileStem = aFilePath.section("/", -1, -1).split('.').first();
    SetStem(fastFileStem);
    if (!Load(file->readAll())) {
        qDebug() << "Error: Failed to load fastfile: " << fastFileStem;
        return false;
    }

    file->close();

    // Open zone file after decompressing ff and writing
    return true;
}

bool FastFile_COD12_PC::Load(const QByteArray aData) {
    QByteArray decompressedData;

    // Create a QDataStream on the input data.
    QDataStream fastFileStream(aData);
    fastFileStream.setByteOrder(QDataStream::LittleEndian);

    // Load the zone file with the decompressed data (using an Xbox platform flag).
    ZoneFile_COD12_PC zoneFile;
    zoneFile.SetStem(GetStem());

    // Skip header magic
    fastFileStream.skipRawData(8);

    quint32 version;
    fastFileStream >> version;

    quint8 unknownFlag, compressionFlag, platformFlag, encryptionFlag;
    fastFileStream >> unknownFlag >> compressionFlag >> platformFlag >> encryptionFlag;

    if (compressionFlag != 1) {
        qDebug() << "Invalid fastfile compression: " << compressionFlag;
        return false;
    } else if (platformFlag != 0) {
        qDebug() << "Invalid platform: " << platformFlag;
        return false;
    } else if (encryptionFlag != 0) {
        qDebug() << "Decryption not supported yet!";
        return false;
    }

    fastFileStream.skipRawData(128);

    quint64 size;
    fastFileStream >> size;

    fastFileStream.skipRawData(432);

    int consumed = 0;
    while(consumed < size)
    {
        // Read Block Header
        quint32 compressedSize, decompressedSize, blockSize, blockPosition;
        fastFileStream >> compressedSize >> decompressedSize >> blockSize >> blockPosition;

        // Validate the block position, it should match
        if(blockPosition != fastFileStream.device()->pos() - 16)
        {
            qDebug() << "Block Position does not match Stream Position.";
            return false;
        }

        // Check for padding blocks
        if(decompressedSize == 0)
        {
            fastFileStream.device()->read((((fastFileStream.device()->pos()) + ((0x800000) - 1)) & ~((0x800000) - 1)) - fastFileStream.device()->pos());
            continue;
        }

        fastFileStream.device()->read(2);

        QByteArray compressedData(compressedSize - 2, Qt::Uninitialized);
        qDebug() << "Data position: " << fastFileStream.device()->pos() << " - Size: " << compressedSize;
        fastFileStream.readRawData(compressedData.data(), compressedSize - 2);
        decompressedData.append(Compression::DecompressDeflate(compressedData));

        consumed += decompressedSize;

        // Sinze Fast Files are aligns, we must skip the full block
        fastFileStream.device()->seek(blockPosition + 16 + blockSize);
    }

    Utils::ExportData(GetStem() + ".zone", decompressedData);

    zoneFile.Load(decompressedData);

    SetZoneFile(std::make_shared<ZoneFile_COD12_PC>(zoneFile));

    return true;
}
