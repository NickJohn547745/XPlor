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

// Bink structure definitions
struct BINKRECT {
    int Left;
    int Top;
    int Width;
    int Height;
};

struct BINK {
    int Width;
    int Height;
    uint32_t Frames;
    uint32_t FrameNum;
    uint32_t FrameRate;
    uint32_t FrameRateDiv;
    uint32_t ReadError;
    uint32_t OpenFlags;
    BINKRECT FrameRects;
    uint32_t NumRects;
    uint32_t FrameChangePercent;
};

#endif // D3DBSP_STRUCTS_H
