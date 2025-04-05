QT += core widgets
TEMPLATE = lib
CONFIG += staticlib c++17

SOURCES += \
    zonefile.cpp \
    zonefile_cod2.cpp \
    zonefile_cod5.cpp \
    zonefile_cod7.cpp \
    zonefile_cod9.cpp

HEADERS += \
    asset_structs.h \
    zonefile.h \
    zonefile_cod2.h \
    zonefile_cod5.h \
    zonefile_cod7.h \
    zonefile_cod9.h

LIBS += \
    -L$$OUT_PWD/../libs/core -lcore

INCLUDEPATH += \
    $$PWD/../core

DEPENDPATH += \
    $$PWD/../core

DESTDIR = $$OUT_PWD/../
