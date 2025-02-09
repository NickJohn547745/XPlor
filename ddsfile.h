#ifndef DDSFILE_H
#define DDSFILE_H

#include "enums.h"
#include <QFile>
#include <QByteArray>
#include <QDataStream>
#include <QtEndian>
#include <QVector>
#include <QDebug>
#include <QImage>
#include <DevILSDK/include/IL/il.h>

struct DDSPixelFormat {
    quint32 size;
    quint32 flags;
    quint32 format;
    quint32 rgbBitCount;
    quint32 rBitMask;
    quint32 gBitMask;
    quint32 bBitMask;
    quint32 aBitMask;
};

struct DDSCaps {
    quint32 caps1;
    quint32 caps2;
    quint32 dDSX;
    quint32 reserved;
};

struct DDSHeader {
    quint32 magic;
    quint32 size;
    quint32 flags;
    quint32 height;
    quint32 width;
    quint32 pitchOrLinearSize;
    quint32 depth;
    quint32 mipMapCount;
    quint32 reserved1[11];
    DDSPixelFormat pixelFormat;
    DDSCaps caps;
    quint32 reserved2;
};

// Mipmap Structure
struct DDSMipmap {
    quint32 size;
    quint32 width;
    quint32 height;
    QByteArray data;
};

class IWIFile;

// DDS File Class
class DDSFile {
public:
    QString fileStem;
    DDSHeader header;
    QVector<DDSMipmap> mipmaps;

    DDSFile();
    DDSFile(const QString &aFilePath);
    DDSFile(const IWIFile &aIWIFile);
    DDSFile(const QByteArray aDDSData, const QString aFileStem);
    DDSFile(const DDSFile &ddsFile);
    DDSFile& operator=(const DDSFile& other);

    bool SaveDDS();
    bool SaveIWI();
    bool SavePNG();
    bool SaveJPG();

    void SetupExportDirs();
    static DDSPixelFormat CalculatePixelFormat(quint8 aIWIFormat);

private:
    static QByteArray ReadDDSFile(const QString &aFilePath);
    QByteArray IWItoDDSData(const IWIFile &aIWIFile);
};

#endif // DDSFILE_H
