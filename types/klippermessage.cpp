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
    document += this->endOfFile.toUtf8() + QByteArray("\n");

    return document;
}


QJsonObject KlipperMessage::document() const
{
    return this->rootObject;
}

void KlipperMessage::setDocument(QJsonObject object)
{
    object["jsonrpc"] = "2.0";
    object["id"] = this->id;
    this->rootObject = object;
}

KlipperResponse KlipperMessage::response() const
{
    return m_response;
}

void KlipperMessage::startTimer()
{
    if(!m_responseTimer)
    {
        m_responseTimer = new QTimer(this);
        m_responseTimer->setInterval(timeout);
        m_responseTimer->setSingleShot(true);
    }

    if(!m_responseTimer->isActive())
        m_responseTimer->start();
    else
    {
        m_responseTimer->stop();
        m_responseTimer->start();
    }
}

void KlipperMessage::stopTimer()
{
    if(m_responseTimer && m_responseTimer->isActive())
        m_responseTimer->stop();
}

void KlipperMessage::setResponse(const KlipperResponse &response)
{
    m_response = response;
    stopTimer();
}

void KlipperMessage::responseTimerTimeout()
{
    emit responseTimeout(document()["id"].toInt());
}
