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

#ifndef QKLIPPERSERVER_H
#define QKLIPPERSERVER_H

#include <QObject>

#include "../QKlipperFile/qklipperfile.h"
#include "qklipperclientidentifier.h"
#include "qklippergcodestore.h"
#include "qklipperaccessdetails.h"
#include "qklipperannouncement.h"
#include "qklipperjobqueue.h"
#include "qklipperuser.h"
#include "qklippergcodemacro.h"

class QKlipperConsole;

class QKlipperServer : public QObject
{
    Q_OBJECT
    friend QKlipperConsole;
public:

    enum ConnectionType
    {
        None = 0,
        Local = 1,
        Remote = 2
    };

    explicit QKlipperServer(QObject *parent = nullptr);
    ~QKlipperServer();

    QString moonrakerLocation() const;

    QString klipperLocation() const;

    QString gcodesLocation() const;

    QString configLocation() const;

    QString instanceLocation() const;

    QString apiKey() const;

    QKlipperGCodeStore *gcodeStore() const;

    QString address() const;
    QString websocketAddress() const;
    QString bridgeAddress() const;

    ConnectionType connectionType() const;

    QList<QKlipperUser> userList() const;

    QKlipperAccessDetails accessDetails() const;

    QString websocketId() const;

    QString connectionId() const;

    QStringList availableObjects() const;

    QStringList gcodeMacroObjects() const;

    QKlipperGCodeMacroList gcodeMacros() const;

    QStringList warnings() const;

    QStringList components() const;

    QStringList failedComponents() const;

    QKlipperAnnouncementList announcements() const;

    QKlipperJobQueue *jobQueue() const;

    QMap<QString, QKlipperFile *> fileSystem() const;
    QKlipperFileList fileList(const QString &directory) const;
    QKlipperFile *file(QString uri);

    QKlipperClientIdentifier clientIdentifier() const;

    qint16 port() const;

public slots:

    void setMoonrakerLocation(const QString &moonrakerLocation);
    void resetMoonrakerLocation();

    void setKlipperLocation(const QString &klipperLocation);
    void resetKlipperLocation();

    void setGcodesLocation(const QString &gcodesLocation);
    void resetGcodesLocation();

    void setConfigLocation(const QString &configLocation);
    void resetConfigLocation();

    void setInstanceLocation(const QString &instanceLocation);
    void resetInstanceLocation();

    void setApiKey(const QString &apiKey);
    void resetApiKey();

    void setAddress(const QString &address);
    void resetAddress();

    void setGcodeStore(QKlipperGCodeStore *gcodeStore);
    void setGcodeStoreValue(const QKlipperGCodeStoreValue &value);
    void resetGcodeStore();

    void setConnectionType(ConnectionType connectionType);
    void resetConnectionType();

    void setUserList(const QList<QKlipperUser> &userList);

    void setAccessDetails(QKlipperAccessDetails &accessDetails);

    void setWebsocketId(const QString &websocketId);

    void setConnectionId(const QString &connectionId);

    void setAvailableObjects(const QStringList &availableObjects);

    void setGcodeMacroObjects(const QStringList &gcodeMacroObjects);

    void setGcodeMacros(const QKlipperGCodeMacroList &gcodeMacros);
    void setGcodeMacro(const QKlipperGCodeMacro &gcodeMacro);

    void setWarnings(const QStringList &warnings);
    void setWarning(const QString &warning);

    void setComponents(const QStringList &components);

    void setFailedComponents(const QStringList &failedComponents);

    void setFile(QKlipperFile *file);
    void setFileMetadata(QString uri, const QKlipperMetadata &metadata);

    void setAnnouncements(const QKlipperAnnouncementList &announcements);

    void setJobQueue(QKlipperJobQueue *jobQueue);

    void setFileSystem(const QMap<QString, QKlipperFile *> &fileSystem);
    void setFileList(const QString &directory, QKlipperFileList files);

    void setClientIdentifier(const QKlipperClientIdentifier &clientIdentifier);

    void setPort(qint16 port);

signals:

    void moonrakerLocationChanged();

    void klipperLocationChanged();

    void gcodesLocationChanged();

    void configLocationChanged();

    void instanceLocationChanged();

    void apiKeyChanged();

    void addressChanged();

    void gcodeStoreChanged();

    void connectionTypeChanged();

    void userListChanged();

    void accessDetailsChanged();

    void websocketIdChanged();

    void connectionIdChanged();

    void availableObjectsChanged();

    void gcodeMacroObjectsChanged();

    void gcodeMacrosChanged();

    void warningsChanged();

    void componentsChanged();

    void failedComponentsChanged();

    void announcementsChanged();

    void jobQueueChanged();

    void fileSystemChanged();

    void fileListChanged(QString);

    void clientIdentifierChanged();

    void portChanged();

    void stateChanged();

private:
    QKlipperClientIdentifier                         m_clientIdentifier;

    ConnectionType                                    m_connectionType;

    QString                                           m_moonrakerLocation;
    QString                                           m_klipperLocation;
    QString                                           m_gcodesLocation;
    QString                                           m_configLocation;
    QString                                           m_instanceLocation;
    QString                                           m_apiKey;
    QString                                           m_address;
    QString                                           m_connectionId;
    QString                                           m_websocketId;

    QKlipperGCodeStore                               *m_gcodeStore = nullptr;

    QKlipperAccessDetails                             m_accessDetails;
    QList<QKlipperUser>                               m_userList;

    QKlipperJobQueue                                 *m_jobQueue = nullptr;

    QKlipperAnnouncementList                          m_announcements;

    QStringList                                       m_availableObjects;
    QStringList                                       m_gcodeMacroObjects;
    QStringList                                       m_warnings;
    QStringList                                       m_components;
    QStringList                                       m_failedComponents;
    QKlipperGCodeMacroList                            m_gcodeMacros;

    QMap<QString, QKlipperFile*>                      m_fileSystem;

    qint16                                            m_port = 0;

    Q_PROPERTY(QString moonrakerLocation READ moonrakerLocation WRITE setMoonrakerLocation RESET resetMoonrakerLocation NOTIFY moonrakerLocationChanged FINAL)
    Q_PROPERTY(QString klipperLocation READ klipperLocation WRITE setKlipperLocation RESET resetKlipperLocation NOTIFY klipperLocationChanged FINAL)
    Q_PROPERTY(QString gcodesLocation READ gcodesLocation WRITE setGcodesLocation RESET resetGcodesLocation NOTIFY gcodesLocationChanged FINAL)
    Q_PROPERTY(QString configLocation READ configLocation WRITE setConfigLocation RESET resetConfigLocation NOTIFY configLocationChanged FINAL)
    Q_PROPERTY(QString instanceLocation READ instanceLocation WRITE setInstanceLocation RESET resetInstanceLocation NOTIFY instanceLocationChanged FINAL)
    Q_PROPERTY(QString apiKey READ apiKey WRITE setApiKey RESET resetApiKey NOTIFY apiKeyChanged FINAL)
    Q_PROPERTY(QString address READ address WRITE setAddress RESET resetAddress NOTIFY addressChanged FINAL)
    Q_PROPERTY(QKlipperGCodeStore *gcodeStore READ gcodeStore WRITE setGcodeStore RESET resetGcodeStore NOTIFY gcodeStoreChanged FINAL)
    Q_PROPERTY(ConnectionType connectionType READ connectionType WRITE setConnectionType RESET resetConnectionType NOTIFY connectionTypeChanged FINAL)
    Q_PROPERTY(QList<QKlipperUser> userList READ userList WRITE setUserList NOTIFY userListChanged FINAL)
    Q_PROPERTY(QKlipperAccessDetails accessDetails READ accessDetails WRITE setAccessDetails NOTIFY accessDetailsChanged FINAL)
    Q_PROPERTY(QString websocketId READ websocketId WRITE setWebsocketId NOTIFY websocketIdChanged FINAL)
    Q_PROPERTY(QString connectionId READ connectionId WRITE setConnectionId NOTIFY connectionIdChanged FINAL)
    Q_PROPERTY(QStringList availableObjects READ availableObjects WRITE setAvailableObjects NOTIFY availableObjectsChanged FINAL)
    Q_PROPERTY(QStringList gcodeMacroObjects READ gcodeMacroObjects WRITE setGcodeMacroObjects NOTIFY gcodeMacroObjectsChanged FINAL)
    Q_PROPERTY(QKlipperGCodeMacroList gcodeMacros READ gcodeMacros WRITE setGcodeMacros NOTIFY gcodeMacrosChanged FINAL)
    Q_PROPERTY(QStringList warnings READ warnings WRITE setWarnings NOTIFY warningsChanged FINAL)
    Q_PROPERTY(QStringList components READ components WRITE setComponents NOTIFY componentsChanged FINAL)
    Q_PROPERTY(QStringList failedComponents READ failedComponents WRITE setFailedComponents NOTIFY failedComponentsChanged FINAL)
    Q_PROPERTY(QKlipperAnnouncementList announcements READ announcements WRITE setAnnouncements NOTIFY announcementsChanged FINAL)
    Q_PROPERTY(QKlipperJobQueue *jobQueue READ jobQueue WRITE setJobQueue NOTIFY jobQueueChanged FINAL)
    Q_PROPERTY(QMap<QString, QKlipperFile *> fileSystem READ fileSystem WRITE setFileSystem NOTIFY fileSystemChanged FINAL)
    Q_PROPERTY(QKlipperClientIdentifier clientIdentifier READ clientIdentifier WRITE setClientIdentifier NOTIFY clientIdentifierChanged FINAL)
    Q_PROPERTY(qint16 port READ port WRITE setPort NOTIFY portChanged FINAL)
};

#endif // QKLIPPERSERVER_H
