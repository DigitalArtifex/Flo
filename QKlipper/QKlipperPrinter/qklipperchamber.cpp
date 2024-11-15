#include "qklipperchamber.h"

QKlipperChamber::QKlipperChamber(QObject *parent)
    : QObject{parent}
{}

qreal QKlipperChamber::currentTemperature() const
{
    return m_currentTemperature;
}

void QKlipperChamber::setCurrentTemperature(qreal currentTemperature)
{
    if (qFuzzyCompare(m_currentTemperature, currentTemperature))
        return;
    m_currentTemperature = currentTemperature;
    emit currentTemperatureChanged();
}

qreal QKlipperChamber::targetTemperature() const
{
    return m_targetTemperature;
}

void QKlipperChamber::setTargetTemperature(qreal targetTemperature)
{
    if (qFuzzyCompare(m_targetTemperature, targetTemperature))
        return;
    m_targetTemperature = targetTemperature;
    emit targetTemperatureChanged();
}

qreal QKlipperChamber::maxWatts() const
{
    return m_maxWatts;
}

void QKlipperChamber::setMaxWatts(qreal maxWatts)
{
    if (qFuzzyCompare(m_maxWatts, maxWatts))
        return;
    m_maxWatts = maxWatts;
    emit maxWattsChanged();
}
