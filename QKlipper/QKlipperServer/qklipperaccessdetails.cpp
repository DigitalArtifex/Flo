#include "qklipperaccessdetails.h"

QKlipperAccessDetails::QKlipperAccessDetails(QObject *parent)
    : QObject{parent}
{}

QKlipperAccessDetails::~QKlipperAccessDetails()
{
}

QKlipperAccessDetails::QKlipperAccessDetails(const QKlipperAccessDetails &value)
{
    m_isLoggedIn = value.m_isLoggedIn;
    m_refreshToken = value.m_refreshToken;
    m_token = value.m_token;
    m_user = value.m_user;
}

QKlipperAccessDetails::QKlipperAccessDetails(QKlipperAccessDetails &&value)
{
    m_isLoggedIn = value.m_isLoggedIn;
    m_refreshToken = value.m_refreshToken;
    m_token = value.m_token;
    m_user = value.m_user;
}

QKlipperAccessDetails &QKlipperAccessDetails::operator=(const QKlipperAccessDetails &value)
{
    m_isLoggedIn = value.m_isLoggedIn;
    m_refreshToken = value.m_refreshToken;
    m_token = value.m_token;
    m_user = value.m_user;

    return *this;
}

bool QKlipperAccessDetails::operator==(const QKlipperAccessDetails &value)
{
    if(m_isLoggedIn != value.m_isLoggedIn)
        return false;
    if(m_refreshToken != value.m_refreshToken)
        return false;
    if(m_token != value.m_token)
        return false;
    if(m_user != value.m_user)
        return false;

    return true;
}

bool QKlipperAccessDetails::operator==(QKlipperAccessDetails &&value)
{
    if(m_isLoggedIn != value.m_isLoggedIn)
        return false;
    if(m_refreshToken != value.m_refreshToken)
        return false;
    if(m_token != value.m_token)
        return false;
    if(m_user != value.m_user)
        return false;

    return true;
}

bool QKlipperAccessDetails::operator!=(const QKlipperAccessDetails &value)
{
    if( m_isLoggedIn == value.m_isLoggedIn &&
        m_refreshToken == value.m_refreshToken &&
        m_token == value.m_token &&
        m_user == value.m_user
        )
        return false;

    return true;
}

bool QKlipperAccessDetails::operator!=(QKlipperAccessDetails &&value)
{
    if( m_isLoggedIn == value.m_isLoggedIn &&
        m_refreshToken == value.m_refreshToken &&
        m_token == value.m_token &&
        m_user == value.m_user
        )
        return false;

    return true;
}

bool QKlipperAccessDetails::isLoggedIn() const
{
    return m_isLoggedIn;
}

void QKlipperAccessDetails::setIsLoggedIn(bool isLoggedIn)
{
    if (m_isLoggedIn == isLoggedIn)
        return;
    m_isLoggedIn = isLoggedIn;
    emit isLoggedInChanged();
}

QString QKlipperAccessDetails::token() const
{
    return m_token;
}

void QKlipperAccessDetails::setToken(const QString &token)
{
    if (m_token == token)
        return;
    m_token = token;
    emit tokenChanged();
}

QString QKlipperAccessDetails::refreshToken() const
{
    return m_refreshToken;
}

void QKlipperAccessDetails::setRefreshToken(const QString &refreshToken)
{
    if (m_refreshToken == refreshToken)
        return;
    m_refreshToken = refreshToken;
    emit refreshTokenChanged();
}

QKlipperUser QKlipperAccessDetails::user() const
{
    return m_user;
}

void QKlipperAccessDetails::setUser(const QKlipperUser &user)
{
    if (m_user == user)
        return;
    m_user = user;
    emit userChanged();
}

QKlipperAccessDetails &QKlipperAccessDetails::operator=(QKlipperAccessDetails &&value)
{
    m_isLoggedIn = value.m_isLoggedIn;
    m_refreshToken = value.m_refreshToken;
    m_token = value.m_token;
    m_user = value.m_user;

    return *this;
}
