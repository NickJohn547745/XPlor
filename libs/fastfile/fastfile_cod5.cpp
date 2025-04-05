#include "fastfile_cod5.h"
#include "zonefile_cod5.h"

#include "utils.h"
#include "compressor.h"
#include "statusbarmanager.h"

#include <QFile>
#include <QDebug>

FastFile_COD5::FastFile_COD5() {

}

FastFile_COD5::~FastFile_COD5() {

}

bool FastFile_COD5::Load(const QString aFilePath) {
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

bool FastFile_COD5::Load(const QByteArray aData) {
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
    quint32 version = pParseFFVersion(&fastFileStream);
    SetVersion(version);
    const QString platformStr = pCalculateFFPlatform(version);
    SetPlatform(platformStr);
    SetGame("COD5");

    // For COD5, simply decompress from offset 12.
    decompressedData = Compressor::DecompressZLIB(aData.mid(12));

    Utils::ExportData(GetStem() + ".zone", decompressedData);

    FF_PLATFORM platform = FF_PLATFORM_NONE;
    if (platformStr == "PC") {
        platform = FF_PLATFORM_PC;
    } else if (platformStr == "360") {
        platform = FF_PLATFORM_XBOX;
    }

    ZoneFile_COD5 zoneFile;
    zoneFile.SetStem(GetStem());
    //zoneFile.Load(decompressedData, GetStem() + ".zone", platform);
    SetZoneFile(std::make_shared<ZoneFile_COD5>(zoneFile));

    return true;
}
