/**!
 * QAbstractKlipperConsole enables both remote and local connections to be handled the same way.
 * It expects the response to be in the JSON RPC2.0 format. This can be changed by overriding the
 * on_moonrakerSocket_readyRead and on_messageReady slots.
 */

#ifndef QABSTRACTKLIPPERCONSOLE_H
#define QABSTRACTKLIPPERCONSOLE_H

#include <QObject>
#include <QFunctionPointer>
#include <QAbstractSocket>
#include <QQueue>
#include <QByteArray>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QTimer>
#include <QtConcurrent/QtConcurrent>

#include "../klipperfile.h"
#include "../klippermessage.h"
#include "../klipperresponse.h"

#include "../gcodestore.h"
#include "../gcodemacro.h"

class QAbstractKlipperConsole;
class Printer;

typedef void(QAbstractKlipperConsole::*StartupFunction)();
typedef void(QAbstractKlipperConsole::*ParserFunction)(KlipperResponse);

class QAbstractKlipperConsole : public QObject
{
    Q_OBJECT
public:
    enum ConnectionLocation
    {
        LocationLocal,
        LocationRemote
    };

    enum ConsoleState
    {
        Error =         0x00000010,
        Startup =       0x00000100,
        Connected =     0x00001000,
        Connecting =    0x00010000,
        Disconnected =  0x00100000,
        Disconnecting = 0x01000000,
        Offline =       0x10000000
    };

    explicit QAbstractKlipperConsole(Printer *printer, QObject *parent = nullptr);
    ~QAbstractKlipperConsole();

    virtual void shutdown() = 0;

    virtual void sendCommand(KlipperMessage message) = 0;
    virtual void sendCommand(QString command, KlipperMessage::MessageOrigin origin = KlipperMessage::System) = 0;
    virtual void connectToMoonraker() = 0;
    virtual void disconnectKlipper() = 0;

    //File Management
    virtual void deleteFile(QString file);
    virtual void deleteFile(KlipperFile file);
    virtual void moveFile(QString source, QString destination);
    virtual void copyFile(QString source, QString destination);

    virtual QString downloadFile(KlipperFile file) = 0;
    virtual bool uploadFile(QString root, QString directory, QString name, QByteArray data) = 0;

    virtual void getFileList(QString directory = QString("gcodes"));
    virtual void createDirectory(QString directory);
    virtual void deleteDirectory(QString directory);

    //Print Management
    virtual void startPrint(QString file);
    virtual void pausePrint();
    virtual void resumePrint();
    virtual void cancelPrint();

    //Machine Management
    virtual void machineShutdown();
    virtual void machineReboot();
    virtual void machineSystemInfo();
    virtual void machineServiceRestart(QString service);
    virtual void machineServiceStop(QString service);
    virtual void machineServiceStart(QString service);
    virtual void machineProcStats();

    virtual void sendGcode(QString gcode);

    //Printer Management
    virtual void printerInfo();
    virtual void restartKlipper();
    virtual void restartFirmware();
    virtual void printerObjectsList();
    virtual void printerSubscribe();
    virtual void printerEmergencyStop();
    virtual void printerQueryEndstops();

    //Server Management
    virtual void serverInfo();
    virtual void serverConfig();
    virtual void serverFileRoots();
    virtual void serverTemperatureStore();
    virtual void serverGcodeStore();
    virtual void serverLogsRollover();
    virtual void serverWebsocketId();

    //Client Management
    virtual void clientIdentifier();

    virtual ConnectionLocation connectionLoaction() const;
    virtual void setConnectionLoaction(ConnectionLocation connectionLoaction);

    Printer *printer() const;
    void setPrinter(Printer *printer);

    void setMoonrakerLocation(const QString &moonrakerLocation);
    QString moonrakerLocation() const;

    bool isMoonrakerConnected() const;
    bool isKlipperConnected() const;
    bool isConnected() const;

    bool hasState(ConsoleState state);

    QAbstractSocket *moonrakerSocket() const;
    void setMoonrakerSocket(QAbstractSocket *moonrakerSocket);


    QGCodeMacroList gcodeMacros() const;

    QStringList moonrakerComponents() const;

    QStringList moonrakerFailedComponents() const;

signals:
    void startup();

    void commandSent(KlipperMessage data);
    void responseReceived(KlipperResponse response);
    void printerUpdateReceived(KlipperResponse response);
    void commandLock();
    void commandUnlock();
    void fileListReceived(QList<KlipperFile> files);
    void directoryListing(QString root, QString directory, QList<KlipperFile> files);
    void systemUpdate();
    void printerUpdate();
    void printerOnline();
    /*!
     * \brief Triggered on successful emergency stop
     */
    void printerEmergencyStopped();

    void klipperConnected();
    void klipperError(QString error, QString message);
    void klipperDisconnected();

    void moonrakerConnected();
    void moonrakerDisconnected();

    void fileDirectoryChanged(QString directory);

    void startupProgress(QString message, qreal progress);

    //Server signals
    void serverGCodeStoreResponse(GCodeStore store);
    void serverLogsRolloverSuccess();

    //Machine Signals
    void machineServiceRestarted(QString service);
    void machineServiceStopped(QString service);
    void machineServiceStarted(QString service);

protected slots:
    //Socket slots
    virtual void on_moonrakerSocket_readyRead();
    virtual void on_messageReady();

    //Timer slots
    virtual void on_klipperRestartTimer_timeout();

    /*
     * Klipper/Moonraker slots
     */

    //File Management
    virtual void on_deleteFile(KlipperResponse response);
    virtual void on_moveFile(KlipperResponse response);
    virtual void on_copyFile(KlipperResponse response);

    virtual void on_getFileList(KlipperResponse response);
    virtual void on_createDirectory(KlipperResponse response);
    virtual void on_deleteDirectory(KlipperResponse response);

    //Print Management
    virtual void on_startPrint(KlipperResponse response);
    virtual void on_pausePrint(KlipperResponse response);
    virtual void on_resumePrint(KlipperResponse response);
    virtual void on_cancelPrint(KlipperResponse response);

    //Machine Management
    virtual void on_machineShutdown(KlipperResponse response);
    virtual void on_machineReboot(KlipperResponse response);
    virtual void on_machineSystemInfo(KlipperResponse response);
    virtual void on_machineServiceRestart(KlipperResponse response);
    virtual void on_machineServiceStop(KlipperResponse response);
    virtual void on_machineServiceStart(KlipperResponse response);
    virtual void on_machineProcStats(KlipperResponse response);

    virtual void on_sendGcode(KlipperResponse response);

    //Printer Management
    virtual void on_printerInfo(KlipperResponse response);
    virtual void on_restartKlipper(KlipperResponse response);
    virtual void on_restartFirmware(KlipperResponse response);
    virtual void on_printerObjectsList(KlipperResponse response);
    virtual void on_printerSubscribe(KlipperResponse response);
    virtual void on_printerEmergencyStop(KlipperResponse response);
    virtual void on_printerQueryEndstops(KlipperResponse response);

    //Server Management
    virtual void on_serverInfo(KlipperResponse response);
    virtual void on_serverConfig(KlipperResponse response);
    virtual void on_serverFileRoots(KlipperResponse response);
    virtual void on_serverTemperatureStore(KlipperResponse response);
    virtual void on_serverGCodeStore(KlipperResponse response);
    virtual void on_serverLogsRollover(KlipperResponse response);
    virtual void on_serverWebsocketId(KlipperResponse response);

    //Client Management
    virtual void on_clientIdentifier(KlipperResponse response);

protected:
    virtual void sendError(QString message);
    virtual void addState(ConsoleState state);
    virtual void removeState(ConsoleState state);

    char _eof = (char)0x03;

    Printer* _printer;

    QByteArray _dataBuffer;

    QQueue<QByteArray> _messageDataQueue;
    QQueue<StartupFunction> _startupSequence;
    QMap<QString, ParserFunction> _parserMap;
    QMap<int, KlipperMessage> _klipperMessageBuffer;

    QStringList _subscriptionObjects;
    QStringList _macroObjects;
    QStringList _moonrakerComponents;
    QStringList _moonrakerFailedComponents;

    QGCodeMacroList _gcodeMacros;

    QString _moonrakerLocation;
    QString _moonrakerVersion;

    ConsoleState _state;

    bool _isKlipperConnected = false;
    bool _isMoonrakerConnected = false;

    int _startupState = 0;
    qint64 _waitForOkId = 0;

    ConnectionLocation _connectionLoaction = LocationLocal;

    QAbstractSocket *_moonrakerSocket = nullptr;

    QTimer *_klipperRestartTimer = nullptr;
};

#endif // QABSTRACTKLIPPERCONSOLE_H
