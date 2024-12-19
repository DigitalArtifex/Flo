#include "qklippersensordata.h"

QKlipperSensorData::QKlipperSensorData(const QKlipperSensorData &data)
{
    m_description = data.m_description;
    m_excludePaused = data.m_excludePaused;
    m_field = data.m_field;
    m_initTracker = data.m_initTracker;
    m_parameter = data.m_parameter;
    m_precision = data.m_precision;
    m_provider = data.m_provider;
    m_reportMaximum = data.m_reportMaximum;
    m_strategy = data.m_strategy;
    m_units = data.m_units;
}

QKlipperSensorData::QKlipperSensorData(const QString &field,
                                       const QString &provider,
                                       const QString &description,
                                       const QString &strategy,
                                       const QString &units,
                                       const QString &parameter,
                                       const bool &initTracker,
                                       const bool &excludePaused,
                                       const bool &reportTotal,
                                       const bool &reportMaximum,
                                       const qint32 &precision)
{
    m_field = field;
    m_provider = provider;
    m_description = description;
    m_strategy = strategy;
    m_units = units;
    m_parameter = parameter;
    m_initTracker = initTracker;
    m_excludePaused = excludePaused;
    m_reportTotal = reportTotal;
    m_reportMaximum = reportMaximum;
    m_precision = precision;
}

bool QKlipperSensorData::operator ==(const QKlipperSensorData &data) const
{
    if (m_description != data.m_description)
    if (m_excludePaused != data.m_excludePaused) return false;
    if (m_field != data.m_field) return false;
    if (m_initTracker != data.m_initTracker) return false;
    if (m_parameter != data.m_parameter) return false;
    if (m_precision != data.m_precision) return false;
    if (m_provider != data.m_provider) return false;
    if (m_reportMaximum != data.m_reportMaximum) return false;
    if (m_strategy != data.m_strategy) return false;
    if (m_units != data.m_units) return false;

    return true;
}

bool QKlipperSensorData::operator !=(const QKlipperSensorData &data) const
{
    return !(*this == data);
}

QKlipperSensorData &QKlipperSensorData::operator =(const QKlipperSensorData &data)
{
    m_description = data.m_description;
    m_excludePaused = data.m_excludePaused;
    m_field = data.m_field;
    m_initTracker = data.m_initTracker;
    m_parameter = data.m_parameter;
    m_precision = data.m_precision;
    m_provider = data.m_provider;
    m_reportMaximum = data.m_reportMaximum;
    m_strategy = data.m_strategy;
    m_units = data.m_units;

    return *this;
}

QString QKlipperSensorData::field() const
{
    return m_field;
}

void QKlipperSensorData::setField(const QString &field)
{
    m_field = field;
    setIsValid(true);
}

bool QKlipperSensorData::isValid() const
{
    return m_isValid;
}

void QKlipperSensorData::setIsValid(bool isValid)
{
    m_isValid = isValid;
}

QString QKlipperSensorData::provider() const
{
    return m_provider;
}

void QKlipperSensorData::setProvider(const QString &provider)
{
    m_provider = provider;
    setIsValid(true);
}

QString QKlipperSensorData::description() const
{
    return m_description;
}

void QKlipperSensorData::setDescription(const QString &description)
{
    m_description = description;
    setIsValid(true);
}

QString QKlipperSensorData::strategy() const
{
    return m_strategy;
}

void QKlipperSensorData::setStrategy(const QString &strategy)
{
    m_strategy = strategy;
    setIsValid(true);
}

QString QKlipperSensorData::units() const
{
    return m_units;
}

void QKlipperSensorData::setUnits(const QString &units)
{
    m_units = units;
    setIsValid(true);
}

QString QKlipperSensorData::parameter() const
{
    return m_parameter;
}

void QKlipperSensorData::setParameter(const QString &parameter)
{
    m_parameter = parameter;
    setIsValid(true);
}

bool QKlipperSensorData::initTracker() const
{
    return m_initTracker;
}

void QKlipperSensorData::setInitTracker(bool initTracker)
{
    m_initTracker = initTracker;
    setIsValid(true);
}

bool QKlipperSensorData::excludePaused() const
{
    return m_excludePaused;
}

void QKlipperSensorData::setExcludePaused(bool excludePaused)
{
    m_excludePaused = excludePaused;
    setIsValid(true);
}

bool QKlipperSensorData::reportTotal() const
{
    return m_reportTotal;
}

void QKlipperSensorData::setReportTotal(bool reportTotal)
{
    m_reportTotal = reportTotal;
    setIsValid(true);
}

bool QKlipperSensorData::reportMaximum() const
{
    return m_reportMaximum;
}

void QKlipperSensorData::setReportMaximum(bool reportMaximum)
{
    m_reportMaximum = reportMaximum;
    setIsValid(true);
}

qint32 QKlipperSensorData::precision() const
{
    return m_precision;
}

void QKlipperSensorData::setPrecision(qint32 precision)
{
    m_precision = precision;
    setIsValid(true);
}
