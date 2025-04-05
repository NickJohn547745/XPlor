QT += core
TEMPLATE = lib
CONFIG += staticlib c++17 debug

SOURCES += \
    lzokay.cpp \

HEADERS += \
    lzx.h \
    lzokay.hpp \
    compressor.h

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
