#include <QtTest/QtTest>

class AutoTest_COD : public QObject {
    Q_OBJECT

private slots:
    virtual void testAddition() = 0;
    virtual void testString() = 0;
};

// Don't generate a main() function
#include "autotest_cod.moc"
