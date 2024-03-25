#include "flo.h"

Flo::Flo(QObject *parent)
    : QObject{parent}
{

}

QString Flo::generatId()
{
    return QUuid::createUuid().toString();
}
