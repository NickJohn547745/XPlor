#include <QtTest/QtTest>
#include <QDirIterator>
#include <QFileInfo>

#include "autotest_cod.h"
#include "compression.h"

class AutoTest_COD5_PC : public AutoTest_COD {
    Q_OBJECT

    const QString EXPORT_DIR = "./exports/cod5/pc";

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

void AutoTest_COD5_PC::initTestCase() {
    // Ensure the exports directory exists.
    createDirectory(EXPORT_DIR);
}

void AutoTest_COD5_PC::testDecompression_data() {
    QTest::addColumn<QString>("fastFilePath_cod5_pc");

    QStringList ffFiles = findFastFiles(getFastFileDirectory());
    for (const QString &filePath : ffFiles) {
        QString fileName = QFileInfo(filePath).fileName();
        QTest::newRow(qPrintable(fileName)) << filePath;
    }
}

void AutoTest_COD5_PC::testDecompression() {
    QFETCH(QString, fastFilePath_cod5_pc);

    // Open the original .ff file.
    QFile testFastFile(fastFilePath_cod5_pc);
    QVERIFY2(testFastFile.open(QIODevice::ReadOnly),
             qPrintable("Failed to open test fastfile: " + fastFilePath_cod5_pc));
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
    QVERIFY2(zoneSize + 36 == testZoneData.size(),
             qPrintable("Decompression validation failed for: " + fastFilePath_cod5_pc));

    // Write the decompressed zone data to the exports folder with a .zone extension.
    QFileInfo fi(fastFilePath_cod5_pc);
    QString outputFileName = fi.completeBaseName() + ".zone";
    QString outputFilePath = QDir(EXPORT_DIR).filePath(outputFileName);
    QFile outputFile(outputFilePath);
    QVERIFY2(outputFile.open(QIODevice::WriteOnly),
             qPrintable("Failed to open output file for writing: " + outputFilePath));
    outputFile.write(testZoneData);
    outputFile.close();
}

void AutoTest_COD5_PC::testCompression_data() {
    QTest::addColumn<QString>("zoneFilePath_cod5_pc");

    QStringList zoneFiles = findZoneFiles(getZoneFileDirectory());
    for (const QString &filePath : zoneFiles) {
        QString fileName = QFileInfo(filePath).fileName();
        QTest::newRow(qPrintable(fileName)) << filePath;
    }
}

void AutoTest_COD5_PC::testCompression() {
    QFETCH(QString, zoneFilePath_cod5_pc);

    QFile zoneFile(zoneFilePath_cod5_pc);
    QVERIFY2(zoneFile.open(QIODevice::ReadOnly), qPrintable("Failed to open zone file: " + zoneFilePath_cod5_pc));
    QByteArray decompressedData = zoneFile.readAll();
    zoneFile.close();

    QFileInfo fi(zoneFilePath_cod5_pc);
    QString originalFFPath = QDir(getFastFileDirectory()).filePath(fi.completeBaseName() + ".ff");

    QFile originalFile(originalFFPath);
    QVERIFY2(originalFile.open(QIODevice::ReadOnly), qPrintable("Failed to open original .ff file: " + originalFFPath));
    QByteArray originalFFData = originalFile.readAll();
    originalFile.close();

    QByteArray header = originalFFData.left(12);

    QByteArray newCompressedData = Compression::CompressZLIBWithSettings(decompressedData, Z_BEST_SPEED);

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

void AutoTest_COD5_PC::cleanupTestCase() {
    // Any cleanup if necessary.
}

// Don't generate a main() function
#include "autotest_cod5_pc.moc"
