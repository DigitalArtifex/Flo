#include "qklipperservice.h"

QKlipperService::QKlipperService(QObject *parent)
    : QObject{parent}
{}

QKlipperService::~QKlipperService()
{

}

bool QKlipperService::operator==(const QKlipperService *value)
{
    if(m_activeState != value->m_activeState) return false;
    if(m_subState != value->m_subState) return false;
    if(m_name != value->m_name) return false;

    return true;
}

bool QKlipperService::operator!=(const QKlipperService *value)
{
    return !(this == value);
}

QString QKlipperService::activeState() const
{
    return m_activeState;
}

void QKlipperService::setActiveState(const QString &activeState)
{
    if (m_activeState == activeState)
        return;

    m_activeState = activeState;
    emit activeStateChanged();
}

QString QKlipperService::subState() const
{
    return m_subState;
}

void QKlipperService::setSubState(const QString &subState)
{
    if (m_subState == subState)
        return;
    m_subState = subState;
    emit subStateChanged();
}

QString QKlipperService::name() const
{
    return m_name;
}

void QKlipperService::setName(const QString &name)
{
    if (m_name == name)
        return;
    m_name = name;
    emit nameChanged();
}
