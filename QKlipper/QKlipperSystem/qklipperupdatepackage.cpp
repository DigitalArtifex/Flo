#include "qklipperupdatepackage.h"

QKlipperUpdatePackage::QKlipperUpdatePackage(QObject *parent)
    : QObject{parent}
{}

QKlipperUpdatePackage::QKlipperUpdatePackage(const QKlipperUpdatePackage &value)
{
    m_debugEnabled = value.m_debugEnabled;
    m_isValid = value.m_isValid;
    m_isDirty = value.m_isDirty;
    m_corrupt = value.m_corrupt;
    m_detached = value.m_detached;
    m_pristine = value.m_pristine;

    m_channel = value.m_channel;
    m_configuredType = value.m_configuredType;
    m_detectedType = value.m_detectedType;
    m_remoteAlias = value.m_remoteAlias;
    m_branch = value.m_branch;
    m_owner = value.m_owner;
    m_repoName = value.m_repoName;
    m_version = value.m_version;
    m_rollbackVersion = value.m_rollbackVersion;
    m_remoteVersion = value.m_remoteVersion;
    m_currentHash = value.m_currentHash;
    m_remoteHash = value.m_remoteHash;
    m_fullVersionString = value.m_fullVersionString;
    m_recoveryUrl = value.m_recoveryUrl;
    m_remoteUrl = value.m_remoteUrl;

    m_warnings = value.m_warnings;
    m_anomalies = value.m_anomalies;
    m_infoTags = value.m_infoTags;
    m_gitMessages = value.m_gitMessages;

    m_commitsBehind = value.m_commitsBehind;
}

QKlipperUpdatePackage::QKlipperUpdatePackage(QKlipperUpdatePackage &&value)
{
    m_debugEnabled = value.m_debugEnabled;
    m_isValid = value.m_isValid;
    m_isDirty = value.m_isDirty;
    m_corrupt = value.m_corrupt;
    m_detached = value.m_detached;
    m_pristine = value.m_pristine;

    m_channel = value.m_channel;
    m_configuredType = value.m_configuredType;
    m_detectedType = value.m_detectedType;
    m_remoteAlias = value.m_remoteAlias;
    m_branch = value.m_branch;
    m_owner = value.m_owner;
    m_repoName = value.m_repoName;
    m_version = value.m_version;
    m_rollbackVersion = value.m_rollbackVersion;
    m_remoteVersion = value.m_remoteVersion;
    m_currentHash = value.m_currentHash;
    m_remoteHash = value.m_remoteHash;
    m_fullVersionString = value.m_fullVersionString;
    m_recoveryUrl = value.m_recoveryUrl;
    m_remoteUrl = value.m_remoteUrl;

    m_warnings = value.m_warnings;
    m_anomalies = value.m_anomalies;
    m_infoTags = value.m_infoTags;
    m_gitMessages = value.m_gitMessages;

    m_commitsBehind = value.m_commitsBehind;
}

QKlipperUpdatePackage &QKlipperUpdatePackage::operator=(const QKlipperUpdatePackage &value)
{
    m_debugEnabled = value.m_debugEnabled;
    m_isValid = value.m_isValid;
    m_isDirty = value.m_isDirty;
    m_corrupt = value.m_corrupt;
    m_detached = value.m_detached;
    m_pristine = value.m_pristine;

    m_channel = value.m_channel;
    m_configuredType = value.m_configuredType;
    m_detectedType = value.m_detectedType;
    m_remoteAlias = value.m_remoteAlias;
    m_branch = value.m_branch;
    m_owner = value.m_owner;
    m_repoName = value.m_repoName;
    m_version = value.m_version;
    m_rollbackVersion = value.m_rollbackVersion;
    m_remoteVersion = value.m_remoteVersion;
    m_currentHash = value.m_currentHash;
    m_remoteHash = value.m_remoteHash;
    m_fullVersionString = value.m_fullVersionString;
    m_recoveryUrl = value.m_recoveryUrl;
    m_remoteUrl = value.m_remoteUrl;

    m_warnings = value.m_warnings;
    m_anomalies = value.m_anomalies;
    m_infoTags = value.m_infoTags;
    m_gitMessages = value.m_gitMessages;

    m_commitsBehind = value.m_commitsBehind;

    return *this;
}

QKlipperUpdatePackage &QKlipperUpdatePackage::operator=(QKlipperUpdatePackage &&value)
{
    m_debugEnabled = value.m_debugEnabled;
    m_isValid = value.m_isValid;
    m_isDirty = value.m_isDirty;
    m_corrupt = value.m_corrupt;
    m_detached = value.m_detached;
    m_pristine = value.m_pristine;

    m_channel = value.m_channel;
    m_configuredType = value.m_configuredType;
    m_detectedType = value.m_detectedType;
    m_remoteAlias = value.m_remoteAlias;
    m_branch = value.m_branch;
    m_owner = value.m_owner;
    m_repoName = value.m_repoName;
    m_version = value.m_version;
    m_rollbackVersion = value.m_rollbackVersion;
    m_remoteVersion = value.m_remoteVersion;
    m_currentHash = value.m_currentHash;
    m_remoteHash = value.m_remoteHash;
    m_fullVersionString = value.m_fullVersionString;
    m_recoveryUrl = value.m_recoveryUrl;
    m_remoteUrl = value.m_remoteUrl;

    m_warnings = value.m_warnings;
    m_anomalies = value.m_anomalies;
    m_infoTags = value.m_infoTags;
    m_gitMessages = value.m_gitMessages;

    m_commitsBehind = value.m_commitsBehind;

    return *this;
}

bool QKlipperUpdatePackage::operator==(const QKlipperUpdatePackage &value)
{
    if(m_debugEnabled != value.m_debugEnabled) return false;
    if(m_isValid != value.m_isValid) return false;
    if(m_isDirty != value.m_isDirty) return false;
    if(m_corrupt != value.m_corrupt) return false;
    if(m_detached != value.m_detached) return false;
    if(m_pristine != value.m_pristine) return false;

    if(m_channel != value.m_channel) return false;
    if(m_configuredType != value.m_configuredType) return false;
    if(m_detectedType != value.m_detectedType) return false;
    if(m_remoteAlias != value.m_remoteAlias) return false;
    if(m_branch != value.m_branch) return false;
    if(m_owner != value.m_owner) return false;
    if(m_repoName != value.m_repoName) return false;
    if(m_version != value.m_version) return false;
    if(m_rollbackVersion != value.m_rollbackVersion) return false;
    if(m_remoteVersion != value.m_remoteVersion) return false;
    if(m_currentHash != value.m_currentHash) return false;
    if(m_remoteHash != value.m_remoteHash) return false;
    if(m_fullVersionString != value.m_fullVersionString) return false;
    if(m_recoveryUrl != value.m_recoveryUrl) return false;
    if(m_remoteUrl != value.m_remoteUrl) return false;

    if(m_warnings != value.m_warnings) return false;
    if(m_anomalies != value.m_anomalies) return false;
    if(m_infoTags != value.m_infoTags) return false;
    if(m_gitMessages != value.m_gitMessages) return false;

    foreach(QKlipperUpdateCommit commit, value.m_commitsBehind)
    {
        if(!m_commitsBehind.contains(commit))
            return false;
    }

    return true;
}

bool QKlipperUpdatePackage::operator==(QKlipperUpdatePackage &&value)
{
    if(m_debugEnabled != value.m_debugEnabled) return false;
    if(m_isValid != value.m_isValid) return false;
    if(m_isDirty != value.m_isDirty) return false;
    if(m_corrupt != value.m_corrupt) return false;
    if(m_detached != value.m_detached) return false;
    if(m_pristine != value.m_pristine) return false;

    if(m_channel != value.m_channel) return false;
    if(m_configuredType != value.m_configuredType) return false;
    if(m_detectedType != value.m_detectedType) return false;
    if(m_remoteAlias != value.m_remoteAlias) return false;
    if(m_branch != value.m_branch) return false;
    if(m_owner != value.m_owner) return false;
    if(m_repoName != value.m_repoName) return false;
    if(m_version != value.m_version) return false;
    if(m_rollbackVersion != value.m_rollbackVersion) return false;
    if(m_remoteVersion != value.m_remoteVersion) return false;
    if(m_currentHash != value.m_currentHash) return false;
    if(m_remoteHash != value.m_remoteHash) return false;
    if(m_fullVersionString != value.m_fullVersionString) return false;
    if(m_recoveryUrl != value.m_recoveryUrl) return false;
    if(m_remoteUrl != value.m_remoteUrl) return false;

    if(m_warnings != value.m_warnings) return false;
    if(m_anomalies != value.m_anomalies) return false;
    if(m_infoTags != value.m_infoTags) return false;
    if(m_gitMessages != value.m_gitMessages) return false;

    foreach(QKlipperUpdateCommit commit, value.m_commitsBehind)
    {
        if(!m_commitsBehind.contains(commit))
            return false;
    }

    return true;
}

bool QKlipperUpdatePackage::operator!=(const QKlipperUpdatePackage &value)
{
    foreach(QKlipperUpdateCommit commit, value.m_commitsBehind)
    {
        if(!m_commitsBehind.contains(commit))
            return true;
    }

    if(m_debugEnabled == value.m_debugEnabled &&
        m_isValid == value.m_isValid &&
        m_isDirty == value.m_isDirty &&
        m_corrupt == value.m_corrupt &&
        m_detached == value.m_detached &&
        m_pristine == value.m_pristine &&
        m_channel == value.m_channel &&
        m_configuredType == value.m_configuredType &&
        m_detectedType == value.m_detectedType &&
        m_remoteAlias == value.m_remoteAlias &&
        m_branch == value.m_branch &&
        m_owner == value.m_owner &&
        m_repoName == value.m_repoName &&
        m_version == value.m_version &&
        m_rollbackVersion == value.m_rollbackVersion &&
        m_remoteVersion == value.m_remoteVersion &&
        m_currentHash == value.m_currentHash &&
        m_remoteHash == value.m_remoteHash &&
        m_fullVersionString == value.m_fullVersionString &&
        m_recoveryUrl == value.m_recoveryUrl &&
        m_remoteUrl == value.m_remoteUrl &&
        m_warnings == value.m_warnings &&
        m_anomalies == value.m_anomalies &&
        m_infoTags == value.m_infoTags &&
        m_gitMessages == value.m_gitMessages)
        return false;

    return true;
}

bool QKlipperUpdatePackage::operator!=(QKlipperUpdatePackage &&value)
{
    foreach(QKlipperUpdateCommit commit, value.m_commitsBehind)
    {
        if(!m_commitsBehind.contains(commit))
            return true;
    }

    if(m_debugEnabled == value.m_debugEnabled &&
        m_isValid == value.m_isValid &&
        m_isDirty == value.m_isDirty &&
        m_corrupt == value.m_corrupt &&
        m_detached == value.m_detached &&
        m_pristine == value.m_pristine &&
        m_channel == value.m_channel &&
        m_configuredType == value.m_configuredType &&
        m_detectedType == value.m_detectedType &&
        m_remoteAlias == value.m_remoteAlias &&
        m_branch == value.m_branch &&
        m_owner == value.m_owner &&
        m_repoName == value.m_repoName &&
        m_version == value.m_version &&
        m_rollbackVersion == value.m_rollbackVersion &&
        m_remoteVersion == value.m_remoteVersion &&
        m_currentHash == value.m_currentHash &&
        m_remoteHash == value.m_remoteHash &&
        m_fullVersionString == value.m_fullVersionString &&
        m_recoveryUrl == value.m_recoveryUrl &&
        m_remoteUrl == value.m_remoteUrl &&
        m_warnings == value.m_warnings &&
        m_anomalies == value.m_anomalies &&
        m_infoTags == value.m_infoTags &&
        m_gitMessages == value.m_gitMessages)
        return false;

    return true;
}

bool QKlipperUpdatePackage::debugEnabled() const
{
    return m_debugEnabled;
}

void QKlipperUpdatePackage::setDebugEnabled(bool debugEnabled)
{
    if (m_debugEnabled == debugEnabled)
        return;
    m_debugEnabled = debugEnabled;
    emit debugEnabledChanged();
}

bool QKlipperUpdatePackage::isValid() const
{
    return m_isValid;
}

void QKlipperUpdatePackage::setIsValid(bool isValid)
{
    if (m_isValid == isValid)
        return;
    m_isValid = isValid;
    emit isValidChanged();
}

bool QKlipperUpdatePackage::isDirty() const
{
    return m_isDirty;
}

void QKlipperUpdatePackage::setIsDirty(bool isDirty)
{
    if (m_isDirty == isDirty)
        return;
    m_isDirty = isDirty;
    emit isDirtyChanged();
}

bool QKlipperUpdatePackage::corrupt() const
{
    return m_corrupt;
}

void QKlipperUpdatePackage::setCorrupt(bool corrupt)
{
    if (m_corrupt == corrupt)
        return;
    m_corrupt = corrupt;
    emit corruptChanged();
}

bool QKlipperUpdatePackage::detached() const
{
    return m_detached;
}

void QKlipperUpdatePackage::setDetached(bool detached)
{
    if (m_detached == detached)
        return;
    m_detached = detached;
    emit detachedChanged();
}

bool QKlipperUpdatePackage::pristine() const
{
    return m_pristine;
}

void QKlipperUpdatePackage::setPristine(bool pristine)
{
    if (m_pristine == pristine)
        return;
    m_pristine = pristine;
    emit pristineChanged();
}

QString QKlipperUpdatePackage::channel() const
{
    return m_channel;
}

void QKlipperUpdatePackage::setChannel(const QString &channel)
{
    if (m_channel == channel)
        return;
    m_channel = channel;
    emit channelChanged();
}

QString QKlipperUpdatePackage::configuredType() const
{
    return m_configuredType;
}

void QKlipperUpdatePackage::setConfiguredType(const QString &configuredType)
{
    if (m_configuredType == configuredType)
        return;
    m_configuredType = configuredType;
    emit configuredTypeChanged();
}

QString QKlipperUpdatePackage::detectedType() const
{
    return m_detectedType;
}

void QKlipperUpdatePackage::setDetectedType(const QString &detectedType)
{
    if (m_detectedType == detectedType)
        return;
    m_detectedType = detectedType;
    emit detectedTypeChanged();
}

QString QKlipperUpdatePackage::remoteAlias() const
{
    return m_remoteAlias;
}

void QKlipperUpdatePackage::setRemoteAlias(const QString &remoteAlias)
{
    if (m_remoteAlias == remoteAlias)
        return;
    m_remoteAlias = remoteAlias;
    emit remoteAliasChanged();
}

QString QKlipperUpdatePackage::branch() const
{
    return m_branch;
}

void QKlipperUpdatePackage::setBranch(const QString &branch)
{
    if (m_branch == branch)
        return;
    m_branch = branch;
    emit branchChanged();
}

QString QKlipperUpdatePackage::owner() const
{
    return m_owner;
}

void QKlipperUpdatePackage::setOwner(const QString &owner)
{
    if (m_owner == owner)
        return;
    m_owner = owner;
    emit ownerChanged();
}

QString QKlipperUpdatePackage::repoName() const
{
    return m_repoName;
}

void QKlipperUpdatePackage::setRepoName(const QString &repoName)
{
    if (m_repoName == repoName)
        return;
    m_repoName = repoName;
    emit repoNameChanged();
}

QString QKlipperUpdatePackage::version() const
{
    return m_version;
}

void QKlipperUpdatePackage::setVersion(const QString &version)
{
    if (m_version == version)
        return;
    m_version = version;
    emit versionChanged();
}

QString QKlipperUpdatePackage::rollbackVersion() const
{
    return m_rollbackVersion;
}

void QKlipperUpdatePackage::setRollbackVersion(const QString &rollbackVersion)
{
    if (m_rollbackVersion == rollbackVersion)
        return;
    m_rollbackVersion = rollbackVersion;
    emit rollbackVersionChanged();
}

QString QKlipperUpdatePackage::remoteVersion() const
{
    return m_remoteVersion;
}

void QKlipperUpdatePackage::setRemoteVersion(const QString &remoteVersion)
{
    if (m_remoteVersion == remoteVersion)
        return;
    m_remoteVersion = remoteVersion;
    emit remoteVersionChanged();
}

QString QKlipperUpdatePackage::currentHash() const
{
    return m_currentHash;
}

void QKlipperUpdatePackage::setCurrentHash(const QString &currentHash)
{
    if (m_currentHash == currentHash)
        return;
    m_currentHash = currentHash;
    emit currentHashChanged();
}

QString QKlipperUpdatePackage::remoteHash() const
{
    return m_remoteHash;
}

void QKlipperUpdatePackage::setRemoteHash(const QString &remoteHash)
{
    if (m_remoteHash == remoteHash)
        return;
    m_remoteHash = remoteHash;
    emit remoteHashChanged();
}

QString QKlipperUpdatePackage::fullVersionString() const
{
    return m_fullVersionString;
}

void QKlipperUpdatePackage::setFullVersionString(const QString &fullVersionString)
{
    if (m_fullVersionString == fullVersionString)
        return;
    m_fullVersionString = fullVersionString;
    emit fullVersionStringChanged();
}

QString QKlipperUpdatePackage::recoveryUrl() const
{
    return m_recoveryUrl;
}

void QKlipperUpdatePackage::setRecoveryUrl(const QString &recoveryUrl)
{
    if (m_recoveryUrl == recoveryUrl)
        return;
    m_recoveryUrl = recoveryUrl;
    emit recoveryUrlChanged();
}

QString QKlipperUpdatePackage::remoteUrl() const
{
    return m_remoteUrl;
}

void QKlipperUpdatePackage::setRemoteUrl(const QString &remoteUrl)
{
    if (m_remoteUrl == remoteUrl)
        return;
    m_remoteUrl = remoteUrl;
    emit remoteUrlChanged();
}

QStringList QKlipperUpdatePackage::warnings() const
{
    return m_warnings;
}

void QKlipperUpdatePackage::setWarnings(const QStringList &warnings)
{
    if (m_warnings == warnings)
        return;
    m_warnings = warnings;
    emit warningsChanged();
}

QStringList QKlipperUpdatePackage::anomalies() const
{
    return m_anomalies;
}

void QKlipperUpdatePackage::setAnomalies(const QStringList &anomalies)
{
    if (m_anomalies == anomalies)
        return;
    m_anomalies = anomalies;
    emit anomaliesChanged();
}

QStringList QKlipperUpdatePackage::infoTags() const
{
    return m_infoTags;
}

void QKlipperUpdatePackage::setInfoTags(const QStringList &infoTags)
{
    if (m_infoTags == infoTags)
        return;
    m_infoTags = infoTags;
    emit infoTagsChanged();
}

QStringList QKlipperUpdatePackage::gitMessages() const
{
    return m_gitMessages;
}

void QKlipperUpdatePackage::setGitMessages(const QStringList &gitMessages)
{
    if (m_gitMessages == gitMessages)
        return;

    m_gitMessages = gitMessages;
    emit gitMessagesChanged();
}

QList<QKlipperUpdateCommit> QKlipperUpdatePackage::commitsBehind() const
{
    return m_commitsBehind;
}

void QKlipperUpdatePackage::setCommitsBehind(const QList<QKlipperUpdateCommit> &commitsBehind)
{
    m_commitsBehind = commitsBehind;
    emit commitsBehindChanged();
}
