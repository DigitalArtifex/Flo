#include "widgetanimation.h"

WidgetAnimation::WidgetAnimation(QWidget *target, Property property, QObject *parent)
    : QObject{parent}
{
    m_target = target;
    m_property = property;

    m_animationsIn = new QParallelAnimationGroup(this->parent());
    m_animationsOut = new QParallelAnimationGroup(this->parent());

    connect(m_animationsIn, SIGNAL(finished()), this, SLOT(on_animations_finished()));
    connect(m_animationsOut, SIGNAL(finished()), this, SLOT(on_animations_finished()));

    m_effect_opacity = new QGraphicsOpacityEffect(m_target);
}

void WidgetAnimation::show()
{
    if(m_animationsIn->state() == QAnimationGroup::Running)
        return;
    if(m_animationsOut->state() == QAnimationGroup::Running)
        m_animationsOut->stop();

    m_animationsIn->clear();

    if(hasPropertyFlag(Property::Opacity))
    {
        m_animationIn_opacity = new QPropertyAnimation(m_effect_opacity, "opacity");
        m_animationIn_opacity->setStartValue(0);
        m_animationIn_opacity->setEndValue(1);
        m_animationIn_opacity->setDuration(1000);
        m_animationsIn->addAnimation(m_animationIn_opacity);
        m_target->setGraphicsEffect(m_effect_opacity);
    }

    if(this->hasPropertyFlag(Property::MaxHeight))
    {
        m_animationIn_maxHeight = new QPropertyAnimation(m_target, "maximumHeight", this->parent());

        m_animationIn_maxHeight->setStartValue(m_heightOut);
        m_animationIn_maxHeight->setEndValue(m_heightIn);
        m_animationIn_maxHeight->setDuration(250);
        m_animationsIn->addAnimation(m_animationIn_maxHeight);
    }

    if(this->hasPropertyFlag(Property::MinHeight))
    {
        m_animationIn_minHeight = new QPropertyAnimation(m_target, "minimumHeight", this->parent());

        m_animationIn_minHeight->setStartValue(m_heightOut);
        m_animationIn_minHeight->setEndValue(m_heightIn);
        m_animationIn_minHeight->setDuration(250);
        m_animationsIn->addAnimation(m_animationIn_minHeight);
    }

    if(this->hasPropertyFlag(Property::MaxWidth))
    {
            m_animationIn_maxWidth = new QPropertyAnimation(m_target, "maximumWidth", this->parent());

        m_animationIn_maxWidth->setStartValue(m_widthOut);
        m_animationIn_maxWidth->setEndValue(m_widthIn);
        m_animationIn_maxWidth->setDuration(250);
        m_animationsIn->addAnimation(m_animationIn_maxWidth);
    }

    if(this->hasPropertyFlag(Property::MinWidth))
    {
            m_animationIn_minWidth = new QPropertyAnimation(m_target, "minimumWidth", this->parent());

        m_animationIn_minWidth->setStartValue(m_widthOut);
        m_animationIn_minWidth->setEndValue(m_widthIn);
        m_animationIn_minWidth->setDuration(250);
        m_animationsIn->addAnimation(m_animationIn_minWidth);
    }

    m_animationsIn->start(QParallelAnimationGroup::KeepWhenStopped);
}

void WidgetAnimation::hide()
{
    if(m_animationsOut->state() == QAnimationGroup::Running)
        return;
    if(m_animationsIn->state() == QAnimationGroup::Running)
        m_animationsIn->stop();

    m_animationsOut->clear();

    if(hasPropertyFlag(Property::Opacity))
    {
        m_animationOut_opacity = new QPropertyAnimation(m_effect_opacity, "opacity");
        m_animationOut_opacity->setStartValue(1);
        m_animationOut_opacity->setEndValue(0);
        m_animationOut_opacity->setDuration(1000);
        m_animationsOut->addAnimation(m_animationOut_opacity);
        //_target->setGraphicsEffect(m_effect_opacity);
    }

    if(this->hasPropertyFlag(Property::MaxHeight))
    {
        m_animationOut_maxHeight = new QPropertyAnimation(m_target, "maximumHeight", this->parent());

        m_animationOut_maxHeight->setStartValue(m_heightIn);
        m_animationOut_maxHeight->setEndValue(m_heightOut);
        m_animationOut_maxHeight->setDuration(250);
        m_animationsOut->addAnimation(m_animationOut_maxHeight);
    }

    if(this->hasPropertyFlag(Property::MinHeight))
    {
        m_animationOut_minHeight = new QPropertyAnimation(m_target, "minimumHeight", this->parent());

        m_animationOut_minHeight->setStartValue(m_heightIn);
        m_animationOut_minHeight->setEndValue(m_heightOut);
        m_animationOut_minHeight->setDuration(250);
        m_animationsOut->addAnimation(m_animationOut_minHeight);
    }

    if(this->hasPropertyFlag(Property::MaxWidth))
    {
        m_animationOut_maxWidth = new QPropertyAnimation(m_target, "maximumWidth", this->parent());

        m_animationOut_maxWidth->setStartValue(m_widthIn);
        m_animationOut_maxWidth->setEndValue(m_widthOut);
        m_animationOut_maxWidth->setDuration(250);
        m_animationsOut->addAnimation(m_animationOut_maxWidth);
    }

    if(this->hasPropertyFlag(Property::MinWidth))
    {
        m_animationOut_minWidth = new QPropertyAnimation(m_target, "minimumWidth", this->parent());

        m_animationOut_minWidth->setStartValue(m_widthIn);
        m_animationOut_minWidth->setEndValue(m_widthOut);
        m_animationOut_minWidth->setDuration(250);
        m_animationsOut->addAnimation(m_animationOut_minWidth);
    }

    m_animationsOut->start(QParallelAnimationGroup::KeepWhenStopped);
}

void WidgetAnimation::setProperty(Property property)
{
    m_property = property;
}

void WidgetAnimation::setHeightIn(qreal height)
{
    m_heightIn = height;
}

void WidgetAnimation::setHeightOut(qreal height)
{
    m_heightOut = height;
}

void WidgetAnimation::setWidthIn(qreal width)
{
    m_widthIn = width;
}

void WidgetAnimation::setWidthOut(qreal width)
{
    m_widthOut = width;
}

bool WidgetAnimation::hasPropertyFlag(Property property)
{
    return ((m_property & property) == property);
}

void WidgetAnimation::on_animations_finished()
{
    emit(finished());
}
