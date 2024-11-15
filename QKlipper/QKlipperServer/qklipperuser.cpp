#include "qklipperuser.h"

QKlipperUser::QKlipperUser(QObject *parent)
    : QObject{parent}
{}

QString QKlipperUser::username() const
{
    return m_username;
}

void QKlipperUser::setUsername(const QString &username)
{
    if (m_username == username)
        return;
    m_username = username;
    emit usernameChanged();
}

QString QKlipperUser::source() const
{
    return m_source;
}

void QKlipperUser::setSource(const QString &source)
{
    if (m_source == source)
        return;

    m_source = source;
    emit sourceChanged();
}

qreal QKlipperUser::createdOn() const
{
    return m_createdOn;
}

void QKlipperUser::setCreatedOn(qreal createdOn)
{
    if (qFuzzyCompare(m_createdOn, createdOn))
        return;

    m_createdOn = createdOn;
    emit createdOnChanged();
}

QKlipperUser::QKlipperUser(const QKlipperUser &value)
{
    m_username = value.m_username;
    m_createdOn = value.m_createdOn;
    m_source = value.m_source;
}

QKlipperUser::QKlipperUser(QKlipperUser &&value)
{
    m_username = value.m_username;
    m_createdOn = value.m_createdOn;
    m_source = value.m_source;
}

QKlipperUser &QKlipperUser::operator=(const QKlipperUser &value)
{
    m_username = value.m_username;
    m_createdOn = value.m_createdOn;
    m_source = value.m_source;

    return *this;
}

bool QKlipperUser::operator==(const QKlipperUser &value)
{
    if(m_username != value.m_username)
        return false;
    if(m_createdOn != value.m_createdOn)
        return false;
    if(m_source != value.m_source)
        return false;

    return true;
}

bool QKlipperUser::operator!=(const QKlipperUser &value)
{
    if(m_username == value.m_username &&
        m_createdOn == value.m_createdOn &&
        m_source == value.m_source)
        return false;

    return true;
}

bool QKlipperUser::operator!=(QKlipperUser &&value)
{
    if(m_username == value.m_username &&
        m_createdOn == value.m_createdOn &&
        m_source == value.m_source)
        return false;

    return true;
}

bool QKlipperUser::operator==(QKlipperUser &&value)
{
    if(m_username != value.m_username)
        return false;
    if(m_createdOn != value.m_createdOn)
        return false;
    if(m_source != value.m_source)
        return false;

    return true;
}

QKlipperUser &QKlipperUser::operator=(QKlipperUser &&value)
{
    m_username = value.m_username;
    m_createdOn = value.m_createdOn;
    m_source = value.m_source;

    return *this;
}
