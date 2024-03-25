#ifndef FLO_H
#define FLO_H

#include <QObject>
#include <QUuid>

#include "printerpool.h"
#include "settings.h"


class Flo : public QObject
{
    Q_OBJECT
    explicit Flo(QObject *parent = nullptr);
public:

    static QString generatId();

signals:

private:
    static PrinterPool *_printerPool;
    static Settings *_settings;
};

#endif // FLO_H
