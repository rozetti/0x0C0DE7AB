#include <QtWidgets>
#include <QVariant>

#include "RZQtCodeEditor.h"
#include "RZQtTextDocumentHelper.h"

#include <QFile>
#include <QString>
#include <QFont>
#include <QTextCursor>

RZQtCodeEditor::RZQtCodeEditor(QWidget *parent) : QTextEdit(parent),
    m_verticalScrollOffset(0),
    m_horizontalOffset(0),
    m_firstVisibleBlockNumber(0),
    m_lastVisibleBlockNumber(0)
{
    // todo crz: use these to propagate changes into the gutter
//    connect(this, SIGNAL(blockCountChanged(int)), this, SLOT(updateLineNumberAreaWidth(int)));
//    connect(this, SIGNAL(updateRequest(QRect,int)), this, SLOT(updateLineNumberArea(QRect,int)));
//    connect(this, SIGNAL(cursorPositionChanged()), this, SLOT(highlightCurrentLine()));

    highlightCurrentLine();
}

void RZQtCodeEditor::resizeEvent(QResizeEvent *e)
{
    QTextEdit::resizeEvent(e);

    emit resized();
}

void RZQtCodeEditor::ScrollBy(int dx, int dy)
{
    scrollContentsBy(dx, dy);
}

void RZQtCodeEditor::scrollContentsBy(int dx, int dy)
{
    m_horizontalOffset += dx;
}

void RZQtCodeEditor::highlightCurrentLine()
{
    QList<QTextEdit::ExtraSelection> extraSelections;

    if (!isReadOnly()) {
        QTextEdit::ExtraSelection selection;

        selection.format.setBackground(m_currentLineHighlightColour);
        selection.format.setProperty(QTextFormat::FullWidthSelection, true);
        selection.cursor = textCursor();
        selection.cursor.clearSelection();
        extraSelections.append(selection);
    }

    setExtraSelections(extraSelections);
}

void RZQtCodeEditor::mousePressEvent ( QMouseEvent * /*event*/ )
{
    m_mouseMoved = false;
}

void RZQtCodeEditor::mouseMoveEvent ( QMouseEvent * /*event*/ )
{
    m_mouseMoved = true;
}

void RZQtCodeEditor::mouseReleaseEvent ( QMouseEvent * event )
{
    if (!m_mouseMoved)
    {
        QTextCursor c = cursorForPosition(event->pos());
        emit clicked(event->pos(), c.position());
    }
}

void RZQtCodeEditor::MoveCursorTo(QPoint pos)
{
    QTextCursor c = cursorForPosition(pos);
    textCursor().setPosition(c.position());
    setTextCursor(c);
    highlightCurrentLine();
}

void RZQtCodeEditor::WrapToContent()
{
    auto height = document()->size().height();
    setFixedHeight(height);
    auto width = document()->size().width();
    setFixedWidth(width);
}
