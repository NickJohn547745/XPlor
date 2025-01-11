#ifndef ZONE_H
#define ZONE_H

#include "enums.h"
#include "qtypes.h"
#include <QDataStream>
#include <QVector>

struct Zone {
    quint32 zoneFileSize;
    quint32 unknown1;
    quint32 unknown2;
    quint32 unknown3;
    quint32 unknown4;
    quint32 unknown5;
    quint32 unknown6;
    quint32 unknown7;
    quint32 unknown8;
    quint32 tagCount;
    quint32 unknown9;
    quint32 recordCount;
    quint32 unknown10;
    quint32 unknown11;
    QVector<quint32> tagPtrs;
    QStringList tags;

    QVector<ASSET_TYPE> assetTypes;
};

QDataStream &operator<<(QDataStream &out, const Zone &zone) {
    // Write adjusted fastfile size
    out << zone.zoneFileSize - 36;
    // Write unknowns 1-8
    out << zone.unknown1;
    out << zone.unknown2;
    out << zone.unknown3;
    out << zone.unknown4;
    out << zone.unknown5;
    out << zone.unknown6;
    out << zone.unknown7;
    out << zone.unknown8;
    // Write tag count
    out << zone.tagCount;
    // Write unknown 9
    out << zone.unknown9;
    // Write record count
    out << zone.recordCount;
    // Write unknowns 10-11
    out << zone.unknown10;
    out << zone.unknown11;
    // Write tag pointers
    foreach (quint32 tagPtr, zone.tagPtrs) {
        out << tagPtr;
    }
    // Write tags
    foreach (QString tag, zone.tags) {
        out << tag.toLocal8Bit();
    }

    return out;
}

QDataStream &operator>>(QDataStream &in, Zone &zone) {
    // Parse file size
    in >> zone.zoneFileSize;
    zone.zoneFileSize += 36;
    // Parse unknowns 1-8
    in >> zone.unknown1;
    in >> zone.unknown2;
    in >> zone.unknown3;
    in >> zone.unknown4;
    in >> zone.unknown5;
    in >> zone.unknown6;
    in >> zone.unknown7;
    in >> zone.unknown8;
    // Parse tag count
    in >> zone.tagCount;
    // Parse unknown 9
    in >> zone.unknown9;
    // Parse record count
    in >> zone.recordCount;

        in >> zone.unknown10;
    if (zone.tagCount) {
        // Parse unknowns 10-11
        in >> zone.unknown11;

        // Parse tag ptrs
        for (quint32 i = 0; i < zone.tagCount - 1; i++) {
            quint32 tagPtr;
            in >> tagPtr;

            zone.tagPtrs.push_back(tagPtr);
        }

        // Parse tags/strings before index
        QString zoneTag;
        char zoneTagChar;
        for (quint32 i = 0; i < zone.tagCount - 1; i++) {
            in >> zoneTagChar;
            while (zoneTagChar != 0) {
                zoneTag += zoneTagChar;
                in >> zoneTagChar;
            }
            zone.tags.push_back(zoneTag);
            zoneTag.clear();
        }
    }

    // Parse index
    for (quint32 i = 0; i < zone.recordCount; i++) {
        // Parse asset type
        quint32 assetType;
        in >> assetType;
        // Add asset type to vector
        zone.assetTypes << (ASSET_TYPE)assetType;
        // Skip separator
        in.skipRawData(4);
    }

    return in;
}

#endif // ZONE_H
