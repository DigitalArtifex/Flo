#ifndef KLIPPERRESPONSE_H
#define KLIPPERRESPONSE_H

#include <QObject>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDateTime>

class KlipperResponse
{

public:
    QJsonObject rootObject;

    KlipperResponse();
    ~KlipperResponse();

    enum StatusType {
        OK,
        FAIL
    };

    enum ResponseOrigin
    {
        System,
        Console,
        User
    };

    ResponseOrigin origin = System;

    StatusType status = StatusType::FAIL;
    bool isOkay() { return (status == StatusType::OK); }

    QDateTime timestamp;

    int timeout = 3000; //in ms

    QJsonObject document();
    void setDocument(QJsonObject document);

    QJsonValueRef operator[](QString key) {
        return this->rootObject[key];
    }
};

#endif // KLIPPERRESPONSE_H
