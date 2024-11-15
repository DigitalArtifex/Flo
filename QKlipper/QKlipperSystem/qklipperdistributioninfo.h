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
class QKlipperDistributionInfo : public QObject
{
    Q_OBJECT

    friend QKlipperSystem;
    friend QKlipperConsole;
public:
    explicit QKlipperDistributionInfo(QObject *parent = nullptr);

    QKlipperDistributionInfo(const QKlipperDistributionInfo &value);
    QKlipperDistributionInfo(QKlipperDistributionInfo &&value);
    QKlipperDistributionInfo &operator=(const QKlipperDistributionInfo &value);
    QKlipperDistributionInfo &operator=(QKlipperDistributionInfo &&value);
    bool operator==(const QKlipperDistributionInfo &value);
    bool operator==(QKlipperDistributionInfo &&value);
    bool operator!=(const QKlipperDistributionInfo &value);
    bool operator!=(QKlipperDistributionInfo &&value);
    QString name() const;

    QString id() const;

    QString version() const;

    QString versionMajor() const;

    QString versionMinor() const;

    QString versionBuildNumber() const;

    QString style() const;

    QString codename() const;

public slots:
    void setName(const QString &name);

    void setId(const QString &id);

    void setVersion(const QString &version);

    void setVersionMajor(const QString &versionMajor);

    void setVersionMinor(const QString &versionMinor);

    void setVersionBuildNumber(const QString &versionBuildNumber);

    void setStyle(const QString &style);

    void setCodename(const QString &codename);

private slots:

signals:

    void nameChanged();

    void idChanged();

    void versionChanged();

    void versionMajorChanged();

    void versionMinorChanged();

    void versionBuildNumberChanged();

    void styleChanged();

    void codenameChanged();

private:
    QString m_name;
    QString m_id;
    QString m_version;
    QString m_versionMajor;
    QString m_versionMinor;
    QString m_versionBuildNumber;
    QString m_style;
    QString m_codename;

    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged FINAL)
    Q_PROPERTY(QString id READ id WRITE setId NOTIFY idChanged FINAL)
    Q_PROPERTY(QString version READ version WRITE setVersion NOTIFY versionChanged FINAL)
    Q_PROPERTY(QString versionMajor READ versionMajor WRITE setVersionMajor NOTIFY versionMajorChanged FINAL)
    Q_PROPERTY(QString versionMinor READ versionMinor WRITE setVersionMinor NOTIFY versionMinorChanged FINAL)
    Q_PROPERTY(QString versionBuildNumber READ versionBuildNumber WRITE setVersionBuildNumber NOTIFY versionBuildNumberChanged FINAL)
    Q_PROPERTY(QString style READ style WRITE setStyle NOTIFY styleChanged FINAL)
    Q_PROPERTY(QString codename READ codename WRITE setCodename NOTIFY codenameChanged FINAL)
};

#endif // QKLIPPERDISTRIBUTIONINFO_H
