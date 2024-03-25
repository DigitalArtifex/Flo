#include "widgetanimation.h"

WidgetAnimation::WidgetAnimation(QWidget *target, Property property, QObject *parent)
    : QObject{parent}
{
    _target = target;
    _property = property;

    _animationsIn = new QParallelAnimationGroup(this->parent());
    _animationsOut = new QParallelAnimationGroup(this->parent());

    connect(_animationsIn, SIGNAL(finished()), this, SLOT(on_animations_finished()));
    connect(_animationsOut, SIGNAL(finished()), this, SLOT(on_animations_finished()));

    _effect_opacity = new QGraphicsOpacityEffect(_target);
}

void WidgetAnimation::show()
{
    if(_animationsIn->state() == QAnimationGroup::Running)
        return;
    if(_animationsOut->state() == QAnimationGroup::Running)
        _animationsOut->stop();

    _animationsIn->clear();

    if(hasPropertyFlag(Property::Opacity))
    {
        _animationIn_opacity = new QPropertyAnimation(_effect_opacity, "opacity");
        _animationIn_opacity->setStartValue(0);
        _animationIn_opacity->setEndValue(1);
        _animationIn_opacity->setDuration(1000);
        _animationsIn->addAnimation(_animationIn_opacity);
        _target->setGraphicsEffect(_effect_opacity);
    }

    if(this->hasPropertyFlag(Property::MaxHeight))
    {
        _animationIn_maxHeight = new QPropertyAnimation(_target, "maximumHeight", this->parent());

        _animationIn_maxHeight->setStartValue(_heightOut);
        _animationIn_maxHeight->setEndValue(_heightIn);
        _animationIn_maxHeight->setDuration(250);
        _animationsIn->addAnimation(_animationIn_maxHeight);
    }

    if(this->hasPropertyFlag(Property::MinHeight))
    {
        _animationIn_minHeight = new QPropertyAnimation(_target, "minimumHeight", this->parent());

        _animationIn_minHeight->setStartValue(_heightOut);
        _animationIn_minHeight->setEndValue(_heightIn);
        _animationIn_minHeight->setDuration(250);
        _animationsIn->addAnimation(_animationIn_minHeight);
    }

    if(this->hasPropertyFlag(Property::MaxWidth))
    {
            _animationIn_maxWidth = new QPropertyAnimation(_target, "maximumWidth", this->parent());

        _animationIn_maxWidth->setStartValue(_widthOut);
        _animationIn_maxWidth->setEndValue(_widthIn);
        _animationIn_maxWidth->setDuration(250);
        _animationsIn->addAnimation(_animationIn_maxWidth);
    }

    if(this->hasPropertyFlag(Property::MinWidth))
    {
            _animationIn_minWidth = new QPropertyAnimation(_target, "minimumWidth", this->parent());

        _animationIn_minWidth->setStartValue(_widthOut);
        _animationIn_minWidth->setEndValue(_widthIn);
        _animationIn_minWidth->setDuration(250);
        _animationsIn->addAnimation(_animationIn_minWidth);
    }

    _animationsIn->start(QParallelAnimationGroup::KeepWhenStopped);
}

void WidgetAnimation::hide()
{
    if(_animationsOut->state() == QAnimationGroup::Running)
        return;
    if(_animationsIn->state() == QAnimationGroup::Running)
        _animationsIn->stop();

    _animationsOut->clear();

    if(hasPropertyFlag(Property::Opacity))
    {
        _animationOut_opacity = new QPropertyAnimation(_effect_opacity, "opacity");
        _animationOut_opacity->setStartValue(1);
        _animationOut_opacity->setEndValue(0);
        _animationOut_opacity->setDuration(1000);
        _animationsOut->addAnimation(_animationOut_opacity);
        //_target->setGraphicsEffect(_effect_opacity);
    }

    if(this->hasPropertyFlag(Property::MaxHeight))
    {
        _animationOut_maxHeight = new QPropertyAnimation(_target, "maximumHeight", this->parent());

        _animationOut_maxHeight->setStartValue(_heightIn);
        _animationOut_maxHeight->setEndValue(_heightOut);
        _animationOut_maxHeight->setDuration(250);
        _animationsOut->addAnimation(_animationOut_maxHeight);
    }

    if(this->hasPropertyFlag(Property::MinHeight))
    {
        _animationOut_minHeight = new QPropertyAnimation(_target, "minimumHeight", this->parent());

        _animationOut_minHeight->setStartValue(_heightIn);
        _animationOut_minHeight->setEndValue(_heightOut);
        _animationOut_minHeight->setDuration(250);
        _animationsOut->addAnimation(_animationOut_minHeight);
    }

    if(this->hasPropertyFlag(Property::MaxWidth))
    {
        _animationOut_maxWidth = new QPropertyAnimation(_target, "maximumWidth", this->parent());

        _animationOut_maxWidth->setStartValue(_widthIn);
        _animationOut_maxWidth->setEndValue(_widthOut);
        _animationOut_maxWidth->setDuration(250);
        _animationsOut->addAnimation(_animationOut_maxWidth);
    }

    if(this->hasPropertyFlag(Property::MinWidth))
    {
        _animationOut_minWidth = new QPropertyAnimation(_target, "minimumWidth", this->parent());

        _animationOut_minWidth->setStartValue(_widthIn);
        _animationOut_minWidth->setEndValue(_widthOut);
        _animationOut_minWidth->setDuration(250);
        _animationsOut->addAnimation(_animationOut_minWidth);
    }

    _animationsOut->start(QParallelAnimationGroup::KeepWhenStopped);
}

void WidgetAnimation::setProperty(Property property)
{
    _property = property;
}

void WidgetAnimation::setHeightIn(qreal height)
{
    _heightIn = height;
}

void WidgetAnimation::setHeightOut(qreal height)
{
    _heightOut = height;
}

void WidgetAnimation::setWidthIn(qreal width)
{
    _widthIn = width;
}

void WidgetAnimation::setWidthOut(qreal width)
{
    _widthOut = width;
}

bool WidgetAnimation::hasPropertyFlag(Property property)
{
    return ((_property & property) == property);
}

void WidgetAnimation::on_animations_finished()
{
    emit(finished());
}
