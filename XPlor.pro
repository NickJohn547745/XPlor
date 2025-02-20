QT       += core gui multimedia

RC_ICONS = XPlor.ico

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

SOURCES += \
    aboutdialog.cpp \
    ddsfile.cpp \
    ddsviewer.cpp \
    fastfile.cpp \
    fastfile_cod2.cpp \
    fastfile_cod5.cpp \
    fastfile_cod7.cpp \
    fastfile_cod9.cpp \
    fastfileviewer.cpp \
    imagewidget.cpp \
    iwifile.cpp \
    iwiviewer.cpp \
    localstringviewer.cpp \
    lzokay.cpp \
    main.cpp \
    mainwindow.cpp \
    iwifile.cpp \
    preferenceeditor.cpp \
    soundviewer.cpp \
    statusbarmanager.cpp \
    stringtableviewer.cpp \
    techsetviewer.cpp \
    xtreewidget.cpp \
    xtreewidgetitem.cpp \
    zonefile.cpp \
    zonefile_cod2.cpp \
    zonefile_cod5.cpp \
    zonefile_cod7.cpp \
    zonefile_cod9.cpp \
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
    fastfile_cod2.h \
    fastfile_cod5.h \
    fastfile_cod7.h \
    fastfile_cod9.h \
    fastfileviewer.h \
    imagewidget.h \
    ipak_structs.h \
    iwifile.h \
    iwiviewer.h \
    localstringviewer.h \
    lzokay.hpp \
    lzx.h \
    mainwindow.h \
    preferenceeditor.h \
    soundviewer.h \
    statusbarmanager.h \
    stringtableviewer.h \
    techsetviewer.h \
    utils.h \
    xtreewidget.h \
    iwifile.h \
    xtreewidgetitem.h \
    zonefile.h \
    zonefile_cod2.h \
    zonefile_cod5.h \
    zonefile_cod7.h \
    zonefile_cod9.h \
    zonefileviewer.h

FORMS += \
    aboutdialog.ui \
    ddsviewer.ui \
    fastfileviewer.ui \
    imagewidget.ui \
    iwiviewer.ui \
    localstringviewer.ui \
    mainwindow.ui \
    modelviewer.ui \
    preferenceeditor.ui \
    soundviewer.ui \
    stringtableviewer.ui \
    techsetviewer.ui \
    zonefileviewer.ui

RESOURCES += data/data.qrc

LIBS += -L$$PWD/DevILSDK/lib/x64/Unicode/Release -lDevIL
LIBS += -L$$PWD/DevILSDK/lib/x64/Unicode/Release -lILU
LIBS += -L$$PWD/DevILSDK/lib/x64/Unicode/Release -lILUT
