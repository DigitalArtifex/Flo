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

QString KlipperMessage::toUri()
{
    QString method = rootObject["method"].toString();

    //change the few that don't conform to a direct conversion
    if(method == "server.files.get_directory")
        method = "server.files.directory";

    method.replace('.', '/');

    QJsonObject paramsObject = rootObject["params"].toObject();
    QStringList paramKeys = paramsObject.keys();
    QString params;

    foreach(QString key, paramKeys)
    {
        switch(paramsObject[key].type())
        {
            case QJsonValue::Null:
            params += QString("&%1").arg(key);
                break;
            case QJsonValue::Bool:
                if(paramsObject[key].toBool())
                    params += QString("&%1=%2").arg(key).arg("true");
                else
                    params += QString("&%1=%2").arg(key).arg("false");
                break;
            case QJsonValue::Double:
                params += QString("&%1=%2").arg(key).arg(paramsObject[key].toDouble());
                break;
            case QJsonValue::String:
                params += QString("&%1=%2").arg(key).arg(paramsObject[key].toString());
                break;
            case QJsonValue::Array:
            case QJsonValue::Object:
            case QJsonValue::Undefined:
                break;
        }
    }

    if(params.startsWith('&'))
    {
        params.removeAt(0);
        params.insert(0, '?');
    }

    QString uri = QString("/%1%2").arg(method).arg(params);

    return uri;
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
