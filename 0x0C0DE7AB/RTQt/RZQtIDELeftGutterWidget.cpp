#include "RZQtIDELeftGutterWidget.h"

#include <QTextDocument>
#include <QTextBlock>
#include <QWidget>
#include <QEvent>
#include <QPainter>
#include <QRect>
#include <QAbstractTextDocumentLayout>
#include <QDebug>

#include <random>

#include "RZQtIDEFactory.h"

RZQtIDELeftGutterWidget::RZQtIDELeftGutterWidget(QWidget *parent) :
    QWidget(parent),
    m_document(0),
    m_lines(RZQtIDEFactory::_instance)
{
}

void RZQtIDELeftGutterWidget::setCurrentLine(int lineNumber)
{
    if (0 == lineNumber)
    {
        throw std::runtime_error("can not set current line to zero");
    }

    if (m_currentLineNumber != 0)
    {
        m_lines.getLine(m_currentLineNumber)->clearIsCurrent();
    }

    m_currentLineNumber = lineNumber;

    m_lines.getLine(m_currentLineNumber)->setIsCurrent();
}

int RZQtIDELeftGutterWidget::currentLine() const
{
    return m_currentLineNumber;
}

void RZQtIDELeftGutterWidget::clearCurrentLine()
{
    m_currentLineNumber = 0;
}

RZQtIDELeftGutterWidgetLines const *RZQtIDELeftGutterWidget::lines() const
{
    return &m_lines;
}

void RZQtIDELeftGutterWidget::changeDocument(QTextDocument *doc)
{
    m_document = doc;

    buildLines();
}

void RZQtIDELeftGutterWidget::scrollTo(int top)
{
    m_verticalScrollOffset = top;

    update();
}

void RZQtIDELeftGutterWidget::paintEvent(QPaintEvent *event)
{
    auto update_rect = event->rect();

    QPainter painter(this);

    painter.fillRect(update_rect, m_gutterBackgroundColour);

    auto const lines = this->lines();

    for (int i = 0; i < lines->count(); ++i)
    {
        // todo crz: find a testable way to move this into the Line class
        auto block = m_document->findBlockByNumber(i);
        auto block_top = m_document->documentLayout()->blockBoundingRect(block).top() - m_verticalScrollOffset;
        auto block_height = m_document->documentLayout()->blockBoundingRect(block).height();

        if (block_top + block_height < update_rect.top()) continue;
        if (block_top > update_rect.bottom()) break;

        auto line = lines->getLine(i + 1);

        if (line->isCurrent())
        {
            painter.setPen(Qt::yellow);
            painter.setBrush(Qt::green);

            QRect r(0, block_top + (block_height / 2) - 4, update_rect.width(), 8);

            painter.drawRect(r);
        }

        painter.setPen(m_gutterTextColour);
        painter.drawText(0, block_top, width() - 2, block_height, Qt::AlignRight, line->text());

        if (line->hasBreakpoint())
        {
            painter.setPen(m_breakpointColour);
            painter.setBrush(m_breakpointColour);
            painter.drawEllipse(QPoint(10, block_top + (block_height / 2)), m_breakpointRadius, m_breakpointRadius);
        }
    }
}

// todo crz: this is not tested
void RZQtIDELeftGutterWidget::buildLines()
{
    m_lines.clear();

    if (nullptr == m_document || m_document->isEmpty())
    {
        return;
    }

    for (int i = 0; i < m_document->blockCount(); ++i)
    {
        IRZQtIDELeftGutterWidgetLine *line = m_lines.append();

        if (0 != m_currentLineNumber && line->number() == m_currentLineNumber)
        {
            line->setIsCurrent();
        }
    }

    if (m_attractMode)
    {
        addRandomAdorments();
    }
}

void RZQtIDELeftGutterWidget::addRandomAdorments()
{
    std::default_random_engine rng(std::random_device{}());
    std::uniform_real_distribution<double> dist(0, 1);

    for (int i = 0; i < m_lines.count(); ++i)
    {
        auto line = m_lines.getLine(i + 1);
        const double random_num = dist(rng);
        if (random_num < 0.2)
        {
            line->setBreakpoint();
        }
    }

    std::uniform_int_distribution<int> line_dist(0, m_lines.count() - 1);
    m_lines.getLine(line_dist(rng) + 1)->setIsCurrent();
}

