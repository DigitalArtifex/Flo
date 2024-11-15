#include "qklipperdistributioninfo.h"

QKlipperDistributionInfo::QKlipperDistributionInfo(QObject *parent)
    : QObject{parent}
{}

QKlipperDistributionInfo::QKlipperDistributionInfo(const QKlipperDistributionInfo &value)
{
    m_name = value.m_name;
    m_id = value.m_id;
    m_version = value.m_version;
    m_versionMajor = value.m_versionMajor;
    m_versionMinor = value.m_versionMinor;
    m_versionBuildNumber = value.m_versionBuildNumber;
    m_style = value.m_style;
    m_codename = value.m_codename;
}
QKlipperDistributionInfo::QKlipperDistributionInfo(QKlipperDistributionInfo &&value)
{
    m_name = value.m_name;
    m_id = value.m_id;
    m_version = value.m_version;
    m_versionMajor = value.m_versionMajor;
    m_versionMinor = value.m_versionMinor;
    m_versionBuildNumber = value.m_versionBuildNumber;
    m_style = value.m_style;
    m_codename = value.m_codename;
}

QKlipperDistributionInfo &QKlipperDistributionInfo::operator=(const QKlipperDistributionInfo &value)
{
    m_name = value.m_name;
    m_id = value.m_id;
    m_version = value.m_version;
    m_versionMajor = value.m_versionMajor;
    m_versionMinor = value.m_versionMinor;
    m_versionBuildNumber = value.m_versionBuildNumber;
    m_style = value.m_style;
    m_codename = value.m_codename;

    return *this;
}

QKlipperDistributionInfo &QKlipperDistributionInfo::operator=(QKlipperDistributionInfo &&value)
{
    m_name = value.m_name;
    m_id = value.m_id;
    m_version = value.m_version;
    m_versionMajor = value.m_versionMajor;
    m_versionMinor = value.m_versionMinor;
    m_versionBuildNumber = value.m_versionBuildNumber;
    m_style = value.m_style;
    m_codename = value.m_codename;

    return *this;
}

bool QKlipperDistributionInfo::operator==(const QKlipperDistributionInfo &value)
{
    if(m_name != value.m_name) return false;
    if(m_id != value.m_id) return false;
    if(m_version != value.m_version) return false;
    if(m_versionMajor != value.m_versionMajor) return false;
    if(m_versionMinor != value.m_versionMinor) return false;
    if(m_versionBuildNumber != value.m_versionBuildNumber) return false;
    if(m_style != value.m_style) return false;
    if(m_codename != value.m_codename) return false;

    return true;
}

bool QKlipperDistributionInfo::operator==(QKlipperDistributionInfo &&value)
{
    if(m_name != value.m_name) return false;
    if(m_id != value.m_id) return false;
    if(m_version != value.m_version) return false;
    if(m_versionMajor != value.m_versionMajor) return false;
    if(m_versionMinor != value.m_versionMinor) return false;
    if(m_versionBuildNumber != value.m_versionBuildNumber) return false;
    if(m_style != value.m_style) return false;
    if(m_codename != value.m_codename) return false;

    return true;
}

bool QKlipperDistributionInfo::operator!=(const QKlipperDistributionInfo &value)
{
    if(m_name == value.m_name &&
        m_id == value.m_id &&
        m_version == value.m_version &&
        m_versionMajor == value.m_versionMajor &&
        m_versionMinor == value.m_versionMinor &&
        m_versionBuildNumber == value.m_versionBuildNumber &&
        m_style == value.m_style &&
        m_codename == value.m_codename)
        return false;

    return true;
}

bool QKlipperDistributionInfo::operator!=(QKlipperDistributionInfo &&value)
{
    if(m_name == value.m_name &&
        m_id == value.m_id &&
        m_version == value.m_version &&
        m_versionMajor == value.m_versionMajor &&
        m_versionMinor == value.m_versionMinor &&
        m_versionBuildNumber == value.m_versionBuildNumber &&
        m_style == value.m_style &&
        m_codename == value.m_codename)
        return false;

    return true;
}

QString QKlipperDistributionInfo::name() const
{
    return m_name;
}

void QKlipperDistributionInfo::setName(const QString &name)
{
    if (m_name == name)
        return;
    m_name = name;
    emit nameChanged();
}

QString QKlipperDistributionInfo::id() const
{
    return m_id;
}

void QKlipperDistributionInfo::setId(const QString &id)
{
    if (m_id == id)
        return;
    m_id = id;
    emit idChanged();
}

QString QKlipperDistributionInfo::version() const
{
    return m_version;
}

void QKlipperDistributionInfo::setVersion(const QString &version)
{
    if (m_version == version)
        return;
    m_version = version;
    emit versionChanged();
}

QString QKlipperDistributionInfo::versionMajor() const
{
    return m_versionMajor;
}

void QKlipperDistributionInfo::setVersionMajor(const QString &versionMajor)
{
    if (m_versionMajor == versionMajor)
        return;
    m_versionMajor = versionMajor;
    emit versionMajorChanged();
}

QString QKlipperDistributionInfo::versionMinor() const
{
    return m_versionMinor;
}

void QKlipperDistributionInfo::setVersionMinor(const QString &versionMinor)
{
    if (m_versionMinor == versionMinor)
        return;
    m_versionMinor = versionMinor;
    emit versionMinorChanged();
}

QString QKlipperDistributionInfo::versionBuildNumber() const
{
    return m_versionBuildNumber;
}

void QKlipperDistributionInfo::setVersionBuildNumber(const QString &versionBuildNumber)
{
    if (m_versionBuildNumber == versionBuildNumber)
        return;
    m_versionBuildNumber = versionBuildNumber;
    emit versionBuildNumberChanged();
}

QString QKlipperDistributionInfo::style() const
{
    return m_style;
}

void QKlipperDistributionInfo::setStyle(const QString &style)
{
    if (m_style == style)
        return;
    m_style = style;
    emit styleChanged();
}

QString QKlipperDistributionInfo::codename() const
{
    return m_codename;
}

void QKlipperDistributionInfo::setCodename(const QString &codename)
{
    if (m_codename == codename)
        return;
    m_codename = codename;
    emit codenameChanged();
}
