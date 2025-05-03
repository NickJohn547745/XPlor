QT += core widgets
TEMPLATE = lib
CONFIG += staticlib c++17

SOURCES += \
    zonefile.cpp \
    360/zonefile_cod2_360.cpp \
    360/zonefile_cod5_360.cpp \
    360/zonefile_cod7_360.cpp \
    360/zonefile_cod9_360.cpp \
    PS3/zonefile_cod5_ps3.cpp \
    PS3/zonefile_cod7_ps3.cpp \
    PS3/zonefile_cod9_ps3.cpp \
    PC/zonefile_cod5_pc.cpp \
    PC/zonefile_cod7_pc.cpp \
    PC/zonefile_cod9_pc.cpp \
    PC/zonefile_cod12_pc.cpp \
    Wii/zonefile_cod7_wii.cpp \
    WiiU/zonefile_cod9_wiiu.cpp

HEADERS += \
    zonefile.h \
    360/zonefile_cod2_360.h \
    360/zonefile_cod5_360.h \
    360/zonefile_cod7_360.h \
    360/zonefile_cod9_360.h \
    PS3/zonefile_cod5_ps3.h \
    PS3/zonefile_cod7_ps3.h \
    PS3/zonefile_cod9_ps3.h \
    PC/zonefile_cod5_pc.h \
    PC/zonefile_cod7_pc.h \
    PC/zonefile_cod9_pc.h \
    PC/zonefile_cod12_pc.h \
    Wii/zonefile_cod7_wii.h \
    WiiU/zonefile_cod9_wiiu.h \
    zonefile_factory.h

LIBS += \
    -L$$OUT_PWD/../libs/core -lcore

INCLUDEPATH += \
    $$PWD/../core \

DEPENDPATH += \
    $$PWD/../core

DESTDIR = $$OUT_PWD/../
