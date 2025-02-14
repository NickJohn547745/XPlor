#include "fastfile_cod5.h"

#include <QFile>
#include <QDebug>

FastFile_COD5::FastFile_COD5() {

}

FastFile_COD5::~FastFile_COD5() {

}

FastFile &FastFile_COD5::operator=(const FastFile &other) {

}

bool FastFile_COD5::Load(const QString aFilePath) {
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
    QByteArray decompressedData;

    // Create a QDataStream on the input data.
    QDataStream fastFileStream(aData);
    fastFileStream.setByteOrder(QDataStream::LittleEndian);

    // Parse header values.
    SetCompany(pParseFFCompany(&fastFileStream));
    fileType  = pParseFFFileType(&fastFileStream);
    signage   = pParseFFSignage(&fastFileStream);
    magic     = pParseFFMagic(&fastFileStream);
    version   = pParseFFVersion(&fastFileStream);
    platform  = pCalculateFFPlatform();
    game      = pCalculateFFGame();

    // For COD5, simply decompress from offset 12.
    decompressedData = Compressor::DecompressZLIB(aData.mid(12));

    QFile testFile("exports/" + fileStem.section('.', 0, 0) + ".zone");
    if(testFile.open(QIODevice::WriteOnly)) {
        testFile.write(decompressedData);
        testFile.close();
    }

    zoneFile.Load(decompressedData, fileStem.section('.', 0, 0) + ".zone");

    return true;
}
