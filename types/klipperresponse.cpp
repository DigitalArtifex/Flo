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
