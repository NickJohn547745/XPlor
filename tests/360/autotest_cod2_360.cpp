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
    // Data-driven test for decompression
    void testDecompression_data();
    void testDecompression();
    // Data-driven test for recompression (compression)
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
    QTest::addColumn<QString>("fastFilePath_cod2_360");

    QStringList ffFiles = findFastFiles(getFastFileDirectory());
    for (const QString &filePath : ffFiles) {
        QString fileName = QFileInfo(filePath).fileName();
        QTest::newRow(qPrintable(fileName)) << filePath;
    }
}

void AutoTest_COD2_360::testDecompression() {
    QFETCH(QString, fastFilePath_cod2_360);

    const QString testName = "Decompress: " + fastFilePath_cod2_360;

    // Open the original .ff file.
    QFile testFastFile(fastFilePath_cod2_360);
    bool fastFileOpened = testFastFile.open(QIODevice::ReadOnly);
    if (!fastFileOpened) {
        recordResult(testName, false);
    }
    QVERIFY2(fastFileOpened
        , qPrintable("Failed to open test fastfile: " + fastFilePath_cod2_360));
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
    //         qPrintable("Decompression validation failed for: " + fastFilePath_cod2_360));

    // Write the decompressed zone data to the exports folder with a .zone extension.
    QFileInfo fi(fastFilePath_cod2_360);
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
    QTest::addColumn<QString>("zoneFilePath_cod2_360");

    QStringList zoneFiles = findZoneFiles(getZoneFileDirectory());
    for (const QString &filePath : zoneFiles) {
        QString fileName = QFileInfo(filePath).fileName();
        QTest::newRow(qPrintable(fileName)) << filePath;
        break;
    }
}

void AutoTest_COD2_360::testCompression() {
    QFETCH(QString, zoneFilePath_cod2_360);

    const QString testName = "Compress: " + zoneFilePath_cod2_360;

    QFile zoneFile(zoneFilePath_cod2_360);
    bool zoneFileOpened = zoneFile.open(QIODevice::ReadOnly);
    if (!zoneFileOpened) {
        recordResult(testName, false);
    }
    QVERIFY2(zoneFileOpened, qPrintable("Failed to open zone file: " + zoneFilePath_cod2_360));
    QByteArray decompressedData = zoneFile.readAll();
    zoneFile.close();

    QFileInfo fi(zoneFilePath_cod2_360);
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

    QByteArray newCompressedData;// = Compressor::CompressZLIB(decompressedData, Z_BEST_COMPRESSION);
    newCompressedData = Compression::CompressZLIBWithSettings(decompressedData, Z_BEST_COMPRESSION, MAX_WBITS, 8, Z_DEFAULT_STRATEGY, {});

    QByteArray recompressedData = header + newCompressedData;

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
    QTest::addColumn<QString>("fastFilePath_cod2_360");

    QStringList ffFiles = findFastFiles(getFastFileDirectory());
    for (const QString &filePath : ffFiles) {
        QString fileName = QFileInfo(filePath).fileName();
        QTest::newRow(qPrintable(fileName)) << filePath;
    }
}

void AutoTest_COD2_360::testFactory() {
    QFETCH(QString, fastFilePath_cod2_360);

    const QString testName = "Create w/ factory: " + fastFilePath_cod2_360;

    // Open the original .ff file.
    QFile testFastFile(fastFilePath_cod2_360);
    bool fastFileOpened = testFastFile.open(QIODevice::ReadOnly);
    if (!fastFileOpened) {
        recordResult(testName, false);
    }
    QVERIFY2(fastFileOpened
             , qPrintable("Failed to open test fastfile: " + fastFilePath_cod2_360));
    const QByteArray testFFData = testFastFile.readAll();
    testFastFile.close();

    std::shared_ptr<FastFile> fastFile = FastFileFactory::Create(testFFData);

    bool correctPlatform = fastFile->GetPlatform() == "360";
    if (!correctPlatform) {
        recordResult(testName, false);
    }
    QVERIFY2(correctPlatform
             , qPrintable("Factory created fastfile for platform: " + fastFile->GetPlatform()));

    bool correctGame = fastFile->GetGame() == "COD2";
    if (!correctGame) {
        recordResult(testName, false);
    }
    QVERIFY2(correctGame
             , qPrintable("Factory created fastfile for game: " + fastFile->GetGame()));

    recordResult(testName, true);
}

void AutoTest_COD2_360::cleanupTestCase() {
    // Any cleanup if necessary.
}

// Don't generate a main() function
#include "autotest_cod2_360.moc"
