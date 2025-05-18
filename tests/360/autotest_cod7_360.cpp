#include <QtTest/QtTest>
#include <QDirIterator>
#include <QFileInfo>

#include "autotest_cod.h"
#include "compression.h"
#include "encryption.h"

class AutoTest_COD7_360 : public AutoTest_COD {
    Q_OBJECT

    const QString EXPORT_DIR = "./exports/cod7/360";

private slots:
    void initTestCase();

    void testDecompression_data();
    void testDecompression();

    void testCompression_data();
    void testCompression();

    void testFactory_data();
    void testFactory();

    void cleanupTestCase();
};

void AutoTest_COD7_360::initTestCase() {
    // Ensure the exports directory exists.
    createDirectory(EXPORT_DIR);
}

void AutoTest_COD7_360::testDecompression_data() {
    AutoTest_COD::testDecompression_data();
}

void AutoTest_COD7_360::testDecompression() {
    QFETCH(QString, fastFilePath);

    const QString testName = "Decompress: " + fastFilePath;

    // Open the original .ff file.
    QFile testFastFile(fastFilePath);
    QVERIFY2(testFastFile.open(QIODevice::ReadOnly),
             qPrintable("Failed to open test fastfile: " + fastFilePath));
    const QByteArray testFFData = testFastFile.readAll();
    testFastFile.close();

    QByteArray decompressedData;
    QByteArray key = QByteArray::fromHex("1ac1d12d527c59b40eca619120ff8217ccff09cd16896f81b829c7f52793405d");

    // Create a QDataStream on the input data.
    QDataStream fastFileStream(testFFData);
    fastFileStream.setByteOrder(QDataStream::BigEndian);
    fastFileStream.skipRawData(16);

    // Read the 8-byte magic.
    QByteArray fileMagic(8, Qt::Uninitialized);
    fastFileStream.readRawData(fileMagic.data(), 8);
    QVERIFY2(fileMagic == "PHEEBs71",
             qPrintable("Invalid fast file magic: " + fileMagic));
    fastFileStream.skipRawData(4);

    // Read IV table name (32 bytes).
    QByteArray fileName(32, Qt::Uninitialized);
    fastFileStream.readRawData(fileName.data(), 32);

    // Build the IV table from the fileName.
    QByteArray ivTable = Encryption::InitIVTable(fileName);

    // Skip the RSA signature (256 bytes).
    QByteArray rsaSignature(256, Qt::Uninitialized);
    fastFileStream.readRawData(rsaSignature.data(), 256);

    // Now the stream should be positioned at 0x13C, where sections begin.
    int sectionIndex = 0;
    while (true) {
        qint32 sectionSize = 0;
        fastFileStream >> sectionSize;
        if (sectionSize == 0)
            break;

        // Read the section data.
        QByteArray sectionData;
        sectionData.resize(sectionSize);
        fastFileStream.readRawData(sectionData.data(), sectionSize);

        // Compute the IV for this section.
        QByteArray iv = Encryption::GetIV(ivTable, sectionIndex);

        // Decrypt the section using Salsa20.
        QByteArray decData = Encryption::salsa20DecryptSection(sectionData, key, iv);

        // Compute SHA1 hash of the decrypted data.
        QByteArray sectionHash = QCryptographicHash::hash(decData, QCryptographicHash::Sha1);

        // Update the IV table based on the section hash.
        Encryption::UpdateIVTable(ivTable, sectionIndex, sectionHash);

        // Build a compressed data buffer by prepending the two-byte zlib header.
        decompressedData.append(Compression::DecompressDeflate(decData));

        sectionIndex++;
    }


    const QByteArray testZoneData = decompressedData;

    // Verify the decompressed data via its embedded zone size.
    QDataStream zoneStream(testZoneData);
    zoneStream.setByteOrder(QDataStream::BigEndian);
    quint32 zoneSize;
    zoneStream >> zoneSize;
    if (abs(zoneSize - testZoneData.size()) != 36) {
        qDebug() << "Zone Size: " << zoneSize;
        qDebug() << "Test zone Size: " << testZoneData.size();
        qDebug() << "Difference: " << abs(zoneSize - testZoneData.size());
    }
    QVERIFY2(zoneSize + 36 == testZoneData.size(),
             qPrintable("Decompression validation failed for: " + fastFilePath));

    // Write the decompressed zone data to the exports folder with a .zone extension.
    QFileInfo fi(fastFilePath);
    QString outputFileName = fi.completeBaseName() + ".zone";
    QString outputFilePath = QDir(EXPORT_DIR).filePath(outputFileName);
    QFile outputFile(outputFilePath);
    QVERIFY2(outputFile.open(QIODevice::WriteOnly),
             qPrintable("Failed to open output file for writing: " + outputFilePath));
    outputFile.write(testZoneData);
    outputFile.close();
}

void AutoTest_COD7_360::testCompression_data() {
    AutoTest_COD::testCompression_data();
}

void AutoTest_COD7_360::testCompression() {
    QFETCH(QString, zoneFilePath);

    const QString testName = "Compress: " + zoneFilePath;

    // Open the original .zone file (decompressed zone data).
    QFile zoneFile(zoneFilePath);
    QVERIFY2(zoneFile.open(QIODevice::ReadOnly),
             qPrintable("Failed to open zone file: " + zoneFilePath));
    const QByteArray zoneData = zoneFile.readAll();
    zoneFile.close();

    QByteArray compressedData;
    QByteArray key = QByteArray::fromHex("1ac1d12d527c59b40eca619120ff8217ccff09cd16896f81b829c7f52793405d");

    // Read the original fastfile header to recover metadata (filename, IV table, etc.)
    QString ffPath = zoneFilePath;
    ffPath.replace(".zone", ".ff");
    QFile originalFF(ffPath);
    QVERIFY2(originalFF.open(QIODevice::ReadOnly),
             qPrintable("Failed to open original fastfile: " + ffPath));
    QByteArray header = originalFF.read(0x13C); // Everything up to section data
    originalFF.seek(24); // IV Table starts at 24 (after magic + skip + filename)
    QByteArray fileName(32, Qt::Uninitialized);
    originalFF.read(fileName.data(), 32);
    originalFF.close();

    QByteArray ivTable = Encryption::InitIVTable(fileName);

    // Rebuild sections from zone data
    QDataStream zoneStream(zoneData);
    zoneStream.setByteOrder(QDataStream::BigEndian);
    quint32 zoneSize;
    zoneStream >> zoneSize;

    QByteArray remainingData = zoneData.mid(4); // exclude size field
    const int chunkSize = 0x40000; // 256KB max section size

    QDataStream fastFileStreamOut(&compressedData, QIODevice::WriteOnly);
    fastFileStreamOut.setByteOrder(QDataStream::BigEndian);

    int sectionIndex = 0;
    int offset = 0;
    while (offset < remainingData.size()) {
        int sectionLen = qMin(chunkSize, remainingData.size() - offset);
        QByteArray chunk = remainingData.mid(offset, sectionLen);

        QByteArray deflated = Compression::CompressDeflate(chunk);

        QByteArray iv = Encryption::GetIV(ivTable, sectionIndex);
        QByteArray encrypted = Encryption::salsa20DecryptSection(deflated, key, iv);
        QByteArray sha1 = QCryptographicHash::hash(chunk, QCryptographicHash::Sha1);
        Encryption::UpdateIVTable(ivTable, sectionIndex, sha1);

        fastFileStreamOut << static_cast<qint32>(encrypted.size());
        fastFileStreamOut.writeRawData(encrypted.constData(), encrypted.size());

        offset += sectionLen;
        sectionIndex++;
    }

    // Write 0 section size terminator
    fastFileStreamOut << static_cast<qint32>(0);

    // Combine with header
    QByteArray fullFastFile = header + compressedData;

    // Save re-encoded fastfile
    QFileInfo fi(zoneFilePath);
    QString outputFileName = fi.completeBaseName() + "_recompressed.ff";
    QString outputFilePath = QDir(EXPORT_DIR).filePath(outputFileName);
    QFile outputFile(outputFilePath);
    QVERIFY2(outputFile.open(QIODevice::WriteOnly),
             qPrintable("Failed to open output file for writing: " + outputFilePath));
    outputFile.write(fullFastFile);
    outputFile.close();
}

void AutoTest_COD7_360::testFactory_data() {
    AutoTest_COD::testFactory_data();
}

void AutoTest_COD7_360::testFactory() {
    QFETCH(QString, fastFilePath);

    const QString testName = "Factory ingest: " + fastFilePath;

    std::shared_ptr<FastFile> fastFile = FastFileFactory::Create(fastFilePath);

    const QString game = fastFile->GetGame();
    bool correctGame = game == "COD7";
    if (!correctGame) {
        recordResult(testName, false);
    }
    QVERIFY2(correctGame
             , qPrintable("Factory parsed wrong game [" + game + "] for fastfile: " + fastFilePath));

    const QString platform = fastFile->GetPlatform();
    bool correctPlatform = platform == "360";
    if (!correctPlatform) {
        recordResult(testName, false);
    }
    QVERIFY2(correctPlatform
             , qPrintable("Factory parsed wrong platform [" + platform + "] for fastfile: " + fastFilePath));

    recordResult(testName, true);
}

void AutoTest_COD7_360::cleanupTestCase() {
    // Any cleanup if necessary.
}

// Don't generate a main() function
#include "autotest_cod7_360.moc"
