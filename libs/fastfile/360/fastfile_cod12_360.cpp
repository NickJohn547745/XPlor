#include "fastfile_cod12_360.h"
#include "zonefile_cod12_360.h"

#include "utils.h"
#include "compression.h"
#include "encryption.h"

#include <QFile>
#include <QDebug>

FastFile_COD12_360::FastFile_COD12_360()
    : FastFile() {
    SetCompany(COMPANY_INFINITY_WARD);
    SetType(FILETYPE_FAST_FILE);
    SetSignage(SIGNAGE_UNSIGNED);
    SetMagic(0);
    SetVersion(0);
    SetGame("COD12");
    SetPlatform("PC");
}

FastFile_COD12_360::FastFile_COD12_360(const QByteArray& aData)
    : FastFile_COD12_360() {

    if (!aData.isEmpty()) {
        Load(aData);
    }
}

FastFile_COD12_360::FastFile_COD12_360(const QString aFilePath)
    : FastFile_COD12_360() {
    if (!aFilePath.isEmpty()) {
        Load(aFilePath);
    }
}

FastFile_COD12_360::~FastFile_COD12_360() {

}

QByteArray FastFile_COD12_360::GetBinaryData() {
    return QByteArray();
}

bool FastFile_COD12_360::Load(const QString aFilePath) {
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

bool FastFile_COD12_360::Load(const QByteArray aData) {
    QByteArray decompressedData;

    // Prepare data stream for parsing
    QDataStream fastFileStream(aData);
    fastFileStream.setByteOrder(QDataStream::LittleEndian);

    // Verify magic header
    QByteArray fileMagic(8, Qt::Uninitialized);
    fastFileStream.readRawData(fileMagic.data(), 8);
    if (fileMagic != "TAff0000") {
        qWarning() << "Invalid fast file magic for COD12!";
        return false;
    }

    // Skip: File size (4 bytes), flags/version (4 bytes), unknown (8 bytes), build tag (32 bytes), RSA signature (256 bytes)
    fastFileStream.skipRawData(4 + 4 + 8 + 32 + 256); // total 304 bytes skipped so far + 8 bytes magic = 312 bytes at correct position.

    // Correctly positioned at 0x138
    QByteArray encryptedData = aData.mid(0x138);
    decompressedData = Encryption::decryptFastFile_BO3(encryptedData);

    // Output for verification/testing
    Utils::ExportData(GetStem() + ".zone", decompressedData);

    // Load the zone file with decompressed data
    ZoneFile_COD12_360 zoneFile;
    zoneFile.SetStem(GetStem());
    if (!zoneFile.Load(decompressedData)) {
        qWarning() << "Failed to load ZoneFile!";
        return false;
    }

    SetZoneFile(std::make_shared<ZoneFile_COD12_360>(zoneFile));

    return true;
}
