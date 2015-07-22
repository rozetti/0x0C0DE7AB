#pragma once

#include <QList>
#include "RZQtIDELeftGutterWidgetLine.h"
#include "RZQtIDEFactory.h"

#include <memory>

class RZQtIDELeftGutterWidgetLines {
public:
    RZQtIDELeftGutterWidgetLines(IRZQtIDEFactory &factory);

    int count() const { return (int)m_lines.size(); }
    void clear();
    IRZQtIDELeftGutterWidgetLine *append();

    IRZQtIDELeftGutterWidgetLine *getLine(int line_number) const;

private:
    std::list<std::unique_ptr<IRZQtIDELeftGutterWidgetLine>> m_lines;

    IRZQtIDEFactory &m_factory;
};
