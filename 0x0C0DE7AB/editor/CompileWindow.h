#pragma once

#include <QMainWindow>

#include "RZQtSubCWorker.h"

namespace Ui {
class CompileWindow;
}

class CompileWindow : public QMainWindow
{
    Q_OBJECT

public:
    CompileWindow(RZQtSubCWorker &worker, QWidget *parent = 0);
    ~CompileWindow();

signals:
    void navigatedBack();
    void runClicked();

public slots:
    void printString(QString const &s, int);
    void compileStarted();
    void compileFinished();
    void clear();

private slots:
    void on_btnRun_clicked();
    void on_btnBack_clicked();

private:
    Ui::CompileWindow *ui;
    RZQtSubCWorker &m_worker;

    QString m_sourceCode;
};

