#include <QtTest/QtTest>

class AutoTest_XPlor : public QObject {
    Q_OBJECT

private slots:
    void testAddition();
    void testString();
};

void AutoTest_XPlor::testAddition() {
    QCOMPARE(2 + 2, 4);
}

void AutoTest_XPlor::testString() {
    QString str = "hello";
    QVERIFY(str.startsWith("h"));
}

#include "autotest_xplor.moc"
