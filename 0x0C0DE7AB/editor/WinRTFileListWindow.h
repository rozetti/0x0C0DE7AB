#ifndef WINRTFILELISTWINDOW_H
#define WINRTFILELISTWINDOW_H

#include <QMainWindow>

namespace Ui {
class WinRTFileListWindow;
}

class WinRTFileListWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit WinRTFileListWindow(QWidget *parent = 0);
    ~WinRTFileListWindow();

private:
    Ui::WinRTFileListWindow *ui;
};

#endif // WINRTFILELISTWINDOW_H
