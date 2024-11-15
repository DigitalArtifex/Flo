#include "qklipperprobedata.h"

QKlipperProbeData::QKlipperProbeData(QObject *parent)

{}

QKlipperProbeData::~QKlipperProbeData()
{

}

QString QKlipperProbeData::name() const
{
    return m_name;
}

void QKlipperProbeData::setName(const QString &name)
{
    if (m_name == name)
        return;
    m_name = name;
}

void QKlipperProbeData::resetName()
{
    setName({}); // TODO: Adapt to use your actual default value
}

bool QKlipperProbeData::isManual() const
{
    return m_isManual;
}

void QKlipperProbeData::setIsManual(bool isManual)
{
    if (m_isManual == isManual)
        return;

    m_isManual = isManual;
}

void QKlipperProbeData::resetIsManual()
{
    setIsManual({}); // TODO: Adapt to use your actual default value
}

bool QKlipperProbeData::lastQuery() const
{
    return m_lastQuery;
}

void QKlipperProbeData::setLastQuery(bool lastQuery)
{
    if (m_lastQuery == lastQuery)
        return;

    m_lastQuery = lastQuery;
}

void QKlipperProbeData::resetLastQuery()
{
    setLastQuery({}); // TODO: Adapt to use your actual default value
}

qreal QKlipperProbeData::zPosition() const
{
    return m_zPosition;
}

void QKlipperProbeData::setZPosition(qreal zPosition)
{
    if (qFuzzyCompare(m_zPosition, zPosition))
        return;

    m_zPosition = zPosition;
}

void QKlipperProbeData::resetZPosition()
{
    setZPosition({}); // TODO: Adapt to use your actual default value
}

qreal QKlipperProbeData::zPositionLower() const
{
    return m_zPositionLower;
}

void QKlipperProbeData::setZPositionLower(qreal zPositionLower)
{
    if (qFuzzyCompare(m_zPositionLower, zPositionLower))
        return;

    m_zPositionLower = zPositionLower;
}

void QKlipperProbeData::resetZPositionLower()
{
    setZPositionLower({}); // TODO: Adapt to use your actual default value
}

qreal QKlipperProbeData::zPositionUpper() const
{
    return m_zPositionUpper;
}

void QKlipperProbeData::setZPositionUpper(qreal zPositionUpper)
{
    if (qFuzzyCompare(m_zPositionUpper, zPositionUpper))
        return;

    m_zPositionUpper = zPositionUpper;
}

void QKlipperProbeData::resetZPositionUpper()
{
    setZPositionUpper({}); // TODO: Adapt to use your actual default value
}

qreal QKlipperProbeData::lastZResult() const
{
    return m_lastZResult;
}

void QKlipperProbeData::setLastZResult(qreal lastZResult)
{
    if (qFuzzyCompare(m_lastZResult, lastZResult))
        return;
    m_lastZResult = lastZResult;
}
