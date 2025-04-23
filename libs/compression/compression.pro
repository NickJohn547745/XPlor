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
    -L$$PWD/../../third_party/xbox_sdk/lib -lxcompress64 \
    -L$$OUT_PWD/../libs/core -lcore \
    -L$$OUT_PWD/../libs/encryption -lencryption

INCLUDEPATH += \
    $$PWD/../../third_party/xbox_sdk/include \
    $$PWD/../core \
    $$PWD/../encryption

DEPENDPATH += \
    $$PWD/../../third_party/xbox_sdk/include \
    $$PWD/../core \
    $$PWD/../encryption

DESTDIR = $$OUT_PWD/../
