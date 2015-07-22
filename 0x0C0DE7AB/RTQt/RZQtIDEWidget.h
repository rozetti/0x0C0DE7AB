#ifndef IDEWIDGET_H
#define IDEWIDGET_H

#include <QWidget>

namespace Ui {
class RZQtIDEWidget;
}

class QTextDocument;

class LineNumberArea;
class RZQtCodeEditor;

class RZQtIDEWidget : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(QString sourceCode READ sourceCode WRITE setSourceCode DESIGNABLE true SCRIPTABLE true)

public:
    explicit RZQtIDEWidget(QWidget *parent = 0);
    ~RZQtIDEWidget();

    void setSourceCode(const QString &text);
    QString sourceCode();
    void setEditing(bool editable);

signals:
    void documentChanged(QTextDocument *);

private:
    bool eventFilter(QObject *target, QEvent *event);

    Ui::RZQtIDEWidget *ui;

    bool m_isEditing;
    bool m_isInVerticalScrollbar { false };
    bool m_isInHorizontalScrollbar { false };
};

#endif // IDEWIDGET_H
