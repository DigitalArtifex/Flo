#ifndef QKLIPPERREMOTECONSOLE_H
#define QKLIPPERREMOTECONSOLE_H

#include <QObject>

#include "qabstractklipperconsole.h"

class QKlipperRemoteConsole : public QAbstractKlipperConsole
{
    Q_OBJECT
public:
    explicit QKlipperRemoteConsole(Printer *printer, QObject *parent = nullptr);

public:
    virtual void shutdown() override;
    virtual void sendCommand(QString command, KlipperMessage::MessageOrigin origin = KlipperMessage::System, bool forced = false) override;
    virtual void sendCommand(KlipperMessage *message, bool immediate = false) override;
    virtual void connectToMoonraker() override;
    virtual void disconnectKlipper() override;
    virtual QString downloadFile(KlipperFile file) override;
    virtual bool uploadFile(QString root, QString directory, QString name, QByteArray data) override;

protected slots:
    virtual void responseReceivedEvent() override;

signals:
};

#endif // QKLIPPERREMOTECONSOLE_H
