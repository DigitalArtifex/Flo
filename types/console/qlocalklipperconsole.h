#ifndef QLOCALKLIPPERCONSOLE_H
#define QLOCALKLIPPERCONSOLE_H

#include <QObject>
#include <QTimer>
#include <QLocalSocket>

#include "qabstractklipperconsole.h"

class QLocalKlipperConsole : public QAbstractKlipperConsole
{
    Q_OBJECT
public:
    QLocalKlipperConsole(Printer *printer, QObject *parent = nullptr);
    ~QLocalKlipperConsole();

    // QKlipperConsole interface
public:
    virtual void shutdown() override;
    virtual void sendCommand(QString command, KlipperMessage::MessageOrigin origin = KlipperMessage::System, bool forced = false) override;
    virtual void sendCommand(KlipperMessage message, bool immediate = false) override;
    virtual void connectToMoonraker() override;
    virtual void disconnectKlipper() override;
    virtual QString downloadFile(KlipperFile file) override;
    virtual bool uploadFile(QString root, QString directory, QString name, QByteArray data) override;

protected slots:
    virtual void responseReceivedEvent() override;

private:

};

#endif // QLOCALKLIPPERCONSOLE_H
