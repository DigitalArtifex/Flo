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
#include <QtConcurrent/QtConcurrent>

#include "../klipperfile.h"
#include "../klippermessage.h"
#include "../klipperresponse.h"

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

    //Service Management
    virtual void serviceRestart(QString service);
    virtual void serviceStop(QString service);
    virtual void serviceStart(QString service);

    virtual void sendGcode(QString gcode);

    //Printer Management
    virtual void printerInfo();
    virtual void restartKlipper();
    virtual void restartFirmware();
    virtual void printerSubscribe();

    //Server Management
    virtual void serverInfo();
    virtual void serverConfig();
    virtual void serverFileRoots();
    virtual void serverTemperatureStore();

    //Client Management
    virtual void clientIdentifier();

    virtual ConnectionLocation connectionLoaction() const = 0;
    virtual void setConnectionLoaction(ConnectionLocation connectionLoaction) = 0;

    Printer *printer() const;
    void setPrinter(Printer *printer);

    QString moonrakerLocation() const;
    bool isMoonrakerConnected() const;
    bool isKlipperConnected() const;
    bool isConnected() const;

    bool hasState(ConsoleState state);

    QAbstractSocket *moonrakerSocket() const;
    void setMoonrakerSocket(QAbstractSocket *moonrakerSocket);

signals:
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

    void klipperConnected();
    void klipperError(QString error, QString message);
    void klipperDisconnected();

    void moonrakerConnected();
    void moonrakerDisconnected();

    void fileDirectoryChanged(QString directory);

    void startupProgress(QString message, qreal progress);

protected slots:
    virtual void on_moonrakerSocket_readyRead();
    virtual void on_messageReady();

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

    //Service Management
    virtual void on_serviceRestart(KlipperResponse response);
    virtual void on_serviceStop(KlipperResponse response);
    virtual void on_serviceStart(KlipperResponse response);

    virtual void on_sendGcode(KlipperResponse response);

    //Printer Management
    virtual void on_printerInfo(KlipperResponse response);
    virtual void on_restartKlipper(KlipperResponse response);
    virtual void on_restartFirmware(KlipperResponse response);
    virtual void on_printerSubscribe(KlipperResponse response);

    //Server Management
    virtual void on_serverInfo(KlipperResponse response);
    virtual void on_serverConfig(KlipperResponse response);
    virtual void on_serverFileRoots(KlipperResponse response);
    virtual void on_serverTemperatureStore(KlipperResponse response);

    //Client Management
    virtual void on_clientIdentifier(KlipperResponse response);

protected:
    virtual void sendError(QString message);
    virtual void addState(ConsoleState state);
    virtual void removeState(ConsoleState state);

    Printer* _printer;

    QByteArray _dataBuffer;

    QQueue<QByteArray> _messageDataQueue;
    QQueue<StartupFunction> _startupSequence;
    QMap<QString, ParserFunction> _parserMap;
    QMap<int, KlipperMessage> _klipperMessageBuffer;

    QString _moonrakerLocation;

    ConsoleState _state;

    bool _isKlipperConnected = false;
    bool _isMoonrakerConnected = false;

    int _startupState = 0;

    ConnectionLocation _connectionLoaction = LocationLocal;

    QAbstractSocket *_moonrakerSocket = nullptr;
};

#endif // QABSTRACTKLIPPERCONSOLE_H
