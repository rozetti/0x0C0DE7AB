include(../common.pri)

QT -= gui
QT       += widgets

TARGET = RTQt
TEMPLATE = lib
CONFIG += staticlib

DEFINES += RTQT_LIBRARY

SOURCES += RTQt.cpp \
    RZQtScrollArea.cpp \
    RZQtTextDocumentHelper.cpp \
    RZQtCodeEditor.cpp \
    RZQtIDELeftGutterWidget.cpp \
    RZQtIDEWidget.cpp \
    RZQtConsoleWidget.cpp \
    RZQtIDELeftGutterWidgetLine.cpp \
    RZQtIDELeftGutterWidgetLines.cpp \
    RZQtIDEFactory.cpp

HEADERS += RTQt.h \
    rtqt_global.h \
    RZQtScrollArea.h \
    RZQtTextDocumentHelper.h \
    RZQtCodeEditor.h \
    RZQtIDELeftGutterWidget.h \
    RZQtIDEWidget.h \
    RZQtConsoleWidget.h \
    RZQtIDELeftGutterWidgetLine.h \
    RZQtIDELeftGutterWidgetLines.h \
    RZQtIDEFactory.h

FORMS += \
    RZQtIDEWidget.ui \
    RZQtConsoleWidget.ui

unix {
    target.path = /usr/lib
    INSTALLS += target
}

