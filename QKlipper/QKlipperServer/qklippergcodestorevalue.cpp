#include "qklippergcodestorevalue.h"

bool QKlipperGCodeStoreValue::operator==(const QKlipperGCodeStoreValue &value)
{
    if(m_gcodeType != value.m_gcodeType) return false;
    if(m_time != value.m_time) return false;
    if(m_message != value.m_message) return false;

    return true;
}

bool QKlipperGCodeStoreValue::operator!=(const QKlipperGCodeStoreValue &value)
{
    if(m_gcodeType == value.m_gcodeType &&
        m_time == value.m_time &&
        m_message == value.m_message)
        return false;

    return true;
}

QString QKlipperGCodeStoreValue::message() const
{
    return m_message;
}

void QKlipperGCodeStoreValue::setMessage(const QString &message)
{
    if (m_message == message)
        return;

    m_message = message;
}

QKlipperGCodeStoreValue::GCodeType QKlipperGCodeStoreValue::gcodeType() const
{
    return m_gcodeType;
}

void QKlipperGCodeStoreValue::setGcodeType(GCodeType gcodeType)
{
    if (m_gcodeType == gcodeType)
        return;

    m_gcodeType = gcodeType;
}

qreal QKlipperGCodeStoreValue::time() const
{
    return m_time;
}

void QKlipperGCodeStoreValue::setTime(qreal time)
{
    if (qFuzzyCompare(m_time, time))
        return;

    m_time = time;
}
