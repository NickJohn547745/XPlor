#include <QtTest/QtTest>
#include <QDirIterator>
#include <QFileInfo>

#include "autotest_cod.h"
#include "compression.h"
#include "fastfile_factory.h"

class AutoTest_COD2_360 : public AutoTest_COD {
    Q_OBJECT

    const QString EXPORT_DIR = "./exports/cod2/360";

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

void AutoTest_COD2_360::initTestCase() {
    // Ensure the exports directory exists.
    createDirectory(EXPORT_DIR);
}

void AutoTest_COD2_360::testDecompression_data() {
    AutoTest_COD::testDecompression_data();
}

void AutoTest_COD2_360::testDecompression() {
    QFETCH(QString, fastFilePath);

    const QString testName = "Decompress: " + fastFilePath;

    // Open the original .ff file.
    QFile testFastFile(fastFilePath);
    bool fastFileOpened = testFastFile.open(QIODevice::ReadOnly);
    if (!fastFileOpened) {
        recordResult(testName, false);
    }
    QVERIFY2(fastFileOpened
             , qPrintable("Failed to open test fastfile: " + fastFilePath));
    const QByteArray testFFData = testFastFile.readAll();
    testFastFile.close();

    // Assume the first 12 bytes are a header; the rest is zlib-compressed zone data.
    const QByteArray compressedData = testFFData.mid(20);
    const QByteArray testZoneData = Compression::DecompressZLIB(compressedData);

    // Verify the decompressed data via its embedded zone size.
    QDataStream zoneStream(testZoneData);
    zoneStream.setByteOrder(QDataStream::LittleEndian);
    quint32 zoneSize;
    zoneStream >> zoneSize;
    // TODO: Find new way to verify as cod2 doesn't store size in zone file
    //QVERIFY2(zoneSize + 44 == testZoneData.size(),
    //         qPrintable("Decompression validation failed for: " + fastFilePath));

    // Write the decompressed zone data to the exports folder with a .zone extension.
    QFileInfo fi(fastFilePath);
    QString outputFileName = fi.completeBaseName() + ".zone";
    QString outputFilePath = QDir(EXPORT_DIR).filePath(outputFileName);
    QFile outputFile(outputFilePath);
    bool zoneFileOpened = outputFile.open(QIODevice::WriteOnly);
    if (!zoneFileOpened) {
        recordResult(testName, false);
    }
    QVERIFY2(zoneFileOpened,
             qPrintable("Failed to open output zone file for writing: " + outputFilePath));
    outputFile.write(testZoneData);
    outputFile.close();

    recordResult(testName, true);
}

void AutoTest_COD2_360::testCompression_data() {
    AutoTest_COD::testCompression_data();
}

void AutoTest_COD2_360::testCompression() {
    QFETCH(QString, zoneFilePath);

    const QString testName = "Compress: " + zoneFilePath;

    QFile zoneFile(zoneFilePath);
    bool zoneFileOpened = zoneFile.open(QIODevice::ReadOnly);
    if (!zoneFileOpened) {
        recordResult(testName, false);
    }
    QVERIFY2(zoneFileOpened, qPrintable("Failed to open zone file: " + zoneFilePath));
    QByteArray decompressedData = zoneFile.readAll();
    zoneFile.close();

    QFileInfo fi(zoneFilePath);
    QString originalFFPath = QDir(getFastFileDirectory()).filePath(fi.completeBaseName() + ".ff");

    QFile originalFile(originalFFPath);
    bool origFileOpened = originalFile.open(QIODevice::ReadOnly);
    if (!origFileOpened) {
        recordResult(testName, false);
    }
    QVERIFY2(origFileOpened, qPrintable("Failed to open original .ff file: " + originalFFPath));
    QByteArray originalFFData = originalFile.readAll();
    originalFile.close();

    QByteArray header = originalFFData.left(20);

    QByteArray recompressedData = header + Compression::CompressZLIB(decompressedData);

    QString recompressedFilePath = QDir(EXPORT_DIR).filePath(fi.completeBaseName() + ".ff");
    QFile recompressedFile(recompressedFilePath);
    bool fastFileOpened = recompressedFile.open(QIODevice::WriteOnly);
    if (!fastFileOpened) {
        recordResult(testName, false);
    }
    QVERIFY2(fastFileOpened, qPrintable("Failed to write recompressed file."));
    recompressedFile.write(recompressedData);
    recompressedFile.close();

    bool dataMatches = recompressedData == originalFFData;
    if (!dataMatches) {
        recordResult(testName, false);
    }
    QCOMPARE(recompressedData, originalFFData);

    recordResult(testName, true);
}

void AutoTest_COD2_360::testFactory_data() {
    AutoTest_COD::testFactory_data();
}

void AutoTest_COD2_360::testFactory() {
    QFETCH(QString, fastFilePath);

    const QString testName = "Factory ingest: " + fastFilePath;

    std::shared_ptr<FastFile> fastFile = FastFileFactory::Create(fastFilePath);

    const QString game = fastFile->GetGame();
    bool correctGame = game == "COD2";
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

void AutoTest_COD2_360::cleanupTestCase() {
    // Any cleanup if necessary.
}

// Don't generate a main() function
#include "autotest_cod2_360.moc"
