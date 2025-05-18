#include "fastfile_cod7_wii.h"
#include "zonefile_cod7_wii.h"

#include "utils.h"
#include "compression.h"

#include <QFile>
#include <QDebug>

FastFile_COD7_Wii::FastFile_COD7_Wii()
    : FastFile() {
    SetCompany(COMPANY_INFINITY_WARD);
    SetType(FILETYPE_FAST_FILE);
    SetSignage(SIGNAGE_UNSIGNED);
    SetMagic(0);
    SetVersion(0);
    SetGame("COD7");
    SetPlatform("Wii");
}

FastFile_COD7_Wii::FastFile_COD7_Wii(const QByteArray& aData)
    : FastFile_COD7_Wii() {
    if (!aData.isEmpty()) {
        Load(aData);
    }
}

FastFile_COD7_Wii::FastFile_COD7_Wii(const QString aFilePath)
    : FastFile_COD7_Wii() {
    if (!aFilePath.isEmpty()) {
        Load(aFilePath);
    }
}

FastFile_COD7_Wii::~FastFile_COD7_Wii() {

}

QByteArray FastFile_COD7_Wii::GetBinaryData() {
    return QByteArray();
}

bool FastFile_COD7_Wii::Load(const QString aFilePath) {
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

bool FastFile_COD7_Wii::Load(const QByteArray aData) {
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
    ZoneFile_COD7_Wii zoneFile;
    zoneFile.SetStem(GetStem());

    // For COD7/COD9, use BigEndian.
    fastFileStream.setByteOrder(QDataStream::BigEndian);

    // For COD7, simply decompress from offset 12.
    decompressedData = Compression::DecompressZLIB(aData.mid(12));

    Utils::ExportData(GetStem() + ".zone", decompressedData);

    QDir workingDir = QDir::currentPath();
    workingDir.mkdir("exports");

    QFile outputFile("exports/" + GetStem() + ".zone");
    if (!outputFile.open(QIODevice::WriteOnly)) {
        qDebug() << "Failed to extract IPAK file.";
    }
    qDebug() << "           - File Name: " << outputFile.fileName();
    outputFile.write(decompressedData);
    outputFile.close();

    zoneFile.Load(decompressedData);

    SetZoneFile(std::make_shared<ZoneFile_COD7_Wii>(zoneFile));

    return true;
}
