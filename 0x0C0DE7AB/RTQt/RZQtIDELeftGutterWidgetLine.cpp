#include "RZQtIDELeftGutterWidgetLine.h"

#include <stdexcept>

RZQtIDELeftGutterWidgetLine::RZQtIDELeftGutterWidgetLine(int line_number) :
    m_lineNumber(line_number)
{
    if (0 == line_number)
    {
        throw std::runtime_error("line number must not be zero");
    }
}

void RZQtIDELeftGutterWidgetLine::setNumber(int line_number)
{
    m_lineNumber = line_number;
}

QString RZQtIDELeftGutterWidgetLine::text() const
{
    return QString::number(m_lineNumber);
}

bool RZQtIDELeftGutterWidgetLine::hasBreakpoint() const
{
    return m_hasBreakpoint;
}

void RZQtIDELeftGutterWidgetLine::setBreakpoint()
{
    m_hasBreakpoint = true;
}

void RZQtIDELeftGutterWidgetLine::clearBreakpoint()
{
    m_hasBreakpoint = false;
}

bool RZQtIDELeftGutterWidgetLine::isCurrent() const
{
    return m_isCurrent;
}

void RZQtIDELeftGutterWidgetLine::setIsCurrent()
{
    m_isCurrent = true;
}

void RZQtIDELeftGutterWidgetLine::clearIsCurrent()
{
    m_isCurrent = false;
}
