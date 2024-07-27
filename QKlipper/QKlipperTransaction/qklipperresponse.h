#ifndef QKLIPPERRESPONSE_H
#define QKLIPPERRESPONSE_H

#include <QObject>

class QKlipperResponse : public QObject
{
    Q_OBJECT
public:
    explicit QKlipperResponse(QObject *parent = nullptr);

signals:
};

#endif // QKLIPPERRESPONSE_H
