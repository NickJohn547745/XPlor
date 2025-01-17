QT       += core gui 3dcore 3drender 3dinput 3dextras

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
RC_ICONS = XPlor.ico

CONFIG += c++17

# INCLUDEPATH += "C:/Program Files (x86)/Windows Kits/10/Include/10.0.26100.0/um"
# LIBS += -L"C:/Program Files (x86)/Windows Kits/10/Lib/10.0.26100.0/um/x64" \
#         -ldxcompiler

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    aboutdialog.cpp \
    main.cpp \
    mainwindow.cpp \
    modelviewer.cpp

HEADERS += \
    aboutdialog.h \
    compression.h \
    enums.h \
    ffparser.h \
    mainwindow.h \
    modelviewer.h \
    structs.h \
    utils.h \
    zfparser.h

FORMS += \
    aboutdialog.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Data.qrc
