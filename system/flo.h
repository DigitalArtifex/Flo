#ifndef FLO_H
#define FLO_H

#include <QObject>
#include <QUuid>
#include <QtConcurrent/QtConcurrent>

#include "printerpool.h"
#include "settings.h"


class Flo : public QObject
{
    Q_OBJECT
    explicit Flo(QObject *parent = nullptr);
public:

    static QString generatId();
    static Flo *instance();
    void start(QObject *parent);

    static PrinterPool *printerPool();
    static Settings *settings();

signals:
    void loading();
    void loadingProgress(QString message, qreal progress);
    void loadingFinished();

private:
    void on_loading();
    void on_loadingProgress(QString message, qreal progress);
    void on_loadingFinished();

private:
    static PrinterPool *m_printerPool;
    static Settings *m_settings;

    static Flo *m_instance;
};

#endif // FLO_H
