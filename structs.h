#ifndef STRUCTS_H
#define STRUCTS_H

#include <QByteArray>

// Define Lump Structure
struct Lump {
    QByteArray content;
    quint32 size = 0;
    bool isEmpty = true;
};

// Lump Index Entry Structure
struct LumpIndexEntry {
    quint32 type;
    quint32 length;
};

#endif // STRUCTS_H
