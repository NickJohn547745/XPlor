#ifndef RAWFILE_H
#define RAWFILE_H

#include <qtcoreexports.h>
#include <QDataStream>
#include <QString>

struct RawFile {
    quint32 gscNamePtr;
    quint32 gscLength;
    quint32 rawFilePathPtr;
    QString rawFilePath;
    QString rawFileContents;
};

inline QDataStream &operator<<(QDataStream &out, const RawFile &rawFile) {
    out << rawFile.gscNamePtr;
    out << rawFile.gscLength;
    out << rawFile.rawFilePathPtr;

    // Parse rawfile path
    QByteArray rawFilePathData(rawFile.rawFilePath.toUtf8());
    out.writeRawData(rawFilePathData.data(), rawFilePathData.size());

    // Parse gsc contents
    QByteArray rawFileContentsData(rawFile.rawFileContents.toUtf8());
    out.writeRawData(rawFileContentsData.data(), rawFileContentsData.size());

    return out;
}

inline QDataStream &operator>>(QDataStream &in, RawFile &rawFile) {
    in >> rawFile.gscNamePtr;
    in >> rawFile.gscLength;
    in >> rawFile.rawFilePathPtr;

    // Parse rawfile path
    QString rawFilePath;
    char scriptPathChar;
    in >> scriptPathChar;
    while (scriptPathChar != 0) {
        rawFilePath += scriptPathChar;
        in >> scriptPathChar;
    }
    rawFile.rawFilePath = rawFilePath;

    // Parse gsc contents
    QString rawFileContents;
    char rawFileContentsChar;
    in >> rawFileContentsChar;
    while (rawFileContentsChar != 0 && rawFileContentsChar != -1) {
        rawFileContents += rawFileContentsChar;
        in >> rawFileContentsChar;
    }
    rawFile.rawFileContents = rawFileContents;

    return in;
}


#endif // RAWFILE_H
