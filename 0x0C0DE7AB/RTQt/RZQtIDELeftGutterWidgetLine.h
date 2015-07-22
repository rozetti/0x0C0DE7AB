#ifndef RZQTIDELEFTGUTTERWIDGETLINE_H
#define RZQTIDELEFTGUTTERWIDGETLINE_H

#include <QList>
#include <QString>

class IRZQtIDELeftGutterWidgetLine
{
public:
    virtual ~IRZQtIDELeftGutterWidgetLine(){}

    virtual int number() const = 0;
    virtual void setNumber(int line_number) = 0;
    virtual QString text() const = 0;

    virtual bool hasBreakpoint() const = 0;
    virtual void setBreakpoint() = 0;
    virtual void clearBreakpoint() = 0;

    virtual bool isCurrent() const = 0;
    virtual void setIsCurrent() = 0;
    virtual void clearIsCurrent() = 0;
};

class RZQtIDELeftGutterWidgetLine : public IRZQtIDELeftGutterWidgetLine
{
public:
    virtual ~RZQtIDELeftGutterWidgetLine() {}

    RZQtIDELeftGutterWidgetLine() {}
    RZQtIDELeftGutterWidgetLine(int lineNumber);

    virtual void setNumber(int line_number) override;
    virtual int number() const override { return m_lineNumber; }

    virtual QString text() const override;

    virtual bool hasBreakpoint() const override;
    virtual void setBreakpoint() override;
    virtual void clearBreakpoint() override;

    virtual bool isCurrent() const override;
    virtual void setIsCurrent() override;
    virtual void clearIsCurrent() override;

private:
    int m_lineNumber {0};
    bool m_hasBreakpoint {false};
    bool m_isCurrent {false};
};

typedef QList<RZQtIDELeftGutterWidgetLine> left_gutter_line_list_t;

#endif // RZQTIDELEFTGUTTERWIDGETLINE_H
