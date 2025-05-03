QT += core widgets
TEMPLATE = lib
CONFIG += staticlib c++17

SOURCES += \
    fastfile.cpp \
    360/fastfile_cod2_360.cpp \
    360/fastfile_cod5_360.cpp \
    360/fastfile_cod7_360.cpp \
    360/fastfile_cod9_360.cpp \
    PS3/fastfile_cod5_ps3.cpp \
    PS3/fastfile_cod7_ps3.cpp \
    PS3/fastfile_cod9_ps3.cpp \
    PC/fastfile_cod5_pc.cpp \
    PC/fastfile_cod7_pc.cpp \
    PC/fastfile_cod9_pc.cpp \
    PC/fastfile_cod12_pc.cpp \
    Wii/fastfile_cod7_wii.cpp \
    WiiU/fastfile_cod9_wiiu.cpp

HEADERS += \
    fastfile.h \
    360/fastfile_cod2_360.h \
    360/fastfile_cod5_360.h \
    360/fastfile_cod7_360.h \
    360/fastfile_cod9_360.h \
    PS3/fastfile_cod5_ps3.h \
    PS3/fastfile_cod7_ps3.h \
    PS3/fastfile_cod9_ps3.h \
    PC/fastfile_cod5_pc.h \
    PC/fastfile_cod7_pc.h \
    PC/fastfile_cod9_pc.h \
    PC/fastfile_cod12_pc.h \
    Wii/fastfile_cod7_wii.h \
    WiiU/fastfile_cod9_wiiu.h \
    fastfile_factory.h

LIBS += \
    -L$$OUT_PWD/../libs/core -lcore \
    -L$$OUT_PWD/../libs/compression -lcompression \
    -L$$OUT_PWD/../libs/encryption -lencryption \
    -L$$OUT_PWD/../libs/zonefile -lzonefile

INCLUDEPATH += \
    $$PWD/../core \
    $$PWD/../compression \
    $$PWD/../encryption \
    $$PWD/../zonefile \
    $$PWD/../zonefile/360 \
    $$PWD/../zonefile/PC \
    $$PWD/../zonefile/PS3 \
    $$PWD/../zonefile/Wii \
    $$PWD/../zonefile/WiiU

DEPENDPATH += \
    $$PWD/../core \
    $$PWD/../compression \
    $$PWD/../encryption \
    $$PWD/../zonefile

DESTDIR = $$OUT_PWD/../
