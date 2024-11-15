#ifndef FLO_H
#define FLO_H

#include <QObject>
#include <QUuid>
#include <QtConcurrent/QtConcurrent>

#include "qklipperinstancepool.h"

#include "settings.h"


class Flo : public QObject
{
    Q_OBJECT
    explicit Flo(QObject *parent = nullptr);
public:

    static QString generatId();
    static Flo *instance();
    void start();

    static QKlipperInstancePool *printerPool();
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
    static QKlipperInstancePool *m_printerPool;
    static Settings *m_settings;

    static Flo *m_instance;
};

#endif // FLO_H
