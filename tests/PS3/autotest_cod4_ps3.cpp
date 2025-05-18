#include <QtTest/QtTest>
#include <QDirIterator>
#include <QFileInfo>

#include "autotest_cod.h"
#include "compression.h"

class AutoTest_COD4_PS3 : public AutoTest_COD {
    Q_OBJECT

    const QString EXPORT_DIR = "./exports/cod4/PS3";

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

void AutoTest_COD4_PS3::initTestCase() {
    // Ensure the exports directory exists.
    createDirectory(EXPORT_DIR);
}

void AutoTest_COD4_PS3::testDecompression_data() {
    AutoTest_COD::testDecompression_data();
}

void AutoTest_COD4_PS3::testDecompression() {
    QFETCH(QString, fastFilePath);

    QFile testFastFile(fastFilePath);
    QVERIFY2(testFastFile.open(QIODevice::ReadOnly),
             qPrintable("Failed to open test fastfile: " + fastFilePath));
    const QByteArray testFFData = testFastFile.readAll();
    testFastFile.close();

    // Validate header
    QVERIFY2(testFFData.size() > 12, "FastFile too small to contain header");
    QByteArray header = testFFData.left(8);
    QVERIFY2(header == "IWffu100", "Invalid FastFile header!");

    QDataStream headerStream(testFFData.mid(8, 6));
    headerStream.setByteOrder(QDataStream::BigEndian);
    qint32 version;
    qint16 identifier;
    headerStream >> version >> identifier;
    QVERIFY2(version == 1, "Unsupported game version");

    QByteArray decompressed;
    int pos = 12;

    // Loop until EOF or invalid chunk
    while (pos <= testFFData.size()) {
        // Read 2-byte BIG-ENDIAN chunk size
        quint16 chunkSize;
        QDataStream chunkStream(testFFData.mid(pos, 2));
        chunkStream.setByteOrder(QDataStream::BigEndian);
        chunkStream >> chunkSize;

        pos += 2;

        if (chunkSize == 0 || pos + chunkSize > testFFData.size()) {
            qWarning() << "Invalid or incomplete chunk detected, stopping.";
            break;
        }

        const QByteArray compressedChunk = testFFData.mid(pos, chunkSize);

        decompressed.append(Compression::DecompressDeflate(compressedChunk));

        pos += chunkSize;
    }

    // Write decompressed .zone file
    QFileInfo fi(fastFilePath);
    QString outputFileName = fi.completeBaseName() + ".zone";
    QString outputFilePath = QDir(EXPORT_DIR).filePath(outputFileName);
    QFile outputFile(outputFilePath);
    QVERIFY2(outputFile.open(QIODevice::WriteOnly),
             qPrintable("Failed to open output file for writing: " + outputFilePath));
    outputFile.write(decompressed);
    outputFile.close();
}


void AutoTest_COD4_PS3::testCompression_data() {
    AutoTest_COD::testCompression_data();
}

void AutoTest_COD4_PS3::testCompression() {
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
    QByteArray recompressedData = header;

    // Split decompressed data into chunks (optional: same size as original or fixed 0x4000)
    const int chunkSize = 0x4000;
    int offset = 0;

    while (offset < decompressedData.size()) {
        QByteArray chunk = decompressedData.mid(offset, chunkSize);
        offset += chunk.size();

        QByteArray compressedChunk = Compression::CompressDeflate(chunk);
        quint16 length = static_cast<quint16>(compressedChunk.size());

        // Write 2-byte big-endian chunk size
        recompressedData.append(static_cast<char>((length >> 8) & 0xFF));
        recompressedData.append(static_cast<char>(length & 0xFF));

        // Write compressed chunk
        recompressedData.append(compressedChunk);
    }

    // No terminator chunk needed if original didn't have one

    // Save new file
    QString recompressedFilePath = QDir(EXPORT_DIR).filePath(fi.completeBaseName() + ".ff");
    QFile recompressedFile(recompressedFilePath);
    QVERIFY2(recompressedFile.open(QIODevice::WriteOnly), qPrintable("Failed to write recompressed file."));
    recompressedFile.write(recompressedData);
    recompressedFile.close();

    // Validate byte-for-byte match
    QCOMPARE(recompressedData, originalFFData);
}


void AutoTest_COD4_PS3::testFactory_data() {
    AutoTest_COD::testFactory_data();
}

void AutoTest_COD4_PS3::testFactory() {
    QFETCH(QString, fastFilePath);

    const QString testName = "Factory ingest: " + fastFilePath;

    std::shared_ptr<FastFile> fastFile = FastFileFactory::Create(fastFilePath);

    const QString game = fastFile->GetGame();
    bool correctGame = game == "COD4";
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

void AutoTest_COD4_PS3::cleanupTestCase() {
    // Any cleanup if necessary.
}

// Don't generate a main() function
#include "autotest_cod4_ps3.moc"
