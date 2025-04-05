#include <QtTest/QtTest>

#include "autotest_cod.cpp"
#include "compressor.h"

class AutoTest_COD5 : public AutoTest_COD {
    Q_OBJECT

private slots:
    void testDecompression();

private:
    //void testDecompression();
};

void AutoTest_COD5::testDecompression() {
    qDebug() << "Available folders:" << QDir("qrc:/").entryList();

    const QString testStem = "ber1";
    const QString testFFPath = QString(":/cod5/fastfile/%1.ff").arg(testStem);
    QFile testFastFile(testFFPath);
    if (!testFastFile.open(QIODevice::ReadOnly)) {
        qDebug() << "Failed to open test fastfile: " << testFFPath;
    }

    const QByteArray testFFData(testFastFile.readAll());
    const QByteArray testZoneData = Compressor::DecompressZLIB(testFFData.mid(12));

    const QString testZonePath = QString(":/cod5/zonefile/%1.zone").arg(testStem);
    QFile testZoneFile(testZonePath);
    if (!testZoneFile.open(QIODevice::ReadOnly)) {
        qDebug() << "Failed to open true zonefile: " << testZonePath;
    }
    const QByteArray trueZoneData(testZoneFile.readAll());

    QCOMPARE(testZoneData, trueZoneData);
}

// Don't generate a main() function
#include "autotest_cod5.moc"
