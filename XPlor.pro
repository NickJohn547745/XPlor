QT       += core gui 3dcore 3drender 3dinput 3dextras

RC_ICONS = XPlor.ico
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

SOURCES += \
    aboutdialog.cpp \
    ddsfile.cpp \
    ddsviewer.cpp \
    fastfile.cpp \
    fastfileviewer.cpp \
    imagewidget.cpp \
    iwifile.cpp \
    iwiviewer.cpp \
    localstringviewer.cpp \
    lzokay.cpp \
    main.cpp \
    mainwindow.cpp \
    modelviewer.cpp \
    iwifile.cpp \
    techsetviewer.cpp \
    xtreewidget.cpp \
    zonefile.cpp \
    zonefileviewer.cpp

HEADERS += \
    aboutdialog.h \
    asset_structs.h \
    compressor.h \
    d3dbsp_structs.h \
    dds_structs.h \
    ddsfile.h \
    ddsviewer.h \
    enums.h \
    fastfile.h \
    fastfileviewer.h \
    imagewidget.h \
    ipak_structs.h \
    iwifile.h \
    iwiviewer.h \
    localstringviewer.h \
    lzokay.hpp \
    lzx.h \
    mainwindow.h \
    modelviewer.h \
    techsetviewer.h \
    utils.h \
    xtreewidget.h \
    iwifile.h \
    zonefile.h \
    zonefileviewer.h

FORMS += \
    aboutdialog.ui \
    ddsviewer.ui \
    fastfileviewer.ui \
    imagewidget.ui \
    iwiviewer.ui \
    localstringviewer.ui \
    mainwindow.ui \
    techsetviewer.ui \
    zonefileviewer.ui

RESOURCES += \
    data/Data.qrc

LIBS += -L$$PWD/DevILSDK/lib/x64/Unicode/Release -lDevIL
LIBS += -L$$PWD/DevILSDK/lib/x64/Unicode/Release -lILU
LIBS += -L$$PWD/DevILSDK/lib/x64/Unicode/Release -lILUT

#LIBS += -L"C:/Program Files (x86)/Windows Kits/10/Lib/10.0.26100.0/um/x64" -ldxcompiler


