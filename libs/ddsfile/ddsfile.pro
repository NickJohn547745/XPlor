QT += core
TEMPLATE = lib
CONFIG += staticlib c++17

SOURCES += \
    ddsfile.cpp

HEADERS += \
    dds_structs.h \
    ddsfile.h \
    enums.h

LIBS += \
    -L$$PWD/../../third_party/devil_sdk/lib/ -lDevIL \
    -L$$PWD/../../third_party/devil_sdk/lib/ -lILU \
    -L$$PWD/../../third_party/devil_sdk/lib/ -lILUT \
    -L$$OUT_PWD/../libs/iwifile -liwifile

INCLUDEPATH += \
    $$PWD/../iwifile/ \
    $$PWD/../../third_party/devil_sdk/include/

DEPENDPATH += \
    $$PWD/../iwifile/ \
    $$PWD/../../third_party/devil_sdk/include/

DESTDIR = $$OUT_PWD/../
