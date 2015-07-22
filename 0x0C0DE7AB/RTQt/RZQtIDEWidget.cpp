#include "RZQtIDEWidget.h"
#include "ui_RZQtIDEWidget.h"

#include <QScroller>
#include <QScrollBar>
#include <QDebug>

RZQtIDEWidget::RZQtIDEWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RZQtIDEWidget)
{
    ui->setupUi(this);
    ui->leftGutter->setAttractMode(); // hack crz

    QObject::connect(this, SIGNAL(documentChanged(QTextDocument*)), ui->leftGutter, SLOT(changeDocument(QTextDocument*)));

    QObject::connect(ui->scrollArea->verticalScrollBar(), SIGNAL(valueChanged(int)),
                     ui->leftGutter, SLOT(scrollTo(int)));

    QScroller::grabGesture(ui->scrollArea, QScroller::LeftMouseButtonGesture);
    auto scroller = QScroller::scroller(ui->scrollArea);
    auto props = scroller->scrollerProperties();
    props.setScrollMetric(QScrollerProperties::HorizontalOvershootPolicy, QScrollerProperties::OvershootAlwaysOff);
    props.setScrollMetric(QScrollerProperties::VerticalOvershootPolicy, QScrollerProperties::OvershootAlwaysOff);
    props.setScrollMetric(QScrollerProperties::OvershootDragResistanceFactor, 0);
    props.setScrollMetric(QScrollerProperties::OvershootDragDistanceFactor, 0);
    props.setScrollMetric(QScrollerProperties::OvershootScrollDistanceFactor, 0);
    scroller->setScrollerProperties(props);

    QObject::connect(ui->codeEditor, &RZQtCodeEditor::clicked, [=](QPoint pos, int /*char_pos*/)
    {
#if defined(_6IT_UI_MOBILE)
        if (m_isEditing)
        {
            this->setEditing(false);
        }
        else
        {
            this->setEditing(true);
            ui->codeEditor->MoveCursorTo(pos);
        }
#else
        ui->codeEditor->MoveCursorTo(pos);
#endif
    });

    QObject::connect(ui->codeEditor, &RZQtCodeEditor::resized, [=]()
    {
        ui->codeEditor->ensureCursorVisible();
    });

    ui->scrollArea->verticalScrollBar()->installEventFilter(this);
    ui->scrollArea->horizontalScrollBar()->installEventFilter(this);
    ui->codeEditor->installEventFilter(this);
}

RZQtIDEWidget::~RZQtIDEWidget()
{
    delete ui;
}

bool RZQtIDEWidget::eventFilter(QObject *target, QEvent *event)
{
    if (ui->scrollArea->verticalScrollBar() == target)
    {
        if (event->type() == QEvent::Enter)
        {
            QScroller::ungrabGesture(ui->scrollArea);
            qDebug("v in");
            m_isInVerticalScrollbar = true;
        }
        if (event->type() == QEvent::Leave)
        {
            QScroller::grabGesture(ui->scrollArea, QScroller::LeftMouseButtonGesture);
            qDebug("v out");
            m_isInVerticalScrollbar = false;
        }

        if (event->type() == QEvent::MouseButtonRelease)
        {
            if (m_isInVerticalScrollbar)
            {
                QScroller::grabGesture(ui->scrollArea, QScroller::LeftMouseButtonGesture);
                qDebug("v up");
                m_isInVerticalScrollbar = false;
            }
        }
    }

    if (ui->scrollArea->horizontalScrollBar() == target)
    {
        if (event->type() == QEvent::Enter)
        {
            QScroller::ungrabGesture(ui->scrollArea);
            qDebug("h in");
            m_isInHorizontalScrollbar = true;
        }
        if (event->type() == QEvent::Leave)
        {
            QScroller::grabGesture(ui->scrollArea, QScroller::LeftMouseButtonGesture);
            qDebug("h out");
            m_isInHorizontalScrollbar = false;
        }

        if (event->type() == QEvent::MouseButtonRelease)
        {
            if (m_isInHorizontalScrollbar)
            {
                QScroller::grabGesture(ui->scrollArea, QScroller::LeftMouseButtonGesture);
                qDebug("h up");
                m_isInHorizontalScrollbar = false;
            }
        }
    }

    return QWidget::eventFilter(target, event);
}

void RZQtIDEWidget::setSourceCode(QString const &text)
{
    ui->codeEditor->setText(text);
    setEditing(false);
    ui->codeEditor->WrapToContent();

    emit documentChanged(ui->codeEditor->document());
}

QString RZQtIDEWidget::sourceCode()
{
    return ui->codeEditor->toPlainText();
}

void RZQtIDEWidget::setEditing(bool editable)
{
    if (editable)
    {
        QGuiApplication::inputMethod()->show();
    }
    else
    {
        QGuiApplication::inputMethod()->hide();
    }

    m_isEditing = editable;
}

