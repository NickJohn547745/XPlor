#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include <QDataStream>
#include <QFile>
#include <QDebug>
#include <QCryptographicHash>

class Encryption {
public:
    static const int VECTOR_SIZE = 16;        // 16 32-bit words
    static const int NUM_OF_BLOCKS_PER_CHUNK = 8192;

    //--------------------------------------------------------------------
    // Helper functions (assuming little–endian order)

    static void Convert32BitTo8Bit(quint32 value, quint8* array);

    static quint32 ConvertArrayTo32Bit(const QByteArray &array);

    static quint32 Rotate(quint32 value, quint32 numBits);

    // Build the IV table from a 0x20–byte feed. The table is 0xFB0 bytes.
    static QByteArray InitIVTable(const QByteArray &feed);

    // "unk" function as in the C# code.
    static int unk(quint64 arg1, quint8 arg2);

    // Compute the IV for a given section index using the IV table.
    static QByteArray GetIV(const QByteArray &table, int index);

    // Update the IV table given the section's SHA1 hash.
    static void UpdateIVTable(QByteArray &table, int index, const QByteArray &sectionHash);

    static quint32 ToUInt32(const QByteArray &data, int offset);

    //--------------------------------------------------------------------
    // Salsa20 decryption for one section.
    // This function resets the counter for each section.
    static QByteArray salsa20DecryptSection(const QByteArray &sectionData, const QByteArray &key, const QByteArray &iv, int blockSize = 64);

    static void fillIVTable(QByteArray fastFileData, QByteArray& ivTable, quint32 ivTableLength);

    static void fillIV(int index, QByteArray& ivPtr, const QByteArray& ivTable, const QVector<quint32>& ivCounter);


    static void generateNewIV(int index, const QByteArray& hash, QByteArray& ivTable, QVector<quint32>& ivCounter);

    static QByteArray decryptFastFile_BO2(const QByteArray& fastFileData);
    static QByteArray decryptFastFile_BO3(const QByteArray& fastFileData);
};

#endif // ENCRYPTION_H
