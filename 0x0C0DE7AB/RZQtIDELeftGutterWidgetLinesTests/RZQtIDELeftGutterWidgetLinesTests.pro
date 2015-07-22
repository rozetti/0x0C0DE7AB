include(../tests_common.pri)

QT       += testlib

QT       -= gui

TARGET = tst_RZQtIDELeftGutterWidgetLinesTestsTest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += \
    RZQtIDELeftGutterWidgetLinesTests.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../RTQt/release/ -lRTQt
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../RTQt/debug/ -lRTQt
else:unix: LIBS += -L$$OUT_PWD/../RTQt/ -lRTQt

INCLUDEPATH += $$PWD/../RTQt
DEPENDPATH += $$PWD/../RTQt

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../RTQt/release/libRTQt.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../RTQt/debug/libRTQt.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../RTQt/release/RTQt.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../RTQt/debug/RTQt.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../RTQt/libRTQt.a
