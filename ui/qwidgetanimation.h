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
    ~QWidgetAnimation();

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
    QPropertyAnimation *m_minHeightAnimation = nullptr;
    QPropertyAnimation *m_maxHeightAnimation = nullptr;
    QPropertyAnimation *m_minWidthAnimation = nullptr;
    QPropertyAnimation *m_maxWidthAnimation = nullptr;
    QPropertyAnimation *m_positionAnimation = nullptr;
    QPropertyAnimation *m_geometryAnimation = nullptr;
    QPropertyAnimation *m_opacityAnimation = nullptr;
    QPropertyAnimation *m_blurAnimation = nullptr;
    QParallelAnimationGroup *m_animations = nullptr;

    //Effects
    QGraphicsOpacityEffect *m_opacityEffect = nullptr;
    QGraphicsBlurEffect *m_blurEffect = nullptr;

    //Control
    QWidget *m_target = nullptr;

    AnimationType m_animationType = Static;

    qint32 m_startHeight = 0;
    qint32 m_endHeight = 0;
    qint32 m_startWidth = 0;
    qint32 m_endWidth = 0;
    qint32 m_duration = 0;

    QPoint m_startPosition = QPoint(0,0);
    QPoint m_endPosition = QPoint(0,0);

    QRect m_startGeometry = QRect(0,0,0,0);
    QRect m_endGeometry = QRect(0,0,0,0);

    qreal m_startOpacity = 0.0;
    qreal m_endOpacity = 0.0;
    qreal m_startBlur = 0.0;
    qreal m_endBlur = 0.0;
};

#endif // QWIDGETANIMATION_H
