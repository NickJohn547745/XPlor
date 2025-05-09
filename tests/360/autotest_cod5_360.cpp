#include <QtTest/QtTest>
#include <QDirIterator>
#include <QFileInfo>

#include "fastfile_factory.h"
#include "autotest_cod.h"
#include "compression.h"

class AutoTest_COD5_360 : public AutoTest_COD {
    Q_OBJECT

    const QString EXPORT_DIR = "./exports/cod5/360";

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

void AutoTest_COD5_360::initTestCase() {
    // Ensure the exports directory exists.
    createDirectory(EXPORT_DIR);
}

void AutoTest_COD5_360::testDecompression_data() {
    QTest::addColumn<QString>("fastFilePath_cod5_360");

    QStringList ffFiles = findFastFiles(getFastFileDirectory());
    int ffCount = 0;
    for (const QString &filePath : ffFiles) {
        QString fileName = QFileInfo(filePath).fileName();
        QTest::newRow(qPrintable(fileName)) << filePath;
        ffCount++;

        if (ffCount == FILE_MAX) { break; }
    }
}

void AutoTest_COD5_360::testDecompression() {
    QFETCH(QString, fastFilePath_cod5_360);
    return;

    const QString testName = "Decompress: " + fastFilePath_cod5_360;

    // Open the original .ff file.
    QFile testFastFile(fastFilePath_cod5_360);
    QVERIFY2(testFastFile.open(QIODevice::ReadOnly),
             qPrintable("Failed to open test fastfile: " + fastFilePath_cod5_360));
    const QByteArray testFFData = testFastFile.readAll();
    testFastFile.close();

    // Assume the first 12 bytes are a header; the rest is zlib-compressed zone data.
    const QByteArray compressedData = testFFData.mid(12);
    const QByteArray testZoneData = Compression::DecompressZLIB(compressedData);

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
             qPrintable("Decompression validation failed for: " + fastFilePath_cod5_360));

    // Write the decompressed zone data to the exports folder with a .zone extension.
    QFileInfo fi(fastFilePath_cod5_360);
    QString outputFileName = fi.completeBaseName() + ".zone";
    QString outputFilePath = QDir(EXPORT_DIR).filePath(outputFileName);
    QFile outputFile(outputFilePath);
    QVERIFY2(outputFile.open(QIODevice::WriteOnly),
             qPrintable("Failed to open output file for writing: " + outputFilePath));
    outputFile.write(testZoneData);
    outputFile.close();
}

void AutoTest_COD5_360::testCompression_data() {
    QTest::addColumn<QString>("zoneFilePath_cod5_360");

    QStringList zoneFiles = findZoneFiles(getZoneFileDirectory());
    int zoneCount = 0;
    for (const QString &filePath : zoneFiles) {
        QString fileName = QFileInfo(filePath).fileName();
        QTest::newRow(qPrintable(fileName)) << filePath;
        zoneCount++;

        if (zoneCount == FILE_MAX) { break; }
    }
}

void AutoTest_COD5_360::testCompression() {
    QFETCH(QString, zoneFilePath_cod5_360);

    QFile zoneFile(zoneFilePath_cod5_360);
    QVERIFY2(zoneFile.open(QIODevice::ReadOnly), qPrintable("Failed to open zone file: " + zoneFilePath_cod5_360));
    QByteArray decompressedData = zoneFile.readAll();
    zoneFile.close();

    QFileInfo fi(zoneFilePath_cod5_360);
    QString originalFFPath = QDir(getFastFileDirectory()).filePath(fi.completeBaseName() + ".ff");

    QFile originalFile(originalFFPath);
    QVERIFY2(originalFile.open(QIODevice::ReadOnly), qPrintable("Failed to open original .ff file: " + originalFFPath));
    QByteArray originalFFData = originalFile.readAll();
    originalFile.close();

    QByteArray header = originalFFData.left(12);

    QByteArray newCompressedData;// = Compressor::CompressZLIB(decompressedData, Z_BEST_COMPRESSION);
    newCompressedData = Compression::CompressZLIBWithSettings(decompressedData, Z_BEST_SPEED, MAX_WBITS, 8, Z_DEFAULT_STRATEGY, {});

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

void AutoTest_COD5_360::testFactory_data() {
    QTest::addColumn<QString>("fastFilePath_cod5_360");

    QStringList ffFiles = findFastFiles(getFastFileDirectory());
    int ffCount = 0;
    for (const QString &filePath : ffFiles) {
        QString fileName = QFileInfo(filePath).fileName();
        QTest::newRow(qPrintable(fileName)) << filePath;
        ffCount++;

        if (ffCount == FILE_MAX) { break; }
    }
}

void AutoTest_COD5_360::testFactory() {
    QFETCH(QString, fastFilePath_cod5_360);

    const QString testName = "Create w/ factory: " + fastFilePath_cod5_360;

    std::shared_ptr<FastFile> fastFile = FastFileFactory::Create(fastFilePath_cod5_360);

    bool correctPlatform = fastFile->GetPlatform() == "360";
    if (!correctPlatform) {
        recordResult(testName, false);
    }
    QVERIFY2(correctPlatform
             , qPrintable("Factory created fastfile for platform: " + fastFile->GetPlatform()));

    bool correctGame = fastFile->GetGame() == "COD5";
    if (!correctGame) {
        recordResult(testName, false);
    }
    QVERIFY2(correctGame
             , qPrintable("Factory created fastfile for game: " + fastFile->GetGame()));

    recordResult(testName, true);
}

void AutoTest_COD5_360::cleanupTestCase() {
    // Any cleanup if necessary.
}

// Don't generate a main() function
#include "autotest_cod5_360.moc"
