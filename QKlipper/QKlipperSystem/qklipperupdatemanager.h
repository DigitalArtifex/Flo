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

#ifndef QKLIPPERUPDATEMANAGER_H
#define QKLIPPERUPDATEMANAGER_H

#include <QObject>
#include <QMultiMap>

#include "qklipperupdatepackage.h"

class QKlipperSystem;
class QKlipperConsole;

class QKlipperUpdateManager : public QObject
{
    Q_OBJECT

    friend QKlipperSystem;
    friend QKlipperConsole;
public:

    explicit QKlipperUpdateManager(QObject *parent = nullptr);

    bool isBusy() const;

    qint32 githubRateLimit() const;

    qint32 githubRequestsRemaining() const;

    qint32 githubLimitResetTime() const;

    qint32 systemPackageCount() const;

    QStringList systemPackages() const;

    QMap<QString, QKlipperUpdatePackage > packages() const;

    QString currentStateMessage() const;

    QString currentApplication() const;

public slots:
    void setIsBusy(bool isBusy);

    void setGithubRateLimit(qint32 githubRateLimit);

    void setGithubRequestsRemaining(qint32 githubRequestsRemaining);

    void setGithubLimitResetTime(qint32 githubLimitResetTime);

    void setSystemPackageCount(qint32 systemPackageCount);

    void setSystemPackages(const QStringList &systemPackages);

    void setPackages(const QMap<QString, QKlipperUpdatePackage > &packages);
    void setPackage(const QString &key, QKlipperUpdatePackage package);

    void setCurrentStateMessage(const QString &currentStateMessage);

    void setCurrentApplication(const QString &currentApplication);

private slots:

signals:

    void isBusyChanged();
    void githubRateLimitChanged();
    void githubRequestsRemainingChanged();
    void githubLimitResetTimeChanged();
    void systemPackageCountChanged();
    void systemPackagesChanged();
    void packagesChanged();
    void currentStateMessageChanged();
    void currentApplicationChanged();

private:
    bool m_isBusy = false;

    qint32 m_githubRateLimit = 0;
    qint32 m_githubRequestsRemaining = 0;
    qint32 m_githubLimitResetTime = 0;
    qint32 m_systemPackageCount = 0;

    QStringList m_systemPackages;

    QMap<QString, QKlipperUpdatePackage> m_packages;

    QString m_currentStateMessage;
    QString m_currentApplication;

    bool m_isUpdating = true;

    Q_PROPERTY(bool isBusy READ isBusy WRITE setIsBusy NOTIFY isBusyChanged FINAL)
    Q_PROPERTY(qint32 githubRateLimit READ githubRateLimit WRITE setGithubRateLimit NOTIFY githubRateLimitChanged FINAL)
    Q_PROPERTY(qint32 githubRequestsRemaining READ githubRequestsRemaining WRITE setGithubRequestsRemaining NOTIFY githubRequestsRemainingChanged FINAL)
    Q_PROPERTY(qint32 githubLimitResetTime READ githubLimitResetTime WRITE setGithubLimitResetTime NOTIFY githubLimitResetTimeChanged FINAL)
    Q_PROPERTY(qint32 systemPackageCount READ systemPackageCount WRITE setSystemPackageCount NOTIFY systemPackageCountChanged FINAL)
    Q_PROPERTY(QStringList systemPackages READ systemPackages WRITE setSystemPackages NOTIFY systemPackagesChanged FINAL)
    Q_PROPERTY(QMap<QString, QKlipperUpdatePackage> packages READ packages WRITE setPackages NOTIFY packagesChanged FINAL)
    Q_PROPERTY(QString currentStateMessage READ currentStateMessage WRITE setCurrentStateMessage NOTIFY currentStateMessageChanged FINAL)
    Q_PROPERTY(QString currentApplication READ currentApplication WRITE setCurrentApplication NOTIFY currentApplicationChanged FINAL)
};

#endif // QKLIPPERUPDATEMANAGER_H
