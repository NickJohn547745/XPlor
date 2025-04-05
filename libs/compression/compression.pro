QT += core
TEMPLATE = lib
CONFIG += staticlib c++17

SOURCES += \
    compression.cpp \
    lzokay.cpp \

HEADERS += \
    compression.h \
    lzokay.h

LIBS += \
    -L$$OUT_PWD/../libs/core -lcore \
    -L$$OUT_PWD/../libs/encryption -lencryption

INCLUDEPATH += \
    $$PWD/../core \
    $$PWD/../encryption

DEPENDPATH += \
    $$PWD/../core \
    $$PWD/../encryption

DESTDIR = $$OUT_PWD/../
