#include <QtTest/QtTest>
//#include "autotest_xplor.cpp"

#include "360/autotest_cod2_360.cpp"
#include "360/autotest_cod4_360.cpp"
#include "360/autotest_cod5_360.cpp"
#include "360/autotest_cod6_360.cpp"
#include "360/autotest_cod7_360.cpp"
#include "360/autotest_cod8_360.cpp"
#include "360/autotest_cod9_360.cpp"
#include "360/autotest_cod10_360.cpp"
#include "360/autotest_cod11_360.cpp"
#include "360/autotest_cod12_360.cpp"

#include "PC/autotest_cod4_pc.cpp"
#include "PC/autotest_cod5_pc.cpp"
#include "PC/autotest_cod6_pc.cpp"
#include "PC/autotest_cod7_pc.cpp"
#include "PC/autotest_cod8_pc.cpp"
#include "PC/autotest_cod9_pc.cpp"
#include "PC/autotest_cod10_pc.cpp"
#include "PC/autotest_cod11_pc.cpp"
#include "PC/autotest_cod12_pc.cpp"

#include "PS3/autotest_cod4_ps3.cpp"
#include "PS3/autotest_cod5_ps3.cpp"
#include "PS3/autotest_cod6_ps3.cpp"
#include "PS3/autotest_cod7_ps3.cpp"
#include "PS3/autotest_cod8_ps3.cpp"
#include "PS3/autotest_cod9_ps3.cpp"
#include "PS3/autotest_cod10_ps3.cpp"
#include "PS3/autotest_cod11_ps3.cpp"
#include "PS3/autotest_cod12_ps3.cpp"

#include "Wii/autotest_cod7_wii.cpp"

#include "WiiU/autotest_cod9_wiiu.cpp"
#include "WiiU/autotest_cod10_wiiu.cpp"

// clearly named defines for filtering logic
#define TEST_EVERYTHING      1

// Global filters
#define TEST_ALL_PLATFORMS   0
#define TEST_ALL_COD_GAMES   0

// individual games
#define TEST_COD2            0
#define TEST_COD4            1
#define TEST_COD5            0
#define TEST_COD6            0
#define TEST_COD7            0
#define TEST_COD8            0
#define TEST_COD9            0
#define TEST_COD10           0
#define TEST_COD11           0
#define TEST_COD12           0

// individual platforms
#define TEST_360             0
#define TEST_PC              0
#define TEST_PS3             0
#define TEST_WII             0
#define TEST_WIIU            0

int main(int argc, char *argv[]) {
    /**********************************/
    /********* XPLOR UI TESTS *********/
    /**********************************/

    // AutoTest_XPlor test_xplor;
    // if (!QTest::qExec(&test_xplor, argc, argv)) {
    //     return -1;
    // }

    /**********************************/
    /********* 360 COD TESTS  *********/
    /**********************************/

    QVector<AutoTest_COD*> cod2Tests;
    QVector<AutoTest_COD*> cod4Tests;
    QVector<AutoTest_COD*> cod5Tests;
    QVector<AutoTest_COD*> cod6Tests;
    QVector<AutoTest_COD*> cod7Tests;
    QVector<AutoTest_COD*> cod8Tests;
    QVector<AutoTest_COD*> cod9Tests;
    QVector<AutoTest_COD*> cod10Tests;
    QVector<AutoTest_COD*> cod11Tests;
    QVector<AutoTest_COD*> cod12Tests;

    QVector<AutoTest_COD*> xbox360Tests;
    QVector<AutoTest_COD*> pcTests;
    QVector<AutoTest_COD*> ps3Tests;
    QVector<AutoTest_COD*> wiiTests;
    QVector<AutoTest_COD*> wiiUTests;

    AutoTest_COD2_360 *test_cod2_360 = new AutoTest_COD2_360();
    test_cod2_360->setFastFileDirectory("G:/Fast Files/Xbox360/COD2");
    test_cod2_360->setZoneFileDirectory("./exports/cod2/360");
    cod2Tests << test_cod2_360;
    xbox360Tests << test_cod2_360;

    AutoTest_COD4_360 *test_cod4_360 = new AutoTest_COD4_360();
    test_cod4_360->setFastFileDirectory("G:/Fast Files/Xbox360/COD4");
    test_cod4_360->setZoneFileDirectory("./exports/cod4/360");
    cod4Tests << test_cod4_360;
    xbox360Tests << test_cod4_360;

    AutoTest_COD5_360 *test_cod5_360 = new AutoTest_COD5_360();
    test_cod5_360->setFastFileDirectory("G:/Fast Files/Xbox360/COD5");
    test_cod5_360->setZoneFileDirectory("./exports/cod5/360");
    cod5Tests << test_cod5_360;
    xbox360Tests << test_cod5_360;

    AutoTest_COD6_360 *test_cod6_360 = new AutoTest_COD6_360();
    test_cod6_360->setFastFileDirectory("G:/Fast Files/Xbox360/COD6");
    test_cod6_360->setZoneFileDirectory("./exports/cod6/360");
    cod6Tests << test_cod6_360;
    xbox360Tests << test_cod6_360;

    AutoTest_COD7_360 *test_cod7_360 = new AutoTest_COD7_360();
    test_cod7_360->setFastFileDirectory("G:/Fast Files/Xbox360/COD7");
    test_cod7_360->setZoneFileDirectory("./exports/cod7/360");
    cod7Tests << test_cod7_360;
    xbox360Tests << test_cod7_360;

    AutoTest_COD8_360 *test_cod8_360 = new AutoTest_COD8_360();
    test_cod8_360->setFastFileDirectory("G:/Fast Files/Xbox360/COD8");
    test_cod8_360->setZoneFileDirectory("./exports/cod8/360");
    cod8Tests << test_cod8_360;
    xbox360Tests << test_cod8_360;

    AutoTest_COD9_360 *test_cod9_360 = new AutoTest_COD9_360();
    test_cod9_360->setFastFileDirectory("G:/Fast Files/Xbox360/COD9");
    test_cod9_360->setZoneFileDirectory("./exports/cod9/360");
    cod9Tests << test_cod9_360;
    xbox360Tests << test_cod9_360;

    AutoTest_COD10_360 *test_cod10_360 = new AutoTest_COD10_360();
    test_cod10_360->setFastFileDirectory("G:/Fast Files/Xbox360/COD10");
    test_cod10_360->setZoneFileDirectory("./exports/cod10/360");
    cod10Tests << test_cod10_360;
    xbox360Tests << test_cod10_360;

    AutoTest_COD11_360 *test_cod11_360 = new AutoTest_COD11_360();
    test_cod11_360->setFastFileDirectory("G:/Fast Files/Xbox360/COD11");
    test_cod11_360->setZoneFileDirectory("./exports/cod11/360");
    cod11Tests << test_cod11_360;
    xbox360Tests << test_cod11_360;

    AutoTest_COD12_360 *test_cod12_360 = new AutoTest_COD12_360();
    test_cod12_360->setFastFileDirectory("G:/Fast Files/Xbox360/COD12");
    test_cod12_360->setZoneFileDirectory("./exports/cod12/360");
    cod12Tests << test_cod12_360;
    xbox360Tests << test_cod12_360;

    /**********************************/
    /*********  PC COD TESTS  *********/
    /**********************************/

    AutoTest_COD4_PC *test_cod4_pc = new AutoTest_COD4_PC();
    test_cod4_pc->setFastFileDirectory("G:/Fast Files/PC/COD4");
    test_cod4_pc->setZoneFileDirectory("./exports/cod4/PC");
    cod4Tests << test_cod4_pc;
    pcTests << test_cod4_pc;

    AutoTest_COD5_PC *test_cod5_pc = new AutoTest_COD5_PC();
    test_cod5_pc->setFastFileDirectory("G:/Fast Files/PC/COD5");
    test_cod5_pc->setZoneFileDirectory("./exports/cod5/PC");
    cod5Tests << test_cod5_pc;
    pcTests << test_cod5_pc;

    AutoTest_COD6_PC *test_cod6_pc = new AutoTest_COD6_PC();
    test_cod6_pc->setFastFileDirectory("G:/Fast Files/PC/COD6");
    test_cod6_pc->setZoneFileDirectory("./exports/cod6/PC");
    cod6Tests << test_cod6_pc;
    pcTests << test_cod6_pc;

    AutoTest_COD7_PC *test_cod7_pc = new AutoTest_COD7_PC();
    test_cod7_pc->setFastFileDirectory("G:/Fast Files/PC/COD7");
    test_cod7_pc->setZoneFileDirectory("./exports/cod7/PC");
    cod7Tests << test_cod7_pc;
    pcTests << test_cod7_pc;

    AutoTest_COD8_PC *test_cod8_pc = new AutoTest_COD8_PC();
    test_cod8_pc->setFastFileDirectory("G:/Fast Files/PC/COD8");
    test_cod8_pc->setZoneFileDirectory("./exports/cod8/PC");
    cod8Tests << test_cod8_pc;
    pcTests << test_cod8_pc;

    AutoTest_COD9_PC *test_cod9_pc = new AutoTest_COD9_PC();
    test_cod9_pc->setFastFileDirectory("G:/Fast Files/PC/COD9");
    test_cod9_pc->setZoneFileDirectory("./exports/cod9/PC");
    cod9Tests << test_cod9_pc;
    pcTests << test_cod9_pc;

    AutoTest_COD10_PC *test_cod10_pc = new AutoTest_COD10_PC();
    test_cod10_pc->setFastFileDirectory("G:/Fast Files/PC/COD10");
    test_cod10_pc->setZoneFileDirectory("./exports/cod10/PC");
    cod10Tests << test_cod10_pc;
    pcTests << test_cod10_pc;

    AutoTest_COD11_PC *test_cod11_pc = new AutoTest_COD11_PC();
    test_cod11_pc->setFastFileDirectory("G:/Fast Files/PC/COD11");
    test_cod11_pc->setZoneFileDirectory("./exports/cod11/PC");
    cod11Tests << test_cod11_pc;
    pcTests << test_cod11_pc;

    AutoTest_COD12_PC *test_cod12_pc = new AutoTest_COD12_PC();
    test_cod12_pc->setFastFileDirectory("G:/Fast Files/PC/COD12");
    test_cod12_pc->setZoneFileDirectory("./exports/cod12/PC");
    cod12Tests << test_cod12_pc;
    pcTests << test_cod12_pc;

    /**********************************/
    /********* PS3 COD TESTS  *********/
    /**********************************/

    AutoTest_COD4_PS3 *test_cod4_ps3 = new AutoTest_COD4_PS3();
    test_cod4_ps3->setFastFileDirectory("G:/Fast Files/PS3/COD4");
    test_cod4_ps3->setZoneFileDirectory("./exports/cod4/PS3");
    cod4Tests << test_cod4_ps3;
    ps3Tests << test_cod4_ps3;

    AutoTest_COD5_PS3 *test_cod5_ps3 = new AutoTest_COD5_PS3();
    test_cod5_ps3->setFastFileDirectory("G:/Fast Files/PS3/COD5");
    test_cod5_ps3->setZoneFileDirectory("./exports/cod5/PS3");
    cod5Tests << test_cod5_ps3;
    ps3Tests << test_cod5_ps3;

    AutoTest_COD6_PS3 *test_cod6_ps3 = new AutoTest_COD6_PS3();
    test_cod6_ps3->setFastFileDirectory("G:/Fast Files/PS3/COD6");
    test_cod6_ps3->setZoneFileDirectory("./exports/cod6/PS3");
    cod6Tests << test_cod6_ps3;
    ps3Tests << test_cod6_ps3;

    AutoTest_COD7_PS3 *test_cod7_ps3 = new AutoTest_COD7_PS3();
    test_cod7_ps3->setFastFileDirectory("G:/Fast Files/PS3/COD7");
    test_cod7_ps3->setZoneFileDirectory("./exports/cod7/PS3");
    cod7Tests << test_cod7_ps3;
    ps3Tests << test_cod7_ps3;

    AutoTest_COD8_PS3 *test_cod8_ps3 = new AutoTest_COD8_PS3();
    test_cod8_ps3->setFastFileDirectory("G:/Fast Files/PS3/COD8");
    test_cod8_ps3->setZoneFileDirectory("./exports/cod8/PS3");
    cod8Tests << test_cod8_ps3;
    ps3Tests << test_cod8_ps3;

    AutoTest_COD9_PS3 *test_cod9_ps3 = new AutoTest_COD9_PS3();
    test_cod9_ps3->setFastFileDirectory("G:/Fast Files/PS3/COD9");
    test_cod9_ps3->setZoneFileDirectory("./exports/cod9/PS3");
    cod9Tests << test_cod9_ps3;
    ps3Tests << test_cod9_ps3;

    AutoTest_COD10_PS3 *test_cod10_ps3 = new AutoTest_COD10_PS3();
    test_cod10_ps3->setFastFileDirectory("G:/Fast Files/PS3/COD10");
    test_cod10_ps3->setZoneFileDirectory("./exports/cod10/PS3");
    cod10Tests << test_cod10_ps3;
    ps3Tests << test_cod10_ps3;

    AutoTest_COD11_PS3 *test_cod11_ps3 = new AutoTest_COD11_PS3();
    test_cod11_ps3->setFastFileDirectory("G:/Fast Files/PS3/COD11");
    test_cod11_ps3->setZoneFileDirectory("./exports/cod11/PS3");
    cod11Tests << test_cod11_ps3;
    ps3Tests << test_cod11_ps3;

    AutoTest_COD12_PS3 *test_cod12_ps3 = new AutoTest_COD12_PS3();
    test_cod12_ps3->setFastFileDirectory("G:/Fast Files/PS3/COD12");
    test_cod12_ps3->setZoneFileDirectory("./exports/cod12/PS3");
    cod12Tests << test_cod12_ps3;
    ps3Tests << test_cod12_ps3;

    /**********************************/
    /********* Wii COD TESTS  *********/
    /**********************************/

    AutoTest_COD7_Wii *test_cod7_wii = new AutoTest_COD7_Wii();
    test_cod7_wii->setFastFileDirectory("G:/Fast Files/Wii/COD7");
    test_cod7_wii->setZoneFileDirectory("./exports/cod7/Wii");
    cod7Tests << test_cod7_wii;
    wiiTests << test_cod7_wii;

    /**********************************/
    /********* WiiU COD TESTS *********/
    /**********************************/

    AutoTest_COD9_WiiU *test_cod9_wiiu = new AutoTest_COD9_WiiU();
    test_cod9_wiiu->setFastFileDirectory("G:/Fast Files/WiiU/COD9");
    test_cod9_wiiu->setZoneFileDirectory("./exports/cod9/WiiU");
    cod9Tests << test_cod9_wiiu;
    wiiUTests << test_cod9_wiiu;

    AutoTest_COD10_WiiU *test_cod10_wiiu = new AutoTest_COD10_WiiU();
    test_cod10_wiiu->setFastFileDirectory("G:/Fast Files/WiiU/COD10");
    test_cod10_wiiu->setZoneFileDirectory("./exports/cod10/PS3");
    cod10Tests << test_cod10_wiiu;
    wiiUTests << test_cod10_wiiu;

    if (TEST_EVERYTHING || TEST_ALL_COD_GAMES || TEST_COD2) {
        qDebug() << "-- RUNNING TEST_COD2 --";
        foreach (auto test, cod2Tests) {
            QTest::qExec(test, argc, argv);
        }
    }
    if (TEST_EVERYTHING || TEST_ALL_COD_GAMES || TEST_COD4) {
        qDebug() << "-- RUNNING TEST_COD4 --";
        foreach (auto test, cod4Tests) {
            QTest::qExec(test, argc, argv);
        }
    }
    if (TEST_EVERYTHING || TEST_ALL_COD_GAMES || TEST_COD5) {
        qDebug() << "-- RUNNING TEST_COD5 --";
        foreach (auto test, cod5Tests) {
            QTest::qExec(test, argc, argv);
        }
    }
    if (TEST_EVERYTHING || TEST_ALL_COD_GAMES || TEST_COD6) {
        qDebug() << "-- RUNNING TEST_COD6 --";
        foreach (auto test, cod6Tests) {
            QTest::qExec(test, argc, argv);
        }
    }
    if (TEST_EVERYTHING || TEST_ALL_COD_GAMES || TEST_COD7) {
        qDebug() << "-- RUNNING TEST_COD7 --";
        foreach (auto test, cod7Tests) {
            QTest::qExec(test, argc, argv);
        }
    }
    if (TEST_EVERYTHING || TEST_ALL_COD_GAMES || TEST_COD8) {
        qDebug() << "-- RUNNING TEST_COD8 --";
        foreach (auto test, cod8Tests) {
            QTest::qExec(test, argc, argv);
        }
    }
    if (TEST_EVERYTHING || TEST_ALL_COD_GAMES || TEST_COD9) {
        qDebug() << "-- RUNNING TEST_COD9 --";
        foreach (auto test, cod9Tests) {
            QTest::qExec(test, argc, argv);
        }
    }
    if (TEST_EVERYTHING || TEST_ALL_COD_GAMES || TEST_COD10) {
        qDebug() << "-- RUNNING TEST_COD10 --";
        foreach (auto test, cod10Tests) {
            QTest::qExec(test, argc, argv);
        }
    }
    if (TEST_EVERYTHING || TEST_ALL_COD_GAMES || TEST_COD11) {
        qDebug() << "-- RUNNING TEST_COD11 --";
        foreach (auto test, cod11Tests) {
            QTest::qExec(test, argc, argv);
        }
    }
    if (TEST_EVERYTHING || TEST_ALL_COD_GAMES || TEST_COD12) {
        qDebug() << "-- RUNNING TEST_COD12 --";
        foreach (auto test, cod12Tests) {
            QTest::qExec(test, argc, argv);
        }
    }

    if (TEST_EVERYTHING || TEST_ALL_PLATFORMS || TEST_360) {
        qDebug() << "-- RUNNING TEST_360 --";
        foreach (auto test, xbox360Tests) {
            QTest::qExec(test, argc, argv);
        }
    }
    if (TEST_EVERYTHING || TEST_ALL_PLATFORMS || TEST_PC) {
        qDebug() << "-- RUNNING TEST_PC --";
        foreach (auto test, pcTests) {
            QTest::qExec(test, argc, argv);
        }
    }
    if (TEST_EVERYTHING || TEST_ALL_PLATFORMS || TEST_PS3) {
        qDebug() << "-- RUNNING TEST_PS3 --";
        foreach (auto test, ps3Tests) {
            QTest::qExec(test, argc, argv);
        }
    }
    if (TEST_EVERYTHING || TEST_ALL_PLATFORMS || TEST_WII) {
        qDebug() << "-- RUNNING TEST_WII --";
        foreach (auto test, wiiTests) {
            QTest::qExec(test, argc, argv);
        }
    }
    if (TEST_EVERYTHING || TEST_ALL_PLATFORMS || TEST_WIIU) {
        qDebug() << "-- RUNNING TEST_WIIU --";
        foreach (auto test, wiiUTests) {
            QTest::qExec(test, argc, argv);
        }
    }

    return 0;
}
