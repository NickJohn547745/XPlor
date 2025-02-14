#include "fastfile.h"
#include "compressor.h"

#include <QFile>
#include <QDebug>

FastFile::~FastFile() {

}

FastFile &FastFile::operator=(const FastFile &other) {
    if (this != &other) {
        mStem = other.GetStem();
        mType = other.GetType();
        mCompany = other.GetCompany();
        mSignage = other.GetSignage();
        mMagic = other.GetMagic();
        mVersion = other.GetVersion();
        mZoneFile = other.GetZoneFile();
        mGame = other.GetGame();
        mPlatform = other.GetPlatform();
    }
    return *this;
}

bool FastFile::Load(const QByteArray aData) {
    QByteArray decompressedData;

    // Create a QDataStream on the input data.
    QDataStream fastFileStream(aData);
    fastFileStream.setByteOrder(QDataStream::LittleEndian);

    // Parse header values.
    if (fastFileStream.device()->peek(2).toHex() == "0000") {
        company   = COMPANY_INFINITY_WARD;
        fileType  = FILETYPE_FAST_FILE;
        signage   = SIGNAGE_UNSIGNED;
        magic     = 0;
        version   = 0;
        platform  = "360";
        game      = "COD2";

    } else {
        company   = pParseFFCompany(&fastFileStream);
        fileType  = pParseFFFileType(&fastFileStream);
        signage   = pParseFFSignage(&fastFileStream);
        magic     = pParseFFMagic(&fastFileStream);
        version   = pParseFFVersion(&fastFileStream);
        platform  = pCalculateFFPlatform();
        game      = pCalculateFFGame();
    }

    if (game == "COD5") {
        // For COD5, simply decompress from offset 12.
        decompressedData = Compressor::DecompressZLIB(aData.mid(12));

        QFile testFile("exports/" + fileStem.section('.', 0, 0) + ".zone");
        if(testFile.open(QIODevice::WriteOnly)) {
            testFile.write(decompressedData);
            testFile.close();
        }

        zoneFile.Load(decompressedData, fileStem.section('.', 0, 0) + ".zone");
    }
    else if (game == "COD7" || game == "COD9") {
        // For COD7/COD9, use BigEndian.
        fastFileStream.setByteOrder(QDataStream::BigEndian);
        if (platform == "PC") {
            fastFileStream.setByteOrder(QDataStream::LittleEndian);
        }

        // Select key based on game.
        QByteArray key;
        if (game == "COD7") {
            fastFileStream.skipRawData(4);
            if (platform == "360") {
                key = QByteArray::fromHex("1ac1d12d527c59b40eca619120ff8217ccff09cd16896f81b829c7f52793405d");
            } else if (platform == "PS3") {
                key = QByteArray::fromHex("46D3F997F29C9ACE175B0DAE3AB8C0C1B8E423E2E3BF7E3C311EA35245BF193A");
                // or
                // key = QByteArray::fromHex("0C99B3DDB8D6D0845D1147E470F28A8BF2AE69A8A9F534767B54E9180FF55370");
            }
        } else if (game == "COD9") {
            if (platform == "360") {
                key = QByteArray::fromHex("0E50F49F412317096038665622DD091332A209BA0A05A00E1377CEDB0A3CB1D3");
            } else if (platform == "PC") {
                key = QByteArray::fromHex("641D8A2FE31D3AA63622BBC9CE8587229D42B0F8ED9B924130BF88B65EDC50BE");
            }
        }

        // Read the 8-byte magic.
        QByteArray fileMagic(8, Qt::Uninitialized);
        fastFileStream.readRawData(fileMagic.data(), 8);
        if (fileMagic != "PHEEBs71") {
            qWarning() << "Invalid fast file magic!";
            return false;
        }
        fastFileStream.skipRawData(4);

        // Read IV table name (32 bytes).
        QByteArray fileName(32, Qt::Uninitialized);
        fastFileStream.readRawData(fileName.data(), 32);

        // Build the IV table from the fileName.
        QByteArray ivTable = Compressor::InitIVTable(fileName);

        // Skip the RSA signature (256 bytes).
        QByteArray rsaSignature(256, Qt::Uninitialized);
        fastFileStream.readRawData(rsaSignature.data(), 256);

        // Now the stream should be positioned at 0x13C, where sections begin.
        int sectionIndex = 0;
        while (true) {
            qint32 sectionSize = 0;
            fastFileStream >> sectionSize;
            qDebug() << "Section index:" << sectionIndex << "Size:" << sectionSize
                     << "Pos:" << fastFileStream.device()->pos();
            if (sectionSize == 0)
                break;

            // Read the section data.
            QByteArray sectionData;
            sectionData.resize(sectionSize);
            fastFileStream.readRawData(sectionData.data(), sectionSize);

            // Compute the IV for this section.
            QByteArray iv = Compressor::GetIV(ivTable, sectionIndex);

            // Decrypt the section using Salsa20.
            QByteArray decData = Compressor::salsa20DecryptSection(sectionData, key, iv);

            // Compute SHA1 hash of the decrypted data.
            QByteArray sectionHash = QCryptographicHash::hash(decData, QCryptographicHash::Sha1);

            // Update the IV table based on the section hash.
            Compressor::UpdateIVTable(ivTable, sectionIndex, sectionHash);

            // Build a compressed data buffer by prepending the two-byte zlib header.
            QByteArray compressedData;
            compressedData.append(char(0x78));
            compressedData.append(char(0x01));
            compressedData.append(decData);

            // For COD7, always decompress.
            // For COD9, conditionally use DEFLATE (set useDeflateForCOD9 as needed).
            if (game == "COD7") {
                decompressedData.append(Compressor::DecompressZLIB(compressedData));
            } else if (game == "COD9") {
                if (platform == "PC") {
                    decompressedData.append(Compressor::DecompressZLIB(compressedData));
                } else if (platform == "360") {
                    decompressedData.append(LZX::DecompressLZX(compressedData, compressedData.size()));
                }
            } else {
                // If not decompressing, append the compressed buffer as-is.
                decompressedData.append(compressedData);
            }

            // Optionally write out test files for COD9.
            if (game == "COD9") {
                QFile testFile("exports/" + QString("%1.out").arg(sectionIndex));
                if(testFile.open(QIODevice::WriteOnly)) {
                    testFile.write(decompressedData);
                    testFile.close();
                }
            }

            sectionIndex++;
        }

        // For COD9, write out the complete decompressed zone for testing.
        if (false && game == "COD9") {
            QFile testFile("exports/test.zone");
            if(testFile.open(QIODevice::WriteOnly)) {
                testFile.write(decompressedData);
                testFile.close();
            }
        }

        // Load the zone file with the decompressed data (using an Xbox platform flag).
        zoneFile.Load(decompressedData, fileStem.section('.', 0, 0) + ".zone", FF_PLATFORM_XBOX);
    } else if (game == "COD2") {
        Utils::ReadUntilHex(&fastFileStream, "78");
        QByteArray compressedData = aData.mid(fastFileStream.device()->pos());
        QByteArray decompressedData = Compressor::DecompressZLIB(compressedData);

        QFile testFile("exports/" + fileStem.split('.')[0] + ".zone");
        if(testFile.open(QIODevice::WriteOnly)) {
            testFile.write(decompressedData);
            testFile.close();
        }

        // Load the zone file with the decompressed data (using an Xbox platform flag).
        zoneFile.Load(decompressedData, fileStem.section('.', 0, 0) + ".zone", FF_PLATFORM_XBOX, FF_GAME_COD2);
    }

    return true;
}



bool FastFile::Load(const QString aFilePath) {
    if (aFilePath.isEmpty()) {
        return false;
    }

    // Check fastfile can be read
    QFile *file = new QFile(aFilePath);
    if (!file->open(QIODevice::ReadOnly)) {
        qDebug() << QString("Error: Failed to open FastFile: %1!").arg(aFilePath);
        return false;
    }

    // Decompress fastfile and close
    const QString fastFileStem = aFilePath.section("/", -1, -1);
    fileStem = fastFileStem;
    if (!Load(file->readAll())) {
        qDebug() << "Error: Failed to load fastfile: " << fastFileStem;
        return false;
    }

    file->close();

    // Open zone file after decompressing ff and writing
    return true;
}

FF_COMPANY FastFile::pParseFFCompany(QDataStream *afastFileStream) {
    // Check for null datastream ptr
    if (!afastFileStream) { return COMPANY_NONE; }
    // Parse company
    QByteArray companyData(2, Qt::Uninitialized);
    afastFileStream->readRawData(companyData.data(), 2);
    if (companyData == "IW") {
        qDebug() << "Company found: 'INFINITY_WARD'";
        return COMPANY_INFINITY_WARD;
    } else if (companyData == "TA") {
        qDebug() << "Company found: 'TREYARCH'";
        return COMPANY_TREYARCH;
    } else if (companyData == "Sl") {
        qDebug() << "Company found: 'SLEDGEHAMMER'";
        return COMPANY_SLEDGEHAMMER;
    } else if (companyData == "NX") {
        qDebug() << "Company found: 'NEVERSOFT'";
        return COMPANY_NEVERSOFT;
    } else {
        qDebug() << QString("Failed to find company, found '%1'!").arg(companyData);
    }
    return COMPANY_NONE;
}

FF_FILETYPE FastFile::pParseFFFileType(QDataStream *afastFileStream) {
    // Parse filetype
    QByteArray fileTypeData(2, Qt::Uninitialized);
    afastFileStream->readRawData(fileTypeData.data(), 2);
    if (fileTypeData == "ff") {
        qDebug() << "File type found: 'FAST_FILE'";
        return FILETYPE_FAST_FILE;
    } else {
        qDebug() << "Failed to find file type!";
    }
    return FILETYPE_NONE;
}

FF_SIGNAGE FastFile::pParseFFSignage(QDataStream *afastFileStream) {
    // Parse filetype
    QByteArray signedData(1, Qt::Uninitialized);
    afastFileStream->readRawData(signedData.data(), 1);
    if (signedData == "u") {
        qDebug() << "Found valid signage: Unsigned";
        return SIGNAGE_UNSIGNED;
    } else if (signedData == "0" || signedData == "x") {
        qDebug() << "Found valid signage: Signed";
        return SIGNAGE_SIGNED;
    } else {
        qDebug() << "Failed to determine signage of fastfile!";
    }
    return SIGNAGE_NONE;
}

QString FastFile::pParseFFMagic(QDataStream *afastFileStream) {
    // Parse magic
    QByteArray magicData(3, Qt::Uninitialized);
    afastFileStream->readRawData(magicData.data(), 3);
    if (magicData == "100") {
        qDebug() << QString("Found valid magic: '%1'").arg(magicData);
        return magicData;
    } else {
        qDebug() << "Magic invalid!";
    }
    return "";
}

quint32 FastFile::pParseFFVersion(QDataStream *afastFileStream) {
    // Parse version
    quint32 version;
    *afastFileStream >> version;
    qDebug() << QString("Found version: '%1'").arg(version);
    return version;
}

QString FastFile::pCalculateFFPlatform() {
    QString result = "NONE";
    switch (version) {
    case 387:           // PC World at War
    case 473:           // PC Black Ops 1
    case 1:             // PC Modern Warfare 3
    case 147:           // PC Black Ops 2
        result = "PC";
        break;
    case 3640721408:    // Xbox 360 Black Ops 1
    case 2449473536:    // Xbox 360 Black Ops 2
        result = "360";
        break;
    }
    qDebug() << QString("Found platform: '%1'").arg(result);
    return result;
}

QString FastFile::pCalculateFFGame() {
    QString result = "NONE";
    switch (version) {
    case 387:           // PC World at War
        result = "COD5";
        break;
    case 473:           // PC Black Ops 1
        break;
    case 3640721408:    // Xbox 360 Black Ops 1
        result = "COD7";
        break;
    case 1:             // PC Modern Warfare 3
        result = "COD8";
        break;
    case 147:           // PC Black Ops 2
    case 2449473536:    // Xbox 360 Black Ops 2
        result = "COD9";
        break;
    }
    qDebug() << QString("Found game: '%1'").arg(result);
    return result;
}
