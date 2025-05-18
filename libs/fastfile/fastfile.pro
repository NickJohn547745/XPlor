QT += core widgets
TEMPLATE = lib
CONFIG += staticlib c++17

SOURCES += \
    # Base class & factory
    fastfile.cpp \
    # 360 classes
    360/fastfile_cod2_360.cpp \
    360/fastfile_cod4_360.cpp \
    360/fastfile_cod5_360.cpp \
    360/fastfile_cod6_360.cpp \
    360/fastfile_cod7_360.cpp \
    360/fastfile_cod8_360.cpp \
    360/fastfile_cod9_360.cpp \
    360/fastfile_cod10_360.cpp \
    360/fastfile_cod11_360.cpp \
    360/fastfile_cod12_360.cpp \
    # PS3 classes
    PS3/fastfile_cod4_ps3.cpp \
    PS3/fastfile_cod5_ps3.cpp \
    PS3/fastfile_cod6_ps3.cpp \
    PS3/fastfile_cod7_ps3.cpp \
    PS3/fastfile_cod8_ps3.cpp \
    PS3/fastfile_cod9_ps3.cpp \
    PS3/fastfile_cod10_ps3.cpp \
    PS3/fastfile_cod11_ps3.cpp \
    PS3/fastfile_cod12_ps3.cpp \
    # PC classes
    PC/fastfile_cod4_pc.cpp \
    PC/fastfile_cod5_pc.cpp \
    PC/fastfile_cod6_pc.cpp \
    PC/fastfile_cod7_pc.cpp \
    PC/fastfile_cod8_pc.cpp \
    PC/fastfile_cod9_pc.cpp \
    PC/fastfile_cod10_pc.cpp \
    PC/fastfile_cod11_pc.cpp \
    PC/fastfile_cod12_pc.cpp \
    # Wii Classes
    Wii/fastfile_cod4_wii.cpp \
    Wii/fastfile_cod7_wii.cpp \
    Wii/fastfile_cod8_wii.cpp \
    # WiiU Classes
    WiiU/fastfile_cod9_wiiu.cpp \
    WiiU/fastfile_cod10_wiiu.cpp

HEADERS += \
    # Base class & factory
    fastfile.h \
    fastfile_factory.h \
    # 360 classes
    360/fastfile_cod2_360.h \
    360/fastfile_cod4_360.h \
    360/fastfile_cod5_360.h \
    360/fastfile_cod6_360.h \
    360/fastfile_cod7_360.h \
    360/fastfile_cod8_360.h \
    360/fastfile_cod9_360.h \
    360/fastfile_cod10_360.h \
    360/fastfile_cod11_360.h \
    360/fastfile_cod12_360.h \
    # PS3 classes
    PS3/fastfile_cod4_ps3.h \
    PS3/fastfile_cod5_ps3.h \
    PS3/fastfile_cod6_ps3.h \
    PS3/fastfile_cod7_ps3.h \
    PS3/fastfile_cod8_ps3.h \
    PS3/fastfile_cod9_ps3.h \
    PS3/fastfile_cod10_ps3.h \
    PS3/fastfile_cod11_ps3.h \
    PS3/fastfile_cod12_ps3.h \
    # PC classes
    PC/fastfile_cod4_pc.h \
    PC/fastfile_cod5_pc.h \
    PC/fastfile_cod6_pc.h \
    PC/fastfile_cod7_pc.h \
    PC/fastfile_cod8_pc.h \
    PC/fastfile_cod9_pc.h \
    PC/fastfile_cod10_pc.h \
    PC/fastfile_cod11_pc.h \
    PC/fastfile_cod12_pc.h \
    # Wii Classes
    Wii/fastfile_cod4_wii.h \
    Wii/fastfile_cod7_wii.h \
    Wii/fastfile_cod8_wii.h \
    # WiiU classes
    WiiU/fastfile_cod9_wiiu.h \
    WiiU/fastfile_cod10_wiiu.h

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
