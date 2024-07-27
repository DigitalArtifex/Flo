#ifndef QKLIPPERINSTANCE_H
#define QKLIPPERINSTANCE_H

#include <QObject>

class QKlipperInstance : public QObject
{
    Q_OBJECT
public:
    explicit QKlipperInstance(QObject *parent = nullptr);

signals:
};

#endif // QKLIPPERINSTANCE_H
