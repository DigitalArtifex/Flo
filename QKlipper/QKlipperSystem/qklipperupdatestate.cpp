#include "qklipperupdatestate.h"

QKlipperUpdateState::QKlipperUpdateState(QObject *parent)
    : QObject{parent}
{}

bool QKlipperUpdateState::isBusy() const
{
    return m_isBusy;
}

void QKlipperUpdateState::setIsBusy(bool isBusy)
{
    if (m_isBusy == isBusy)
        return;
    m_isBusy = isBusy;
    emit isBusyChanged();
}

qint32 QKlipperUpdateState::githubRateLimit() const
{
    return m_githubRateLimit;
}

void QKlipperUpdateState::setGithubRateLimit(qint32 githubRateLimit)
{
    if (m_githubRateLimit == githubRateLimit)
        return;
    m_githubRateLimit = githubRateLimit;
    emit githubRateLimitChanged();
}

qint32 QKlipperUpdateState::githubRequestsRemaining() const
{
    return m_githubRequestsRemaining;
}

void QKlipperUpdateState::setGithubRequestsRemaining(qint32 githubRequestsRemaining)
{
    if (m_githubRequestsRemaining == githubRequestsRemaining)
        return;
    m_githubRequestsRemaining = githubRequestsRemaining;
    emit githubRequestsRemainingChanged();
}

qint32 QKlipperUpdateState::githubLimitResetTime() const
{
    return m_githubLimitResetTime;
}

void QKlipperUpdateState::setGithubLimitResetTime(qint32 githubLimitResetTime)
{
    if (m_githubLimitResetTime == githubLimitResetTime)
        return;
    m_githubLimitResetTime = githubLimitResetTime;
    emit githubLimitResetTimeChanged();
}

qint32 QKlipperUpdateState::systemPackageCount() const
{
    return m_systemPackageCount;
}

void QKlipperUpdateState::setSystemPackageCount(qint32 systemPackageCount)
{
    if (m_systemPackageCount == systemPackageCount)
        return;
    m_systemPackageCount = systemPackageCount;
    emit systemPackageCountChanged();
}

QStringList QKlipperUpdateState::systemPackages() const
{
    return m_systemPackages;
}

void QKlipperUpdateState::setSystemPackages(const QStringList &systemPackages)
{
    if (m_systemPackages == systemPackages)
        return;
    m_systemPackages = systemPackages;
    emit systemPackagesChanged();
}

QMultiMap<QString, QKlipperUpdatePackage> QKlipperUpdateState::packages() const
{
    return m_packages;
}

void QKlipperUpdateState::setPackages(const QMultiMap<QString, QKlipperUpdatePackage> &packages)
{
    m_packages = packages;
    emit packagesChanged();
}
