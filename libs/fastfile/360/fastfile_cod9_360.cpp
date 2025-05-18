#include "fastfile_cod9_360.h"
#include "zonefile_cod9_360.h"
#include "encryption.h"

#include <QFile>
#include <QDebug>

FastFile_COD9_360::FastFile_COD9_360()
    : FastFile() {
    SetCompany(COMPANY_INFINITY_WARD);
    SetType(FILETYPE_FAST_FILE);
    SetSignage(SIGNAGE_UNSIGNED);
    SetMagic(0);
    SetVersion(0);
    SetPlatform("360");
    SetGame("COD9");
}

FastFile_COD9_360::FastFile_COD9_360(const QByteArray& aData)
    : FastFile_COD9_360() {

    if (!aData.isEmpty()) {
        Load(aData);
    }
}

FastFile_COD9_360::FastFile_COD9_360(const QString aFilePath)
    : FastFile_COD9_360() {

    if (!aFilePath.isEmpty()) {
        Load(aFilePath);
    }
}

FastFile_COD9_360::~FastFile_COD9_360() {

}

QByteArray FastFile_COD9_360::GetBinaryData() {
    return QByteArray();
}

bool FastFile_COD9_360::Load(const QString aFilePath) {
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
    const QString fastFileStem = aFilePath.section("/", -1, -1).section(".", 0, 0);
    SetStem(fastFileStem);
    if (!Load(file->readAll())) {
        qDebug() << "Error: Failed to load fastfile: " << fastFileStem + ".ff";
        return false;
    }

    file->close();

    // Open zone file after decompressing ff and writing
    return true;
}

bool FastFile_COD9_360::Load(const QByteArray aData) {
    QByteArray decompressedData;

    // Create a QDataStream on the input data.
    QDataStream fastFileStream(aData);
    fastFileStream.setByteOrder(QDataStream::LittleEndian);

    // For COD7/COD9, use BigEndian.
    fastFileStream.setByteOrder(QDataStream::BigEndian);

    // Select key based on game.
    QByteArray key = QByteArray::fromHex("0E50F49F412317096038665622DD091332A209BA0A05A00E1377CEDB0A3CB1D3");

    // Read the 8-byte magic.
    QByteArray fileMagic(8, Qt::Uninitialized);
    fastFileStream.readRawData(fileMagic.data(), 8);
    if (fileMagic != "PHEEBs71") {
        qWarning() << "Invalid fast file magic!";
        return false;
    }
    fastFileStream.skipRawData(4);

    // Read IV table name (32 bytes).
    QByteArray fileName(32, Qt::Uninitialized);
    fastFileStream.readRawData(fileName.data(), 32);

    // Skip the RSA signature (256 bytes).
    QByteArray rsaSignature(256, Qt::Uninitialized);
    fastFileStream.readRawData(rsaSignature.data(), 256);

    decompressedData = Encryption::decryptFastFile_BO2(aData);

    // For COD9, write out the complete decompressed zone for testing.
    QFile testFile("exports/" + GetStem() + ".zone");
    if(testFile.open(QIODevice::WriteOnly)) {
        testFile.write(decompressedData);
        testFile.close();
    }

    // Load the zone file with the decompressed data (using an Xbox platform flag).
    ZoneFile_COD9_360 zoneFile;
    zoneFile.SetStem(GetStem());
    zoneFile.Load(decompressedData);
    SetZoneFile(std::make_shared<ZoneFile_COD9_360>(zoneFile));

    return true;
}
