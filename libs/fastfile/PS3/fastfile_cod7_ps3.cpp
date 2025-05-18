#include "fastfile_cod7_ps3.h"
#include "zonefile_cod7_ps3.h"

#include "utils.h"
#include "compression.h"
#include "encryption.h"

#include <QFile>
#include <QDebug>

FastFile_COD7_PS3::FastFile_COD7_PS3()
    : FastFile() {
    SetCompany(COMPANY_INFINITY_WARD);
    SetType(FILETYPE_FAST_FILE);
    SetSignage(SIGNAGE_UNSIGNED);
    SetMagic(0);
    SetVersion(0);
    SetGame("COD7");
    SetPlatform("PS3");
}

FastFile_COD7_PS3::FastFile_COD7_PS3(const QByteArray& aData)
    : FastFile_COD7_PS3() {

    if (!aData.isEmpty()) {
        Load(aData);
    }
}

FastFile_COD7_PS3::FastFile_COD7_PS3(const QString aFilePath)
    : FastFile_COD7_PS3() {

    if (!aFilePath.isEmpty()) {
        Load(aFilePath);
    }
}

FastFile_COD7_PS3::~FastFile_COD7_PS3() {

}

QByteArray FastFile_COD7_PS3::GetBinaryData() {
    return QByteArray();
}

bool FastFile_COD7_PS3::Load(const QString aFilePath) {
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

bool FastFile_COD7_PS3::Load(const QByteArray aData) {
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
    SetGame("COD7");

    // Load the zone file with the decompressed data (using an Xbox platform flag).
    ZoneFile_COD7_PS3 zoneFile;
    zoneFile.SetStem(GetStem());

    // For COD7/COD9, use BigEndian.
    fastFileStream.setByteOrder(QDataStream::BigEndian);
    if (GetPlatform() == "PC") {
        fastFileStream.setByteOrder(QDataStream::LittleEndian);

        // Select key based on game.
        QByteArray key;
        fastFileStream.skipRawData(4);
        if (GetPlatform() == "360") {
            key = QByteArray::fromHex("1ac1d12d527c59b40eca619120ff8217ccff09cd16896f81b829c7f52793405d");
        } else if (GetPlatform() == "PS3") {
            key = QByteArray::fromHex("46D3F997F29C9ACE175B0DAE3AB8C0C1B8E423E2E3BF7E3C311EA35245BF193A");
            // or
            // key = QByteArray::fromHex("0C99B3DDB8D6D0845D1147E470F28A8BF2AE69A8A9F534767B54E9180FF55370");
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
    }

    SetZoneFile(std::make_shared<ZoneFile_COD7_PS3>(zoneFile));

    return true;
}
