QT += core widgets gui multimedia

RC_ICONS = zentry.ico

SUBDIRS += zentry

CONFIG += c++17

SOURCES += \
    zentrymain.cpp \
    zentrywindow.cpp

HEADERS += \
    zentrywindow.h

FORMS +=

app.depends += \
    libs/compression

LIBS += \
    -L$$OUT_PWD/../../libs/ -lcompression \
    -L$$PWD/../../third_party/xbox_sdk/lib -lxcompress64

INCLUDEPATH += \
    $$PWD/../../libs/compression \
    $$PWD/../../third_party/xbox_sdk/include

DEPENDPATH += \
    $$PWD/../../libs/compression \
    $$PWD/../../third_party/xbox_sdk/include

