#include "clientidentifier.h"

qint64 ClientIdentifier::websocketId() const
{
    return _websocketId;
}

void ClientIdentifier::setWebsocketId(qint64 websocketId)
{
    _websocketId = websocketId;
}

qint64 ClientIdentifier::connectionId() const
{
    return _connectionId;
}

void ClientIdentifier::setConnectionId(qint64 connectionId)
{
    _connectionId = connectionId;
}
