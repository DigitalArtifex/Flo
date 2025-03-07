#ifndef QANIMATEDLISTITEM_H
#define QANIMATEDLISTITEM_H

#include <QObject>
#include <QFrame>
#include <QVBoxLayout>
#include <QTimer>
#include <QMouseEvent>
#include <QStyle>
#include <QMenu>
#include <QElapsedTimer>
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>
#include <QParallelAnimationGroup>

class QAnimatedListItem : public QFrame
{
    Q_OBJECT
public:
    explicit QAnimatedListItem(QWidget *parent = nullptr);

    virtual void setSelectable(bool selectable);
    virtual void setSelected(bool selected, bool trigger = true);

    QParallelAnimationGroup *animations() const;

    QWidget *centralWidget() const;

public slots:
    void setCentralWidget(QWidget *centralWidget);
    void initAnimations();

signals:
    //Animation Signals
    void animationFinished(QAnimatedListItem *item);
    void selected(QAnimatedListItem *item);
    void deselected(QAnimatedListItem *item);
    void longPressed(QAnimatedListItem *item);
    void doubleClicked(QAnimatedListItem *item);

private slots:
    virtual void on_clickTimer_timeout();

    virtual void mouseDoubleClickEvent(QMouseEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);

    void onAnimationFinished();

protected:
    void setContextMenu(QMenu *menu);

private:
    bool m_selectable = true;
    bool m_selected = false;
    bool m_pressed = false;
    bool m_longPressed = false;

    QTimer *m_clickTimer = nullptr;

    QParallelAnimationGroup *m_animations = nullptr;

    QWidget *m_centralWidget = nullptr;
    QVBoxLayout *m_centralLayout = nullptr;

    QMenu *m_contextMenu = nullptr;
};

#endif // QANIMATEDLISTITEM_H
