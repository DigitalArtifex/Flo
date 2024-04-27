/**!
 *
 */

#ifndef QKLIPPERCONSOLE_H
#define QKLIPPERCONSOLE_H

#include <QObject>

#include "printer.h"

#include "klippermessage.h"
#include "klipperresponse.h"

class QKlipperConsole : public QObject
{
    Q_OBJECT
public:
    enum ConnectionLocation
    {
        LocationLocal,
        LocationRemote
    };

    explicit QKlipperConsole(Printer *printer, QObject *parent = nullptr);
    ~QKlipperConsole();

    virtual void sendCommand(QString command) = 0;

    virtual void shutdown() = 0;

    virtual void sendCommand(QString command, KlipperMessage::MessageOrigin origin = KlipperMessage::System) = 0;
    virtual void sendCommand(KlipperMessage message) = 0;
    virtual void setMoonrakerLocation(QString location) = 0;
    virtual void connectKlipper() = 0;
    virtual void disconnectKlipper() = 0;

    virtual void loadPresets() = 0;
    virtual QList<ConsolePreset> getPresetList() = 0;
    virtual void sendPreset(QString key, KlipperMessage::MessageOrigin origin = KlipperMessage::System) = 0;

    //File Management
    virtual void deleteFile(QString file) = 0;
    virtual void deleteFile(KlipperFile file) = 0;
    virtual void moveFile(QString source, QString destination) = 0;
    virtual void copyFile(QString source, QString destination) = 0;

    virtual QString downloadFile(KlipperFile file) = 0;
    virtual bool uploadFile(QString root, QString directory, QString name, QByteArray data) = 0;

    virtual void getFileList(QString directory = QString("gcodes")) = 0;
    virtual void createDirectory(QString directory) = 0;
    virtual void deleteDirectory(QString directory) = 0;

    //Print Management
    virtual void startPrint(QString file) = 0;
    virtual void pausePrint() = 0;
    virtual void resumePrint() = 0;
    virtual void cancelPrint() = 0;

    //Machine Management
    virtual void machineShutdown() = 0;
    virtual void machineReboot() = 0;

    //Service Management
    virtual void serviceRestart(QString service) = 0;
    virtual void serviceStop(QString service) = 0;
    virtual void serviceStart(QString service) = 0;

    virtual void sendGcode(QString gcode) = 0;

    //Printer Management
    virtual void printerInfo() = 0;
    virtual void restartKlipper() = 0;
    virtual void restartFirmware() = 0;
    virtual void printerSubscribe() = 0;

    //Server Management
    virtual void serverInfo() = 0;
    virtual void serverConfig() = 0;
    virtual void serverFileRoots() = 0;

    //Client Management
    virtual void clientIdentifier() = 0;

    virtual ConnectionLocation connectionLoaction() const = 0;
    virtual void setConnectionLoaction(ConnectionLocation connectionLoaction) = 0;

signals:
    void commandSent(KlipperMessage data);
    void responseReceived(KlipperResponse response);
    void printerUpdateReceived(KlipperResponse response);
    void commandLock();
    void commandUnlock();
    void fileListReceived(QList<KlipperFile> files);
    void directoryListing(QString root, QString directory, QList<KlipperFile> files);
    void systemUpdate();
    void printerFound();
    void printerUpdate();
    void printerOnline();

    void klipperConnected();
    void klipperError(QString error, QString message);
    void klipperDisconnected();

    void moonrakerConnected();
    void moonrakerDisconnected();

    void fileDirectoryChanged(QString directory);
};

#endif // QKLIPPERCONSOLE_H
