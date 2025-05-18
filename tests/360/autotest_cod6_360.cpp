#include <QtTest/QtTest>
#include <QDirIterator>
#include <QFileInfo>

#include "autotest_cod.h"
#include "compression.h"

class AutoTest_COD6_360 : public AutoTest_COD {
    Q_OBJECT

    const QString EXPORT_DIR = "./exports/cod6/360";

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

void AutoTest_COD6_360::initTestCase() {
    // Ensure the exports directory exists.
    createDirectory(EXPORT_DIR);
}

void AutoTest_COD6_360::testDecompression_data() {
    AutoTest_COD::testDecompression_data();
}

void AutoTest_COD6_360::testDecompression() {
    QFETCH(QString, fastFilePath);

    const QString testName = "Decompress: " + fastFilePath;

    // Open the original .ff file.
    QFile testFastFile(fastFilePath);
    QVERIFY2(testFastFile.open(QIODevice::ReadOnly),
             qPrintable("Failed to open test fastfile: " + fastFilePath));
    const QByteArray testFFData = testFastFile.readAll();
    testFastFile.close();

    const QString magic = testFFData.mid(0, 12);
    QVERIFY2(magic.contains("IWffu100"),
             qPrintable("Encountered signed fastfile: " + magic));

    QByteArray pattern;
    pattern.append(static_cast<unsigned char>(0x78));
    pattern.append(static_cast<unsigned char>(0xDA));
    pattern.append(static_cast<unsigned char>(0xEC));

    int index = testFFData.indexOf(pattern);
    QByteArray compressedData = testFFData.mid(index);
    QByteArray testZoneData = Compression::DecompressZLIB(compressedData);

    //while (index != -1 && testZoneData.isEmpty()) {
    //    compressedData = testFFData.mid(index);
    //    testZoneData = Compression::DecompressZLIB(compressedData);

    //    index = testFFData.indexOf(pattern, index + 2);
    //}

    QVERIFY2(!testZoneData.isEmpty(),
             qPrintable("Zlib decompression failed!"));

    // Verify the decompressed data via its embedded zone size.
    QDataStream zoneStream(testZoneData);
    zoneStream.setByteOrder(QDataStream::BigEndian);
    quint32 zoneSize;
    zoneStream >> zoneSize;
    if (abs(zoneSize - testZoneData.size()) != 32) {
        qDebug() << "Zone Size: " << zoneSize;
        qDebug() << "Test zone Size: " << testZoneData.size();
        qDebug() << "Difference: " << abs(zoneSize - testZoneData.size());
    }
    QVERIFY2(zoneSize + 32 == testZoneData.size(),
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

void AutoTest_COD6_360::testCompression_data() {
    AutoTest_COD::testCompression_data();
}

void AutoTest_COD6_360::testCompression() {
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

    QByteArray pattern;
    pattern.append(static_cast<unsigned char>(0x78));
    pattern.append(static_cast<unsigned char>(0xDA));
    pattern.append(static_cast<unsigned char>(0xEC));

    int zlibOffset = originalFFData.indexOf(pattern);

    QByteArray header = originalFFData.mid(0, zlibOffset);

    QByteArray newCompressedData;// = Compressor::CompressZLIB(decompressedData, Z_BEST_COMPRESSION);
    newCompressedData = Compression::CompressZLIBWithSettings(decompressedData, Z_BEST_COMPRESSION, MAX_WBITS, 8, Z_DEFAULT_STRATEGY, {});

    QByteArray recompressedData = header + newCompressedData;

    QString recompressedFilePath = QDir(EXPORT_DIR).filePath(fi.completeBaseName() + ".ff");
    QFile recompressedFile(recompressedFilePath);
    QVERIFY2(recompressedFile.open(QIODevice::WriteOnly), qPrintable("Failed to write recompressed file."));
    recompressedFile.write(recompressedData);
    recompressedFile.close();

    QCOMPARE(recompressedData, originalFFData);
}

void AutoTest_COD6_360::testFactory_data() {
    AutoTest_COD::testFactory_data();
}

void AutoTest_COD6_360::testFactory() {
    QFETCH(QString, fastFilePath);

    const QString testName = "Factory ingest: " + fastFilePath;

    std::shared_ptr<FastFile> fastFile = FastFileFactory::Create(fastFilePath);

    const QString game = fastFile->GetGame();
    bool correctGame = game == "COD6";
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

void AutoTest_COD6_360::cleanupTestCase() {
    // Any cleanup if necessary.
}

// Don't generate a main() function
#include "autotest_cod6_360.moc"
