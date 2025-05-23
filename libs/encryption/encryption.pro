QT += core
TEMPLATE = lib
CONFIG += staticlib c++17

SOURCES += \
    salsa20.cpp \
    sha1.cpp \
    encryption.cpp

HEADERS += \
    ecrypt-config.h \
    ecrypt-machine.h \
    ecrypt-portable.h \
    ecrypt-sync.h \
    encryption.h \
    os_types.h \
    config_win32.h \
    sha1.h

app.depends += \
    compression

LIBS += \
    -L$$OUT_PWD/../ -lcompression

INCLUDEPATH += \
    $$PWD/../compression

DEPENDPATH += \
    $$PWD/../compression

DESTDIR = $$OUT_PWD/../
