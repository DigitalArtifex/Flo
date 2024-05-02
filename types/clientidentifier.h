#ifndef CLIENTIDENTIFIER_H
#define CLIENTIDENTIFIER_H

#include <QObject>

class ClientIdentifier
{
    Q_GADGET
public:

    qint64 websocketId() const;
    void setWebsocketId(qint64 websocketId);

    qint64 connectionId() const;
    void setConnectionId(qint64 connectionId);

private:
    qint64 _websocketId = 0;
    qint64 _connectionId = 0;
};

#endif // CLIENTIDENTIFIER_H
