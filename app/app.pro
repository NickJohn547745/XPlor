QT += core widgets gui multimedia

RC_ICONS = app.ico

SUBDIRS += app

CONFIG += c++17

SOURCES += \
    aboutdialog.cpp \
    ddsviewer.cpp \
    fastfileviewer.cpp \
    imagewidget.cpp \
    iwiviewer.cpp \
    localstringviewer.cpp \
    main.cpp \
    mainwindow.cpp \
    materialviewer.cpp \
    preferenceeditor.cpp \
    soundviewer.cpp \
    stringtableviewer.cpp \
    techsetviewer.cpp \
    xtreewidget.cpp \
    xtreewidgetitem.cpp \
    zonefileviewer.cpp

HEADERS += \
    aboutdialog.h \
    d3dbsp_structs.h \
    ddsviewer.h \
    fastfileviewer.h \
    imagewidget.h \
    iwiviewer.h \
    localstringviewer.h \
    mainwindow.h \
    materialviewer.h \
    preferenceeditor.h \
    soundviewer.h \
    stringtableviewer.h \
    techsetviewer.h \
    xtreewidget.h \
    xtreewidgetitem.h \
    zonefileviewer.h

FORMS += \
    aboutdialog.ui \
    ddsviewer.ui \
    fastfileviewer.ui \
    imagewidget.ui \
    iwiviewer.ui \
    localstringviewer.ui \
    mainwindow.ui \
    materialviewer.ui \
    modelviewer.ui \
    preferenceeditor.ui \
    soundviewer.ui \
    stringtableviewer.ui \
    techsetviewer.ui \
    zonefileviewer.ui

RESOURCES += ../data/data.qrc

app.depends += \
    libs/core \
    libs/compression \
    libs/encryption \
    libs/fastfile \
    libs/ddsfile \
    libs/ipakfile \
    libs/iwifile \
    libs/zonefile

LIBS += \
    -L$$PWD/../third_party/devil_sdk/lib/ -lDevIL -lILU -lILUT \
    -L$$PWD/../third_party/zlib/lib/ -lzlib \
    -L$$PWD/../third_party/xbox_sdk/lib -lxcompress64 \
    -L$$OUT_PWD/../libs/ -lcore \
    -L$$OUT_PWD/../libs/ -lcompression \
    -L$$OUT_PWD/../libs/ -lencryption \
    -L$$OUT_PWD/../libs/ -lfastfile \
    -L$$OUT_PWD/../libs/ -lddsfile \
    -L$$OUT_PWD/../libs/ -lipakfile \
    -L$$OUT_PWD/../libs/ -liwifile \
    -L$$OUT_PWD/../libs/ -lzonefile

INCLUDEPATH += \
    $$PWD/../third_party/devil_sdk/include/ \
    $$PWD/../third_party/zlib/include \
    $$PWD/../third_party/xbox_sdk/include \
    $$PWD/../libs/core \
    $$PWD/../libs/compression \
    $$PWD/../libs/encryption \
    $$PWD/../libs/fastfile \
    $$PWD/../libs/ddsfile \
    $$PWD/../libs/ipakfile \
    $$PWD/../libs/iwifile \
    $$PWD/../libs/zonefile

DEPENDPATH += \
    $$PWD/../third_party/devil_sdk/include/ \
    $$PWD/../third_party/zlib/include \
    $$PWD/../third_party/xbox_sdk/include \
    $$PWD/../libs/core \
    $$PWD/../libs/compression \
    $$PWD/../libs/encryption \
    $$PWD/../libs/fastfile \
    $$PWD/../libs/ddsfile \
    $$PWD/../libs/ipakfile \
    $$PWD/../libs/iwifile \
    $$PWD/../libs/zonefile

# Copy DLLs to Debug folder
QMAKE_POST_LINK += xcopy /Y /E /I \"G:/Projects/Qt/XPlor/third_party/devil_sdk/lib\\*.dll\" \"$$OUT_PWD/debug/\" $$escape_expand(\\n\\t)
QMAKE_POST_LINK += xcopy /Y /E /I \"G:/Projects/Qt/XPlor/third_party/zlib/lib\\*.dll\" \"$$OUT_PWD/debug/\" $$escape_expand(\\n\\t)
QMAKE_POST_LINK += xcopy /Y /E /I \"G:/Projects/Qt/XPlor/third_party/xna/lib\\*.dll\" \"$$OUT_PWD/debug/\" $$escape_expand(\\n\\t)
QMAKE_POST_LINK += xcopy /Y /E /I \"$$PWD/../third_party/xbox_sdk/lib\\*.dll\" \"$$OUT_PWD/debug/\" $$escape_expand(\\n\\t)

# Copy DLLs to Release folder
QMAKE_POST_LINK += xcopy /Y /E /I \"G:/Projects/Qt/XPlor/third_party/devil_sdk/lib\\*.dll\" \"$$OUT_PWD/release/\" $$escape_expand(\\n\\t)
QMAKE_POST_LINK += xcopy /Y /E /I \"G:/Projects/Qt/XPlor/third_party/zlib/lib\\*.dll\" \"$$OUT_PWD/release/\" $$escape_expand(\\n\\t)
QMAKE_POST_LINK += xcopy /Y /E /I \"G:/Projects/Qt/XPlor/third_party/xna/lib\\*.dll\" \"$$OUT_PWD/release/\" $$escape_expand(\\n\\t)
QMAKE_POST_LINK += xcopy /Y /E /I \"$$PWD/../third_party/xbox_sdk/lib\\*.dll\" \"$$OUT_PWD/release/\" $$escape_expand(\\n\\t)
