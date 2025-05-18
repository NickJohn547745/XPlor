#include "encryption.h"
#include "QtZlib/zlib.h"
#include "ecrypt-sync.h"
#include "compression.h"

void Encryption::Convert32BitTo8Bit(quint32 value, quint8 *array) {
    array[0] = static_cast<quint8>(value >> 0);
    array[1] = static_cast<quint8>(value >> 8);
    array[2] = static_cast<quint8>(value >> 16);
    array[3] = static_cast<quint8>(value >> 24);
}

quint32 Encryption::ConvertArrayTo32Bit(const QByteArray &array) {
    return ((static_cast<quint32>(static_cast<uchar>(array[0])) << 0)  |
            (static_cast<quint32>(static_cast<uchar>(array[1])) << 8)  |
            (static_cast<quint32>(static_cast<uchar>(array[2])) << 16) |
            (static_cast<quint32>(static_cast<uchar>(array[3])) << 24));
}

quint32 Encryption::Rotate(quint32 value, quint32 numBits) {
    return (value << numBits) | (value >> (32 - numBits));
}

QByteArray Encryption::InitIVTable(const QByteArray &feed) {
    const int tableSize = 0xFB0;
    QByteArray table;
    table.resize(tableSize);
    int ptr = 0;
    for (int i = 0; i < 200; ++i) {
        for (int x = 0; x < 5; ++x) {
            if (static_cast<uchar>(feed.at(ptr)) == 0x00)
                ptr = 0;
            int base = i * 20 + x * 4;
            table[base]     = feed.at(ptr);
            table[base + 1] = feed.at(ptr);
            table[base + 2] = feed.at(ptr);
            table[base + 3] = feed.at(ptr);
            ++ptr;
        }
    }
    // Copy block numbers [1,0,0,0] into the last 16 bytes
    QByteArray oneBlock;
    oneBlock.append(char(1)); oneBlock.append(char(0)); oneBlock.append(char(0)); oneBlock.append(char(0));
    table.replace(0xFA0, 4, oneBlock);
    table.replace(0xFA4, 4, oneBlock);
    table.replace(0xFA8, 4, oneBlock);
    table.replace(0xFAC, 4, oneBlock);
    return table;
}

int Encryption::unk(quint64 arg1, quint8 arg2) {
    if (arg2 >= 0x40)
        return 0;
    return static_cast<int>(arg1 >> arg2);
}

QByteArray Encryption::GetIV(const QByteArray &table, int index) {
    int num1 = 0xFA0 + index;
    int num2 = unk(0x51EB851FLL * num1, 0x20);
    int adjust = ((num2 >> 6) + (num2 >> 31));
    int startIndex = 20 * (num1 - 200 * adjust);
    // Return 8 bytes from that location.
    return table.mid(startIndex, 8);
}

void Encryption::UpdateIVTable(QByteArray &table, int index, const QByteArray &sectionHash) {
    int blockNumIndex = index % 4;
    int baseOffset = 0xFA0 + blockNumIndex * 4;
    quint32 blockNumVal = (static_cast<uchar>(table.at(baseOffset))      ) |
                          (static_cast<uchar>(table.at(baseOffset + 1)) << 8 ) |
                          (static_cast<uchar>(table.at(baseOffset + 2)) << 16) |
                          (static_cast<uchar>(table.at(baseOffset + 3)) << 24);
    int blockNum = blockNumVal * 4 + index;
    int num2 = unk(0x51EB851FLL * blockNum, 0x20);
    int adjust = ((num2 >> 6) + (num2 >> 31));
    int startIndex = 20 * (blockNum - 200 * adjust) + 1;
    int hashIndex = 0;
    for (int x = 0; x < 4; ++x) {
        table[startIndex - 1] = table.at(startIndex - 1) ^ sectionHash.at(hashIndex);
        table[startIndex]     = table.at(startIndex)     ^ sectionHash.at(hashIndex + 1);
        table[startIndex + 1] = table.at(startIndex + 1) ^ sectionHash.at(hashIndex + 2);
        table[startIndex + 2] = table.at(startIndex + 2) ^ sectionHash.at(hashIndex + 3);
        table[startIndex + 3] = table.at(startIndex + 3) ^ sectionHash.at(hashIndex + 4);
        startIndex += 5;
        hashIndex += 5;
    }
}

quint32 Encryption::ToUInt32(const QByteArray &data, int offset) {
    // Converts 4 bytes (starting at offset) from data into a 32-bit unsigned integer (little-endian)
    return ((static_cast<quint32>(static_cast<uchar>(data[offset]))      ) |
            (static_cast<quint32>(static_cast<uchar>(data[offset+1])) << 8 ) |
            (static_cast<quint32>(static_cast<uchar>(data[offset+2])) << 16) |
            (static_cast<quint32>(static_cast<uchar>(data[offset+3])) << 24));
}

QByteArray Encryption::salsa20DecryptSection(const QByteArray &sectionData, const QByteArray &key, const QByteArray &iv, int blockSize)
{
    // Choose the appropriate constant based on key length.
    QByteArray constants;
    if (key.size() == 32)
        constants = "expand 32-byte k";
    else if (key.size() == 16)
        constants = "expand 16-byte k";
    else {
        qWarning() << "Invalid key size:" << key.size() << "; expected 16 or 32 bytes.";
        return QByteArray();
    }

    QVector<quint32> state(VECTOR_SIZE);

    // Set state[0] using the first 4 bytes of the constant.
    state[0] = ConvertArrayTo32Bit(constants.mid(0, 4));

    // state[1] through state[4] come from the first 16 bytes of the key.
    state[1] = ToUInt32(key, 0);
    state[2] = ToUInt32(key, 4);
    state[3] = ToUInt32(key, 8);
    state[4] = ToUInt32(key, 12);

    // state[5] comes from the next 4 bytes of the constant.
    state[5] = ConvertArrayTo32Bit(constants.mid(4, 4));

    // state[6] and state[7] come from the IV (which must be 8 bytes).
    state[6] = ConvertArrayTo32Bit(iv.mid(0, 4));
    state[7] = ConvertArrayTo32Bit(iv.mid(4, 4));

    // state[8] and state[9] are the 64-bit block counter (start at 0).
    state[8] = 0;
    state[9] = 0;

    // state[10] comes from the next 4 bytes of the constant.
    state[10] = ConvertArrayTo32Bit(constants.mid(8, 4));

    // For state[11] through state[14]:
    // If the key is 32 bytes, use bytes 16..31; if 16 bytes, reuse the first 16 bytes.
    if (key.size() == 32) {
        state[11] = ToUInt32(key, 16);
        state[12] = ToUInt32(key, 20);
        state[13] = ToUInt32(key, 24);
        state[14] = ToUInt32(key, 28);
    } else { // key.size() == 16
        state[11] = ToUInt32(key, 0);
        state[12] = ToUInt32(key, 4);
        state[13] = ToUInt32(key, 8);
        state[14] = ToUInt32(key, 12);
    }

    // state[15] comes from the last 4 bytes of the constant.
    state[15] = ConvertArrayTo32Bit(constants.mid(12, 4));

    // Prepare the output buffer.
    QByteArray output(sectionData.size(), Qt::Uninitialized);
    int numBlocks = sectionData.size() / blockSize;
    int remainder = sectionData.size() % blockSize;

    // Process each full block.
    for (int blockIndex = 0; blockIndex < numBlocks; ++blockIndex) {
        QVector<quint32> x = state; // make a copy of the current state for this block

        // Run 20 rounds (10 iterations) of Salsa20.
        for (int round = 20; round > 0; round -= 2) {
            x[4]  ^= Rotate(x[0]  + x[12], 7);
            x[8]  ^= Rotate(x[4]  + x[0], 9);
            x[12] ^= Rotate(x[8]  + x[4], 13);
            x[0]  ^= Rotate(x[12] + x[8], 18);

            x[9]  ^= Rotate(x[5]  + x[1], 7);
            x[13] ^= Rotate(x[9]  + x[5], 9);
            x[1]  ^= Rotate(x[13] + x[9], 13);
            x[5]  ^= Rotate(x[1]  + x[13], 18);

            x[14] ^= Rotate(x[10] + x[6], 7);
            x[2]  ^= Rotate(x[14] + x[10], 9);
            x[6]  ^= Rotate(x[2]  + x[14], 13);
            x[10] ^= Rotate(x[6]  + x[2], 18);

            x[3]  ^= Rotate(x[15] + x[11], 7);
            x[7]  ^= Rotate(x[3]  + x[15], 9);
            x[11] ^= Rotate(x[7]  + x[3], 13);
            x[15] ^= Rotate(x[11] + x[7], 18);

            x[1]  ^= Rotate(x[0]  + x[3], 7);
            x[2]  ^= Rotate(x[1]  + x[0], 9);
            x[3]  ^= Rotate(x[2]  + x[1], 13);
            x[0]  ^= Rotate(x[3]  + x[2], 18);

            x[6]  ^= Rotate(x[5]  + x[4], 7);
            x[7]  ^= Rotate(x[6]  + x[5], 9);
            x[4]  ^= Rotate(x[7]  + x[6], 13);
            x[5]  ^= Rotate(x[4]  + x[7], 18);

            x[11] ^= Rotate(x[10] + x[9], 7);
            x[8]  ^= Rotate(x[11] + x[10], 9);
            x[9]  ^= Rotate(x[8]  + x[11], 13);
            x[10] ^= Rotate(x[9]  + x[8], 18);

            x[12] ^= Rotate(x[15] + x[14], 7);
            x[13] ^= Rotate(x[12] + x[15], 9);
            x[14] ^= Rotate(x[13] + x[12], 13);
            x[15] ^= Rotate(x[14] + x[13], 18);
        }

        // Produce the 64-byte keystream block by adding the original state.
        QVector<quint8> keyStreamBlock(blockSize);
        for (int i = 0; i < VECTOR_SIZE; ++i) {
            x[i] += state[i];
            Convert32BitTo8Bit(x[i], keyStreamBlock.data() + 4 * i);
        }

        // XOR the keystream block with the corresponding block of sectionData.
        const uchar* inBlock = reinterpret_cast<const uchar*>(sectionData.constData()) + blockIndex * blockSize;
        uchar* outBlock = reinterpret_cast<uchar*>(output.data()) + blockIndex * blockSize;
        for (int j = 0; j < blockSize; ++j) {
            outBlock[j] = inBlock[j] ^ keyStreamBlock[j];
        }
        // Increment the 64-bit block counter.
        state[8]++;
        if (state[8] == 0)
            state[9]++;
    }

    // Process any remaining bytes.
    if (remainder > 0) {
        QVector<quint32> x = state;
        for (int round = 20; round > 0; round -= 2) {
            x[4]  ^= Rotate(x[0]  + x[12], 7);
            x[8]  ^= Rotate(x[4]  + x[0], 9);
            x[12] ^= Rotate(x[8]  + x[4], 13);
            x[0]  ^= Rotate(x[12] + x[8], 18);

            x[9]  ^= Rotate(x[5]  + x[1], 7);
            x[13] ^= Rotate(x[9]  + x[5], 9);
            x[1]  ^= Rotate(x[13] + x[9], 13);
            x[5]  ^= Rotate(x[1]  + x[13], 18);

            x[14] ^= Rotate(x[10] + x[6], 7);
            x[2]  ^= Rotate(x[14] + x[10], 9);
            x[6]  ^= Rotate(x[2]  + x[14], 13);
            x[10] ^= Rotate(x[6]  + x[2], 18);

            x[3]  ^= Rotate(x[15] + x[11], 7);
            x[7]  ^= Rotate(x[3]  + x[15], 9);
            x[11] ^= Rotate(x[7]  + x[3], 13);
            x[15] ^= Rotate(x[11] + x[7], 18);

            x[1]  ^= Rotate(x[0]  + x[3], 7);
            x[2]  ^= Rotate(x[1]  + x[0], 9);
            x[3]  ^= Rotate(x[2]  + x[1], 13);
            x[0]  ^= Rotate(x[3]  + x[2], 18);

            x[6]  ^= Rotate(x[5]  + x[4], 7);
            x[7]  ^= Rotate(x[6]  + x[5], 9);
            x[4]  ^= Rotate(x[7]  + x[6], 13);
            x[5]  ^= Rotate(x[4]  + x[7], 18);

            x[11] ^= Rotate(x[10] + x[9], 7);
            x[8]  ^= Rotate(x[11] + x[10], 9);
            x[9]  ^= Rotate(x[8]  + x[11], 13);
            x[10] ^= Rotate(x[9]  + x[8], 18);

            x[12] ^= Rotate(x[15] + x[14], 7);
            x[13] ^= Rotate(x[12] + x[15], 9);
            x[14] ^= Rotate(x[13] + x[12], 13);
            x[15] ^= Rotate(x[14] + x[13], 18);
        }
        QVector<quint8> keyStreamBlock(blockSize);
        for (int i = 0; i < VECTOR_SIZE; ++i) {
            x[i] += state[i];
            Convert32BitTo8Bit(x[i], keyStreamBlock.data() + 4 * i);
        }
        const uchar* inBlock = reinterpret_cast<const uchar*>(sectionData.constData()) + numBlocks * blockSize;
        uchar* outBlock = reinterpret_cast<uchar*>(output.data()) + numBlocks * blockSize;
        for (int j = 0; j < remainder; ++j)
            outBlock[j] = inBlock[j] ^ keyStreamBlock[j];
    }

    return output;
}

void Encryption::fillIVTable(QByteArray fastFileData, QByteArray &ivTable, quint32 ivTableLength)
{
    QDataStream stream(fastFileData);
    stream.skipRawData(24);

    quint32 nameKeyLength = 0;
    for (int i = 0; i < 32 && !stream.atEnd(); i++) {
        if (!stream.atEnd() && stream.device()->peek(1).toHex() != "00") {
            nameKeyLength++;
            stream.skipRawData(1);
        } else {
            break;
        }
    }

    if (nameKeyLength < 32) {
        stream.skipRawData(32 - nameKeyLength);
    }

    if (ivTableLength < 16) {
        qWarning() << "IV table length too small!";
        return;
    }

    for (quint32 i = 0; i < ivTableLength - 16; i++) {
        if (stream.atEnd()) {
            qWarning() << "Stream ended while filling IV table!";
            return;
        }
        quint8 ivVal;
        stream >> ivVal;
        ivTable[i] = ivVal;
    }
}

void Encryption::fillIV(int index, QByteArray &ivPtr, const QByteArray &ivTable, const QVector<quint32> &ivCounter)
{
    if (index < 0 || index >= ivCounter.size()) {
        qWarning() << "Invalid IV index: " << index;
        return;
    }

    int ivOffset = ((index + 4 * (ivCounter[index] - 1)) % 800) * 20;

    if (ivOffset + 8 > ivTable.size()) {
        qWarning() << "IV offset out of bounds! Offset: " << ivOffset;
        return;
    }

    ivPtr = ivTable.mid(ivOffset, 8);
}

void Encryption::generateNewIV(int index, const QByteArray &hash, QByteArray &ivTable, QVector<quint32> &ivCounter)
{
    if (index < 0 || index >= ivCounter.size()) {
        qWarning() << "Invalid index: " << index;
        return;
    }

    quint32 safeCounter = fmin(ivCounter[index], 800u - 1);
    int ivOffset = (index + 4 * safeCounter) % 800 * 5;

    for (int i = 0; i < 20; i++) {
        if (ivOffset + i >= ivTable.size()) {
            qWarning() << "Index out of bounds for IV table!";
            return;
        }
        ivTable[ivOffset + i] ^= hash[i];
    }

    ivCounter[index]++;
}

QByteArray Encryption::decryptFastFile_BO2(const QByteArray &fastFileData)
{
    const QByteArray bo2_salsa20_key = QByteArray::fromHex("641D8A2FE31D3AA63622BBC9CE8587229D42B0F8ED9B924130BF88B65EDC50BE");

    QByteArray fileData = fastFileData;
    QByteArray finalFastFile;

    QByteArray ivTable(16000, 0);
    fillIVTable(fileData, ivTable, 16000 - 1);

    QVector<quint32> ivCounter(4, 1);
    QDataStream stream(fileData);
    stream.setByteOrder(QDataStream::LittleEndian);
    stream.skipRawData(0x138);

    QByteArray sha1Hash(20, 0);
    QByteArray ivPtr(8, 0);
    int chunkIndex = 0;

    while (!stream.atEnd()) {
        quint32 dataLength;
        stream >> dataLength;

        if (dataLength == 0 || dataLength > fileData.size() - stream.device()->pos()) {
            qWarning() << "Invalid data length at offset: " << stream.device()->pos();
            break;
        }

        fillIV(chunkIndex % 4, ivPtr, ivTable, ivCounter);

        ECRYPT_ctx x;
        ECRYPT_keysetup(&x, reinterpret_cast<const u8*>(bo2_salsa20_key.constData()), 256, 0);
        ECRYPT_ivsetup(&x, reinterpret_cast<const u8*>(ivPtr.constData()));

        QByteArray encryptedBlock = fileData.mid(stream.device()->pos(), dataLength);
        QByteArray decryptedBlock;
        decryptedBlock.resize(dataLength);

        ECRYPT_decrypt_bytes(&x, reinterpret_cast<const u8*>(encryptedBlock.constData()),
                             reinterpret_cast<u8*>(decryptedBlock.data()), dataLength);

        QCryptographicHash sha1(QCryptographicHash::Sha1);
        sha1.addData(decryptedBlock);
        sha1Hash = sha1.result();

        z_stream strm = {};
        strm.zalloc = Z_NULL;
        strm.zfree = Z_NULL;
        strm.opaque = Z_NULL;
        strm.avail_in = static_cast<uInt>(decryptedBlock.size());
        strm.next_in = reinterpret_cast<Bytef*>(decryptedBlock.data());

        QByteArray decompressedData;
        decompressedData.resize(fmax(dataLength * 2, 4096));
        strm.avail_out = decompressedData.size();
        strm.next_out = reinterpret_cast<Bytef*>(decompressedData.data());

        int zReturn = inflateInit2(&strm, -15);
        if (zReturn != Z_OK) {
            qWarning() << "inflateInit2 failed with error code" << zReturn;
            break;
        }

        zReturn = inflate(&strm, Z_FINISH);
        inflateEnd(&strm);

        if (zReturn != Z_STREAM_END) {
            qDebug() << "Error decompressing at offset: " << stream.device()->pos() << " : " << zReturn;
            decompressedData.clear();
        } else {
            decompressedData.resize(strm.total_out);
        }

        finalFastFile.append(decompressedData);

        generateNewIV(chunkIndex % 4, sha1Hash, ivTable, ivCounter);

        if (stream.device()->pos() + static_cast<qint64>(dataLength) > fileData.size()) {
            qWarning() << "Skipping past file size!";
            break;
        }

        stream.skipRawData(dataLength);
        chunkIndex++;
    }

    return finalFastFile;
}

QByteArray Encryption::decryptFastFile_BO3(const QByteArray &fastFileData) {
    const QByteArray salsaKey = QByteArray::fromHex("0E50F49F412317096038665622DD091332A209BA0A05A00E1377CEDB0A3CB1D3");

    QByteArray ivTable(0xFB0, 0);
    fillIVTable(fastFileData, ivTable, 0xFB0 - 1);

    QVector<quint32> ivCounter(4, 1);
    QDataStream stream(fastFileData);
    stream.setByteOrder(QDataStream::LittleEndian);

    QByteArray finalFastFile;
    QByteArray sha1Hash(20, 0);
    QByteArray ivPtr(8, 0);
    int chunkIndex = 0;

    while (!stream.atEnd()) {
        if (stream.device()->bytesAvailable() < 4) {
            qWarning() << "No sufficient data for chunk size at offset:" << stream.device()->pos();
            break;
        }

        quint32 dataLength;
        stream >> dataLength;

        if (dataLength == 0 || dataLength > fastFileData.size() - stream.device()->pos()) {
            qWarning() << "Invalid data length at offset:" << stream.device()->pos();
            break;
        }

        fillIV(chunkIndex % 4, ivPtr, ivTable, ivCounter);

        ECRYPT_ctx x;
        ECRYPT_keysetup(&x, reinterpret_cast<const u8*>(salsaKey.constData()), 256, 0);
        ECRYPT_ivsetup(&x, reinterpret_cast<const u8*>(ivPtr.constData()));

        QByteArray encryptedBlock = fastFileData.mid(stream.device()->pos(), dataLength);
        QByteArray decryptedBlock(dataLength, Qt::Uninitialized);

        ECRYPT_decrypt_bytes(&x,
                             reinterpret_cast<const u8*>(encryptedBlock.constData()),
                             reinterpret_cast<u8*>(decryptedBlock.data()),
                             dataLength);

        // SHA1 hash update
        sha1Hash = QCryptographicHash::hash(decryptedBlock, QCryptographicHash::Sha1);

        // Decompress (ZLIB raw DEFLATE)
        QByteArray decompressedData = Compression::DecompressDeflate(decryptedBlock);
        if (decompressedData.isEmpty()) {
            qWarning() << "Failed decompression at chunk index:" << chunkIndex;
            return QByteArray();
        }

        finalFastFile.append(decompressedData);

        // Update IV table using SHA1
        generateNewIV(chunkIndex % 4, sha1Hash, ivTable, ivCounter);

        stream.skipRawData(dataLength);
        chunkIndex++;
    }

    return finalFastFile;
}
