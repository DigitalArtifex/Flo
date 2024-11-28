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

class QKlipperUpdatePackage : public QObject
{
    Q_OBJECT
public:
    explicit QKlipperUpdatePackage(QObject *parent = nullptr);

    QKlipperUpdatePackage(const QKlipperUpdatePackage &value);
    QKlipperUpdatePackage(QKlipperUpdatePackage &&value);
    QKlipperUpdatePackage &operator=(const QKlipperUpdatePackage &value);
    QKlipperUpdatePackage &operator=(QKlipperUpdatePackage &&value);
    bool operator==(const QKlipperUpdatePackage &value);
    bool operator==(QKlipperUpdatePackage &&value);
    bool operator!=(const QKlipperUpdatePackage &value);
    bool operator!=(QKlipperUpdatePackage &&value);

    bool debugEnabled() const;

    bool isValid() const;

    bool isDirty() const;

    bool corrupt() const;

    bool detached() const;

    bool pristine() const;

    QString channel() const;

    QString configuredType() const;

    QString detectedType() const;

    QString remoteAlias() const;

    QString branch() const;

    QString owner() const;

    QString repoName() const;

    QString version() const;

    QString rollbackVersion() const;

    QString remoteVersion() const;

    QString currentHash() const;

    QString remoteHash() const;

    QString fullVersionString() const;

    QString recoveryUrl() const;

    QString remoteUrl() const;

    QStringList warnings() const;

    QStringList anomalies() const;

    QStringList infoTags() const;

    QStringList gitMessages() const;

    QList<QKlipperUpdateCommit> commitsBehind() const;

    bool updating() const;

    QString stateMessage() const;

public slots:
    void setDebugEnabled(bool debugEnabled);

    void setIsValid(bool isValid);

    void setIsDirty(bool isDirty);

    void setCorrupt(bool corrupt);

    void setDetached(bool detached);

    void setPristine(bool pristine);

    void setChannel(const QString &channel);

    void setConfiguredType(const QString &configuredType);

    void setDetectedType(const QString &detectedType);

    void setRemoteAlias(const QString &remoteAlias);

    void setBranch(const QString &branch);

    void setOwner(const QString &owner);

    void setRepoName(const QString &repoName);

    void setVersion(const QString &version);

    void setRollbackVersion(const QString &rollbackVersion);

    void setRemoteVersion(const QString &remoteVersion);

    void setCurrentHash(const QString &currentHash);

    void setRemoteHash(const QString &remoteHash);

    void setFullVersionString(const QString &fullVersionString);

    void setRecoveryUrl(const QString &recoveryUrl);

    void setRemoteUrl(const QString &remoteUrl);

    void setWarnings(const QStringList &warnings);

    void setAnomalies(const QStringList &anomalies);

    void setInfoTags(const QStringList &infoTags);

    void setGitMessages(const QStringList &gitMessages);

    void setCommitsBehind(const QList<QKlipperUpdateCommit> &commitsBehind);

    void setUpdating(bool updating);
    void setUpdatingFinished(bool finished);

    void setStateMessage(const QString &stateMessage);

signals:

    void debugEnabledChanged();

    void isValidChanged();

    void isDirtyChanged();

    void corruptChanged();

    void detachedChanged();

    void pristineChanged();

    void channelChanged();

    void configuredTypeChanged();

    void detectedTypeChanged();

    void remoteAliasChanged();

    void branchChanged();

    void ownerChanged();

    void repoNameChanged();

    void versionChanged();

    void rollbackVersionChanged();

    void remoteVersionChanged();

    void currentHashChanged();

    void remoteHashChanged();

    void fullVersionStringChanged();

    void recoveryUrlChanged();

    void remoteUrlChanged();

    void warningsChanged();

    void anomaliesChanged();

    void infoTagsChanged();

    void gitMessagesChanged();

    void commitsBehindChanged();

    void updatingChanged();
    void updatingFinished();

    void stateMessageChanged();

private:
    bool m_debugEnabled = false;
    bool m_isValid = false;
    bool m_isDirty = false;
    bool m_corrupt = false;
    bool m_detached = false;
    bool m_pristine = false;
    bool m_updating = false;

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

    Q_PROPERTY(bool debugEnabled READ debugEnabled WRITE setDebugEnabled NOTIFY debugEnabledChanged FINAL)
    Q_PROPERTY(bool isValid READ isValid WRITE setIsValid NOTIFY isValidChanged FINAL)
    Q_PROPERTY(bool isDirty READ isDirty WRITE setIsDirty NOTIFY isDirtyChanged FINAL)
    Q_PROPERTY(bool corrupt READ corrupt WRITE setCorrupt NOTIFY corruptChanged FINAL)
    Q_PROPERTY(bool detached READ detached WRITE setDetached NOTIFY detachedChanged FINAL)
    Q_PROPERTY(bool pristine READ pristine WRITE setPristine NOTIFY pristineChanged FINAL)
    Q_PROPERTY(QString channel READ channel WRITE setChannel NOTIFY channelChanged FINAL)
    Q_PROPERTY(QString configuredType READ configuredType WRITE setConfiguredType NOTIFY configuredTypeChanged FINAL)
    Q_PROPERTY(QString detectedType READ detectedType WRITE setDetectedType NOTIFY detectedTypeChanged FINAL)
    Q_PROPERTY(QString remoteAlias READ remoteAlias WRITE setRemoteAlias NOTIFY remoteAliasChanged FINAL)
    Q_PROPERTY(QString branch READ branch WRITE setBranch NOTIFY branchChanged FINAL)
    Q_PROPERTY(QString owner READ owner WRITE setOwner NOTIFY ownerChanged FINAL)
    Q_PROPERTY(QString repoName READ repoName WRITE setRepoName NOTIFY repoNameChanged FINAL)
    Q_PROPERTY(QString version READ version WRITE setVersion NOTIFY versionChanged FINAL)
    Q_PROPERTY(QString rollbackVersion READ rollbackVersion WRITE setRollbackVersion NOTIFY rollbackVersionChanged FINAL)
    Q_PROPERTY(QString remoteVersion READ remoteVersion WRITE setRemoteVersion NOTIFY remoteVersionChanged FINAL)
    Q_PROPERTY(QString currentHash READ currentHash WRITE setCurrentHash NOTIFY currentHashChanged FINAL)
    Q_PROPERTY(QString remoteHash READ remoteHash WRITE setRemoteHash NOTIFY remoteHashChanged FINAL)
    Q_PROPERTY(QString fullVersionString READ fullVersionString WRITE setFullVersionString NOTIFY fullVersionStringChanged FINAL)
    Q_PROPERTY(QString recoveryUrl READ recoveryUrl WRITE setRecoveryUrl NOTIFY recoveryUrlChanged FINAL)
    Q_PROPERTY(QString remoteUrl READ remoteUrl WRITE setRemoteUrl NOTIFY remoteUrlChanged FINAL)
    Q_PROPERTY(QStringList warnings READ warnings WRITE setWarnings NOTIFY warningsChanged FINAL)
    Q_PROPERTY(QStringList anomalies READ anomalies WRITE setAnomalies NOTIFY anomaliesChanged FINAL)
    Q_PROPERTY(QStringList infoTags READ infoTags WRITE setInfoTags NOTIFY infoTagsChanged FINAL)
    Q_PROPERTY(QStringList gitMessages READ gitMessages WRITE setGitMessages NOTIFY gitMessagesChanged FINAL)
    Q_PROPERTY(QList<QKlipperUpdateCommit> commitsBehind READ commitsBehind WRITE setCommitsBehind NOTIFY commitsBehindChanged FINAL)
    Q_PROPERTY(bool updating READ updating WRITE setUpdating NOTIFY updatingChanged FINAL)
    Q_PROPERTY(QString stateMessage READ stateMessage WRITE setStateMessage NOTIFY stateMessageChanged FINAL)
};

#endif // QKLIPPERUPDATEPACKAGE_H
