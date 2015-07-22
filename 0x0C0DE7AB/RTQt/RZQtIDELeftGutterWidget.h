#ifndef LEFTGUTTERWIDGET_H
#define LEFTGUTTERWIDGET_H

#include <QWidget>
#include <QList>

#include "RZQtIDELeftGutterWidgetLine.h"
#include "RZQtIDELeftGutterWidgetLines.h"

class QTextDocument;

class RZQtIDELeftGutterWidget : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(QColor gutterBackgroundColour READ gutterBackgroundColour WRITE setGutterBackgroundColour DESIGNABLE true SCRIPTABLE true)
    Q_PROPERTY(QColor gutterTextColour READ gutterTextColour WRITE setGutterTextColour DESIGNABLE true SCRIPTABLE true)
    Q_PROPERTY(QColor breakpointColour READ breakpointColour WRITE setBreakpointColour DESIGNABLE true SCRIPTABLE true)
    Q_PROPERTY(int textSize READ textSize WRITE setTextSize DESIGNABLE true SCRIPTABLE true)
    Q_PROPERTY(int breakpointRadius READ breakpointRadius WRITE setBreakpointRadius DESIGNABLE true SCRIPTABLE true)

public:
    explicit RZQtIDELeftGutterWidget(QWidget *parent = 0);

    inline QColor gutterBackgroundColour() const {return m_gutterBackgroundColour; }
    inline void setGutterBackgroundColour(QColor const &value) { m_gutterBackgroundColour = value; }

    inline QColor gutterTextColour() const {return m_gutterTextColour; }
    inline void setGutterTextColour(QColor const &value) { m_gutterTextColour = value; }

    inline QColor breakpointColour() const {return m_breakpointColour; }
    inline void setBreakpointColour(QColor const &value) { m_breakpointColour = value; }

    inline int textSize() const { return m_textSize; }
    inline void setTextSize(int value) { m_textSize = value; }

    inline int breakpointRadius() const { return m_breakpointRadius; }
    inline void setBreakpointRadius(int value) { m_breakpointRadius = value; }

    RZQtIDELeftGutterWidgetLines const *lines() const;
    void setCurrentLine(int lineNumber);
    int currentLine() const;
    void clearCurrentLine();

public slots:
    void changeDocument(QTextDocument *);
    void scrollTo(int);
    void setAttractMode() { m_attractMode = true; } // hack crz

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

signals:

private:
    void buildLines();
    void addRandomAdorments();

    QTextDocument *m_document;

    int m_verticalScrollOffset {0};
    int m_currentLineNumber {0};

    RZQtIDELeftGutterWidgetLines m_lines;

    QColor m_gutterBackgroundColour { Qt::lightGray };
    QColor m_gutterTextColour { Qt::blue };
    QColor m_breakpointColour { Qt::red };
    int m_textSize {12};
    int m_breakpointRadius {8};

    bool m_attractMode {false};
};

#endif // LEFTGUTTERWIDGET_H
