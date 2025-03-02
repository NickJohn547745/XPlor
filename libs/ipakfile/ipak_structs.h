#ifndef IPAK_STRUCTS_H
#define IPAK_STRUCTS_H

#include <QDataStream>
#include <QString>
#include <QVector>

struct IPAKHeader
{
    QString magic;
    quint32 magicInt;
    QString version;
    quint32 versionInt;
    quint32 size;
    quint32 sectionCount;
    QString platform;
    // Serial read method
    friend QDataStream &operator>>(QDataStream &in, IPAKHeader &data) {
        in.setByteOrder(QDataStream::LittleEndian);
        in >> data.magicInt;
        if (data.magicInt == 1262571593) {
            in.setByteOrder(QDataStream::BigEndian);
            data.platform = "Console";
        } else {
            data.platform = "PC";
        }
        in >> data.versionInt >> data.size >> data.sectionCount;
        // Format magic into string
        const char *magicChars = reinterpret_cast<const char *>(&data.magicInt);
        data.magic = QString::fromUtf8(magicChars, 4);

        // Format version into hex
        data.version = QString::number(data.versionInt, 16).toUpper();
        return in;
    }
    // Serial write method
    friend QDataStream &operator<<(QDataStream &out, const IPAKHeader &data) {
        out.setByteOrder(QDataStream::LittleEndian);
        if (data.magicInt == 1262571593) {
            out.setByteOrder(QDataStream::BigEndian);
        }
        out << data.magicInt << data.version << data.size << data.sectionCount;
        return out;
    }
};

struct IPAKSection
{
    QString type;
    quint32 typeInt;
    quint32 offset;
    quint32 size;
    quint32 itemCount;
    // Serial read method
    friend QDataStream &operator>>(QDataStream &in, IPAKSection &data) {
        in >> data.typeInt >> data.offset >> data.size >> data.itemCount;
        // Format type into string
        if (data.typeInt == 1) {
            data.type = "Index";
        } else if (data.typeInt == 2) {
            data.type = "Data";
        } else {
            data.type = "Unknown";
        }
        return in;
    }
    // Serial write method
    friend QDataStream &operator<<(QDataStream &out, const IPAKSection &data) {
        out << data.typeInt << data.offset << data.size << data.itemCount;
        return out;
    }
};

struct IPAKDataChunkCommand {
    quint32 size;
    bool compressed;
    // Serial read method
    friend QDataStream &operator>>(QDataStream &in, IPAKDataChunkCommand &data) {
        quint32 sizeAndCompression;
        in >> sizeAndCompression;

        data.size = sizeAndCompression & 0x00FFFFFF;
        data.compressed = (sizeAndCompression >> 24) & 0x01;

        return in;
    }
    // Serial write method
    friend QDataStream &operator<<(QDataStream &out, const IPAKDataChunkCommand &data) {
        quint32 sanitizedSize = data.size & 0x00FFFFFF;
        quint32 sanitizedCompressed = data.compressed & 0x01;
        quint32 sizeAndCompression = (sanitizedCompressed << 24) | sanitizedSize;

        out << sizeAndCompression;
        return out;
    }
};

struct IPAKDataChunkHeader
{
    quint32 count;
    quint32 offset;
    QVector<IPAKDataChunkCommand> commands;
    // Serial read method
    friend QDataStream &operator>>(QDataStream &in, IPAKDataChunkHeader &data) {
        quint32 countAndOffset;
        in >> countAndOffset;
        data.count = (countAndOffset >> 24) & 0xFF;
        data.offset = countAndOffset & 0x00FFFFFF;
        return in;
    }
    // Serial write method
    friend QDataStream &operator<<(QDataStream &out, const IPAKDataChunkHeader &data) {
        quint32 count = data.count & 0xFF;
        quint32 offset = data.offset & 0x00FFFFFF;
        out << ((count << 24) | offset);
        return out;
    }
};

struct IPAKIndexEntry
{
    quint32 dataHash;
    quint32 nameHash;
    quint32 offset;
    quint32 size;
    // Serial read method
    friend QDataStream &operator>>(QDataStream &in, IPAKIndexEntry &data) {
        in >> data.dataHash >> data.nameHash >> data.offset >> data.size;
        return in;
    }
    // Serial write method
    friend QDataStream &operator<<(QDataStream &out, const IPAKIndexEntry &data) {
        out << data.dataHash << data.nameHash << data.offset << data.size;
        return out;
    }
};

struct IPAKDataChunkMetaData
{
    quint64 key;
    QString name;
    int format;
    int offset;
    int size;
    int width;
    int height;
    int levels;
    int mip;
    // Serial read method
    friend QDataStream &operator>>(QDataStream &in, IPAKDataChunkMetaData &data) {
        in >> data.key;
        in.readRawData(reinterpret_cast<char *>(data.name.data()), sizeof(60));
        in >> data.format >> data.offset >> data.size >> data.width
            >> data.height >> data.levels >> data.mip;
        return in;
    }
    // Serial write method
    friend QDataStream &operator<<(QDataStream &out, const IPAKDataChunkMetaData &data) {
        out << data.key;
        out.writeRawData(reinterpret_cast<const char *>(data.name.constData()), sizeof(60));
        out << data.format << data.offset << data.size << data.width
            << data.height << data.levels << data.mip;
        return out;
    }
};

#endif // IPAK_STRUCTS_H
