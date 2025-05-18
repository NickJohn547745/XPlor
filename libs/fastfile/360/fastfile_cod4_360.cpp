#include "fastfile_cod4_360.h"
#include "zonefile_cod4_360.h"

#include "utils.h"
#include "compression.h"
#include "statusbarmanager.h"

#include <QFile>
#include <QDebug>

FastFile_COD4_360::FastFile_COD4_360()
    : FastFile() {
    SetCompany(COMPANY_INFINITY_WARD);
    SetType(FILETYPE_FAST_FILE);
    SetSignage(SIGNAGE_UNSIGNED);
    SetMagic(0);
    SetVersion(0);
    SetPlatform("360");
    SetGame("COD4");
}

FastFile_COD4_360::FastFile_COD4_360(const QByteArray& aData)
    : FastFile_COD4_360() {

    if (!aData.isEmpty()) {
        Load(aData);
    }
}

FastFile_COD4_360::FastFile_COD4_360(const QString aFilePath)
    : FastFile_COD4_360() {

    if (!aFilePath.isEmpty()) {
        Load(aFilePath);
    }
}

FastFile_COD4_360::~FastFile_COD4_360() {

}

QByteArray FastFile_COD4_360::GetBinaryData() {
    return QByteArray();
}

bool FastFile_COD4_360::Load(const QString aFilePath) {
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
    QString fastFileStem = aFilePath.split('/').last().replace(".ff", "");
    SetStem(fastFileStem);
    if (!Load(file->readAll())) {
        qDebug() << "Error: Failed to load fastfile: " << fastFileStem;
        return false;
    }

    file->close();

    // Open zone file after decompressing ff and writing
    return true;
}

bool FastFile_COD4_360::Load(const QByteArray aData) {
    StatusBarManager::instance().updateStatus("Loading COD5 Fast File w/data", 1000);
    QByteArray decompressedData;

    // Create a QDataStream on the input data.
    QDataStream fastFileStream(aData);
    fastFileStream.setByteOrder(QDataStream::LittleEndian);

    // For COD5, simply decompress from offset 12.
    decompressedData = Compression::DecompressZLIB(aData.mid(12));

    Utils::ExportData(GetStem() + ".zone", decompressedData);

    ZoneFile_COD4_360 zoneFile;
    zoneFile.SetStem(GetStem());
    zoneFile.Load(decompressedData);
    SetZoneFile(std::make_shared<ZoneFile_COD4_360>(zoneFile));

    return true;
}
