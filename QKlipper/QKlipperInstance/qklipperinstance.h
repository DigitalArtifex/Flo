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

#ifndef QKLIPPERINSTANCE_H
#define QKLIPPERINSTANCE_H

#include <QObject>
#include <QImage>

#include <QQueue>
#include <QByteArray>
#include <QFunctionPointer>
#include <QAbstractSocket>
#include <QLocalSocket>
#include <QTcpSocket>
#include <QSslSocket>

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>

#include "../QKlipperConsole/qklipperconsole.h"
#include "../QKlipperPrinter/qklipperprinter.h"
#include "../QKlipperServer/qklipperserver.h"
#include "../QKlipperSystem/qklippersystem.h"

class QKlipperInstance : public QObject
{
    Q_OBJECT
public:

    explicit QKlipperInstance(QObject *parent = nullptr);
    ~QKlipperInstance();

    QString name() const;

    QString address() const;

    QString id() const;

    QString apiKey() const;

    qint16 port() const;

    QKlipperConsole *console() const;

    QKlipperServer *server() const;

    QKlipperSystem *system() const;

    QKlipperPrinter *printer() const;

    QString instanceLocation() const;

    QKlipperServer::ConnectionType connectionType() const;

    Q_INVOKABLE void connect();
    Q_INVOKABLE void disconnect();
    Q_INVOKABLE void reset();

    QString profileColor() const;

    bool isConnected() const;

    bool autoConnect() const;

    QImage thumbnail() const;

    bool hasUpdate() const;

public slots:
    void setName(const QString &name);
    void setAddress(const QString &address);
    void setId(const QString &id);
    void setApiKey(const QString &apiKey);
    void setPort(qint16 port);

    void setInstanceLocation(const QString &instanceLocation);
    void printerStateChanged();

    void setConnectionType(QKlipperServer::ConnectionType connectionType);

    void setConsole(QKlipperConsole *console);

    void setProfileColor(const QString &profileColor);

    void setAutoConnect(bool autoConnect);

    void setThumbnail(const QImage &thumbnail);

    void setHasUpdate(bool hasUpdate);

signals:

    void nameChanged();

    void addressChanged();

    void idChanged();

    void apiKeyChanged();

    void portChanged();

    void instanceLocationChanged();

    void connectionTypeChanged();

    void consoleChanged();

    void profileColorChanged();

    void connected(QKlipperInstance*);
    void disconnected(QKlipperInstance*);

    void isConnectedChanged();

    void printJobAdded(QKlipperInstance*, QKlipperPrintJob*);
    void printJobRemoved(QKlipperInstance*, QKlipperPrintJob*);

    void error(QKlipperInstance*, QKlipperError&);

    void autoConnectChanged();

    void thumbnailChanged();

    void hasUpdateChanged();

protected slots:
    void setIsConnected(bool isConnected);
    void onConsoleConnectionStateChanged();
    void onServerPrintJobAdded(QKlipperPrintJob *job);
    void onServerPrintJobRemoved(QKlipperPrintJob *job);
    void onConsoleError(QKlipperError &error);

private:
    QImage m_thumbnail;

    QKlipperConsole *m_console = nullptr;
    QKlipperServer *m_server = nullptr;
    QKlipperSystem *m_system = nullptr;
    QKlipperPrinter *m_printer = nullptr;

    QString m_name;
    QString m_address;
    QString m_id;
    QString m_apiKey;
    QString m_instanceLocation;
    QString m_profileColor;

    qint16 m_port;

    QKlipperServer::ConnectionType m_connectionType = QKlipperServer::None;

    QMap<QString,QKlipperError> m_errors;

    bool m_isConnected = false;
    bool m_hasError = false;
    bool m_autoConnect = false;
    bool m_hasUpdate = false;

    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged FINAL)
    Q_PROPERTY(QString address READ address WRITE setAddress NOTIFY addressChanged FINAL)
    Q_PROPERTY(QString id READ id WRITE setId NOTIFY idChanged FINAL)
    Q_PROPERTY(QString apiKey READ apiKey WRITE setApiKey NOTIFY apiKeyChanged FINAL)
    Q_PROPERTY(qint16 port READ port WRITE setPort NOTIFY portChanged FINAL)
    Q_PROPERTY(QString instanceLocation READ instanceLocation WRITE setInstanceLocation NOTIFY instanceLocationChanged FINAL)
    Q_PROPERTY(QKlipperServer::ConnectionType connectionType READ connectionType WRITE setConnectionType NOTIFY connectionTypeChanged FINAL)
    Q_PROPERTY(QKlipperConsole *console READ console WRITE setConsole NOTIFY consoleChanged FINAL)
    Q_PROPERTY(QString profileColor READ profileColor WRITE setProfileColor NOTIFY profileColorChanged FINAL)
    Q_PROPERTY(bool isConnected READ isConnected WRITE setIsConnected NOTIFY isConnectedChanged FINAL)
    Q_PROPERTY(bool autoConnect READ autoConnect WRITE setAutoConnect NOTIFY autoConnectChanged FINAL)
    Q_PROPERTY(QImage thumbnail READ thumbnail WRITE setThumbnail NOTIFY thumbnailChanged FINAL)
    Q_PROPERTY(bool hasUpdate READ hasUpdate WRITE setHasUpdate NOTIFY hasUpdateChanged FINAL)
};

#endif // QKLIPPERINSTANCE_H
