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
    virtual void sendCommand(QString command, KlipperMessage::MessageOrigin origin) override;
    virtual void sendCommand(KlipperMessage message) override;
    virtual void setMoonrakerLocation(QString location) override;
    virtual void connectToMoonraker() override;
    virtual void disconnectKlipper() override;
    virtual void deleteFile(QString file) override;
    virtual void deleteFile(KlipperFile file) override;
    virtual void moveFile(QString source, QString destination) override;
    virtual void copyFile(QString source, QString destination) override;
    virtual QString downloadFile(KlipperFile file) override;
    virtual bool uploadFile(QString root, QString directory, QString name, QByteArray data) override;
    virtual void getFileList(QString directory) override;
    virtual void createDirectory(QString directory) override;
    virtual void deleteDirectory(QString directory) override;
    virtual void startPrint(QString file) override;
    virtual void pausePrint() override;
    virtual void resumePrint() override;
    virtual void cancelPrint() override;
    virtual void machineShutdown() override;
    virtual void machineReboot() override;
    virtual void serviceRestart(QString service) override;
    virtual void serviceStop(QString service) override;
    virtual void serviceStart(QString service) override;
    virtual void sendGcode(QString gcode) override;
    virtual void printerInfo() override;
    virtual void restartKlipper() override;
    virtual void restartFirmware() override;
    virtual void printerSubscribe() override;
    virtual void serverInfo() override;
    virtual void serverConfig() override;
    virtual void serverFileRoots() override;
    virtual void clientIdentifier() override;
    virtual ConnectionLocation connectionLoaction() const override;
    virtual void setConnectionLoaction(ConnectionLocation connectionLoaction) override;
};

#endif // QLOCALKLIPPERCONSOLE_H
