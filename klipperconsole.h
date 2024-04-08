#ifndef KLIPPERCONSOLE_H
#define KLIPPERCONSOLE_H

#include <QObject>
#include <QDateTime>
#include <QThread>
#include <QQueue>
#include <QLocalSocket>

#include <QDir>
#include <QDirIterator>
#include <QFile>

#include <QIcon>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QMap>
#include <QQueue>

#include <QTimer>
#include <QtConcurrent/QtConcurrent>

#include "types/klippermessage.h"
#include "types/klipperresponse.h"

#include "types/klipperfile.h"

#include "types/bed.h"
#include "types/extruder.h"
#include "types/position.h"
#include "types/toolhead.h"

class Printer;

struct ConsolePreset
{
    QString name;
    QString icon;
    QString file;
    QString type;
};

class KlipperConsole : public QObject
{
    Q_OBJECT
    static bool busy;
    bool commandLocked = false;
    int lockId = 0;

    QString klipperLocation;
    QLocalSocket *klipperSocket;

    QTimer *messageReadTimer = NULL;
    QByteArray messageBuffer;

    QMap<QString, ConsolePreset> presets;

    QMap<int, KlipperMessage> klipperMessageBuffer;

public:
    KlipperConsole(Printer *printer, QObject *parent = nullptr);
    ~KlipperConsole();

    virtual void shutdown();

    void sendCommand(QString command, KlipperMessage::MessageOrigin origin = KlipperMessage::System);
    void sendCommand(KlipperMessage message);
    void setMoonrakerLocation(QString location);
    void connectKlipper();
    void disconnectKlipper();

    void loadPresets();
    QList<ConsolePreset> getPresetList();
    void sendPreset(QString key, KlipperMessage::MessageOrigin origin = KlipperMessage::System);

    //File Management
    void getFileList(QString directory = QString("gcodes"));
    void deleteFile(QString file);
    void moveFile(QString source, QString destination);
    void copyFile(QString source, QString destination);
    void createDirectory(QString directory);
    void deleteDirectory(QString directory);

    //Print Management
    void startPrint(QString file);
    void pausePrint();
    void resumePrint();
    void cancelPrint();

    //Machine Management
    void machineShutdown();
    void machineReboot();

    //Service Management
    void serviceRestart(QString service);
    void serviceStop(QString service);
    void serviceStart(QString service);

    void sendGcode(QString gcode);

    //Printer Management
    void printerInfo();
    void restartKlipper();
    void restartFirmware();
    void printerSubscribe();

    //Server Management
    void serverInfo();
    void serverConfig();
    void serverFileRoots();

    //Client Management
    void clientIdentifier();

signals:
    void commandSent(QString data);
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

private slots:
    void on_messageReceived(KlipperResponse message);
    void on_klipperSocket_readyRead();
    void on_messageParse();

    void on_klipperRestartTimer_timeout();

private:
    void sendError(QString message);

    Printer* _printer;
    QTimer *_messageParseTimer = nullptr;
    QTimer *_klipperRestartTimer = nullptr;
    QQueue<QByteArray> messageQueue;
    QString _moonrakerLocation;

    bool _moonrakerConnected = false;
    bool _klipperConnected = false;
    bool _printerConnected = false;
    bool _startup = true;
    bool _shutdown = false;

    int _startupState = 0;
};

#endif // KLIPPERCONSOLE_H
