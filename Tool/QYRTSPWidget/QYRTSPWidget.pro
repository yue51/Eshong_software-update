#-------------------------------------------------
#
# Project created by QtCreator 2011-07-08T15:33:32
#
#-------------------------------------------------

TARGET = QYRTSPWidget
TEMPLATE = lib
CONFIG +=staticlib

QT += core gui
QT += opengl

SOURCES += \
    QYPanelVideo.cpp \
    QYVideoWidget.cpp \
    QYPixViewer.cpp \
    QYDlgToolBar.cpp \
    QYVideoShow.cpp \
    QYDlgHotBar.cpp \
    QYDlgPano.cpp \
    QYDlgPanoHalf.cpp

HEADERS += \
    QYPanelVideo.h \
    QYVideoWidget.h \
    QYPixViewer.h \
    QYDlgToolBar.h \
    QYVideoShow.h \
    QYDlgHotBar.h \
    QYDlgPano.h \
    QYDlgPanoHalf.h

INCLUDEPATH += ./

RESOURCES += \
    resQYRTSPWidget.qrc

FORMS += \
    QYVideoWidget.ui \
    QYDlgToolBar.ui \
    QYVideoShow.ui \
    QYDlgHotBar.ui \
    QYDlgPano.ui \
    QYDlgPanoHalf.ui

DESTDIR += ./Lib
DLLDESTDIR = ./Bin
