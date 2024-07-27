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
#include <QStorageInfo>
#include <QtConcurrent/QtConcurrent>

#include "../klipperfile.h"
#include "../klippermessage.h"
#include "../klipperresponse.h"

#include "../gcode/qgcodestore.h"
#include "../gcode/qgcodemacro.h"
#include "../gcode/qgcodecommand.h"
#include "../gcode/qgcodemove.h"

#include "../system.h"

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

    struct KlipperCommand
    {
        QString command;
        QString help;

        QStringList parameters;
    };

    explicit QAbstractKlipperConsole(Printer *printer, QObject *parent = nullptr);
    ~QAbstractKlipperConsole();

    virtual void shutdown() = 0;

    virtual void sendCommand(KlipperMessage message, bool immediate = false) = 0;
    virtual void sendCommand(QString command, KlipperMessage::MessageOrigin origin = KlipperMessage::System, bool immediate = false) = 0;
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
    virtual void machinePeripheralsUSB();
    virtual void machinePeripheralsSerial();
    virtual void machinePeripheralsVideo();
    virtual void machinePeripheralsCanbus(qint32 canBus);
    virtual void machineProcStats();
    virtual void machineUpdateStatus();
    virtual void machineUpdateFull();
    virtual void machineUpdateMoonraker();
    virtual void machineUpdateKlipper();
    virtual void machineUpdateClient(QString client);
    virtual void machineUpdateSystem();
    virtual void machineUpdateRecover(QString name, bool hardRecover = false);
    virtual void machineUpdateRollback(QString name);

    virtual void sendGcode(QString gcode, KlipperMessage::MessageOrigin origin = KlipperMessage::System);

    //Printer Management
    virtual void printerInfo();
    virtual void restartKlipper();
    virtual void restartFirmware();
    virtual void printerObjectsList();
    virtual void printerSubscribe();
    virtual void printerEmergencyStop();
    virtual void printerQueryEndstops();

    /*
     * Server Management
     */

    //File management
    virtual void serverInfo();
    virtual void serverConfig();
    virtual void serverFileRoots();
    virtual void serverFilesMetadata(QString fileName);
    virtual void serverFilesMetadata(KlipperFile file);

    //Store management
    virtual void serverTemperatureStore();
    virtual void serverGcodeStore();
    virtual void serverLogsRollover();
    virtual void serverWebsocketId();

    //Webcam Management
    virtual void serverWebcamList();
    virtual void serverWebcamCreate(System::Webcam webcam);
    virtual void serverWebcamUpdate(System::Webcam webcam);
    virtual void serverWebcamDelete(System::Webcam webcam);

    //Announcement Management
    virtual void serverAnnouncementsList(bool includeDismissed = false);
    virtual void serverAnnouncementsUpdate();
    virtual void serverAnnouncementDismiss(QString entryId, qint64 waketime = 0);

    //Job queue Management
    virtual void serverJobQueueStatus();
    virtual void serverJobQueueStart();
    virtual void serverJobQueuePause();
    virtual void serverJobQueueJump(QString id);
    virtual void serverJobQueueAdd(QStringList filenames);
    virtual void serverJobQueueDelete(QStringList ids);

    //Client Management
    virtual void clientIdentifier();

    //Access Management
    virtual void accessLogin(QString username, QString password, QString source = QString("moonraker"));
    virtual void accessLogout();
    virtual void accessGetUser();
    virtual void accessCreateUser(QString username, QString password);
    virtual void accessDeleteUser(QString username);
    virtual void accessUsersList();
    virtual void accessUserPasswordReset(QString password, QString newPassword);

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

    QGCodeCommandList gcodeCommands() const;

    bool isKlipperCommand(QString command);
    QStringList klipperCommands();
    KlipperCommand klipperCommand(QString command);

protected:
    void loadKlipperCommands();

signals:
    void startup();

    void commandSent(KlipperMessage data);
    void responseReceived(KlipperResponse response);
    void printerUpdateReceived(KlipperResponse response);
    void commandLock();
    void commandUnlock();
    void fileListReceived(QList<KlipperFile> files);
    void directoryListing(QString root, QString directory, QList<KlipperFile> files);
    void printerOnline();

    //Update signals
    void systemUpdate();
    void printerUpdate();
    void extrudersUpdate();
    /*!
     * \brief Triggered on successful emergency stop
     */
    void printerEmergencyStopped();

    void printerGCodeMove(QGCodeMove move);

    void klipperConnected();
    void klipperError(QString error, QString message);
    void klipperDisconnected();

    void moonrakerConnected();
    void moonrakerDisconnected();

    void fileDirectoryChanged(QString directory);

    void startupProgress(QString message, qreal progress);

    //Server signals
    void serverGCodeStoreResponse(GCodeStore store);
    void serverGCodesUpdated();
    void serverGCodeMacrosUpdated();
    void serverLogsRolloverSuccess();
    void serverMetadataResult(KlipperFile::Metadata metadata);
    void serverWebcamsListed();
    void serverWebcamCreated(System::Webcam webcam);
    void serverWebcamDeleted(System::Webcam webcam);
    void serverAnnouncementsListed();
    void serverAnnouncementDismissed(QString entryId);
    void serverJobQueueStatusUpdate();

    //Machine Signals
    void machineServiceRestarted(QString service);
    void machineServiceStopped(QString service);
    void machineServiceStarted(QString service);
    void machineUpdateStatusReceived();
    void machineUpdateRecovered();
    void machineUpdateRollbackComplete();
    void machineUpdatedFull();
    void machineUpdatedMoonraker();
    void machineUpdatedKlipper();
    void machineUpdatedClient(QString client);
    void machineUpdatedSystem();

    //Access signals
    void accessUserLoggedIn();
    void accessUserLoggedOut();
    void accessUsersListed();
    void accessUserCreated(const System::User &user);
    void accessUserDeleted(const System::User &user);
    void accessUserPasswordResetSuccessful();

protected slots:
    //Socket slots
    virtual void on_moonrakerSocket_readyRead();
    virtual void on_messageReady();
    virtual void responseReceivedEvent();

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
    virtual void on_machinePeripheralsUSB(KlipperResponse response);
    virtual void on_machinePeripheralsSerial(KlipperResponse response);
    virtual void on_machinePeripheralsVideo(KlipperResponse response);
    virtual void on_machinePeripheralsCanbus(KlipperResponse response);
    virtual void on_machineUpdateStatus(KlipperResponse response);
    virtual void on_machineUpdateFull(KlipperResponse response);
    virtual void on_machineUpdateMoonraker(KlipperResponse response);
    virtual void on_machineUpdateKlipper(KlipperResponse response);
    virtual void on_machineUpdateClient(KlipperResponse response);
    virtual void on_machineUpdateSystem(KlipperResponse response);
    virtual void on_machineUpdateRecover(KlipperResponse response);
    virtual void on_machineUpdateRollback(KlipperResponse response);

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
    virtual void on_serverFilesMetadata(KlipperResponse response);
    virtual void on_serverWebcamList(KlipperResponse response);
    virtual void on_serverWebcamCreate(KlipperResponse response);
    virtual void on_serverWebcamDelete(KlipperResponse response);
    virtual void on_serverAnnouncementsList(KlipperResponse response);
    virtual void on_serverAnnouncementsUpdate(KlipperResponse response);
    virtual void on_serverAnnouncementDismissed(KlipperResponse response);
    virtual void on_serverJobQueueStatus(KlipperResponse response);

    //Access Management
    virtual void on_accessLogin(KlipperResponse response);
    virtual void on_accessLogout(KlipperResponse response);
    virtual void on_accessGetUser(KlipperResponse response);
    virtual void on_accessCreateUser(KlipperResponse response);
    virtual void on_accessDeleteUser(KlipperResponse response);
    virtual void on_accessUsersList(KlipperResponse response);
    virtual void on_accessUserPasswordReset(KlipperResponse response);

    //Client Management
    virtual void on_clientIdentifier(KlipperResponse response);

protected:
    virtual void sendError(QString message);
    virtual void addState(ConsoleState state);
    virtual void removeState(ConsoleState state);

    char m_eof = (char)0x03;

    Printer* m_printer;

    QByteArray m_dataBuffer;

    QQueue<QByteArray> m_messageDataQueue;
    QQueue<StartupFunction> m_startupSequence;
    QQueue<KlipperMessage> m_messageOutbox;
    QMap<QString, ParserFunction> m_parserMap;
    QMap<QString, ParserFunction> m_actionMap;
    QMap<int, KlipperMessage> m_klipperMessageBuffer;
    QMap<QString, KlipperCommand> m_klipperCommands;

    QStringList m_subscriptionObjects;
    QStringList m_macroObjects;
    QStringList m_moonrakerComponents;
    QStringList m_moonrakerFailedComponents;

    QGCodeMacroList m_gcodeMacros;
    QGCodeCommandList m_gcodeCommands;

    QString m_moonrakerLocation;
    QString m_moonrakerVersion;
    QString m_progressText;

    qreal m_progress = 0.0;
    qint64 m_progressSteps = 0;

    ConsoleState m_state;

    bool m_isKlipperConnected = false;
    bool m_isMoonrakerConnected = false;
    bool m_awaitingResponse = false;

    int m_startupState = 0;
    qint64 m_waitForOkId = 0;

    ConnectionLocation m_connectionLoaction = LocationLocal;

    QAbstractSocket *m_moonrakerSocket = nullptr;

    QTimer *m_klipperRestartTimer = nullptr;
};

#endif // QABSTRACTKLIPPERCONSOLE_H
