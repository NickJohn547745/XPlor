QT += core widgets
TEMPLATE = lib
CONFIG += staticlib c++17 debug

SOURCES += \
    logmanager.cpp \
    statusbarmanager.cpp

HEADERS += \
    enums.h \
    logmanager.h \
    stringutils.h \
    utils.h \
    statusbarmanager.h

DESTDIR = $$OUT_PWD/../
