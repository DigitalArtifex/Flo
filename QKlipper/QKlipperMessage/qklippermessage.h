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

#ifndef QKLIPPERMESSAGE_H
#define QKLIPPERMESSAGE_H

#include <QObject>
#include <QMap>
#include <QVariant>
#include <QTimer>

#include <QUrl>

#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonValue>

#include <QKlipper/qklippererror.h>

#define QKLIPPER_RPC_EOF (char)0x03;

class QKlipperMessage : public QObject
{
    Q_OBJECT
public:
    enum Protocol
    {
        RpcProtocol = 1,
        HttpProtocol = 2,
        HttpPostProtocol = 3,
        HttpDeleteProtocol = 4
    };

    enum State
    {
        None = 0,
        Sending = 1,
        Complete = 2,
        Error = 3,
        Timeout = 4
    };

    enum Origin
    {
        System = 1,
        User = 2
    };

    explicit QKlipperMessage(QObject *parent = nullptr);
    ~QKlipperMessage();

    qint32 id() const;

    Protocol protocol() const;

    QMap<QString, QVariant> params() const;
    QVariant param(QString key) const;

    QString method() const;

    QString toUri(bool parameterEncoded = true) const;
    QByteArray toRpc() const;

    State state() const;

    QJsonValue response() const;

    Origin origin() const;

    QDateTime timestamp() const;

    QDateTime responseTimestamp() const;

    QKlipperError error() const;

    QJsonValue bodyData() const;

public slots:

    void setId(qint32 id);
    void resetId();

    void setProtocol(Protocol protocol);
    void resetProtocol();

    void setParams(const QMap<QString, QVariant> &params);
    void setParam(QString key, QVariant value);
    void resetParams();

    void setMethod(const QString &method);
    void resetMethod();

    void setState(State state);
    void resetState();

    void setResponse(const QJsonValue &response);
    void setResponse(const QByteArray &response);
    void resetResponse();

    void startTimer();

    void setOrigin(Origin origin);
    void resetOrigin();

    void setTimestamp(const QDateTime &timestamp);

    void setResponseTimestamp(const QDateTime &responseTimestamp);

    void setError(const QKlipperError &error);

    void setBodyData(const QJsonValue &bodyData);

protected slots:
    void on_responseTimerTimeout();

signals:
    void protocolChanged();
    void methodChanged();
    void paramsChanged();
    void idChanged();
    void stateChanged();
    void responseChanged();
    void responseTimeout();

    void originChanged();

    void timestampChanged();

    void responseTimestampChanged();

    void errorChanged();

    void bodyDataChanged();

private:
    static qint32 s_currentId;

    Protocol m_protocol = HttpProtocol;
    State m_state = None;
    Origin m_origin = System;

    QTimer *m_responseTimer = nullptr;

    qint32 m_id = 0;

    QString m_method;

    QMap<QString,QVariant> m_params;

    QJsonValue m_bodyData;
    QJsonValue m_response;
    QDateTime m_timestamp;
    QDateTime m_responseTimestamp;

    QKlipperError m_error;

    Q_PROPERTY(qint32 id READ id WRITE setId RESET resetId NOTIFY idChanged FINAL)
    Q_PROPERTY(Protocol protocol READ protocol WRITE setProtocol RESET resetProtocol NOTIFY protocolChanged FINAL)
    Q_PROPERTY(QMap<QString, QVariant> params READ params WRITE setParams RESET resetParams NOTIFY paramsChanged FINAL)
    Q_PROPERTY(QString method READ method WRITE setMethod RESET resetMethod NOTIFY methodChanged FINAL)
    Q_PROPERTY(State state READ state WRITE setState RESET resetState NOTIFY stateChanged FINAL)
    Q_PROPERTY(QJsonValue response READ response WRITE setResponse RESET resetResponse NOTIFY responseChanged FINAL)
    Q_PROPERTY(Origin origin READ origin WRITE setOrigin RESET resetOrigin NOTIFY originChanged FINAL)
    Q_PROPERTY(QDateTime timestamp READ timestamp WRITE setTimestamp NOTIFY timestampChanged FINAL)
    Q_PROPERTY(QDateTime responseTimestamp READ responseTimestamp WRITE setResponseTimestamp NOTIFY responseTimestampChanged FINAL)
    Q_PROPERTY(QKlipperError error READ error WRITE setError NOTIFY errorChanged FINAL)
    Q_PROPERTY(QJsonValue bodyData READ bodyData WRITE setBodyData NOTIFY bodyDataChanged FINAL)
};

#endif // QKLIPPERMESSAGE_H
