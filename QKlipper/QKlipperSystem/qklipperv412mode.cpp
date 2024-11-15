#include "qklipperv412mode.h"

QKlipperV412Mode::QKlipperV412Mode()
    : QVariant{}
{}

QKlipperV412Mode::QKlipperV412Mode(const QKlipperV412Mode &value)
{
    m_description = value.m_description;
    m_flags = value.m_flags;
    m_format = value.m_format;
    m_resolutions = value.m_resolutions;
}

QKlipperV412Mode &QKlipperV412Mode::operator=(const QKlipperV412Mode &value)
{
    m_description = value.m_description;
    m_flags = value.m_flags;
    m_format = value.m_format;
    m_resolutions = value.m_resolutions;

    return *this;
}

bool QKlipperV412Mode::operator==(const QKlipperV412Mode &value)
{
    if(m_description != value.m_description) return false;
    if(m_flags != value.m_flags) return false;
    if(m_format != value.m_format) return false;
    if(m_resolutions != value.m_resolutions) return false;

    return true;
}

bool QKlipperV412Mode::operator!=(const QKlipperV412Mode &value)
{
    if(m_description == value.m_description &&
        m_flags == value.m_flags &&
        m_format == value.m_format &&
        m_resolutions == value.m_resolutions)
        return false;

    return true;
}

QString QKlipperV412Mode::description() const
{
    return m_description;
}

void QKlipperV412Mode::setDescription(const QString &description)
{
    m_description = description;
}

QString QKlipperV412Mode::format() const
{
    return m_format;
}

void QKlipperV412Mode::setFormat(const QString &format)
{
    m_format = format;
}

QStringList QKlipperV412Mode::flags() const
{
    return m_flags;
}

void QKlipperV412Mode::setFlags(const QStringList &flags)
{
    m_flags = flags;
}

QStringList QKlipperV412Mode::resolutions() const
{
    return m_resolutions;
}

void QKlipperV412Mode::setResolutions(const QStringList &resolutions)
{
    m_resolutions = resolutions;
}

