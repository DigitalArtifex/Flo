#ifndef QANIMATEDWIDGET_H
#define QANIMATEDWIDGET_H

#include <QObject>
#include <QFrame>
#include <QLabel>
#include <QGridLayout>
#include <QPixmap>
#include <QPainter>
#include <QResizeEvent>

#include "qwidgetanimation.h"

class QAnimatedWidget : public QFrame
{
    Q_OBJECT
public:
    explicit QAnimatedWidget(QWidget *parent = nullptr);
    ~QAnimatedWidget();

    virtual void animateIn();
    virtual void animateOut();


    QWidget *widget() const;
    void setWidget(QWidget *widget);
    void setGeometryIn(const QRect &geometryIn);
    void setGeometryOut(const QRect &geometryOut);
    void setPositionIn(QPoint positionIn);
    void setPositionOut(QPoint positionOut);
    void setBlurIn(qreal blurIn);
    void setBlurOut(qreal blurOut);
    void setOpacityIn(qreal opacityIn);
    void setOpacityOut(qreal opacityOut);
    void setDuration(qint32 duration);
    void setHeightIn(qint32 heightIn);
    void setHeightOut(qint32 heightOut);
    void setWidthIn(qint32 widthIn);
    void setWidthOut(qint32 widthOut);

    virtual void setStyleSheet(QString styleSheet);

protected:
    virtual void resizeEvent(QResizeEvent *event);

signals:
    void animatedIn();
    void animatedOut();

private slots:
    void on_animationIn_finished();
    void on_animationOut_finished();
    void on_animationFinal_finished();

private:
    QWidgetAnimation *m_animationIn = nullptr;
    QWidgetAnimation *m_animationOut = nullptr;
    QWidgetAnimation *m_animationFinal = nullptr;

    QGridLayout *m_layout = nullptr;

    QRect m_geometryIn = QRect(0,0,0,0);
    QRect m_geometryOut = QRect(0,0,0,0);
    QPoint m_positionIn = QPoint(0,0);
    QPoint m_positionOut = QPoint(0,0);

    qreal m_blurIn = 0;
    qreal m_blurOut = 0;
    qreal m_opacityIn = 0;
    qreal m_opacityOut = 0;

    qint32 m_duration = 100;
    qint32 m_heightIn = 0;
    qint32 m_heightOut = 0;
    qint32 m_widthIn = 0;
    qint32 m_widthOut = 0;

    QWidget *m_widget = nullptr;
    QLabel *m_snapshotLabel = nullptr;
};

#endif // QANIMATEDWIDGET_H
