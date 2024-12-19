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

#ifndef QKLIPPERUPDATEPACKAGE_H
#define QKLIPPERUPDATEPACKAGE_H

#include <QObject>

#include "qklipperupdatecommit.h"

class QKlipperConsole;

class QKlipperUpdatePackage
{
        friend QKlipperConsole;
public:
    QKlipperUpdatePackage() = default;
    ~QKlipperUpdatePackage() = default;

    QKlipperUpdatePackage(const QKlipperUpdatePackage &value)
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
    QKlipperUpdatePackage &operator=(const QKlipperUpdatePackage &value)
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
    bool operator==(const QKlipperUpdatePackage &value) const
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

        if(m_commitsBehind != value.m_commitsBehind) return false;

        return true;
    }

    bool operator!=(const QKlipperUpdatePackage &value) const { return !(*this == value); }

    bool debugEnabled() const { return m_debugEnabled; }

    bool isValid() const { return m_isValid; }

    bool isDirty() const { return m_isDirty; }

    bool corrupt() const { return m_corrupt; }

    bool detached() const { return m_detached; }

    bool pristine() const { return m_pristine; }

    QString channel() const { return m_channel; }

    QString configuredType() const { return m_configuredType; }

    QString detectedType() const { return m_detectedType; }

    QString remoteAlias() const { return m_remoteAlias; }

    QString branch() const { return m_branch; }

    QString owner() const { return m_owner; }

    QString repoName() const { return m_repoName; }

    QString version() const { return m_version; }

    QString rollbackVersion() const { return m_rollbackVersion; }

    QString remoteVersion() const { return m_remoteVersion; }

    QString currentHash() const { return m_currentHash; }

    QString remoteHash() const { return m_remoteHash; }

    QString fullVersionString() const { return m_fullVersionString; }

    QString recoveryUrl() const { return m_recoveryUrl; }

    QString remoteUrl() const { return m_remoteUrl; }

    QStringList warnings() const { return m_warnings; }

    QStringList anomalies() const { return m_anomalies; }

    QStringList infoTags() const { return m_infoTags; }

    QStringList gitMessages() const { return m_gitMessages; }

    QList<QKlipperUpdateCommit> commitsBehind() const { return m_commitsBehind; }

    QString stateMessage() const { return m_stateMessage; }

protected:
    void setDebugEnabled(bool debugEnabled) { m_debugEnabled = debugEnabled; }

    void setIsValid(bool isValid) { m_isValid = isValid; }

    void setIsDirty(bool isDirty) { m_isDirty = isDirty; }

    void setCorrupt(bool corrupt) { m_corrupt = corrupt; }

    void setDetached(bool detached) { m_detached = detached; }

    void setPristine(bool pristine) { m_pristine = pristine; }

    void setChannel(const QString &channel) { m_channel = channel; }

    void setConfiguredType(const QString &configuredType) { m_configuredType = configuredType; }

    void setDetectedType(const QString &detectedType) { m_detectedType = detectedType; }

    void setRemoteAlias(const QString &remoteAlias) { m_remoteAlias = remoteAlias; }

    void setBranch(const QString &branch) { m_branch = branch; }

    void setOwner(const QString &owner) { m_owner = owner; }

    void setRepoName(const QString &repoName) { m_repoName = repoName; }

    void setVersion(const QString &version) { m_version = version; }

    void setRollbackVersion(const QString &rollbackVersion) { m_rollbackVersion = rollbackVersion; }

    void setRemoteVersion(const QString &remoteVersion) { m_remoteVersion = remoteVersion; }

    void setCurrentHash(const QString &currentHash) { m_currentHash = currentHash; }

    void setRemoteHash(const QString &remoteHash) { m_remoteHash = remoteHash; }

    void setFullVersionString(const QString &fullVersionString) { m_fullVersionString = fullVersionString; }

    void setRecoveryUrl(const QString &recoveryUrl) { m_recoveryUrl = recoveryUrl; }

    void setRemoteUrl(const QString &remoteUrl) { m_remoteUrl = remoteUrl; }

    void setWarnings(const QStringList &warnings) { m_warnings = warnings; }

    void setAnomalies(const QStringList &anomalies) { m_anomalies = anomalies; }

    void setInfoTags(const QStringList &infoTags) { m_infoTags = infoTags; }

    void setGitMessages(const QStringList &gitMessages) { m_gitMessages = gitMessages; }

    void setCommitsBehind(const QList<QKlipperUpdateCommit> &commitsBehind) { m_commitsBehind = commitsBehind; }

    void setStateMessage(const QString &stateMessage) { m_stateMessage = stateMessage; }

private:
    bool m_debugEnabled = false;
    bool m_isValid = false;
    bool m_isDirty = false;
    bool m_corrupt = false;
    bool m_detached = false;
    bool m_pristine = false;

    QString m_channel;
    QString m_configuredType;
    QString m_detectedType;
    QString m_remoteAlias;
    QString m_branch;
    QString m_owner;
    QString m_repoName;
    QString m_version;
    QString m_rollbackVersion;
    QString m_remoteVersion;
    QString m_currentHash;
    QString m_remoteHash;
    QString m_fullVersionString;
    QString m_recoveryUrl;
    QString m_remoteUrl;
    QString m_stateMessage;

    QStringList m_warnings;
    QStringList m_anomalies;
    QStringList m_infoTags;
    QStringList m_gitMessages;

    QList<QKlipperUpdateCommit> m_commitsBehind;
};

Q_DECLARE_METATYPE(QKlipperUpdatePackage)

#endif // QKLIPPERUPDATEPACKAGE_H
