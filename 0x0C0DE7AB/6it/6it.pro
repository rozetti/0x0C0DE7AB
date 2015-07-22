include(../common.pri)

#QT       -= gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

DEFINES += _6IT_DEBU66ER

TARGET = 6it

TEMPLATE = lib
CONFIG += staticlib
INCLUDEPATH += $(_6IT_ROOT)/6IT

SOURCES += \
    $(_6IT_ROOT)/6IT/SubC_complete.c \
    RZQtSubCWorker.cpp \
    RZQtSubCSyntaxHighlighter.cpp

HEADERS += \
    RZQtSubCWorker.h \
    RZQtSubCSyntaxHighlighter.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

FORMS +=

