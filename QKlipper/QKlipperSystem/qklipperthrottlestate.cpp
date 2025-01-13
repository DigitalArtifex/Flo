#include "qklipperthrottlestate.h"

QKlipperThrottleState::QKlipperThrottleState(QObject *parent)
    : QObject{parent}
{}

bool QKlipperThrottleState::operator==(const QKlipperThrottleState &value)
{
    if(m_bits != value.m_bits) return false;
    if(m_flags != value.m_flags) return false;

    return true;
}

bool QKlipperThrottleState::operator!=(const QKlipperThrottleState &value)
{
    if(m_bits == value.m_bits && m_flags == value.m_flags)
        return false;

    return true;
}

qint32 QKlipperThrottleState::bits() const
{
    return m_bits;
}

void QKlipperThrottleState::setBits(qint32 bits)
{
    if (m_bits == bits)
        return;

    m_bits = bits;
    emit bitsChanged();
}

QStringList QKlipperThrottleState::flags() const
{
    return m_flags;
}

void QKlipperThrottleState::setFlags(const QStringList &flags)
{
    if (m_flags == flags)
        return;

    m_flags = flags;
    emit flagsChanged();
}

