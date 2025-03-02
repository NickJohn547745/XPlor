QT += core widgets
TEMPLATE = lib
CONFIG += staticlib c++17 debug

SOURCES += \
    fastfile_cod2.cpp \
    fastfile_cod5.cpp \
    fastfile_cod7.cpp \
    fastfile_cod9.cpp \
    fastfile.cpp

HEADERS += \
    fastfile.h \
    fastfile_cod2.h \
    fastfile_cod5.h \
    fastfile_cod7.h \
    fastfile_cod9.h

LIBS += \
    -L$$OUT_PWD/../libs/core -lcore \
    -L$$OUT_PWD/../libs/compression -lcompression \
    -L$$OUT_PWD/../libs/encryption -lencryption \
    -L$$OUT_PWD/../libs/zonefile -lzonefile

INCLUDEPATH += \
    $$PWD/../core \
    $$PWD/../compression \
    $$PWD/../encryption \
    $$PWD/../zonefile

DEPENDPATH += \
    $$PWD/../core \
    $$PWD/../compression \
    $$PWD/../encryption \
    $$PWD/../zonefile

DESTDIR = $$OUT_PWD/../
