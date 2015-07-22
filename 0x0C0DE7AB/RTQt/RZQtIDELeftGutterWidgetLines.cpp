#include "RZQtIDELeftGutterWidgetLines.h"

#include <algorithm>

RZQtIDELeftGutterWidgetLines::RZQtIDELeftGutterWidgetLines(IRZQtIDEFactory &factory) :
    m_factory(factory)
{
}

void RZQtIDELeftGutterWidgetLines::clear()
{
    m_lines.clear();
}

IRZQtIDELeftGutterWidgetLine *RZQtIDELeftGutterWidgetLines::append()
{
    IRZQtIDELeftGutterWidgetLine *line = m_factory.createLeftGutterLine();

    line->setNumber(m_lines.size() + 1);
    m_lines.push_back(std::unique_ptr<IRZQtIDELeftGutterWidgetLine>(line));

    return line;
}

IRZQtIDELeftGutterWidgetLine *RZQtIDELeftGutterWidgetLines::getLine(int line_number) const
{
    if (0 == line_number)
    {
        throw std::runtime_error("cannot have line number 0");
    }

    auto it = m_lines.begin();
    std::advance(it, line_number - 1);
    return it->get();
}
