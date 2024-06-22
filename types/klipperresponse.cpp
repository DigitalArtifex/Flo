#include "klipperresponse.h"

KlipperResponse::KlipperResponse()
{

}

KlipperResponse::~KlipperResponse()
{

}

QJsonObject KlipperResponse::document()
{
    return this->rootObject;
}

void KlipperResponse::setDocument(QJsonObject document)
{
    this->rootObject = document;
}

qint64 KlipperResponse::id() const
{
    return m_id;
}

void KlipperResponse::setId(qint64 id)
{
    m_id = id;
}
