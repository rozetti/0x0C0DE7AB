#pragma once

#include <QMainWindow>
#include <QMutex>

class SubCWorker;

namespace Ui {
class RunWindow;
}

class RunWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit RunWindow(QWidget *parent = 0);
    ~RunWindow();

signals:
    void navigatedBack();

public slots:
    void printString(QString const &s, int);

private slots:
    void on_btnBack_clicked();
    void runStarted();
    void runFinished();

private:
    Ui::RunWindow *ui;
};

