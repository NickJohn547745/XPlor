#include "fastfile_cod2_360.h"

#include "utils.h"
#include "compression.h"
#include "zonefile_cod2_360.h"

#include <QFile>
#include <QDebug>

FastFile_COD2_360::FastFile_COD2_360()
    : FastFile() {
    SetCompany(COMPANY_INFINITY_WARD);
    SetType(FILETYPE_FAST_FILE);
    SetSignage(SIGNAGE_UNSIGNED);
    SetMagic(0);
    SetVersion(0);
    SetPlatform("360");
    SetGame("COD2");
}

FastFile_COD2_360::FastFile_COD2_360(const QByteArray& aData)
    : FastFile_COD2_360() {

    if (!aData.isEmpty()) {
        Load(aData);
    }
}

FastFile_COD2_360::FastFile_COD2_360(const QString aFilePath)
    : FastFile_COD2_360() {

    if (!aFilePath.isEmpty()) {
        Load(aFilePath);
    }
}

FastFile_COD2_360::~FastFile_COD2_360() {

}

QByteArray FastFile_COD2_360::GetBinaryData() {
    return QByteArray();
}

bool FastFile_COD2_360::Load(const QString aFilePath) {
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
        qDebug() << "Error: Failed to load fastfile: " << fastFileStem;
        return false;
    }

    file->close();

    // Open zone file after decompressing ff and writing
    return true;
}

bool FastFile_COD2_360::Load(const QByteArray aData) {
    // Create a QDataStream on the input data.
    QDataStream fastFileStream(aData);
    fastFileStream.setByteOrder(QDataStream::LittleEndian);

    Utils::ReadUntilHex(&fastFileStream, "78");
    QByteArray compressedData = aData.mid(fastFileStream.device()->pos());
    QByteArray decompressedData = Compression::DecompressZLIB(compressedData);

    Utils::ExportData(GetStem() + ".zone", decompressedData);

    // Load the zone file with the decompressed data (using an Xbox platform flag).
    ZoneFile_COD2_360 zoneFile;
    zoneFile.SetStem(GetStem());
    zoneFile.Load(decompressedData);
    SetZoneFile(std::make_shared<ZoneFile_COD2_360>(zoneFile));

    return true;
}
