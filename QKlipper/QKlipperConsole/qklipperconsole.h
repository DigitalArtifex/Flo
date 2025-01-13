/*!
 * QKlipper - A Qt library for the Klipper/Moonraker API
 * Copyright (C) 2024 James Dudeck
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of  MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef QKLIPPERCONSOLE_H
#define QKLIPPERCONSOLE_H

#include <QObject>
#include <QQueue>
#include <QMap>

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>

#include <QLocalSocket>
#include <QTcpSocket>
#include <QSslSocket>
#include <QtWebSockets/QWebSocket>

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QHttpMultiPart>

#include <QCoreApplication>

#include "../QKlipperMessage/qklippermessage.h"
#include "../QKlipperFile/qklipperfile.h"
#include "../QKlipperSystem/qklippersystem.h"
#include "../QKlipperServer/qklipperserver.h"

#include "../QKlipperPrinter/qklipperprinter.h"

#include "../qklippererror.h"

class QKlipperConsole;
class QKlipperInstance;
typedef void(QKlipperConsole::*StartupFunction)();
typedef void(QKlipperConsole::*ParserFunction)(QKlipperMessage*);

//!  QKlipperConsole class
/*!
  This class is responsible for the actual communication to the klipper instance via moonraker.
  It provides methods for the moonraker API for controlling and querying aspects of the klipper
  instance.

  Prior to connecting, it is required to pass instance references to QKlipperPrinter, QKlipperSystem
  and QKlipperServer that have been setup and configured. This is handled by the QKlipperInstance class.
*/
class QKlipperConsole : public QObject
{
    Q_OBJECT
    friend QKlipperInstance;
public:
    //!  ConnectionState enum
    /*!
      This enum provides flags for the various connection states of the console
    */
    enum ConnectionState
    {
        Idle =                 0, /*!!< Connection state is idle. This is the default state */
        Startup =              0b00000001, /*!!< Connection has been established and currently syncing */
        Connecting =           0b00000010, /*!!< Connecting to websocket address */
        Connected =            0b00000100, /*!!< Connection to websocket established */
        MoonrakerConnected =   0b00001000, /*!!< Connection to moonraker established */
        KlipperConnected =     0b00010000, /*!!< Connection to klipper verified */
        Initialized =          0b00100000, /*!!< Connection startup sequence finished */
        Syncronized =          0b00111100, /*!!< Connection to websocket, moonraker and klipper established and startup sequence completed */
        Restarting =           0b01000000, /*!!< Connection to websocket, moonraker and klipper established and startup sequence completed */
        Error =                0b10000000  /*!!< Error detected with the connection */
    };

    /*!
     * \fn QKlipperConsole::QKlipperConsole()
     * \brief Constructor
     *
     * \param parent The parent object
     */
    explicit QKlipperConsole(QObject *parent = nullptr);

    /*!
     * Destructor
     */
    ~QKlipperConsole();

    /*!
      Connect to the websocket address and process
      startup sequence.

      \returns True if the websocket has connected.
    */
    bool connect();

    /*!
     * Disconnect from the websocket and reset objects
     */
    void disconnect();

    /*!
     * Connection state of the console
     *
     * \returns The current connection state value
     */
    ConnectionState connectionState() const;

    /*!
     * Checks the current connection state to see if it has the passed flag
     *
     * \param state The connection flag to check for
     *
     * \returns True is the current connection state contains the state flag
     */
    bool hasConnectionState(ConnectionState state);

    /*!
     * Adds a flag to the current connection state
     */
    void addConnectionState(ConnectionState state);

    /*!
     * Removes a flag from the current connection state
     */
    void removeConnectionState(ConnectionState state);

    /*!
     * Checks if the current state for the connecting flag
     *
     * \returns True if the connection state contains the connecting flag
     */
    bool isConnecting();

    /*!
     * Checks if the current state for the connecting, MoonrakerConnected flags
     *
     * \returns True if the connection state contains the connecting flag
     */
    bool isConnected();

    /*!
     * The current progress of the startup sequence
     *
     * \returns The statup progress (0-100)
     */
    qreal startupSequenceProgress() const;

    /*!
     * Current startup sequence text
     *
     * \returns Current startup sequence text
     */
    QString startupSequenceText() const;

    QKlipperPrinter *printer() const;

    QKlipperSystem *system() const;

    QKlipperServer *server() const;

public slots:

    /*!
     * Asyncronously requests user login
     *
     * \param username Username to login
     *
     * \param password Password for the user
     */
    void accessLogin(QString username, QString password);

    /*!
     * Asyncronously logs the current user out
     */
    void accessLogout();

    /*!
     * Asyncronously requests current user information
     */
    void accessGetUser();

    /*!
     * Asyncronously requests user creation
     *
     * \param username Username to login
     *
     * \param password Password for the user
     */
    void accessCreateUser(QString username, QString password);

    /*!
     * Asyncronously requests user deletion
     *
     * \param username Username to login
     */
    void accessDeleteUser(QString username);

    /*!
     * Asyncronously requests user list
     */
    void accessUsersList();

    /*!
     * Asyncronously requests password change for the current user
     *
     * \param password Password for the user
     *
     * \param newPassword New password for the user
     */
    void accessUserPasswordReset(QString password, QString newPassword);

    /*!
     * Asyncronously requests job queue items to be deleted
     */
    void clientIdentifier();

    /*!
     * Asyncronously adds a new value to the database
     *
     * \param key Database key for the value
     *
     * \param value The value
     */
    void databaseCreate(const QString &key, const QVariant &value);

    /*!
     * Asyncronously removes the database value for the given key
     *
     * \param key Database key to remove
     */
    void databaseDelete(const QString &key);

    /*!
     * Reads a stored value in the database
     *
     * \param key Database key to remove
     */
    QVariant databaseGetItem(const QString &key);

    /*!
     * Requests a list of available power devices
     */
    void machinePowerDeviceList();

    /*!
     * Queries status of the power devices
     *
     * \param names Names of the power devices to query
     */
    void machinePowerDeviceStatus(QStringList names);

    /*!
     * Sets status of the power device
     *
     * \param names Name of the power devices to turn on or off
     */
    void machinePowerDeviceSetState(const QString &name, const QString &action = "toggle");

    void machineLedStripList();
    void machineLedStrip(const QStringList &names);
    void machineLedStripOn(const QStringList &names);
    void machineLedStripOff(const QStringList &names);
    void machineSetLedStrip(QKlipperLedStrip *stripData);

    void machineSensorsList();
    void machineSensorInfo(const QString &name);
    void machineSensorMeasurement(const QString &name);
    void machineSensorMeasurements();

    /*!
     * Sends command to shutdown machine. Server will disconnect
     */
    void machineShutdown(QKlipperError *error = nullptr);

    /*!
     * Sends command to reboot machine. Server will disconnect
     */
    void machineReboot(QKlipperError *error = nullptr);

    /*!
     * Asyncronously queries machine info
     */
    void machineSystemInfo();

    /*!
     * Sends a command to restart a klipper service
     *
     * This is a blocking method
     *
     * \param service The name of the service
     *
     * \param error Optional reference to the QKlipperError object
     */
    bool machineServiceRestart(QString service, QKlipperError *error = nullptr);

    /*!
     * Sends a command to stop a klipper service
     *
     * This is a blocking method
     *
     * \param service The name of the service
     *
     * \param error Optional reference to the QKlipperError object
     */
    bool machineServiceStop(QString service, QKlipperError *error = nullptr);

    /*!
     * Sends a command to start a klipper service
     *
     * This is a blocking method
     *
     * \param service The name of the service
     *
     * \param error Optional reference to the QKlipperError object
     */
    bool machineServiceStart(QString service, QKlipperError *error = nullptr);

    /*!
     * Asyncronously queries a list of USB devices
     */
    void machinePeripheralsUSB();

    /*!
     * Asyncronously queries a list of serial devices
     */
    void machinePeripheralsSerial();

    /*!
     * Asyncronously queries a list of video devices
     */
    void machinePeripheralsVideo();

    /*!
     * Asyncronously queries an unregistered CAN Bus
     *
     *
     * \param canBus Index of the interface
     */
    void machinePeripheralsCanbus(qint32 canBus);

    /*!
     * Asyncronously queries machine proc stats
     */
    void machineProcStats();

    /*!
     * Asyncronously queries machine update status
     */
    void machineUpdateStatus();

    /*!
     * Asyncronously requests a refresh of the update status
     */
    void machineUpdateRefresh();

    /*!
     * Sends a command to perform a full update of the system, klipper and moonraker
     *
     * This is a blocking method
     *
     * \param error Optional reference to the QKlipperError object
     */
    bool machineUpdateFull(QKlipperError *error = nullptr);

    /*!
     * Sends a command to perform an update on Moonraker
     *
     * This is a blocking method
     *
     * \param error Optional reference to the QKlipperError object
     */
    bool machineUpdateMoonraker(QKlipperError *error = nullptr);

    /*!
     * Sends a command to perform an update on Klipper
     *
     * This is a blocking method
     *
     * \param error Optional reference to the QKlipperError object
     */
    bool machineUpdateKlipper(QKlipperError *error = nullptr);

    /*!
     * Sends a command to perform an update on the specified client
     *
     * This is a blocking method
     *
     * \param client Name of the client to update
     *
     * \param error Optional reference to the QKlipperError object
     */
    bool machineUpdateClient(QString client, QKlipperError *error = nullptr);

    /*!
     * Sends a command to perform an update on the system
     *
     * This is a blocking method
     *
     * \param error Optional reference to the QKlipperError object
     */
    bool machineUpdateSystem(QKlipperError *error = nullptr);

    /*!
     * Sends a command to perform an update on the specified client
     *
     * This is a blocking method
     *
     * \param client Name of the client to recover
     *
     * \param hardRecover Performs a hard reset (default is false)
     *
     * \param error Optional reference to the QKlipperError object
     */
    bool machineUpdateRecover(QString name, bool hardRecover = false, QKlipperError *error = nullptr);

    /*!
     * Sends a command to perform an update rollback on specified client
     *
     * This is a blocking method
     *
     * \param name Name of the client to rollback
     *
     * \param error Optional reference to the QKlipperError object
     */
    bool machineUpdateRollback(QString name, QKlipperError *error = nullptr);

    /*!
     * Asyncronously queries printer info
     */
    void printerInfo();

    /*!
     * Asyncronously queries printer MCU info
     */
    void printerMCUInfo();

    /*!
     * Asyncronously queries available objects to subscribe to. Must be called during startup sequence
     */
    void printerObjectsList();

    /*!
     * Asyncronously queries a specific printer object
     */
    void printerObjectsQuery(QString &object);

    /*!
     * Asyncronously queries a list of printer objects
     */
    void printerObjectsQuery(QStringList &objects);

    /*!
     * Asyncronously queries all available printer objects
     */
    void printerObjectsQuery();

    /*!
     * Asyncronously subscribes to all available printer objects for update. Must be called during startup
     * sequence, after printer.objects.list
     */
    void printerSubscribe();

    /*!
     * Asyncronously queries printer endstops
     */
    void printerQueryEndstops();

    /*!
     * Sends a command to start a print job
     *
     * This is a blocking method
     *
     * \param gcode The gcode script to run
     *
     * \param error Optional reference to the QKlipperError object
     */
    bool printerPrintStart(QString file, QKlipperError *error = nullptr);

    /*!
     * Sends a command to start a print job
     *
     * This is a blocking method
     *
     * \param gcode The gcode script to run
     *
     * \param error Optional reference to the QKlipperError object
     */
    bool printerPrintStart(QKlipperFile *file, QKlipperError *error = nullptr);

    /*!
     * Sends a command to pause the printer's current print job
     *
     * This is a blocking method
     *
     * \param gcode The gcode script to run
     *
     * \param error Optional reference to the QKlipperError object
     */
    bool printerPrintPause(QKlipperError *error = nullptr);

    /*!
     * Sends a command to resume the printer's current print job
     *
     * This is a blocking method
     *
     * \param gcode The gcode script to run
     *
     * \param error Optional reference to the QKlipperError object
     */
    bool printerPrintResume(QKlipperError *error = nullptr);

    /*!
     * Sends a command to cancel the printer's current print job
     *
     * This is a blocking method
     *
     * \param gcode The gcode script to run
     *
     * \param error Optional reference to the QKlipperError object
     */
    bool printerPrintCancel(QKlipperError *error = nullptr);

    /*!
     * Sends an emergency stop command to the printer
     *
     * This is a blocking method
     *
     * \param gcode The gcode script to run
     *
     * \param error Optional reference to the QKlipperError object
     */
    bool printerEmergencyStop(QKlipperError *error = nullptr);

    /*!
     * Sends the requested gcode command and returns when it is completed
     *
     * This is a blocking method
     *
     * \param gcode The gcode script to run
     *
     * \param error Optional reference to the QKlipperError object
     *
     * \param origin Optional declaration of source. If the origin is set to anything other than 'User' the message
     * will automatically be deleted
     */
    bool printerGcodeScript(QString gcode, QKlipperError *error = nullptr, QKlipperMessage::Origin origin = QKlipperMessage::System);

    /*!
     * Sends a restart command to klipper and returns if it was successful
     * or not.
     *
     * This is a blocking method
     *
     * \param error Optional reference to the QKlipperError object
     */
    bool restartKlipper(QKlipperError *error = nullptr);

    /*!
     * Sends a reset firmware command and returns if it was successful
     * or not.
     *
     * This is a blocking method
     *
     * \param error Optional reference to the QKlipperError object
     */
    bool restartFirmware(QKlipperError *error = nullptr);

    /*!
     * Sends a restart command to the server and returns if it was successful
     * or not.
     *
     * This is a blocking method
     *
     * \param error Optional reference to the QKlipperError object
     */
    bool serverRestart(QKlipperError *error = nullptr);

    /*!
     * Asyncronously queries server info
     */
    void serverInfo();

    /*!
     * Asyncronously queries server config
     */
    void serverConfig();

    /*!
     * Asyncronously queries available file roots
     */
    void serverFileRoots();

    /*!
     * Asyncronously queries file metadata
     *
     * \param fileName URI of the file without root
     */
    void serverFilesMetadata(QString fileName);

    /*!
     * Asyncronously queries file metadata
     *
     * \param file KlipperFile object
     */
    void serverFilesMetadata(QKlipperFile *file);

    /*!
     * Asyncronously queries list of files in specified directory
     *
     * \param fileName URI of the file without root
     */
    void serverFilesList(QString directory = QString("gcodes"));

    /*!
     * Asyncronously queries file delete request
     *
     * \param file URI of the file without root
     */
    void serverFileDelete(QString file);

    /*!
     * Asyncronously queries file delete request
     *
     * \param file KlipperFile object of the file to be deleted
     */
    void serverFileDelete(QKlipperFile *file);

    /*!
     * Asyncronously queries file move request
     *
     * \param source URI of the file to move
     *
     * \param destination URI of the new file location
     */
    void serverFileMove(QString source, QString destination);

    /*!
     * Asyncronously queries file copy request
     *
     * \param source URI of the file to copy
     *
     * \param destination URI of the new file location
     */
    void serverFileCopy(QString source, QString destination);

    /*!
     * Requests the raw data of the specified file
     *
     * This is a blocking method
     *
     * \param file QKlipperFile object of the file to download
     *
     * \param error Optional reference to the QKlipperError object
     *
     * \returns QByteArray of the file contents
     */
    QByteArray serverFileDownload(QKlipperFile *file, QKlipperError *error = nullptr);

    /*!
     * Requests the raw data of the specified file
     *
     * This is a blocking method
     *
     * \param file QKlipperFile object of the file to download
     *
     * \param error Optional reference to the QKlipperError object
     *
     * \returns QByteArray of the file contents
     */
    QByteArray serverFileDownload(QString file, QKlipperError *error = nullptr);

    /*!
     * Uploads the specified data to the server
     *
     * This is a blocking method
     *
     * \param root Root directory (configs, gcodes etc)
     *
     * \param directory Path to upload the file to. Server will attempt to create the path if it
     * doesn't exist
     *
     * \param name Name of the newly created file
     *
     * \param data The data to be uploaded
     *
     * \param error Optional reference to the QKlipperError object
     */
    bool serverFileUpload(QString root, QString directory, QString name, QByteArray data, QKlipperError *error = nullptr);

    /*!
     * Asyncronously requests creation of specified directory
     *
     * \param source URI of the file to copy
     *
     * \param destination URI of the new file location
     */
    void serverDirectoryPost(QString directory);

    /*!
     * Asyncronously requests deletion of specified directory
     *
     * \param source URI of the file to copy
     *
     * \param destination URI of the new file location
     */
    void serverDirectoryDelete(QString directory, bool forced);

    /*!
     * Asyncronously requests temperature store history
     */
    void serverTemperatureStore();

    /*!
     * Asyncronously requests gcode store history
     */
    void serverGcodeStore();

    /*!
     * Asyncronously requests rollover of all logs
     */
    void serverLogsRollover();

    /*!
     * Asyncronously requests rollover of logs for specified application
     *
     * \param application Name of the application
     */
    void serverLogsRollover(QString &application);

    /*!
     * Asyncronously requests websocket id
     */
    void serverWebsocketId();

    /*!
     * Asyncronously requests list of available webcams
     */
    void serverWebcamList();

    /*!
     * Asyncronously requests creation of webcam object
     *
     * \param webcam QKlipperWebcam object
     */
    void serverWebcamCreate(QKlipperWebcam *webcam);

    /*!
     * Asyncronously requests updating the information of specified webcam
     *
     * \param webcam QKlipperWebcam object
     */
    void serverWebcamUpdate(QKlipperWebcam *webcam);

    /*!
     * Asyncronously requests deletion of webcam object
     *
     * \param webcam QKlipperWebcam object
     */
    void serverWebcamDelete(QKlipperWebcam *webcam);

    /*!
     * Asyncronously requests list of announcements
     *
     * \param includeDismissed Optional parameter to include dismissed announcements
     */
    void serverAnnouncementsList(bool includeDismissed = false);

    /*!
     * Asyncronously requests update of announcements
     */
    void serverAnnouncementsUpdate();

    /*!
     * Asyncronously requests dismissal of specified announcement
     *
     * \param entryId UID of the entry
     *
     * \param waketime Time to wait before resetting the dismissed state. (0 means it will not reset)
     */
    void serverAnnouncementDismiss(QString entryId, qint64 waketime = 0);

    /*!
     * Asyncronously requests job queue status
     */
    void serverJobQueueStatus();

    /*!
     * Asyncronously requests job queue to start
     */
    void serverJobQueueStart();

    /*!
     * Asyncronously requests job queue to pause
     */
    void serverJobQueuePause();

    /*!
     * Asyncronously requests job queue to jump to specified job ID
     *
     * \param id UID of the job to jump to the front
     */
    void serverJobQueueJump(QString id);

    /*!
     * Asyncronously requests files to be added to the job queue
     *
     * \param filenames List of files uris (without root) to add to the job queue
     */
    void serverJobQueueAdd(QStringList filenames);

    /*!
     * \brief Asyncronously requests job queue items to be deleted
     *
     * \param ids List of UIDs to remove from the queue
     */
    void serverJobQueueDelete(QStringList ids);

    /*!
     * \brief Asyncronously sends a message to the RPC websocket
     *
     * \param message QKlipperMessage to send
     */
    void sendRpcMessage(QKlipperMessage *message);

    /*!
     * \brief Asyncronously sends a message via http
     *
     * \param message QKlipperMessage to send
     */
    void sendWebSocketMessageAsync(QKlipperMessage *message);

    /*!
     * \brief Sends a message via http
     *
     * \param message QKlipperMessage to send
     *
     * \param error Optional error object
     *
     * \returns True if successful
     */
    bool sendWebSocketMessage(QKlipperMessage *message, QKlipperError *error = nullptr);


signals:
    void connectionStateChanged();

    void startupSequenceProgressChanged();
    void startupSequenceTextChanged();
    void errorOccured(QKlipperError &error);
    void messageSent(QKlipperMessage *message);
    void gcodeResponse(QString &message);

private slots:

    void setPrinter(QKlipperPrinter *printer);

    void setSystem(QKlipperSystem *system);

    void setServer(QKlipperServer *server);

    void rpcUpdateSocketDataReady(); //local socket
    void rpcUpdateSocketDataReceived(QString data); //websocket
    void scanRpcUpdateBuffer();

    void parseNotification(QKlipperMessage *message);
    void parseResponse(QKlipperMessage *message);
    void processStartupSequence();
    void deleteMessage(QKlipperMessage *message);

    void accessLoginParser(QKlipperMessage *message);
    void accessLogoutParser(QKlipperMessage *message);
    void accessGetUserParser(QKlipperMessage *message);
    void accessCreateUserParser(QKlipperMessage *message);
    void accessDeleteUserParser(QKlipperMessage *message);
    void accessUsersListParser(QKlipperMessage *message);
    void accessUserPasswordResetParser(QKlipperMessage *message);

    void clientIdentifierParser(QKlipperMessage *message);

    void machineSystemInfoParser(QKlipperMessage *message);
    void machineProcStatsParser(QKlipperMessage *message);
    void machinePeripheralsUSBParser(QKlipperMessage *message);
    void machinePeripheralsSerialParser(QKlipperMessage *message);
    void machinePeripheralsVideoParser(QKlipperMessage *message);
    void machinePeripheralsCanbusParser(QKlipperMessage *message);
    void machineUpdateStatusParser(QKlipperMessage *message);
    void machinePowerDeviceListParser(QKlipperMessage *message);
    void machinePowerDeviceParser(QKlipperMessage *message);
    void machineLedStripListParser(QKlipperMessage *message);
    void machineSensorListParser(QKlipperMessage *message);
    void machineSensorParser(QKlipperMessage *message);
    void machineSensorMeasurementParser(QKlipperMessage *message);

    void printerInfoParser(QKlipperMessage *message);
    void printerObjectsListParser(QKlipperMessage *message);
    void printerObjectsQueryParser(QKlipperMessage *message);
    void printerSubscribeParser(QKlipperMessage *message);
    void printerQueryEndstopsParser(QKlipperMessage *message);

    void serverInfoParser(QKlipperMessage *message);
    void serverConfigParser(QKlipperMessage *message);
    void serverFileRootsParser(QKlipperMessage *message);
    void serverTemperatureStoreParser(QKlipperMessage *message);
    void serverGCodeStoreParser(QKlipperMessage *message);
    void serverLogsRolloverParser(QKlipperMessage *message);
    void serverWebsocketIdParser(QKlipperMessage *message);
    void serverFilesMetadataParser(QKlipperMessage *message);
    void serverFilesDeleteParser(QKlipperMessage *message);
    void serverFilesMoveParser(QKlipperMessage *message);
    void serverFilesCopyParser(QKlipperMessage *message);
    void serverFilesListParser(QKlipperMessage *message);
    void serverDirectoryPostParser(QKlipperMessage *message);
    void serverDirectoryDeleteParser(QKlipperMessage *message);
    void serverWebcamListParser(QKlipperMessage *message);
    void serverWebcamCreateParser(QKlipperMessage *message);
    void serverWebcamDeleteParser(QKlipperMessage *message);
    void serverAnnouncementsListParser(QKlipperMessage *message);
    void serverAnnouncementsUpdateParser(QKlipperMessage *message);
    void serverAnnouncementDismissParser(QKlipperMessage *message);
    void serverJobQueueStatusParser(QKlipperMessage *message);
    void serverJobQueueStartParser(QKlipperMessage *message);
    void serverJobQueuePauseParser(QKlipperMessage *message);
    void serverJobQueueJumpParser(QKlipperMessage *message);
    void serverJobQueueAddParser(QKlipperMessage *message);
    void serverJobQueueDeleteParser(QKlipperMessage *message);

    void setConnectionState(ConnectionState connectionState);
    void resetConnectionState();

    void resetStartupSequence();

    void setStartupSequenceProgress(qreal startupSequenceProgress);
    void resetStartupSequenceProgress();

    void setStartupSequenceText(const QString &startupSequenceText);
    void resetStartupSequenceText();

    void generateParserMap();

    void setupNetworkAccessManager();

    void resetConnectionTimer();
    void startConnectionTimer();
    void stopConnectionTimer();
    void onRpcConnectionTimeout();

    void processError(QKlipperError *error);

private:

    //these methods return not found if they have not been setup in moonraker.cfg
    const static inline QStringList m_ignoreErrorOnStartup = QStringList {
        "machine.device_power.devices",
        "machine.wled.strips",
        "server.sensors.list"
    };

    QMap<qint32, QKlipperMessage*> m_messageMap;
    QQueue<QKlipperMessage*> m_messageOutbox;

    QMap<QString, ParserFunction> m_parserMap;
    QMap<QString, ParserFunction> m_actionMap;

    QQueue<StartupFunction> m_startupSequence;
    qint32                  m_startupSequenceCount = 0;
    qreal                   m_startupSequenceProgress = 0;
    QString                 m_startupSequenceText = 0;
    QString                 m_errorMessage;

    ConnectionState m_connectionState = Idle;

    QAbstractSocket *m_rpcUpdateSocket = nullptr;
    QByteArray m_rpcDataBuffer;
    QQueue<QByteArray> m_rpcResponseQueue;

    QKlipperPrinter *m_printer = nullptr;
    QKlipperSystem *m_system = nullptr;
    QKlipperServer *m_server = nullptr;

    QNetworkAccessManager *m_networkManager = nullptr;

    QTimer *m_rpcConnectionTimer = nullptr;
    qint16 m_rpcConnectionTimeoutValue = 10000; //in ms

    Q_PROPERTY(ConnectionState connectionState READ connectionState WRITE setConnectionState RESET resetConnectionState NOTIFY connectionStateChanged FINAL)
    Q_PROPERTY(qreal startupSequenceProgress READ startupSequenceProgress WRITE setStartupSequenceProgress RESET resetStartupSequenceProgress NOTIFY startupSequenceProgressChanged FINAL)
    Q_PROPERTY(QString startupSequenceText READ startupSequenceText WRITE setStartupSequenceText RESET resetStartupSequenceText NOTIFY startupSequenceTextChanged FINAL)
};

inline constexpr QKlipperConsole::ConnectionState operator|(QKlipperConsole::ConnectionState a, QKlipperConsole::ConnectionState b)
{
    return static_cast<QKlipperConsole::ConnectionState>(static_cast<unsigned int>(a) | static_cast<unsigned int>(b));
}

inline constexpr QKlipperConsole::ConnectionState operator&(QKlipperConsole::ConnectionState a, QKlipperConsole::ConnectionState b)
{
    return static_cast<QKlipperConsole::ConnectionState>(static_cast<unsigned int>(a) & static_cast<unsigned int>(b));
}

inline constexpr QKlipperConsole::ConnectionState operator^(QKlipperConsole::ConnectionState a, QKlipperConsole::ConnectionState b)
{
    return static_cast<QKlipperConsole::ConnectionState>(static_cast<unsigned int>(a) ^ static_cast<unsigned int>(b));
}

inline constexpr QKlipperConsole::ConnectionState operator~(QKlipperConsole::ConnectionState a)
{
    return static_cast<QKlipperConsole::ConnectionState>(~static_cast<unsigned int>(a));
}

inline constexpr QKlipperConsole::ConnectionState operator|=(QKlipperConsole::ConnectionState &a, QKlipperConsole::ConnectionState b)
{
    return a = static_cast<QKlipperConsole::ConnectionState>(static_cast<unsigned int>(a) | static_cast<unsigned int>(b));
}

inline constexpr QKlipperConsole::ConnectionState operator&=(QKlipperConsole::ConnectionState &a, QKlipperConsole::ConnectionState b)
{
    return a = static_cast<QKlipperConsole::ConnectionState>(static_cast<unsigned int>(a) & static_cast<unsigned int>(b));
}

inline constexpr QKlipperConsole::ConnectionState operator^=(QKlipperConsole::ConnectionState &a, QKlipperConsole::ConnectionState b)
{
    return a = static_cast<QKlipperConsole::ConnectionState>(static_cast<unsigned int>(a) ^ static_cast<unsigned int>(b));
}

#endif // QKLIPPERCONSOLE_H
