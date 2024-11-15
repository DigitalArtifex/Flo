#include "qklipperservicestate.h"

QKlipperServiceState::QKlipperServiceState(QObject *parent)
    : QObject{parent}
{}

QKlipperServiceState::~QKlipperServiceState()
{

}

QKlipperServiceState::QKlipperServiceState(const QKlipperServiceState &value)
{
    m_activeState = value.m_activeState;
    m_subState = value.m_subState;
    m_name = value.m_name;
}

QKlipperServiceState::QKlipperServiceState(QKlipperServiceState &&value)
{
    m_activeState = value.m_activeState;
    m_subState = value.m_subState;
    m_name = value.m_name;
}

QKlipperServiceState &QKlipperServiceState::operator=(const QKlipperServiceState &value)
{
    m_activeState = value.m_activeState;
    m_subState = value.m_subState;
    m_name = value.m_name;

    return *this;
}

QKlipperServiceState &QKlipperServiceState::operator=(QKlipperServiceState &&value)
{
    m_activeState = value.m_activeState;
    m_subState = value.m_subState;
    m_name = value.m_name;

    return *this;
}

bool QKlipperServiceState::operator==(const QKlipperServiceState &value)
{
    if(m_activeState != value.m_activeState) return false;
    if(m_subState != value.m_subState) return false;
    if(m_name != value.m_name) return false;

    return true;
}

bool QKlipperServiceState::operator==(QKlipperServiceState &&value)
{
    if(m_activeState != value.m_activeState) return false;
    if(m_subState != value.m_subState) return false;
    if(m_name != value.m_name) return false;

    return true;
}

bool QKlipperServiceState::operator!=(const QKlipperServiceState &value)
{
    if(m_activeState == value.m_activeState &&
    m_subState == value.m_subState &&
    m_name == value.m_name) return false;

    return true;
}

bool QKlipperServiceState::operator!=(QKlipperServiceState &&value)
{
    if(m_activeState == value.m_activeState &&
        m_subState == value.m_subState &&
        m_name == value.m_name) return false;

    return true;
}

QString QKlipperServiceState::activeState() const
{
    return m_activeState;
}

void QKlipperServiceState::setActiveState(const QString &activeState)
{
    if (m_activeState == activeState)
        return;
    m_activeState = activeState;
    emit activeStateChanged();
}

QString QKlipperServiceState::subState() const
{
    return m_subState;
}

void QKlipperServiceState::setSubState(const QString &subState)
{
    if (m_subState == subState)
        return;
    m_subState = subState;
    emit subStateChanged();
}

QString QKlipperServiceState::name() const
{
    return m_name;
}

void QKlipperServiceState::setName(const QString &name)
{
    if (m_name == name)
        return;
    m_name = name;
    emit nameChanged();
}
