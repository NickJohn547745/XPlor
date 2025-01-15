#ifndef LOCALIZE_H
#define LOCALIZE_H

#include <QDataStream>
#include <QString>

struct Localize {
    quint32 valuePtr;
    quint32 namePtr;
    QString referenceStr;
    QString localizedStr;
};

inline QDataStream &operator<<(QDataStream &out, const Localize &localize) {
    out << localize.valuePtr << localize.namePtr;

    // Parse gsc contents
    QByteArray localizedStrData(localize.localizedStr.toUtf8());
    out.writeRawData(localizedStrData.data(), localizedStrData.size());

    // Parse rawfile path
    QByteArray refStrData(localize.referenceStr.toUtf8());
    out.writeRawData(refStrData.data(), refStrData.size());

    return out;
}

inline QDataStream &operator>>(QDataStream &in, Localize &localize) {
    // Parse value and name pointers
    in >> localize.valuePtr >> localize.namePtr;

    // Parse localized string
    QString localizedStr;
    char localizedStrChar;
    in >> localizedStrChar;
    while (localizedStrChar != 0) {
        localizedStr += localizedStrChar;
        in >> localizedStrChar;
    }
    localize.localizedStr = localizedStr;

    // Parse localized reference name
    QString refStr;
    char refStrChar;
    in >> refStrChar;
    while (refStrChar != 0) {
        refStr += refStrChar;
        in >> refStrChar;
    }
    localize.referenceStr = refStr;

    return in;
}

#endif // LOCALIZE_H
