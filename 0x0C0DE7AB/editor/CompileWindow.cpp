#include "CompileWindow.h"
#include "ui_CompileWindow.h"

#include "RZQtSubCWorker.h"

#include <QDir>
#include <QThread>
#include <QObject>
#include <QFile>
#include <QtWidgets>

static Ui::CompileWindow *_ui;

CompileWindow::CompileWindow(RZQtSubCWorker &worker, QWidget *parent) :
    QMainWindow(parent),
    m_worker(worker),
    ui(new Ui::CompileWindow)
{
    _ui = ui;

    ui->setupUi(this);
}

CompileWindow::~CompileWindow()
{
    delete ui;
}

void CompileWindow::printString(const QString &s, int id)
{
    ui->console->printString(s, id);
}

void CompileWindow::on_btnBack_clicked()
{
    ui->console->clear(); // hack crz

    emit navigatedBack();
}

void CompileWindow::on_btnRun_clicked()
{
    emit runClicked();
}

void CompileWindow::compileStarted()
{
    ui->btnRun->setEnabled(false);
}

void CompileWindow::compileFinished()
{
    ui->btnRun->setEnabled(true);
}

void CompileWindow::clear()
{
    ui->console->clear();
}

