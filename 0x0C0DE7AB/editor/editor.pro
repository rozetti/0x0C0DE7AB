include(../common.pri)

ui_mobile {
UI_FOLDER = Mobile
FORMS += Mobile/FileListWindow.ui
FORMS += Mobile/ViewSourceWindow.ui
} else:ui_desktop {
UI_FOLDER = Desktop
FORMS += Desktop/FileListWindow.ui
FORMS += Desktop/ViewSourceWindow.ui
} else {
error("unsupported UI")
}

WINRT_MANIFEST.background = black
WINRT_MANIFEST.name = 0x0C0DE7AB
WINRT_MANIFEST.logo_splash = SplashScreen.png

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
INCLUDEPATH += $(_6IT_ROOT)/6IT

TARGET = editor
TEMPLATE = app

SOURCES += main.cpp\
    FileListWindow.cpp \
    ViewSourceWindow.cpp \
    CompileWindow.cpp \
    RunWindow.cpp

HEADERS  += \
    FileListWindow.h \
    ViewSourceWindow.h \
    CompileWindow.h \
    RunWindow.h

FORMS    += \
    RunWindow.ui \
    CompileWindow.ui

RESOURCES += \
    $(_6IT_ROOT)/Samples/TestFiles/samples.qrc \
    Stylesheets.qrc

DISTFILES += \
    source.txt


win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../6it/release/ -l6it
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../6it/debug/ -l6it
else:unix: LIBS += -L$$OUT_PWD/../6it/ -l6it

INCLUDEPATH += $$PWD/../6it
DEPENDPATH += $$PWD/../6it

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../6it/release/lib6it.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../6it/debug/lib6it.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../6it/release/6it.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../6it/debug/6it.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../6it/lib6it.a

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
