#ifndef KLIPPERMESSAGE_H
#define KLIPPERMESSAGE_H

#include <QObject>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDateTime>

class KlipperMessage
{

    QJsonObject rootObject;

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

    int timeout = 3000; //in ms

    QJsonObject document();
    void setDocument(QJsonObject object);

    QJsonValueRef operator[](QString key) {
        return this->rootObject[key];
    }
};

#endif // KLIPPERMESSAGE_H
