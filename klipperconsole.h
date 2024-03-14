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

#include "types/klippermessage.h"
#include "types/klipperresponse.h"

#include "settings.h"
#include "types/klipperfile.h"
#include "types/bed.h"
#include "types/extruder.h"
#include "types/position.h"
#include "types/printer.h"
#include "types/toolhead.h"

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
    KlipperConsole();
    ~KlipperConsole();

    void sendCommand(QString command, KlipperMessage::MessageOrigin origin = KlipperMessage::System);
    void sendCommand(KlipperMessage message);
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

    void restartKlipper();
    void restartFirmware();

signals:
    void commandSent(QString data);
    void responseReceived(KlipperResponse response);
    void systemUpdateReceived(KlipperResponse response);
    void printerUpdateReceived(KlipperResponse response);
    void commandLock();
    void commandUnlock();
    void fileListReceived(QList<KlipperFile> files);
    void directoryListReceived(QList<KlipperFile> files);
    void newPrinter(Printer *printer);
    void printerUpdate(Printer *printer);

    void klipperConnected();
    void klipperDisconnected();

    void fileDirectoryChanged(QString directory);

private slots:
    void on_messageReceived(KlipperResponse message);
    void on_messageReadTimer();
    void on_messageParseTimer();

private:
    void sendError(QString message);

    Printer* _printer;
    QTimer *_messageParseTimer = nullptr;
    QQueue<QByteArray> messageQueue;
};

#endif // KLIPPERCONSOLE_H
