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
    QWidgetAnimation *_animationIn = nullptr;
    QWidgetAnimation *_animationOut = nullptr;
    QWidgetAnimation *_animationFinal = nullptr;

    QGridLayout *_layout = nullptr;

    QRect _geometryIn = QRect(0,0,0,0);
    QRect _geometryOut = QRect(0,0,0,0);
    QPoint _positionIn = QPoint(0,0);
    QPoint _positionOut = QPoint(0,0);

    qreal _blurIn = 0;
    qreal _blurOut = 0;
    qreal _opacityIn = 0;
    qreal _opacityOut = 0;

    qint32 _duration = 100;
    qint32 _heightIn = 0;
    qint32 _heightOut = 0;
    qint32 _widthIn = 0;
    qint32 _widthOut = 0;

    QWidget *_widget = nullptr;
    QLabel *_snapshotLabel = nullptr;
};

#endif // QANIMATEDWIDGET_H
