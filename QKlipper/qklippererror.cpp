#include "qklippererror.h"

QKlipperError::QKlipperError()
{
    m_id = QUuid::createUuid().toString();
}

bool QKlipperError::operator==(const QKlipperError &value)
{
    if(m_id != value.m_id)
        return false;

    if(m_errorString != value.m_errorString)
        return false;

    if(m_origin != value.m_origin)
        return false;

    if(m_type != value.m_type)
        return false;

    if(m_errorTitle != value.m_errorTitle)
        return false;

    return true;
}

bool QKlipperError::operator==(QKlipperError &&value)
{
    if(m_id != value.m_id)
        return false;

    if(m_errorString != value.m_errorString)
        return false;

    if(m_origin != value.m_origin)
        return false;

    if(m_type != value.m_type)
        return false;

    if(m_errorTitle != value.m_errorTitle)
        return false;

    return true;
}

bool QKlipperError::operator!=(const QKlipperError &value)
{
    return !(*(this) == value);
}

bool QKlipperError::operator!=(QKlipperError &&value)
{
    return !(*(this) == value);
}

QString QKlipperError::errorString() const
{
    return m_errorString;
}

void QKlipperError::setErrorString(const QString &errorString)
{
    m_errorString = errorString;
}

QString QKlipperError::origin() const
{
    return m_origin;
}

void QKlipperError::setOrigin(const QString &origin)
{
    m_origin = origin;
}

QKlipperError::Type QKlipperError::type() const
{
    return m_type;
}

void QKlipperError::setType(Type type)
{
    m_type = type;
}

QString QKlipperError::errorTitle() const
{
    return m_errorTitle;
}

void QKlipperError::setErrorTitle(const QString &errorTitle)
{
    m_errorTitle = errorTitle;
}

QString QKlipperError::id() const
{
    return m_id;
}

void QKlipperError::setId(const QString &id)
{
    m_id = id;
}
