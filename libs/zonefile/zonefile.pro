QT += core widgets
TEMPLATE = lib
CONFIG += staticlib c++17

SOURCES += \
    # Base class
    zonefile.cpp \
    # 360 classes
    360/zonefile_cod2_360.cpp \
    360/zonefile_cod4_360.cpp \
    360/zonefile_cod5_360.cpp \
    360/zonefile_cod6_360.cpp \
    360/zonefile_cod7_360.cpp \
    360/zonefile_cod8_360.cpp \
    360/zonefile_cod9_360.cpp \
    360/zonefile_cod10_360.cpp \
    360/zonefile_cod11_360.cpp \
    360/zonefile_cod12_360.cpp \
    # PS3 classes
    PS3/zonefile_cod4_ps3.cpp \
    PS3/zonefile_cod5_ps3.cpp \
    PS3/zonefile_cod6_ps3.cpp \
    PS3/zonefile_cod7_ps3.cpp \
    PS3/zonefile_cod8_ps3.cpp \
    PS3/zonefile_cod9_ps3.cpp \
    PS3/zonefile_cod10_ps3.cpp \
    PS3/zonefile_cod11_ps3.cpp \
    PS3/zonefile_cod12_ps3.cpp \
    # PC classes
    PC/zonefile_cod4_pc.cpp \
    PC/zonefile_cod5_pc.cpp \
    PC/zonefile_cod6_pc.cpp \
    PC/zonefile_cod7_pc.cpp \
    PC/zonefile_cod8_pc.cpp \
    PC/zonefile_cod9_pc.cpp \
    PC/zonefile_cod10_pc.cpp \
    PC/zonefile_cod11_pc.cpp \
    PC/zonefile_cod12_pc.cpp \
    # Wii classes
    Wii/zonefile_cod4_wii.cpp \
    Wii/zonefile_cod7_wii.cpp \
    Wii/zonefile_cod8_wii.cpp \
    # WiiU classes
    WiiU/zonefile_cod9_wiiu.cpp \
    WiiU/zonefile_cod10_wiiu.cpp

HEADERS += \
    # Base class
    zonefile.h \
    # 360 classes
    360/zonefile_cod2_360.h \
    360/zonefile_cod4_360.h \
    360/zonefile_cod5_360.h \
    360/zonefile_cod6_360.h \
    360/zonefile_cod7_360.h \
    360/zonefile_cod8_360.h \
    360/zonefile_cod9_360.h \
    360/zonefile_cod10_360.h \
    360/zonefile_cod11_360.h \
    360/zonefile_cod12_360.h \
    # PS3 classes
    PS3/zonefile_cod4_ps3.h \
    PS3/zonefile_cod5_ps3.h \
    PS3/zonefile_cod6_ps3.h \
    PS3/zonefile_cod7_ps3.h \
    PS3/zonefile_cod8_ps3.h \
    PS3/zonefile_cod9_ps3.h \
    PS3/zonefile_cod10_ps3.h \
    PS3/zonefile_cod11_ps3.h \
    PS3/zonefile_cod12_ps3.h \
    # PC classes
    PC/zonefile_cod4_pc.h \
    PC/zonefile_cod5_pc.h \
    PC/zonefile_cod6_pc.h \
    PC/zonefile_cod7_pc.h \
    PC/zonefile_cod8_pc.h \
    PC/zonefile_cod9_pc.h \
    PC/zonefile_cod10_pc.h \
    PC/zonefile_cod11_pc.h \
    PC/zonefile_cod12_pc.h \
    # Wii classes
    Wii/zonefile_cod4_wii.h \
    Wii/zonefile_cod7_wii.h \
    Wii/zonefile_cod8_wii.h \
    # WiiU classes
    WiiU/zonefile_cod9_wiiu.h \
    WiiU/zonefile_cod10_wiiu.h

LIBS += \
    -L$$OUT_PWD/../libs/core -lcore

INCLUDEPATH += \
    $$PWD/../core \

DEPENDPATH += \
    $$PWD/../core

DESTDIR = $$OUT_PWD/../
