#ifndef QANIMATEDLISTITEM_H
#define QANIMATEDLISTITEM_H

#include <QObject>
#include <QFrame>
#include <QVBoxLayout>
#include <QTimer>
#include <QMouseEvent>
#include <QStyle>
#include <QElapsedTimer>

#include "../qwidgetanimation.h"

class QAnimatedListItem : public QFrame
{
    Q_OBJECT
public:
    explicit QAnimatedListItem(QWidget *parent = nullptr);

    virtual void animateIn();
    virtual void animateOut();

    virtual void setSelectable(bool selectable);
    virtual void setSelected(bool selected, bool trigger = true);
    virtual void setWidget(QWidget *widget);

    virtual QWidget *widget();

    void setGeometryIn(const QRect &geometryIn);
    void setGeometryOut(const QRect &geometryOut);

    void setPositionIn(QPoint positionIn);
    void setPositionOut(QPoint positionOut);

    void setBlurIn(qreal blurIn);
    void setBlurOut(qreal blurOut);

    void setOpacityIn(qreal opacityIn);
    void setOpacityOut(qreal opacityOut);

    void setDuration(qint32 duration);

    qint32 heightIn() const;
    void setHeightIn(qint32 heightIn);

    qint32 heightOut() const;
    void setHeightOut(qint32 heightOut);

    qint32 widthIn() const;
    void setWidthIn(qint32 widthIn);

    qint32 widthOut() const;
    void setWidthOut(qint32 widthOut);

signals:
    //Animation Signals
    void animationIn_finished(QAnimatedListItem *item);
    void animationOut_finished(QAnimatedListItem *item);
    void selected(QAnimatedListItem *item);
    void deselected(QAnimatedListItem *item);
    void longPressed(QAnimatedListItem *item);
    void doubleClicked(QAnimatedListItem *item);

private slots:
    virtual void on_clickTimer_timeout();

    virtual void mouseDoubleClickEvent(QMouseEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);

    void on_animationIn_finished();
    void on_animationOut_finished();

private:
    bool m_selectable = true;
    bool m_selected = false;
    bool m_pressed = false;
    bool m_longPressed = false;

    QTimer *m_clickTimer = nullptr;

    QWidgetAnimation *m_animationIn = nullptr;
    QWidgetAnimation *m_animationOut = nullptr;
    QWidgetAnimation *m_animationFinal = nullptr;

    QRect m_geometryIn = QRect(0,0,0,0);
    QRect m_geometryOut = QRect(0,0,0,0);
    QPoint m_positionIn = QPoint(0,0);
    QPoint m_positionOut = QPoint(0,0);

    qreal m_blurIn = 0;
    qreal m_blurOut = 0;
    qreal m_opacityIn = 0;
    qreal m_opacityOut = 0;

    qint32 m_duration = 0;
    qint32 m_heightIn = 0;
    qint32 m_heightOut = 0;
    qint32 m_widthIn = 0;
    qint32 m_widthOut = 0;
    qint32 m_clickCount = 0;

    QWidget *m_widget = nullptr;
};

#endif // QANIMATEDLISTITEM_H
