#include "RZQtScrollArea.h"

#include <QtWidgets>

RZQtScrollArea::RZQtScrollArea(QWidget *parent) :
    QScrollArea(parent),
    m_allowHorizontalScrolling(true),
    m_allowVerticalScrolling(true),
    m_clampToBottom(false)
{
    QScroller::grabGesture(viewport(), QScroller::LeftMouseButtonGesture);

    updateScrollingPolicy();
}

void RZQtScrollArea::mousePressEvent(QMouseEvent *event)
{
    emit userInteracted();
}

void RZQtScrollArea::allowVerticalScrolling(bool b)
{
    m_allowVerticalScrolling = b;
    updateScrollingPolicy();
}

void RZQtScrollArea::allowHorizontalScrolling(bool b)
{
    m_allowHorizontalScrolling = b;
    updateScrollingPolicy();
}

void RZQtScrollArea::setClampToBottom(bool b)
{
    m_clampToBottom = b;
    updateScrollingPolicy();
}

void RZQtScrollArea::setAllowOvershoot(bool b)
{
    m_allowOvershoot = b;
    updateScrollingPolicy();
}

void RZQtScrollArea::moveScrollBarToBottom(int min, int max)
{
    Q_UNUSED(min);
    verticalScrollBar()->setValue(max);
}

void RZQtScrollArea::updateScrollingPolicy()
{
    auto scroller = QScroller::scroller(viewport());
    auto props = scroller->scrollerProperties();

    if (!m_allowOvershoot)
    {
        props.setScrollMetric(QScrollerProperties::HorizontalOvershootPolicy, QScrollerProperties::OvershootAlwaysOff);
        props.setScrollMetric(QScrollerProperties::VerticalOvershootPolicy, QScrollerProperties::OvershootAlwaysOff);
        props.setScrollMetric(QScrollerProperties::OvershootDragResistanceFactor, 0);
        props.setScrollMetric(QScrollerProperties::OvershootDragDistanceFactor, 0);
        props.setScrollMetric(QScrollerProperties::OvershootScrollDistanceFactor, 0);
    }
    else
    {
        if (m_allowHorizontalScrolling)
        {
            setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
            props.setScrollMetric(QScrollerProperties::HorizontalOvershootPolicy, QScrollerProperties::OvershootWhenScrollable);
        }
        else
        {
            setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
            props.setScrollMetric(QScrollerProperties::HorizontalOvershootPolicy, QScrollerProperties::OvershootAlwaysOff);
        }

        if (m_allowVerticalScrolling)
        {
            setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
            props.setScrollMetric(QScrollerProperties::VerticalOvershootPolicy, QScrollerProperties::OvershootWhenScrollable);
        }
        else
        {
            setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
            props.setScrollMetric(QScrollerProperties::VerticalOvershootPolicy, QScrollerProperties::OvershootAlwaysOff);
        }
    }

    scroller->setScrollerProperties(props);

    QScrollBar* vs = verticalScrollBar();
    if (m_clampToBottom)
    {
        QObject::connect(vs, SIGNAL(rangeChanged(int,int)), this, SLOT(moveScrollBarToBottom(int, int)));
    }
    else
    {
        QObject::disconnect(vs, SIGNAL(rangeChanged(int,int)), this, SLOT(moveScrollBarToBottom(int, int)));
    }
}

