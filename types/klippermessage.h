#ifndef KLIPPERMESSAGE_H
#define KLIPPERMESSAGE_H

#include <QObject>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDateTime>
#include <QTimer>

#include "klipperresponse.h"

class KlipperMessage : public QObject
{
    Q_OBJECT
    static int currentID;
    static int getID();

public:

    enum MessageOrigin
    {
        System,
        Console,
        User
    };

    KlipperMessage(bool commandLock = false, QDateTime timestamp = QDateTime::currentDateTime());
    ~KlipperMessage();

    QDateTime timestamp;
    bool commandLock = false;

    MessageOrigin origin = System;

    QString endOfFile = QString((char)0x03); //Moonraker API end of file
    qreal rpcVersion = 2.0;
    int id = 0;

    QByteArray toRpc(QJsonDocument::JsonFormat format = QJsonDocument::Compact);
    QString toUri(bool parameterEncoded = true);

    int timeout = 3000; //in ms

    QJsonObject document() const;
    void setDocument(QJsonObject object);

    QJsonValueRef operator[](QString key) {
        return this->rootObject[key];
    }

    KlipperResponse response() const;

    void startTimer();
    void stopTimer();

signals:
    void responseTimeout(int id);

public slots:
    void setResponse(const KlipperResponse &response);

protected slots:
    void responseTimerTimeout();

private:
    QJsonObject rootObject;
    QTimer *m_responseTimer = nullptr;
    KlipperResponse m_response;
};

#endif // KLIPPERMESSAGE_H
