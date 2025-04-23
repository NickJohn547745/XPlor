QT += core
TEMPLATE = lib
CONFIG += staticlib c++17

SOURCES += \
    ipakfile.cpp

HEADERS += \
    ipak_structs.h

DESTDIR = $$OUT_PWD/../
