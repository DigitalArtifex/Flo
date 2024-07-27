#ifndef QKLIPPERMESSAGE_H
#define QKLIPPERMESSAGE_H

#include <QObject>

class QKlipperMessage : public QObject
{
    Q_OBJECT
public:
    explicit QKlipperMessage(QObject *parent = nullptr);

signals:
};

#endif // QKLIPPERMESSAGE_H
