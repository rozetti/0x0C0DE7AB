#include <QApplication>
#include <QStyle>
#include <QStyleFactory>
#include <QThread>
#include <QFile>
#include <QDebug>

#include "ViewSourceWindow.h"
#include "FileListWindow.h"
#include "CompileWindow.h"
#include "RunWindow.h"
#include "RZQtSubCWorker.h"

static QString load_stylesheet(QString const &filename)
{
    QFile f(filename);

    QString s;
    if (f.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Loaded Stylesheet " << filename;
        s = f.readAll();
        f.close();
    }

    return s;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    auto keys = QStyleFactory::keys();
    for (auto s : keys)
    {
        qDebug(s.toStdString().c_str());
    }

    QString ss = load_stylesheet(":/Stylesheets/common.qss");

#ifdef _6IT_UI_MOBILE
    ss.append(load_stylesheet(":/Stylesheets/common_mobile.qss"));
#else
    ss.append(load_stylesheet(":/Stylesheets/common_desktop.qss"));
#endif

#ifdef _6IT_QT_WINRT_DESKTOP
    ss.append(load_stylesheet(":/Stylesheets/winrt_desktop.qss"));
#elif defined(_6IT_QT_WINRT_PHONE)
    a.setStyle(QStyleFactory::create("Fusion"));
    ss.append(load_stylesheet(":/Stylesheets/winrt_phone.qss"));
#elif defined(_6IT_QT_WINRT_DESKTOP)
    ss.append(load_stylesheet(":/Stylesheets/windows_desktop.qss"));
#elif defined(_6IT_QT_IOS)
    ss.append(load_stylesheet(":/Stylesheets/ios.qss"));
#elif defined(_6IT_QT_ANDROID)
    a.setStyle(QStyleFactory::create("Fusion"));
    ss.append(load_stylesheet(":/Stylesheets/android.qss"));
#elif defined(_6IT_QT_LINUX_DESKTOP)
    ss.append(load_stylesheet(":/Stylesheets/linux_desktop.qss"));
#endif

    a.setStyleSheet(ss);

    QThread thread;
    auto pworker = new RZQtSubCWorker();
    auto &worker = *pworker;
    worker.moveToThread(&thread);
    thread.start();

    FileListWindow fileListWindow;
    ViewSourceWindow editorWindow;
    RunWindow runWindow;
    CompileWindow compileWindow(worker);
    fileListWindow.show();

    QObject::connect(&fileListWindow, SIGNAL(sourceSelected(QString)), &editorWindow, SLOT(show()));
    QObject::connect(&fileListWindow, SIGNAL(sourceSelected(QString)), &editorWindow, SLOT(loadFile(QString)));
    QObject::connect(&fileListWindow, SIGNAL(sourceSelected(QString)), &fileListWindow, SLOT(hide()));

    QObject::connect(&editorWindow, SIGNAL(navigatedBack()), &fileListWindow, SLOT(show()));
    QObject::connect(&editorWindow, SIGNAL(navigatedBack()), &editorWindow, SLOT(hide()));

    QObject::connect(&editorWindow, SIGNAL(runCode(QString const &)), &editorWindow, SLOT(hide()));
    QObject::connect(&editorWindow, SIGNAL(runCode(QString const &)), &compileWindow, SLOT(show()));
    QObject::connect(&editorWindow, SIGNAL(runCode(QString const &)), &compileWindow, SLOT(clear()));
    QObject::connect(&editorWindow, SIGNAL(runCode(QString const &)), &worker, SLOT(setSource(QString const &)));

    QObject::connect(&compileWindow, SIGNAL(navigatedBack()), &editorWindow, SLOT(show()));
    QObject::connect(&compileWindow, SIGNAL(navigatedBack()), &compileWindow, SLOT(hide()));
    QObject::connect(&worker, SIGNAL(compilationWillStart()), &compileWindow, SLOT(compileStarted()));
    QObject::connect(&worker, SIGNAL(compilationDidFinish()), &compileWindow, SLOT(compileFinished()));

    QObject::connect(&compileWindow, SIGNAL(runClicked()), &compileWindow, SLOT(hide()));
    QObject::connect(&compileWindow, SIGNAL(runClicked()), &runWindow, SLOT(show()));
    QObject::connect(&compileWindow, SIGNAL(runClicked()), &worker, SLOT(run()));

    QObject::connect(&runWindow, SIGNAL(navigatedBack()), &compileWindow, SLOT(show()));
    QObject::connect(&runWindow, SIGNAL(navigatedBack()), &runWindow, SLOT(hide()));
    QObject::connect(&worker, SIGNAL(runWillStart()), &runWindow, SLOT(runStarted()));
    QObject::connect(&worker, SIGNAL(runDidFinish()), &runWindow, SLOT(runFinished()));

    QObject::connect(&worker, SIGNAL(sourceChanged()), &worker, SLOT(compile()));
    QObject::connect(&worker, SIGNAL(compilerConsoleOutput(QString const &, int)), &compileWindow, SLOT(printString(QString const &, int)));
    QObject::connect(&worker, SIGNAL(runConsoleOutput(QString const &, int)), &runWindow, SLOT(printString(QString const &, int)));

    return a.exec();
}
