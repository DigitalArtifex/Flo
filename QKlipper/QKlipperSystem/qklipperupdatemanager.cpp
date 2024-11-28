#include "qklipperupdatemanager.h"

QKlipperUpdateManager::QKlipperUpdateManager(QObject *parent)
    : QObject{parent}
{}

bool QKlipperUpdateManager::isBusy() const
{
    return m_isBusy;
}

void QKlipperUpdateManager::setIsBusy(bool isBusy)
{
    if (m_isBusy == isBusy)
        return;
    m_isBusy = isBusy;
    emit isBusyChanged();
}

qint32 QKlipperUpdateManager::githubRateLimit() const
{
    return m_githubRateLimit;
}

void QKlipperUpdateManager::setGithubRateLimit(qint32 githubRateLimit)
{
    if (m_githubRateLimit == githubRateLimit)
        return;
    m_githubRateLimit = githubRateLimit;
    emit githubRateLimitChanged();
}

qint32 QKlipperUpdateManager::githubRequestsRemaining() const
{
    return m_githubRequestsRemaining;
}

void QKlipperUpdateManager::setGithubRequestsRemaining(qint32 githubRequestsRemaining)
{
    if (m_githubRequestsRemaining == githubRequestsRemaining)
        return;
    m_githubRequestsRemaining = githubRequestsRemaining;
    emit githubRequestsRemainingChanged();
}

qint32 QKlipperUpdateManager::githubLimitResetTime() const
{
    return m_githubLimitResetTime;
}

void QKlipperUpdateManager::setGithubLimitResetTime(qint32 githubLimitResetTime)
{
    if (m_githubLimitResetTime == githubLimitResetTime)
        return;
    m_githubLimitResetTime = githubLimitResetTime;
    emit githubLimitResetTimeChanged();
}

qint32 QKlipperUpdateManager::systemPackageCount() const
{
    return m_systemPackageCount;
}

void QKlipperUpdateManager::setSystemPackageCount(qint32 systemPackageCount)
{
    if (m_systemPackageCount == systemPackageCount)
        return;
    m_systemPackageCount = systemPackageCount;
    emit systemPackageCountChanged();
}

QStringList QKlipperUpdateManager::systemPackages() const
{
    return m_systemPackages;
}

void QKlipperUpdateManager::setSystemPackages(const QStringList &systemPackages)
{
    if (m_systemPackages == systemPackages)
        return;

    m_systemPackages = systemPackages;
    emit systemPackagesChanged();
}

QMap<QString, QKlipperUpdatePackage*> QKlipperUpdateManager::packages() const
{
    return m_packages;
}

void QKlipperUpdateManager::setPackages(const QMap<QString, QKlipperUpdatePackage*> &packages)
{
    m_packages = packages;
    emit packagesChanged();
}

void QKlipperUpdateManager::setPackage(const QString &key, QKlipperUpdatePackage *package)
{
    if(!m_packages.contains(key))
        m_packages.insert(key, package);
    else
        m_packages[key] = package;

    emit packagesChanged();
}

QString QKlipperUpdateManager::currentStateMessage() const
{
    return m_currentStateMessage;
}

void QKlipperUpdateManager::setCurrentStateMessage(const QString &currentStateMessage)
{
    if (m_currentStateMessage == currentStateMessage)
        return;

    m_currentStateMessage = currentStateMessage;
    emit currentStateMessageChanged();
}

QString QKlipperUpdateManager::currentApplication() const
{
    return m_currentApplication;
}

void QKlipperUpdateManager::setCurrentApplication(const QString &currentApplication)
{
    if (m_currentApplication == currentApplication)
        return;

    m_currentApplication = currentApplication;
    emit currentApplicationChanged();
}
