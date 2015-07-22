#include "RunWindow.h"
#include "ui_RunWindow.h"

#include "RZQtSubCWorker.h"

#include <QDir>
#include <QThread>
#include <QObject>
#include <QFile>
#include <QtWidgets>
#include <QScroller>

extern "C"
{
#include "6IT.h"
}

static Ui::RunWindow *_ui;

void RunWindow::printString(QString const &s, int id)
{
    ui->console->printString(s, id);
}

RunWindow::RunWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RunWindow)
{
    _ui = ui;

    ui->setupUi(this);
}

RunWindow::~RunWindow()
{
    delete ui;
}

void RunWindow::on_btnBack_clicked()
{
    ui->console->clear();

    emit navigatedBack();
}

void RunWindow::runStarted()
{
    ui->console->clear();
}

void RunWindow::runFinished()
{
}
