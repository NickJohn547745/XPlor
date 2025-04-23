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
    // Data-driven test for decompression
    void testDecompression_data();
    void testDecompression();
    // Data-driven test for recompression (compression)
    void testCompression_data();
    void testCompression();
    void cleanupTestCase();
};

void AutoTest_COD6_360::initTestCase() {
    // Ensure the exports directory exists.
    createDirectory(EXPORT_DIR);
}

void AutoTest_COD6_360::testDecompression_data() {
    QTest::addColumn<QString>("fastFilePath_cod6_360");

    QStringList ffFiles = findFastFiles(getFastFileDirectory());
    for (const QString &filePath : ffFiles) {
        QString fileName = QFileInfo(filePath).fileName();
        QTest::newRow(qPrintable(fileName)) << filePath;
    }
}

void AutoTest_COD6_360::testDecompression() {
    QFETCH(QString, fastFilePath_cod6_360);

    const QString testName = "Decompress: " + fastFilePath_cod6_360;

    // Open the original .ff file.
    QFile testFastFile(fastFilePath_cod6_360);
    QVERIFY2(testFastFile.open(QIODevice::ReadOnly),
             qPrintable("Failed to open test fastfile: " + fastFilePath_cod6_360));
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
             qPrintable("Decompression validation failed for: " + fastFilePath_cod6_360));

    // Write the decompressed zone data to the exports folder with a .zone extension.
    QFileInfo fi(fastFilePath_cod6_360);
    QString outputFileName = fi.completeBaseName() + ".zone";
    QString outputFilePath = QDir(EXPORT_DIR).filePath(outputFileName);
    QFile outputFile(outputFilePath);
    QVERIFY2(outputFile.open(QIODevice::WriteOnly),
             qPrintable("Failed to open output file for writing: " + outputFilePath));
    outputFile.write(testZoneData);
    outputFile.close();
}

void AutoTest_COD6_360::testCompression_data() {
    QTest::addColumn<QString>("zoneFilePath_cod6_360");

    QStringList zoneFiles = findZoneFiles(getZoneFileDirectory());
    for (const QString &filePath : zoneFiles) {
        QString fileName = QFileInfo(filePath).fileName();
        QTest::newRow(qPrintable(fileName)) << filePath;
    }
}

void AutoTest_COD6_360::testCompression() {
    QFETCH(QString, zoneFilePath_cod6_360);

    QFile zoneFile(zoneFilePath_cod6_360);
    QVERIFY2(zoneFile.open(QIODevice::ReadOnly), qPrintable("Failed to open zone file: " + zoneFilePath_cod6_360));
    QByteArray decompressedData = zoneFile.readAll();
    zoneFile.close();

    QFileInfo fi(zoneFilePath_cod6_360);
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

void AutoTest_COD6_360::cleanupTestCase() {
    // Any cleanup if necessary.
}

// Don't generate a main() function
#include "autotest_cod6_360.moc"
