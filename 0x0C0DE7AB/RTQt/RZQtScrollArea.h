#ifndef RZQSCROLLAREA_H
#define RZQSCROLLAREA_H

#include <QScrollArea>

class RZQtScrollArea : public QScrollArea
{
    Q_OBJECT

    Q_PROPERTY(bool clampToBottom READ clampToBottom WRITE setClampToBottom DESIGNABLE true)
    Q_PROPERTY(bool allowOvershoot READ allowOvershoot WRITE setAllowOvershoot DESIGNABLE true)

public:
    RZQtScrollArea(QWidget *parent = 0);

    void mousePressEvent(QMouseEvent *event);

    void allowVerticalScrolling(bool b);
    void allowHorizontalScrolling(bool b);
    bool clampToBottom() const { return m_clampToBottom; }
    void setClampToBottom(bool b);

    bool allowOvershoot() const { return m_allowOvershoot; }
    void setAllowOvershoot(bool);

private:
    void updateScrollingPolicy();

signals:
    void userInteracted();

private:
    bool m_allowVerticalScrolling;
    bool m_allowHorizontalScrolling;
    bool m_clampToBottom;
    bool m_allowOvershoot { true };

private slots:
    void moveScrollBarToBottom(int min, int max);
};

#endif // RZQSCROLLAREA_H
