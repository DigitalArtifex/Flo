#include "qwidgetanimation.h"

QWidgetAnimation::QWidgetAnimation(QWidget *target, QObject *parent) :
    QObject(parent)
{
    _target = target;
    _animations = new QParallelAnimationGroup();
    connect(_animations, SIGNAL(finished()), this, SLOT(on_animationsFinished()));
}

void QWidgetAnimation::start()
{
    _animations = new QParallelAnimationGroup();

    emit started();

    if(hasAnimationType(Height))
    {
        _minHeightAnimation = new QPropertyAnimation(_target, "minHeight");
        _minHeightAnimation->setStartValue(_startHeight);
        _minHeightAnimation->setEndValue(_endHeight);
        _minHeightAnimation->setDuration(_duration);
        _animations->addAnimation(_minHeightAnimation);

        _maxHeightAnimation = new QPropertyAnimation(_target, "maxHeight");
        _maxHeightAnimation->setStartValue(_startHeight);
        _maxHeightAnimation->setEndValue(_endHeight);
        _maxHeightAnimation->setDuration(_duration);
        _animations->addAnimation(_maxHeightAnimation);
    }

    if(hasAnimationType(Width))
    {
        _minWidthAnimation = new QPropertyAnimation(_target, "minWidth");
        _minWidthAnimation->setStartValue(_startWidth);
        _minWidthAnimation->setEndValue(_endWidth);
        _minWidthAnimation->setDuration(_duration);
        _animations->addAnimation(_minWidthAnimation);

        _maxWidthAnimation = new QPropertyAnimation(_target, "maxWidth");
        _maxWidthAnimation->setStartValue(_startWidth);
        _maxWidthAnimation->setEndValue(_endWidth);
        _maxWidthAnimation->setDuration(_duration);
        _animations->addAnimation(_maxWidthAnimation);
    }

    if(hasAnimationType(Geometry))
    {
        _geometryAnimation = new QPropertyAnimation(_target, "geometry");
        _geometryAnimation->setStartValue(_startGeometry);
        _geometryAnimation->setEndValue(_endGeometry);
        _geometryAnimation->setDuration(_duration);
        _animations->addAnimation(_geometryAnimation);
    }

    if(hasAnimationType(Position))
    {
        _positionAnimation = new QPropertyAnimation(_target, "pos");
        _positionAnimation->setStartValue(_startPosition);
        _positionAnimation->setEndValue(_endPosition);
        _positionAnimation->setDuration(_duration);
        _animations->addAnimation(_positionAnimation);
    }

    if(hasAnimationType(Opacity))
    {
        _opacityEffect = new QGraphicsOpacityEffect(_target);
        _opacityAnimation = new QPropertyAnimation(_opacityEffect, "opacity");
        _opacityAnimation->setStartValue(_startOpacity);
        _opacityAnimation->setEndValue(_endOpacity);
        _opacityAnimation->setDuration(_duration);
        _animations->addAnimation(_opacityAnimation);
        _target->setGraphicsEffect(_opacityEffect);
    }

    if(hasAnimationType(Blur))
    {
        _blurEffect = new QGraphicsBlurEffect(_target);
        _blurAnimation = new QPropertyAnimation(_blurEffect, "blurRadius");
        _blurAnimation->setStartValue(_startBlur);
        _blurAnimation->setEndValue(_endBlur);
        _blurAnimation->setDuration(_duration);
        _animations->addAnimation(_blurAnimation);
        _target->setGraphicsEffect(_blurEffect);
    }

    connect(_animations, SIGNAL(finished()), this, SLOT(on_animationsFinished()));
    _animations->start(QAbstractAnimation::DeleteWhenStopped);
}

void QWidgetAnimation::stop()
{
    _animations->stop();
}

qreal QWidgetAnimation::startOpacity() const
{
    return _startOpacity;
}

void QWidgetAnimation::setStartOpacity(qreal newStartOpacity)
{
    _startOpacity = newStartOpacity;
}

qreal QWidgetAnimation::endOpacity() const
{
    return _endOpacity;
}

void QWidgetAnimation::setEndOpacity(qreal newEndOpacity)
{
    _endOpacity = newEndOpacity;
}

qreal QWidgetAnimation::startBlur() const
{
    return _startBlur;
}

void QWidgetAnimation::setStartBlur(qreal newStartBlur)
{
    _startBlur = newStartBlur;
}

qreal QWidgetAnimation::endBlur() const
{
    return _endBlur;
}

void QWidgetAnimation::setEndBlur(qreal newEndBlur)
{
    _endBlur = newEndBlur;
}

QRect QWidgetAnimation::startGeometry() const
{
    return _startGeometry;
}

void QWidgetAnimation::setStartGeometry(const QRect &newStartGeometry)
{
    _startGeometry = newStartGeometry;
}

QPoint QWidgetAnimation::endPosition() const
{
    return _endPosition;
}

void QWidgetAnimation::setEndPosition(QPoint newEndPosition)
{
    _endPosition = newEndPosition;
}

QRect QWidgetAnimation::endGeometry() const
{
    return _endGeometry;
}

void QWidgetAnimation::setEndGeometry(const QRect &newEndGeometry)
{
    _endGeometry = newEndGeometry;
}

QPoint QWidgetAnimation::startPosition() const
{
    return _startPosition;
}

void QWidgetAnimation::setStartPosition(QPoint newStartPosition)
{
    _startPosition = newStartPosition;
}

qint32 QWidgetAnimation::endWidth() const
{
    return _endWidth;
}

void QWidgetAnimation::setEndWidth(qint32 newEndWidth)
{
    _endWidth = newEndWidth;
}

qint32 QWidgetAnimation::startWidth() const
{
    return _startWidth;
}

void QWidgetAnimation::setStartWidth(qint32 newStartWidth)
{
    _startWidth = newStartWidth;
}

qint32 QWidgetAnimation::endHeight() const
{
    return _endHeight;
}

void QWidgetAnimation::setEndHeight(qint32 newEndHeight)
{
    _endHeight = newEndHeight;
}

qint32 QWidgetAnimation::startHeight() const
{
    return _startHeight;
}

void QWidgetAnimation::setStartHeight(qint32 newStartHeight)
{
    _startHeight = newStartHeight;
}

bool QWidgetAnimation::hasAnimationType(AnimationType type) const
{
    return ((_animationType & type) == type);
}

void QWidgetAnimation::setAnimationType(AnimationType newAnimationType)
{
    _animationType = newAnimationType;
}

void QWidgetAnimation::setDuration(qint32 newDuration)
{
    _duration = newDuration;
}

void QWidgetAnimation::on_animationsFinished()
{
    _target->setGraphicsEffect(0);

    delete _animations;

    emit finished();
}

QWidgetAnimation::AnimationType QWidgetAnimation::animationType() const
{
    return _animationType;
}
