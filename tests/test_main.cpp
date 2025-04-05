#include <QtTest/QtTest>
#include "autotest_xplor.cpp"
// #include "autotest_cod1.cpp"
// #include "autotest_cod2.cpp"
// #include "autotest_cod3.cpp"
// #include "autotest_cod4.cpp"
#include "autotest_cod5.cpp"

int main(int argc, char *argv[]) {
    // AutoTest_XPlor test_xplor;
    // if (!QTest::qExec(&test_xplor, argc, argv)) {
    //     return -1;
    // }

    // AutoTest_COD1 test_cod1;
    // if (QTest::qExec(&test_cod1, argc, argv)) {
    //     return -10;
    // }

    // AutoTest_COD2 test_cod2;
    // if (QTest::qExec(&test_cod2, argc, argv)) {
    //     return -10;
    // }

    // AutoTest_COD3 test_cod3;
    // if (QTest::qExec(&test_cod3, argc, argv)) {
    //     return -10;
    // }

    // AutoTest_COD4 test_cod4;
    // if (QTest::qExec(&test_cod4, argc, argv)) {
    //     return -10;
    // }

    AutoTest_COD5 test_cod5;
    if (!QTest::qExec(&test_cod5, argc, argv)) {
        return -10;
    }

    return 0;
}
