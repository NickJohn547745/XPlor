TEMPLATE = app
CONFIG += no_main

# Enable the testlib module
QT += testlib concurrent core-private

# Define a test-specific flag
DEFINES += QT_TESTS

TARGET = tests

# List all test source files
SOURCES += \
    # 360 autotests
    360/autotest_cod2_360.cpp \
    360/autotest_cod4_360.cpp \
    360/autotest_cod5_360.cpp \
    360/autotest_cod6_360.cpp \
    360/autotest_cod7_360.cpp \
    360/autotest_cod8_360.cpp \
    360/autotest_cod9_360.cpp \
    360/autotest_cod10_360.cpp \
    360/autotest_cod11_360.cpp \
    360/autotest_cod12_360.cpp \
    # PC autotests
    PC/autotest_cod4_pc.cpp \
    PC/autotest_cod5_pc.cpp \
    PC/autotest_cod6_pc.cpp \
    PC/autotest_cod7_pc.cpp \
    PC/autotest_cod8_pc.cpp \
    PC/autotest_cod9_pc.cpp \
    PC/autotest_cod10_pc.cpp \
    PC/autotest_cod11_pc.cpp \
    PC/autotest_cod12_pc.cpp \
    # PS3 autotests
    PS3/autotest_cod4_ps3.cpp \
    PS3/autotest_cod5_ps3.cpp \
    PS3/autotest_cod6_ps3.cpp \
    PS3/autotest_cod7_ps3.cpp \
    PS3/autotest_cod8_ps3.cpp \
    PS3/autotest_cod9_ps3.cpp \
    PS3/autotest_cod10_ps3.cpp \
    PS3/autotest_cod11_ps3.cpp \
    PS3/autotest_cod12_ps3.cpp \
    # Wii autotests
    Wii/autotest_cod7_wii.cpp \
    # WiiU autotests
    WiiU/autotest_cod9_wiiu.cpp \
    WiiU/autotest_cod10_wiiu.cpp \
    # XPlor autotests
    autotest_xplor.cpp \
    # Main test function
    test_main.cpp

HEADERS += \
    autotest_cod.h


# Prevent tests from being built in release mode (optional)
# CONFIG(debug, debug|release) {
#     message("Including test files in Debug mode")
# } else {
#     SOURCES -= autotest_cod5.cpp
# }

app.depends += \
    libs/core \
    libs/compression \
    libs/encryption \
    libs/zonefile \
    libs/fastfile

LIBS += \
    -L$$OUT_PWD/../libs/ -lcore -lencryption -lcompression -lfastfile -lzonefile \
    -L$$PWD/../third_party/xbox_sdk/lib -lxcompress64

INCLUDEPATH += \
    $$PWD/../third_party/xbox_sdk/include \
    $$PWD/../libs/core \
    $$PWD/../libs/encryption \
    $$PWD/../libs/compression \
    $$PWD/../libs/fastfile \
    $$PWD/../libs/zonefile

DEPENDPATH += \
    $$PWD/../third_party/xbox_sdk/include \
    $$PWD/../libs/core \
    $$PWD/../libs/encryption \
    $$PWD/../libs/compression \
    $$PWD/../libs/fastfile \
    $$PWD/../libs/zonefile

RESOURCES +=

# Copy DLLs to Debug & Release folder
QMAKE_POST_LINK += xcopy /Y /E /I \"$$PWD/../third_party/xbox_sdk/lib\\*.dll\" \"$$OUT_PWD/debug/\" $$escape_expand(\\n\\t)
QMAKE_POST_LINK += xcopy /Y /E /I \"$$PWD/../third_party/xbox_sdk/lib\\*.dll\" \"$$OUT_PWD/release/\" $$escape_expand(\\n\\t)
