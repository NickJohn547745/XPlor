#include "fastfile_cod6_pc.h"
#include "zonefile_cod6_pc.h"

#include "utils.h"
#include "compression.h"
#include "statusbarmanager.h"

#include <QFile>
#include <QDebug>

FastFile_COD6_PC::FastFile_COD6_PC()
    : FastFile() {
    SetCompany(COMPANY_INFINITY_WARD);
    SetType(FILETYPE_FAST_FILE);
    SetSignage(SIGNAGE_UNSIGNED);
    SetMagic(0);
    SetVersion(0);
    SetPlatform("PC");
    SetGame("COD6");
}

FastFile_COD6_PC::FastFile_COD6_PC(const QByteArray& aData)
    : FastFile_COD6_PC() {

    if (!aData.isEmpty()) {
        Load(aData);
    }
}

FastFile_COD6_PC::FastFile_COD6_PC(const QString aFilePath)
    : FastFile_COD6_PC() {

    if (!aFilePath.isEmpty()) {
        Load(aFilePath);
    }
}

FastFile_COD6_PC::~FastFile_COD6_PC() {

}

QByteArray FastFile_COD6_PC::GetBinaryData() {
    return QByteArray();
}

bool FastFile_COD6_PC::Load(const QString aFilePath) {
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

bool FastFile_COD6_PC::Load(const QByteArray aData) {
    StatusBarManager::instance().updateStatus("Loading COD5 Fast File w/data", 1000);
    QByteArray decompressedData;

    // Create a QDataStream on the input data.
    QDataStream fastFileStream(aData);
    fastFileStream.setByteOrder(QDataStream::LittleEndian);

    // For COD5, simply decompress from offset 12.
    decompressedData = Compression::DecompressZLIB(aData.mid(12));

    Utils::ExportData(GetStem() + ".zone", decompressedData);

    ZoneFile_COD6_PC zoneFile;
    zoneFile.SetStem(GetStem());
    zoneFile.Load(decompressedData);
    SetZoneFile(std::make_shared<ZoneFile_COD6_PC>(zoneFile));

    return true;
}
