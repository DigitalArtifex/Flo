#include "qklippervirtualizationstate.h"

QKlipperVirtualizationState::QKlipperVirtualizationState(QObject *parent) : QObject{parent}
{

}

bool QKlipperVirtualizationState::operator==(const QKlipperVirtualizationState &value)
{
    if(m_type != value.m_type)
        return false;

    if(m_identifier != value.m_identifier)
        return false;

    return true;
}

bool QKlipperVirtualizationState::operator!=(const QKlipperVirtualizationState &value)
{
    return !(*this == value);
}

QString QKlipperVirtualizationState::type() const
{
    return m_type;
}

void QKlipperVirtualizationState::setType(const QString &type)
{
    m_type = type;
}

QString QKlipperVirtualizationState::identifier() const
{
    return m_identifier;
}

void QKlipperVirtualizationState::setIdentifier(const QString &identifier)
{
    m_identifier = identifier;
}
