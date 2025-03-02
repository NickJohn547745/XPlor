QT += core
TEMPLATE = lib
CONFIG += staticlib c++17 debug

SOURCES += \
    lzokay.cpp \
    salsa20.cpp \
    sha1.cpp

HEADERS += \
    lzx.h \
    lzokay.hpp \
    sha1.h \
    os_types.h \
    config_win32.h \
    compressor.h

LIBS += \
    -L$$OUT_PWD/../libs/encryption -lencryption

INCLUDEPATH += \
    $$PWD/../encryption

DEPENDPATH += \
    $$PWD/../encryption

DESTDIR = $$OUT_PWD/../
