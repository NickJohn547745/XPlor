QT += core
TEMPLATE = lib
CONFIG += staticlib c++17 debug

SOURCES += \
    ipakfile.cpp

HEADERS += \
    ipak_structs.h

DESTDIR = $$OUT_PWD/../
