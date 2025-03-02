QT += core
TEMPLATE = lib
CONFIG += staticlib c++17 debug

SOURCES +=

HEADERS += \
    ecrypt-config.h \
    ecrypt-machine.h \
    ecrypt-portable.h \
    ecrypt-sync.h

DESTDIR = $$OUT_PWD/../
