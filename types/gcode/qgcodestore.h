#ifndef QGCODESTORE_H
#define QGCODESTORE_H

#include <QObject>

class GCodeStoreValue
{
    Q_GADGET
public:
    enum GCodeType {
        Command,
        Response
    };

    QString message;
    GCodeType type = Response;
    qreal time;
};

typedef QList<GCodeStoreValue> GCodeStore;

#endif // QGCODESTORE_H
