#include "qwidgetanimation.h"

QWidgetAnimation::QWidgetAnimation(QWidget *target, QObject *parent) :
    QObject(parent)
{
    m_target = target;
}

QWidgetAnimation::~QWidgetAnimation()
{
    if(m_animations)
        m_animations->deleteLater();
}

void QWidgetAnimation::start()
{
    emit started();

    m_animations = new QParallelAnimationGroup();
    connect(m_animations, SIGNAL(finished()), this, SLOT(on_animationsFinished()));

    if(hasAnimationType(Height))
    {
        m_minHeightAnimation = new QPropertyAnimation(m_target, "minHeight");
        m_minHeightAnimation->setStartValue(m_startHeight);
        m_minHeightAnimation->setEndValue(m_endHeight);
        m_minHeightAnimation->setDuration(m_duration);
        m_animations->addAnimation(m_minHeightAnimation);

        m_maxHeightAnimation = new QPropertyAnimation(m_target, "maxHeight");
        m_maxHeightAnimation->setStartValue(m_startHeight);
        m_maxHeightAnimation->setEndValue(m_endHeight);
        m_maxHeightAnimation->setDuration(m_duration);
        m_animations->addAnimation(m_maxHeightAnimation);
    }

    if(hasAnimationType(Width))
    {
        m_minWidthAnimation = new QPropertyAnimation(m_target, "minWidth");
        m_minWidthAnimation->setStartValue(m_startWidth);
        m_minWidthAnimation->setEndValue(m_endWidth);
        m_minWidthAnimation->setDuration(m_duration);
        m_animations->addAnimation(m_minWidthAnimation);

        m_maxWidthAnimation = new QPropertyAnimation(m_target, "maxWidth");
        m_maxWidthAnimation->setStartValue(m_startWidth);
        m_maxWidthAnimation->setEndValue(m_endWidth);
        m_maxWidthAnimation->setDuration(m_duration);
        m_animations->addAnimation(m_maxWidthAnimation);
    }

    if(hasAnimationType(Geometry))
    {
        m_geometryAnimation = new QPropertyAnimation(m_target, "geometry");
        m_geometryAnimation->setStartValue(m_startGeometry);
        m_geometryAnimation->setEndValue(m_endGeometry);
        m_geometryAnimation->setDuration(m_duration);
        m_animations->addAnimation(m_geometryAnimation);
    }

    if(hasAnimationType(Position))
    {
        m_positionAnimation = new QPropertyAnimation(m_target, "pos");
        m_positionAnimation->setStartValue(m_startPosition);
        m_positionAnimation->setEndValue(m_endPosition);
        m_positionAnimation->setDuration(m_duration);
        m_animations->addAnimation(m_positionAnimation);
    }

    if(hasAnimationType(Opacity))
    {
        m_opacityEffect = new QGraphicsOpacityEffect(m_target);
        m_opacityAnimation = new QPropertyAnimation(m_opacityEffect, "opacity");
        m_opacityAnimation->setStartValue(m_startOpacity);
        m_opacityAnimation->setEndValue(m_endOpacity);
        m_opacityAnimation->setDuration(m_duration);
        m_animations->addAnimation(m_opacityAnimation);
        m_target->setGraphicsEffect(m_opacityEffect);
    }

    if(hasAnimationType(Blur))
    {
        m_blurEffect = new QGraphicsBlurEffect(m_target);
        m_blurAnimation = new QPropertyAnimation(m_blurEffect, "blurRadius");
        m_blurAnimation->setStartValue(m_startBlur);
        m_blurAnimation->setEndValue(m_endBlur);
        m_blurAnimation->setDuration(m_duration);
        m_animations->addAnimation(m_blurAnimation);
        m_target->setGraphicsEffect(m_blurEffect);
    }

    connect(m_animations, SIGNAL(finished()), this, SLOT(on_animationsFinished()));
    m_animations->start(QAbstractAnimation::DeleteWhenStopped);
}

void QWidgetAnimation::stop()
{
    if(m_animations)
    {
        m_animations->stop();
        on_animationsFinished();
    }
}

bool QWidgetAnimation::isAnimating()
{
    if(!m_animations)
        return false;

    return m_animations ? m_animations->state() == QParallelAnimationGroup::Running : false;
}

qreal QWidgetAnimation::startOpacity() const
{
    return m_startOpacity;
}

void QWidgetAnimation::setStartOpacity(qreal newStartOpacity)
{
    m_startOpacity = newStartOpacity;
}

qreal QWidgetAnimation::endOpacity() const
{
    return m_endOpacity;
}

void QWidgetAnimation::setEndOpacity(qreal newEndOpacity)
{
    m_endOpacity = newEndOpacity;
}

qreal QWidgetAnimation::startBlur() const
{
    return m_startBlur;
}

void QWidgetAnimation::setStartBlur(qreal newStartBlur)
{
    m_startBlur = newStartBlur;
}

qreal QWidgetAnimation::endBlur() const
{
    return m_endBlur;
}

void QWidgetAnimation::setEndBlur(qreal newEndBlur)
{
    m_endBlur = newEndBlur;
}

QRect QWidgetAnimation::startGeometry() const
{
    return m_startGeometry;
}

void QWidgetAnimation::setStartGeometry(const QRect &newStartGeometry)
{
    m_startGeometry = newStartGeometry;
}

QPoint QWidgetAnimation::endPosition() const
{
    return m_endPosition;
}

void QWidgetAnimation::setEndPosition(QPoint newEndPosition)
{
    m_endPosition = newEndPosition;
}

QRect QWidgetAnimation::endGeometry() const
{
    return m_endGeometry;
}

void QWidgetAnimation::setEndGeometry(const QRect &newEndGeometry)
{
    m_endGeometry = newEndGeometry;
}

QPoint QWidgetAnimation::startPosition() const
{
    return m_startPosition;
}

void QWidgetAnimation::setStartPosition(QPoint newStartPosition)
{
    m_startPosition = newStartPosition;
}

qint32 QWidgetAnimation::endWidth() const
{
    return m_endWidth;
}

void QWidgetAnimation::setEndWidth(qint32 newEndWidth)
{
    m_endWidth = newEndWidth;
}

qint32 QWidgetAnimation::startWidth() const
{
    return m_startWidth;
}

void QWidgetAnimation::setStartWidth(qint32 newStartWidth)
{
    m_startWidth = newStartWidth;
}

qint32 QWidgetAnimation::endHeight() const
{
    return m_endHeight;
}

void QWidgetAnimation::setEndHeight(qint32 newEndHeight)
{
    m_endHeight = newEndHeight;
}

qint32 QWidgetAnimation::startHeight() const
{
    return m_startHeight;
}

void QWidgetAnimation::setStartHeight(qint32 newStartHeight)
{
    m_startHeight = newStartHeight;
}

bool QWidgetAnimation::hasAnimationType(AnimationType type) const
{
    return ((m_animationType & type) == type);
}

void QWidgetAnimation::setAnimationType(AnimationType newAnimationType)
{
    m_animationType = newAnimationType;
}

void QWidgetAnimation::setDuration(qint32 newDuration)
{
    m_duration = newDuration;
}

void QWidgetAnimation::on_animationsFinished()
{
    if(m_target)
        m_target->setGraphicsEffect(0);

    emit finished();

    m_animations = nullptr;
}

QWidgetAnimation::AnimationType QWidgetAnimation::animationType() const
{
    return m_animationType;
}
