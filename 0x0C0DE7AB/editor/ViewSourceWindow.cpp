#include "ViewSourceWindow.h"
#include "ui_ViewSourceWindow.h"

#include <QString>
#include <QFile>
#include <QInputEvent>
#include <QPoint>
#include <QScrollBar>
#include <QScroller>
#include <QTextDocument>
#include <QDebug>

#include "RZQtSubCSyntaxHighlighter.h"

ViewSourceWindow::ViewSourceWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ViewSourceWindow)
{
    ui->setupUi(this);

    QObject::connect(ui->ide, &RZQtIDEWidget::documentChanged, [=](QTextDocument *doc)
    {
        // todo crz: need to check this gets binned when the document is binned
        new RZQtSubCSyntaxHighlighter(doc);
    });

#ifdef _6IT_UI_MOBILE
#ifdef _6IT_QT_IOS
    // todo crz: this doesn't work, the OSK is very dodgy on iOS
    QObject::connect(QGuiApplication::inputMethod(), &QInputMethod::keyboardRectangleChanged, [=]()
    {
        auto im = QGuiApplication::inputMethod();
        auto rect = im->keyboardRectangle();

        qDebug() << "OSK rect: " << rect;

        //ui->oskSpacer->changeSize(rect.width(), rect.height());
        //ui->verticalLayout->invalidate();
    });
    QObject::connect(QGuiApplication::inputMethod(), &QInputMethod::visibleChanged, [=]()
    {
        auto visible = QGuiApplication::inputMethod()->isVisible();

        auto im = QGuiApplication::inputMethod();
        auto rect = im->keyboardRectangle();

        qDebug() << "OSK rect: " << rect;

        if (visible)
        {
            ui->oskSpacer->changeSize(0, rect.height());
        }
        else
        {
            ui->oskSpacer->changeSize(0, 0);
        }
        ui->verticalLayout->invalidate();

        qDebug() << "OSK visible: " << visible;
    });
#else
    QObject::connect(QGuiApplication::inputMethod(), &QInputMethod::keyboardRectangleChanged, [=]()
    {
        auto im = QGuiApplication::inputMethod();
        auto rect = im->keyboardRectangle();

        ui->oskSpacer->changeSize(rect.width(), rect.height());
        ui->verticalLayout->invalidate();
    });
#endif
#endif
}

ViewSourceWindow::~ViewSourceWindow()
{
    delete ui;
}

void ViewSourceWindow::loadFile(QString filename)
{
    qDebug(filename.toStdString().c_str());

    QFile file(filename);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug("error opening file");
        return;
    }

    auto data = QString(file.readAll().data());
    void setSourceCode(const QString &text);

    ui->ide->setSourceCode(data);
}

void ViewSourceWindow::navigateBack()
{
    QGuiApplication::inputMethod()->hide();
    emit navigatedBack();
}

void ViewSourceWindow::compile()
{
    emit runCode(ui->ide->sourceCode());
}

void ViewSourceWindow::on_btnBack_clicked()
{
    navigateBack();
}

void ViewSourceWindow::on_pushButton_clicked()
{
    ui->ide->setEditing(true);
}

void ViewSourceWindow::on_btnRun_clicked()
{
    compile();
}

