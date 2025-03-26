#include "locationindicatorprivate.h"

LocationIndicatorPrivate::LocationIndicatorPrivate(QObject *parent)
    : QObject{parent}
{
    m_xAnimation = new QPropertyAnimation(this, "x", this);
    m_xAnimation->setDuration(150);
    m_yAnimation = new QPropertyAnimation(this, "y", this);
    m_yAnimation->setDuration(150);
}

LocationIndicatorPrivate::~LocationIndicatorPrivate()
{
    if(m_xAnimation)
        delete m_xAnimation;

    if(m_yAnimation)
        delete m_yAnimation;
}

qreal LocationIndicatorPrivate::x() const
{
    return m_x;
}

void LocationIndicatorPrivate::setXPrivate(qreal x)
{
    if (qFuzzyCompare(m_x, x))
        return;

    m_x = x;
    emit xChanged();
}

qreal LocationIndicatorPrivate::y() const
{
    return m_y;
}

void LocationIndicatorPrivate::setX(qreal x)
{
    if(!m_animated)
    {
        setXPrivate(x);
        return;
    }

    if(m_xAnimation->state() == QPropertyAnimation::Running)
        m_xAnimation->stop();

    m_xAnimation->setStartValue(m_x);
    m_xAnimation->setEndValue(x);

    m_xAnimation->start();
}

void LocationIndicatorPrivate::setY(qreal y)
{
    if(!m_animated)
    {
        setYPrivate(y);
        return;
    }

    if(m_yAnimation->state() == QPropertyAnimation::Running)
        m_yAnimation->stop();

    m_yAnimation->setStartValue(m_y);
    m_yAnimation->setEndValue(y);

    m_yAnimation->start();
}

void LocationIndicatorPrivate::setYPrivate(qreal y)
{
    if (qFuzzyCompare(m_y, y))
        return;

    m_y = y;
    emit yChanged();
}

bool LocationIndicatorPrivate::animated() const
{
    return m_animated;
}

void LocationIndicatorPrivate::setAnimated(bool animated)
{
    if (m_animated == animated)
        return;

    m_animated = animated;
    emit animatedChanged();
}
