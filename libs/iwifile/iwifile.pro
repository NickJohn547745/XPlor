QT += core
TEMPLATE = lib
CONFIG += staticlib c++17

SOURCES += \
    iwifile.cpp

HEADERS += \
    iwifile.h

LIBS += \
    -L$$PWD/../../third_party/devil_sdk/lib/ -lDevIL \
    -L$$PWD/../../third_party/devil_sdk/lib/ -lILU \
    -L$$PWD/../../third_party/devil_sdk/lib/ -lILUT \
    -L$$OUT_PWD/../libs/ddsfile -lddsfile

INCLUDEPATH += \
    $$PWD/../../third_party/devil_sdk/include/ \
    $$PWD/../ddsfile

DEPENDPATH += \
    $$PWD/../../third_party/devil_sdk/include/ \
    $$PWD/../ddsfile

DESTDIR = $$OUT_PWD/../
