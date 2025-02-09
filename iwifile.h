#ifndef IWIFILE_H
#define IWIFILE_H

#include "qimage.h"
#include <QFile>
#include <QByteArray>
#include <QDataStream>
#include <QtEndian>
#include <QVector>
#include <QDebug>
#include <QDir>
#include <QApplication>

// Supported versions
static const QVector<quint8> supportedVersions = {
    0x05, // CoD2
    0x06, // CoD4, CoD5
    0x08, // CoDMW2, CoDMW3
    0x0D, // CoDBO1
    0x1B  // CoDBO2
};

class DDSFile;

struct IWIHeader {
    char Magic[3];
    quint8 Version;

    bool isSupported() const;
};

struct IWIInfo {
    quint8 Format;
    quint8 Usage;
    quint16 Width;
    quint16 Height;
    quint16 Depth;
};

struct IWIMipmap {
    qint32 offset;
    qint32 size;
    QByteArray data;
};

class IWIFile {
public:
    QString fileStem;
    IWIHeader header;
    IWIInfo info;
    QVector<IWIMipmap> mipmaps;

    IWIFile();
    IWIFile(const QString &aFilePath);
    IWIFile(DDSFile &aDDSFile);
    IWIFile(const IWIFile &iwiFile);
    IWIFile& operator=(const IWIFile& other);
    ~IWIFile();

    bool SaveIWI();
    bool SaveDDS();
    bool SavePNG();
    bool SaveJPG();
    void SetupExportDirs();
};

#endif // IWIFILE_H
