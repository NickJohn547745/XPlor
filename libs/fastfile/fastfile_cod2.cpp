#include "fastfile_cod2.h"

#include "utils.h"
#include "compressor.h"
#include "zonefile_cod2.h"

#include <QFile>
#include <QDebug>

FastFile_COD2::FastFile_COD2() {

}

FastFile_COD2::~FastFile_COD2() {

}

bool FastFile_COD2::Load(const QString aFilePath) {
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
    qDebug() << "fastFileStem: " << fastFileStem;
    SetStem(fastFileStem);
    if (!Load(file->readAll())) {
        qDebug() << "Error: Failed to load fastfile: " << fastFileStem;
        return false;
    }

    file->close();

    // Open zone file after decompressing ff and writing
    return true;
}

bool FastFile_COD2::Load(const QByteArray aData) {
    // Create a QDataStream on the input data.
    QDataStream fastFileStream(aData);
    fastFileStream.setByteOrder(QDataStream::LittleEndian);

    // Parse header values.
    SetCompany(COMPANY_INFINITY_WARD);
    SetType(FILETYPE_FAST_FILE);
    SetSignage(SIGNAGE_UNSIGNED);
    SetMagic(0);
    SetVersion(0);
    SetPlatform("360");
    SetGame("COD2");

    Utils::ReadUntilHex(&fastFileStream, "78");
    QByteArray compressedData = aData.mid(fastFileStream.device()->pos());
    QByteArray decompressedData = Compressor::DecompressZLIB(compressedData);

    QDir exportsDir(QDir::currentPath());
    exportsDir.mkdir("exports");

    QFile testFile("exports/" + GetStem() + ".zone");
    if(testFile.open(QIODevice::WriteOnly)) {
        testFile.write(decompressedData);
        testFile.close();
    }

    // Load the zone file with the decompressed data (using an Xbox platform flag).
    ZoneFile_COD2 zoneFile;
    zoneFile.Load(decompressedData, GetStem() + ".zone", FF_PLATFORM_XBOX);
    SetZoneFile(std::make_shared<ZoneFile_COD2>(zoneFile));

    return true;
}
