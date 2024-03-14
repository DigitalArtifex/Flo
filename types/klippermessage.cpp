#include "klippermessage.h"

int KlipperMessage::currentID = 0;

int KlipperMessage::getID()
{
    return ++currentID;
}

KlipperMessage::KlipperMessage(bool commandLock, QDateTime timestamp)
{
    this->commandLock = commandLock;
    this->timestamp = timestamp;
    this->id = KlipperMessage::getID();

    rootObject["jsonrpc"] = "2.0";
    rootObject["id"] = this->id;
}

KlipperMessage::~KlipperMessage()
{

}

QByteArray KlipperMessage::toRpc(QJsonDocument::JsonFormat format)
{
    QByteArray document = QJsonDocument(rootObject).toJson(format);
    document += this->endOfFile.toUtf8();

    return document;
}


QJsonObject KlipperMessage::document()
{
    return this->rootObject;
}

void KlipperMessage::setDocument(QJsonObject object)
{
    object["jsonrpc"] = "2.0";
    object["id"] = this->id;
    this->rootObject = object;
}
