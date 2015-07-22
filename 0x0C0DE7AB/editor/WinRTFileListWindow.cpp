#include "WinRTFileListWindow.h"
#include "ui_WinRTFileListWindow.h"

WinRTFileListWindow::WinRTFileListWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::WinRTFileListWindow)
{
    ui->setupUi(this);
}

WinRTFileListWindow::~WinRTFileListWindow()
{
    delete ui;
}
