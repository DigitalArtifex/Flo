/*
 * QKlipper - A Qt library for the Klipper/Moonraker API
 * Copyright (C) 2024 James Dudeck
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of  MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef QKLIPPERDISTRIBUTIONINFO_H
#define QKLIPPERDISTRIBUTIONINFO_H

#include <QObject>

class QKlipperSystem;
class QKlipperConsole;

/*!
 * \brief Filled by machine.system_info
 */
class QKlipperDistributionInfo
{
    friend QKlipperSystem;
    friend QKlipperConsole;
public:
    QKlipperDistributionInfo() = default;
    ~QKlipperDistributionInfo() = default;

    QKlipperDistributionInfo(const QKlipperDistributionInfo &value)
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
    QKlipperDistributionInfo &operator=(const QKlipperDistributionInfo &value)
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
    bool operator==(const QKlipperDistributionInfo &value)
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
    bool operator!=(const QKlipperDistributionInfo &value)
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
    QString name() const { return m_name; }

    QString id() const { return m_id; }

    QString version() const { return m_version; }

    QString versionMajor() const { return m_versionMajor; }

    QString versionMinor() const { return m_versionMinor; }

    QString versionBuildNumber() const { return m_versionBuildNumber; }

    QString style() const { return m_style; }

    QString codename() const { return m_codename; }

protected:
    void setName(const QString &name) { m_name = name; }

    void setId(const QString &id) { m_id = id; }

    void setVersion(const QString &version) { m_version = version; }

    void setVersionMajor(const QString &versionMajor) { m_versionMajor = versionMajor; }

    void setVersionMinor(const QString &versionMinor) { m_versionMinor = versionMinor; }

    void setVersionBuildNumber(const QString &versionBuildNumber) { m_versionBuildNumber = versionBuildNumber; }

    void setStyle(const QString &style) { m_style = style; }

    void setCodename(const QString &codename) { m_codename = codename; }

private:
    QString m_name;
    QString m_id;
    QString m_version;
    QString m_versionMajor;
    QString m_versionMinor;
    QString m_versionBuildNumber;
    QString m_style;
    QString m_codename;
};

#endif // QKLIPPERDISTRIBUTIONINFO_H
