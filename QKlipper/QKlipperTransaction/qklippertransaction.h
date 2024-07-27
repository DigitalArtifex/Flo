#ifndef QKLIPPERTRANSACTION_H
#define QKLIPPERTRANSACTION_H

#include <QObject>

class QKlipperTransaction : public QObject
{
    Q_OBJECT
public:
    explicit QKlipperTransaction(QObject *parent = nullptr);

signals:
};

#endif // QKLIPPERTRANSACTION_H
