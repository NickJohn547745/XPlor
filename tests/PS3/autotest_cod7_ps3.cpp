#include <QtTest/QtTest>
#include <QDirIterator>
#include <QFileInfo>

#include "autotest_cod.h"
#include "compression.h"
#include "encryption.h"

class AutoTest_COD7_PS3 : public AutoTest_COD {
    Q_OBJECT

    const QString EXPORT_DIR = "./exports/cod7/PS3";

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

void AutoTest_COD7_PS3::initTestCase() {
    // Ensure the exports directory exists.
    createDirectory(EXPORT_DIR);
}

void AutoTest_COD7_PS3::testDecompression_data() {
    AutoTest_COD::testDecompression_data();
}

void AutoTest_COD7_PS3::testDecompression() {
    QFETCH(QString, fastFilePath);

    const QString testName = "Decompress: " + fastFilePath;

    // Open the original .ff file.
    QFile testFastFile(fastFilePath);
    QVERIFY2(testFastFile.open(QIODevice::ReadOnly),
             qPrintable("Failed to open test fastfile: " + fastFilePath));
    const QByteArray testFFData = testFastFile.readAll();
    testFastFile.close();

    QByteArray decompressedData;
    QByteArray key = QByteArray::fromHex("46D3F997F29C9ACE175B0DAE3AB8C0C1B8E423E2E3BF7E3C311EA35245BF193A");

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

void AutoTest_COD7_PS3::testCompression_data() {
    AutoTest_COD::testCompression_data();
}

void AutoTest_COD7_PS3::testCompression() {
    QFETCH(QString, zoneFilePath);

    QFile zoneFile(zoneFilePath);
    QVERIFY2(zoneFile.open(QIODevice::ReadOnly), qPrintable("Failed to open zone file: " + zoneFilePath));
    QByteArray decompressedData = zoneFile.readAll();
    zoneFile.close();

    QFileInfo fi(zoneFilePath);
    QString originalFFPath = QDir(getFastFileDirectory()).filePath(fi.completeBaseName() + ".ff");

    QFile originalFile(originalFFPath);
    QVERIFY2(originalFile.open(QIODevice::ReadOnly), qPrintable("Failed to open original .ff file: " + originalFFPath));
    QByteArray originalFFData = originalFile.readAll();
    originalFile.close();

    QByteArray header = originalFFData.left(12);

    QByteArray newCompressedData;// = Compressor::CompressZLIB(decompressedData, Z_BEST_COMPRESSION);
    newCompressedData = Compression::CompressZLIBWithSettings(decompressedData, Z_BEST_COMPRESSION, MAX_WBITS, 8, Z_DEFAULT_STRATEGY, {});

    int remainder = (newCompressedData.size() + 12) % 32;
    if (remainder != 0) {
        int paddingNeeded = 32 - remainder;
        newCompressedData.append(QByteArray(paddingNeeded, '\0'));
    }

    QByteArray recompressedData = header + newCompressedData;

    QString recompressedFilePath = QDir(EXPORT_DIR).filePath(fi.completeBaseName() + ".ff");
    QFile recompressedFile(recompressedFilePath);
    QVERIFY2(recompressedFile.open(QIODevice::WriteOnly), qPrintable("Failed to write recompressed file."));
    recompressedFile.write(recompressedData);
    recompressedFile.close();

    QCOMPARE(recompressedData, originalFFData);
}

void AutoTest_COD7_PS3::testFactory_data() {
    AutoTest_COD::testFactory_data();
}

void AutoTest_COD7_PS3::testFactory() {
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
    bool correctPlatform = platform == "PS3";
    if (!correctPlatform) {
        recordResult(testName, false);
    }
    QVERIFY2(correctPlatform
             , qPrintable("Factory parsed wrong platform [" + platform + "] for fastfile: " + fastFilePath));

    recordResult(testName, true);
}

void AutoTest_COD7_PS3::cleanupTestCase() {
    // Any cleanup if necessary.
}

// Don't generate a main() function
#include "autotest_cod7_ps3.moc"
