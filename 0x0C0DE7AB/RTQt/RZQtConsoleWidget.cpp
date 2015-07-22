#include "RZQtConsoleWidget.h"
#include "ui_RZQtConsoleWidget.h"

#include <QScroller>
#include <QMutex>
#include <QMutexLocker>
#include <QDebug>
#include <QScrollBar>

RZQtConsoleWidget::RZQtConsoleWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RZQtConsoleWidget)
{
    ui->setupUi(this);

    ui->scrollArea->setAllowOvershoot(false);
    ui->scrollArea->setClampToBottom(true);

    QObject::connect(this, SIGNAL(consoleTextChanged(int)), this, SLOT(updateConsoleText(int)), Qt::QueuedConnection);
}

RZQtConsoleWidget::~RZQtConsoleWidget()
{
    delete ui;
}

void RZQtConsoleWidget::printString(QString const &s, int id)
{
    QMutexLocker locker(&m_consoleOutputMutex);

    qDebug() << id << ": " << s.toStdString().c_str();
    m_consoleOutput.append(s);

    m_lastSignalId = id;

    emit consoleTextChanged(id);
}

void RZQtConsoleWidget::updateConsoleText(int id)
{
    if (id < m_lastSignalId)
    {
        qDebug() << "dumping: " << id;
        return;
    }

    QMutexLocker locker(&m_consoleOutputMutex);

    ui->consoleOutput->setPlainText(m_consoleOutput);
    WrapToContent();
}

void RZQtConsoleWidget::clear()
{
    ui->scrollArea->verticalScrollBar()->setValue(0);
    ui->scrollArea->horizontalScrollBar()->setValue(0);
    ui->consoleOutput->setPlainText("");

    QMutexLocker locker(&m_consoleOutputMutex);

    m_consoleOutput = "";
}

void RZQtConsoleWidget::WrapToContent()
{
    auto height = ui->consoleOutput->document()->size().height();
    ui->consoleOutput->setFixedHeight(height);
    auto width = ui->consoleOutput->document()->size().width();
    ui->consoleOutput->setFixedWidth(width);
}
