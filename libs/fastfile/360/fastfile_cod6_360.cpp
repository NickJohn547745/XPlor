#include "fastfile_cod6_360.h"
#include "zonefile_cod6_360.h"

#include "compression.h"
#include "encryption.h"

#include <QFile>
#include <QDebug>

FastFile_COD6_360::FastFile_COD6_360()
    : FastFile() {
    SetCompany(COMPANY_INFINITY_WARD);
    SetType(FILETYPE_FAST_FILE);
    SetSignage(SIGNAGE_UNSIGNED);
    SetMagic(0);
    SetVersion(0);
    SetPlatform("360");
    SetGame("COD6");
}

FastFile_COD6_360::FastFile_COD6_360(const QByteArray& aData)
    : FastFile_COD6_360() {

    if (!aData.isEmpty()) {
        Load(aData);
    }
}

FastFile_COD6_360::FastFile_COD6_360(const QString aFilePath)
    : FastFile_COD6_360() {

    if (!aFilePath.isEmpty()) {
        Load(aFilePath);
    }
}

FastFile_COD6_360::~FastFile_COD6_360() {

}

QByteArray FastFile_COD6_360::GetBinaryData() {
    return QByteArray();
}

bool FastFile_COD6_360::Load(const QString aFilePath) {
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
    const QString fastFileStem = aFilePath.section("/", -1, -1);
    SetStem(fastFileStem);
    if (!Load(file->readAll())) {
        qDebug() << "Error: Failed to load fastfile: " << fastFileStem;
        return false;
    }

    file->close();

    // Open zone file after decompressing ff and writing
    return true;
}

bool FastFile_COD6_360::Load(const QByteArray aData) {
    QByteArray decompressedData;

    // Create a QDataStream on the input data.
    QDataStream fastFileStream(aData);

    // Load the zone file with the decompressed data (using an Xbox platform flag).
    ZoneFile_COD6_360 zoneFile;
    zoneFile.SetStem(GetStem());

    // For COD7/COD9, use BigEndian.
    fastFileStream.setByteOrder(QDataStream::BigEndian);

    // Select key based on game.
    QByteArray key = QByteArray::fromHex("1ac1d12d527c59b40eca619120ff8217ccff09cd16896f81b829c7f52793405d");
    fastFileStream.skipRawData(4);

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

    // Build the IV table from the fileName.
    QByteArray ivTable = Encryption::InitIVTable(fileName);

    // Skip the RSA signature (256 bytes).
    QByteArray rsaSignature(256, Qt::Uninitialized);
    fastFileStream.readRawData(rsaSignature.data(), 256);

    // Now the stream should be positioned at 0x13C, where sections begin.
    int sectionIndex = 0;
    while (true) {
        qint32 sectionSize = 0;
        fastFileStream >> sectionSize;
        qDebug() << "Section index:" << sectionIndex << "Size:" << sectionSize
                 << "Pos:" << fastFileStream.device()->pos();
        if (sectionSize == 0)
            break;

        // Read the section data.
        QByteArray sectionData;
        sectionData.resize(sectionSize);
        fastFileStream.readRawData(sectionData.data(), sectionSize);

        // Compute the IV for this section.
        QByteArray iv = Encryption::GetIV(ivTable, sectionIndex);

        // Decrypt the section using Salsa20.
        QByteArray decData = Encryption::salsa20DecryptSection(sectionData, key, iv);

        // Compute SHA1 hash of the decrypted data.
        QByteArray sectionHash = QCryptographicHash::hash(decData, QCryptographicHash::Sha1);

        // Update the IV table based on the section hash.
        Encryption::UpdateIVTable(ivTable, sectionIndex, sectionHash);

        // Build a compressed data buffer by prepending the two-byte zlib header.
        QByteArray compressedData;
        compressedData.append(char(0x78));
        compressedData.append(char(0x01));
        compressedData.append(decData);

        decompressedData.append(Compression::DecompressZLIB(compressedData));

        sectionIndex++;
    }

    zoneFile.Load(decompressedData);

    SetZoneFile(std::make_shared<ZoneFile_COD6_360>(zoneFile));

    return true;
}
