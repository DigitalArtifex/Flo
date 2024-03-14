#include "dashboardanimation.h"

DashboardAnimation::DashboardAnimation(QObject *target, Property property, QObject *parent)
    : QObject{parent}
{
    _target = target;
    _property = property;

    _animationsIn = new QParallelAnimationGroup(this->parent());
    _animationsOut = new QParallelAnimationGroup(this->parent());
}

void DashboardAnimation::show()
{
    if(_animationsIn->state() == QAnimationGroup::Running)
        return;
    if(_animationsOut->state() == QAnimationGroup::Running)
        _animationsOut->stop();

    _animationsIn->clear();

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

void DashboardAnimation::hide()
{
    if(_animationsOut->state() == QAnimationGroup::Running)
        return;
    if(_animationsIn->state() == QAnimationGroup::Running)
        _animationsIn->stop();

    _animationsOut->clear();

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

void DashboardAnimation::setProperty(Property property)
{
    _property = property;
}

void DashboardAnimation::setHeightIn(qreal height)
{
    _heightIn = height;
}

void DashboardAnimation::setHeightOut(qreal height)
{
    _heightOut = height;
}

void DashboardAnimation::setWidthIn(qreal width)
{
    _widthIn = width;
}

void DashboardAnimation::setWidthOut(qreal width)
{
    _widthOut = width;
}

bool DashboardAnimation::hasPropertyFlag(Property property)
{
    return ((_property & property) == property);
}
