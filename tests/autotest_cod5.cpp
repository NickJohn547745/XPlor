#include <QtTest/QtTest>

#include "autotest_cod.cpp"

class AutoTest_COD5 : public AutoTest_COD {
    Q_OBJECT

private slots:
    void testAddition();
    void testString();
};

void AutoTest_COD5::testAddition() {
    QCOMPARE(2 + 2, 4);
}

void AutoTest_COD5::testString() {
    QString str = "hello";
    QVERIFY(str.startsWith("h"));
}

// Don't generate a main() function
#include "autotest_cod5.moc"
