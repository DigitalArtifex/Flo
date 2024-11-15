#include "qklipperadjustmentscrew.h"

QKlipperAdjustmentScrew::QKlipperAdjustmentScrew(QObject *parent)
    : QObject{parent}
{}

QString QKlipperAdjustmentScrew::name() const
{
    return m_name;
}

void QKlipperAdjustmentScrew::setName(const QString &name)
{
    if (m_name == name)
        return;
    m_name = name;
    emit nameChanged();
}

QString QKlipperAdjustmentScrew::thread() const
{
    return m_thread;
}

void QKlipperAdjustmentScrew::setThread(const QString &thread)
{
    if (m_thread == thread)
        return;
    m_thread = thread;
    emit threadChanged();
}

QPair<qreal, qreal> QKlipperAdjustmentScrew::tiltAdjust() const
{
    return m_tiltAdjust;
}

void QKlipperAdjustmentScrew::setTiltAdjust(const QPair<qreal, qreal> &tiltAdjust)
{
    if (m_tiltAdjust == tiltAdjust)
        return;
    m_tiltAdjust = tiltAdjust;
    emit tiltAdjustChanged();
}

qreal QKlipperAdjustmentScrew::speed() const
{
    return m_speed;
}

void QKlipperAdjustmentScrew::setSpeed(qreal speed)
{
    if (qFuzzyCompare(m_speed, speed))
        return;
    m_speed = speed;
    emit speedChanged();
}

QKlipperAdjustmentScrew::Adjustment QKlipperAdjustmentScrew::adjustment() const
{
    return m_adjustment;
}

void QKlipperAdjustmentScrew::setAdjustment(const Adjustment &adjustment)
{
    m_adjustment = adjustment;
    emit adjustmentChanged();
}
