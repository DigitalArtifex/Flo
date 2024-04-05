#ifndef QWIDGETANIMATION_H
#define QWIDGETANIMATION_H

#include <QObject>
#include <QWidget>
#include <QPoint>
#include <QRect>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QGraphicsBlurEffect>
#include <QGraphicsOpacityEffect>

class QWidgetAnimation : public QObject
{
    Q_OBJECT
public:
    enum AnimationType {
        Static = 0,
        Height = 1,
        Width = 2,
        Position = 4,
        Geometry = 8,
        Opacity = 16,
        Blur = 32,
    };

    explicit QWidgetAnimation(QWidget *target, QObject *parent = nullptr);

    virtual void start();
    virtual void stop();

    qreal startOpacity() const;
    void setStartOpacity(qreal newStartOpacity);

    qreal endOpacity() const;
    void setEndOpacity(qreal newEndOpacity);

    qreal startBlur() const;
    void setStartBlur(qreal newStartBlur);

    qreal endBlur() const;
    void setEndBlur(qreal newEndBlur);

    QRect startGeometry() const;
    void setStartGeometry(const QRect &newStartGeometry);

    QPoint endPosition() const;
    void setEndPosition(QPoint newEndPosition);

    QRect endGeometry() const;
    void setEndGeometry(const QRect &newEndGeometry);

    QPoint startPosition() const;
    void setStartPosition(QPoint newStartPosition);

    qint32 endWidth() const;
    void setEndWidth(qint32 newEndWidth);

    qint32 startWidth() const;
    void setStartWidth(qint32 newStartWidth);

    qint32 endHeight() const;
    void setEndHeight(qint32 newEndHeight);

    qint32 startHeight() const;
    void setStartHeight(qint32 newStartHeight);

    bool hasAnimationType(AnimationType type) const;
    void setAnimationType(AnimationType newAnimationType);

    void setDuration(qint32 newDuration);

    AnimationType animationType() const;

signals:
    void finished();
    void started();

protected slots:
    void on_animationsFinished();

private:
    //Animations
    QPropertyAnimation *_minHeightAnimation = nullptr;
    QPropertyAnimation *_maxHeightAnimation = nullptr;
    QPropertyAnimation *_minWidthAnimation = nullptr;
    QPropertyAnimation *_maxWidthAnimation = nullptr;
    QPropertyAnimation *_positionAnimation = nullptr;
    QPropertyAnimation *_geometryAnimation = nullptr;
    QPropertyAnimation *_opacityAnimation = nullptr;
    QPropertyAnimation *_blurAnimation = nullptr;
    QParallelAnimationGroup *_animations = nullptr;

    //Effects
    QGraphicsOpacityEffect *_opacityEffect = nullptr;
    QGraphicsBlurEffect *_blurEffect = nullptr;

    //Control
    QWidget *_target = nullptr;

    AnimationType _animationType = Static;

    qint32 _startHeight = 0;
    qint32 _endHeight = 0;
    qint32 _startWidth = 0;
    qint32 _endWidth = 0;
    qint32 _duration = 0;

    QPoint _startPosition = QPoint(0,0);
    QPoint _endPosition = QPoint(0,0);

    QRect _startGeometry = QRect(0,0,0,0);
    QRect _endGeometry = QRect(0,0,0,0);

    qreal _startOpacity = 0.0;
    qreal _endOpacity = 0.0;
    qreal _startBlur = 0.0;
    qreal _endBlur = 0.0;
};

#endif // QWIDGETANIMATION_H
