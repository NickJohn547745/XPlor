#include <QtTest/QtTest>
#include <QDirIterator>
#include <QFileInfo>

#include "autotest_cod.h"
#include "compression.h"

class AutoTest_COD10_WiiU : public AutoTest_COD {
    Q_OBJECT

    const QString EXPORT_DIR = "./exports/cod10/WiiU";

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

void AutoTest_COD10_WiiU::initTestCase() {
    // Ensure the exports directory exists.
    createDirectory(EXPORT_DIR);
}

void AutoTest_COD10_WiiU::testDecompression_data() {
    AutoTest_COD::testDecompression_data();
}

void AutoTest_COD10_WiiU::testDecompression() {
    QFETCH(QString, fastFilePath);

    // Open the original .ff file.
    QFile testFastFile(fastFilePath);
    QVERIFY2(testFastFile.open(QIODevice::ReadOnly),
             qPrintable("Failed to open test fastfile: " + fastFilePath));
    const QByteArray testFFData = testFastFile.readAll();
    testFastFile.close();

    // Assume the first 12 bytes are a header; the rest is zlib-compressed zone data.
    const QByteArray compressedData = testFFData.mid(12);
    const QByteArray testZoneData = Compression::DecompressZLIB(compressedData);

    // Verify the decompressed data via its embedded zone size.
    QDataStream zoneStream(testZoneData);
    zoneStream.setByteOrder(QDataStream::LittleEndian);
    quint32 zoneSize;
    zoneStream >> zoneSize;
    QVERIFY2(zoneSize + 44 == testZoneData.size(),
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

void AutoTest_COD10_WiiU::testCompression_data() {
    AutoTest_COD::testCompression_data();
}

void AutoTest_COD10_WiiU::testCompression() {
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

void AutoTest_COD10_WiiU::testFactory_data() {
    AutoTest_COD::testFactory_data();
}

void AutoTest_COD10_WiiU::testFactory() {
    QFETCH(QString, fastFilePath);

    const QString testName = "Factory ingest: " + fastFilePath;

    std::shared_ptr<FastFile> fastFile = FastFileFactory::Create(fastFilePath);

    const QString game = fastFile->GetGame();
    bool correctGame = game == "COD10";
    if (!correctGame) {
        recordResult(testName, false);
    }
    QVERIFY2(correctGame
             , qPrintable("Factory parsed wrong game [" + game + "] for fastfile: " + fastFilePath));

    const QString platform = fastFile->GetPlatform();
    bool correctPlatform = platform == "WiiU";
    if (!correctPlatform) {
        recordResult(testName, false);
    }
    QVERIFY2(correctPlatform
             , qPrintable("Factory parsed wrong platform [" + platform + "] for fastfile: " + fastFilePath));

    recordResult(testName, true);
}

void AutoTest_COD10_WiiU::cleanupTestCase() {
    // Any cleanup if necessary.
}

// Don't generate a main() function
#include "autotest_cod10_wiiu.moc"
