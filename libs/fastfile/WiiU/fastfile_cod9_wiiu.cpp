#include "fastfile_cod9_wiiu.h"
#include "zonefile_cod9_wiiu.h"
#include "encryption.h"

#include <QFile>
#include <QDebug>

FastFile_COD9_WiiU::FastFile_COD9_WiiU()
    : FastFile() {
    SetCompany(COMPANY_INFINITY_WARD);
    SetType(FILETYPE_FAST_FILE);
    SetSignage(SIGNAGE_UNSIGNED);
    SetMagic(0);
    SetVersion(0);
    SetGame("COD9");
    SetPlatform("WiiU");
}

FastFile_COD9_WiiU::FastFile_COD9_WiiU(const QByteArray& aData)
    : FastFile_COD9_WiiU() {
    if (!aData.isEmpty()) {
        Load(aData);
    }
}

FastFile_COD9_WiiU::FastFile_COD9_WiiU(const QString aFilePath)
    : FastFile_COD9_WiiU() {
    if (!aFilePath.isEmpty()) {
        Load(aFilePath);
    }
}

FastFile_COD9_WiiU::~FastFile_COD9_WiiU() {

}

QByteArray FastFile_COD9_WiiU::GetBinaryData() {
    return QByteArray();
}

bool FastFile_COD9_WiiU::Load(const QString aFilePath) {
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

bool FastFile_COD9_WiiU::Load(const QByteArray aData) {
    QByteArray decompressedData;

    // Create a QDataStream on the input data.
    QDataStream fastFileStream(aData);
    fastFileStream.setByteOrder(QDataStream::LittleEndian);

    // Parse header values.
    SetCompany(pParseFFCompany(&fastFileStream));
    SetType(pParseFFFileType(&fastFileStream));
    SetSignage(pParseFFSignage(&fastFileStream));
    SetMagic(pParseFFMagic(&fastFileStream));
    quint32 version = pParseFFVersion(&fastFileStream);
    SetVersion(version);
    SetPlatform(pCalculateFFPlatform(version));
    SetGame("COD9");

    // For COD7/COD9, use BigEndian.
    fastFileStream.setByteOrder(QDataStream::BigEndian);
    if (GetPlatform() == "PC") {
        fastFileStream.setByteOrder(QDataStream::LittleEndian);
    }

    // Select key based on game.
    QByteArray key;
    if (GetPlatform() == "360") {
        key = QByteArray::fromHex("0E50F49F412317096038665622DD091332A209BA0A05A00E1377CEDB0A3CB1D3");
    } else if (GetPlatform() == "PC") {
        key = QByteArray::fromHex("641D8A2FE31D3AA63622BBC9CE8587229D42B0F8ED9B924130BF88B65EDC50BE");
    }

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

    if (GetPlatform() == "360") {
        //decompressedData = Compressor::cod9_decryptFastFile(aData);
    } else if (GetPlatform() == "PC") {
        decompressedData = Encryption::decryptFastFile_BO2(aData);
    }

    // For COD9, write out the complete decompressed zone for testing.
    QFile testFile("exports/" + GetStem() + ".zone");
    if(testFile.open(QIODevice::WriteOnly)) {
        testFile.write(decompressedData);
        testFile.close();
    }

    // Load the zone file with the decompressed data (using an Xbox platform flag).
    ZoneFile_COD9_WiiU zoneFile;
    zoneFile.SetStem(GetStem());
    zoneFile.Load(decompressedData);
    SetZoneFile(std::make_shared<ZoneFile_COD9_WiiU>(zoneFile));

    return true;
}
