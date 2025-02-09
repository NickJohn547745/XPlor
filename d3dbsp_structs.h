#ifndef D3DBSP_STRUCTS_H
#define D3DBSP_STRUCTS_H

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

#endif // D3DBSP_STRUCTS_H
