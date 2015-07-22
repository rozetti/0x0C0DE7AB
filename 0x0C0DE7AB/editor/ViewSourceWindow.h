#ifndef VIEWSOURCEWINDOW_H
#define VIEWSOURCEWINDOW_H

#include <QMainWindow>

namespace Ui {
class ViewSourceWindow;
}

class ViewSourceWindow : public QMainWindow
{
    Q_OBJECT

signals:
    void navigatedBack();
    void runCode(QString const &);

public:
    explicit ViewSourceWindow(QWidget *parent = 0);
    ~ViewSourceWindow();

public slots:
    void loadFile(QString file);
    void navigateBack();
    void compile();

private slots:
    void on_btnBack_clicked();

    void on_pushButton_clicked();


    void on_btnRun_clicked();

private:
    Ui::ViewSourceWindow *ui;
};

#endif // VIEWSOURCEWINDOW_H
