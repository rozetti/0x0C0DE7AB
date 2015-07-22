#ifndef CONSOLEWIDGET_H
#define CONSOLEWIDGET_H

#include <QWidget>
#include <QMutex>

namespace Ui {
class RZQtConsoleWidget;
}

class RZQtConsoleWidget : public QWidget
{
    Q_OBJECT

signals:
    void consoleTextChanged(int);

public slots:
    void printString(QString const &s, int);
    void clear();

private slots:
    void updateConsoleText(int);

public:
    explicit RZQtConsoleWidget(QWidget *parent = 0);
    ~RZQtConsoleWidget();

private:
    void WrapToContent();

private:
    Ui::RZQtConsoleWidget *ui;

    QString m_consoleOutput;
    QMutex m_consoleOutputMutex;

    int m_lastSignalId { -1 };
};

#endif // CONSOLEWIDGET_H
