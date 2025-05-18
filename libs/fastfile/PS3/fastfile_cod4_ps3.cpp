#include "fastfile_cod4_ps3.h"
#include "zonefile_cod4_ps3.h"

#include "utils.h"
#include "compression.h"
#include "statusbarmanager.h"

#include <QFile>
#include <QDebug>

FastFile_COD4_PS3::FastFile_COD4_PS3()
    : FastFile() {
    SetCompany(COMPANY_INFINITY_WARD);
    SetType(FILETYPE_FAST_FILE);
    SetSignage(SIGNAGE_UNSIGNED);
    SetMagic(0);
    SetVersion(0);
    SetGame("COD4");
    SetPlatform("PS3");
}

FastFile_COD4_PS3::FastFile_COD4_PS3(const QByteArray& aData)
    : FastFile_COD4_PS3() {

    if (!aData.isEmpty()) {
        Load(aData);
    }
}

FastFile_COD4_PS3::FastFile_COD4_PS3(const QString aFilePath)
    : FastFile_COD4_PS3() {

    if (!aFilePath.isEmpty()) {
        Load(aFilePath);
    }
}

FastFile_COD4_PS3::~FastFile_COD4_PS3() {

}

QByteArray FastFile_COD4_PS3::GetBinaryData() {
    return QByteArray();
}

bool FastFile_COD4_PS3::Load(const QString aFilePath) {
    StatusBarManager::instance().updateStatus("Loading COD5 Fast File w/path", 1000);

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

bool FastFile_COD4_PS3::Load(const QByteArray aData) {
    StatusBarManager::instance().updateStatus("Loading COD5 Fast File w/data", 1000);
    QByteArray decompressedData;

    // Create a QDataStream on the input data.
    QDataStream fastFileStream(aData);
    fastFileStream.setByteOrder(QDataStream::LittleEndian);

    // Parse header values.
    SetCompany(pParseFFCompany(&fastFileStream));
    SetType(pParseFFFileType(&fastFileStream));
    SetSignage(pParseFFSignage(&fastFileStream));
    SetMagic(pParseFFMagic(&fastFileStream));
    SetVersion(pParseFFVersion(&fastFileStream));

    int pos = 12;
    // Loop until EOF or invalid chunk
    while (pos <= aData.size()) {
        // Read 2-byte BIG-ENDIAN chunk size
        quint16 chunkSize;
        QDataStream chunkStream(aData.mid(pos, 2));
        chunkStream.setByteOrder(QDataStream::BigEndian);
        chunkStream >> chunkSize;

        pos += 2;

        if (chunkSize == 0 || pos + chunkSize > aData.size()) {
            qWarning() << "Invalid or incomplete chunk detected, stopping.";
            break;
        }

        const QByteArray compressedChunk = aData.mid(pos, chunkSize);

        decompressedData.append(Compression::DecompressDeflate(compressedChunk));

        pos += chunkSize;
    }

    Utils::ExportData(GetStem() + ".zone", decompressedData);

    ZoneFile_COD4_PS3 zoneFile;
    zoneFile.SetStem(GetStem());
    zoneFile.Load(decompressedData);
    SetZoneFile(std::make_shared<ZoneFile_COD4_PS3>(zoneFile));

    return true;
}
