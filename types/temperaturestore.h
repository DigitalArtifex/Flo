#ifndef TEMPERATURESTORE_H
#define TEMPERATURESTORE_H

#include <QObject>

class TemperatureStoreValue
{
    Q_GADGET
public:
    qreal temperature = 0;
    qreal power = 0;
    qreal target = 0;
    qreal speed = 0;
};

typedef QList<TemperatureStoreValue> TemperatureStore;

#endif // TEMPERATURESTORE_H
