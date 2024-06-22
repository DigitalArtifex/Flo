#include "clientidentifier.h"

qint64 ClientIdentifier::websocketId() const
{
    return m_websocketId;
}

void ClientIdentifier::setWebsocketId(qint64 websocketId)
{
    m_websocketId = websocketId;
}

qint64 ClientIdentifier::connectionId() const
{
    return m_connectionId;
}

void ClientIdentifier::setConnectionId(qint64 connectionId)
{
    m_connectionId = connectionId;
}
