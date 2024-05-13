#include "qabstractklipperconsole.h"

#include "../printer.h"

QAbstractKlipperConsole::QAbstractKlipperConsole(Printer *printer, QObject *parent)
{
    _parserMap[QString("printer.info")] = (ParserFunction)&QAbstractKlipperConsole::on_printerInfo;
    _parserMap[QString("printer.objects.list")] = (ParserFunction)&QAbstractKlipperConsole::on_printerObjectsList;
    _parserMap[QString("printer.objects.subscribe")] = (ParserFunction)&QAbstractKlipperConsole::on_printerSubscribe;
    _parserMap[QString("notify_status_update")] = (ParserFunction)&QAbstractKlipperConsole::on_printerSubscribe;
    _parserMap[QString("printer.print.start")] = (ParserFunction)&QAbstractKlipperConsole::on_startPrint;
    _parserMap[QString("printer.print.pause")] = (ParserFunction)&QAbstractKlipperConsole::on_pausePrint;
    _parserMap[QString("printer.print.resume")] = (ParserFunction)&QAbstractKlipperConsole::on_resumePrint;
    _parserMap[QString("printer.print.cancel")] = (ParserFunction)&QAbstractKlipperConsole::on_cancelPrint;
    _parserMap[QString("printer.emergency_stop")] = (ParserFunction)&QAbstractKlipperConsole::on_printerEmergencyStop;
    _parserMap[QString("printer.query_endstops.status")] = (ParserFunction)&QAbstractKlipperConsole::on_printerQueryEndstops;

    _parserMap[QString("server.connection.identify")] = (ParserFunction)&QAbstractKlipperConsole::on_clientIdentifier;
    _parserMap[QString("server.info")] = (ParserFunction)&QAbstractKlipperConsole::on_serverInfo;
    _parserMap[QString("server.files.post_directory")] = (ParserFunction)&QAbstractKlipperConsole::on_createDirectory;
    _parserMap[QString("server.files.delete_directory")] = (ParserFunction)&QAbstractKlipperConsole::on_deleteDirectory;
    _parserMap[QString("server.files.roots")] = (ParserFunction)&QAbstractKlipperConsole::on_serverFileRoots;
    _parserMap[QString("server.files.get_directory")] = (ParserFunction)&QAbstractKlipperConsole::on_getFileList;
    _parserMap[QString("server.temperature_store")] = (ParserFunction)&QAbstractKlipperConsole::on_serverTemperatureStore;
    _parserMap[QString("server.websocket.id")] = (ParserFunction)&QAbstractKlipperConsole::on_serverWebsocketId;
    _parserMap[QString("server.logs.rollover")] = (ParserFunction)&QAbstractKlipperConsole::on_serverLogsRollover;
    _parserMap[QString("server.files.list")] = (ParserFunction)&QAbstractKlipperConsole::on_getFileList;
    _parserMap[QString("server.files.metadata")] = (ParserFunction)&QAbstractKlipperConsole::on_serverFilesMetadata;
    _parserMap[QString("server.webcams.list")] = (ParserFunction)&QAbstractKlipperConsole::on_serverWebcamList;
    _parserMap[QString("server.webcams.post_item")] = (ParserFunction)&QAbstractKlipperConsole::on_serverWebcamCreate;
    _parserMap[QString("server.webcams.delete_item")] = (ParserFunction)&QAbstractKlipperConsole::on_serverWebcamDelete;
    _parserMap[QString("server.announcements.list")] = (ParserFunction)&QAbstractKlipperConsole::on_serverAnnouncementsList;
    _parserMap[QString("server.announcements.update")] = (ParserFunction)&QAbstractKlipperConsole::on_serverAnnouncementsUpdate;

    //Job queue management
    _parserMap[QString("server.job_queue.status")] = (ParserFunction)&QAbstractKlipperConsole::on_serverJobQueueStatus;
    _parserMap[QString("server.job_queue.post_job")] = (ParserFunction)&QAbstractKlipperConsole::on_serverJobQueueStatus;
    _parserMap[QString("server.job_queue.pause")] = (ParserFunction)&QAbstractKlipperConsole::on_serverJobQueueStatus;
    _parserMap[QString("server.job_queue.delete_job")] = (ParserFunction)&QAbstractKlipperConsole::on_serverJobQueueStatus;
    _parserMap[QString("server.job_queue.start")] = (ParserFunction)&QAbstractKlipperConsole::on_serverJobQueueStatus;
    _parserMap[QString("server.job_queue.jump")] = (ParserFunction)&QAbstractKlipperConsole::on_serverJobQueueStatus;

    _parserMap[QString("machine.system_info")] = (ParserFunction)&QAbstractKlipperConsole::on_machineSystemInfo;
    _parserMap[QString("machine.services.restart")] = (ParserFunction)&QAbstractKlipperConsole::on_machineServiceRestart;
    _parserMap[QString("machine.services.stop")] = (ParserFunction)&QAbstractKlipperConsole::on_machineServiceStop;
    _parserMap[QString("machine.services.start")] = (ParserFunction)&QAbstractKlipperConsole::on_machineServiceStart;
    _parserMap[QString("machine.proc_stats")] = (ParserFunction)&QAbstractKlipperConsole::on_machineProcStats;
    _parserMap[QString("notify_proc_stat_update")] = (ParserFunction)&QAbstractKlipperConsole::on_machineProcStats;
    _parserMap[QString("machine.peripherals.usb")] = (ParserFunction)&QAbstractKlipperConsole::on_machinePeripheralsUSB;
    _parserMap[QString("machine.peripherals.serial")] = (ParserFunction)&QAbstractKlipperConsole::on_machinePeripheralsSerial;
    _parserMap[QString("machine.peripherals.video")] = (ParserFunction)&QAbstractKlipperConsole::on_machinePeripheralsVideo;
    _parserMap[QString("machine.peripherals.canbus")] = (ParserFunction)&QAbstractKlipperConsole::on_machinePeripheralsCanbus;
    _parserMap[QString("machine.update.status")] = (ParserFunction)&QAbstractKlipperConsole::on_machineUpdateStatus;
    _parserMap[QString("machine.update.full")] = (ParserFunction)&QAbstractKlipperConsole::on_machineUpdateFull;
    _parserMap[QString("machine.update.moonraker")] = (ParserFunction)&QAbstractKlipperConsole::on_machineUpdateMoonraker;
    _parserMap[QString("machine.update.klipper")] = (ParserFunction)&QAbstractKlipperConsole::on_machineUpdateKlipper;
    _parserMap[QString("machine.update.client")] = (ParserFunction)&QAbstractKlipperConsole::on_machineUpdateClient;
    _parserMap[QString("machine.update.system")] = (ParserFunction)&QAbstractKlipperConsole::on_machineUpdateSystem;

    _parserMap[QString("access.login")] = (ParserFunction)&QAbstractKlipperConsole::on_accessLogin;
    _parserMap[QString("access.logout")] = (ParserFunction)&QAbstractKlipperConsole::on_accessLogout;
    _parserMap[QString("access.get_user")] = (ParserFunction)&QAbstractKlipperConsole::on_accessGetUser;
    _parserMap[QString("access.post_user")] = (ParserFunction)&QAbstractKlipperConsole::on_accessCreateUser;
    _parserMap[QString("access.delete_user")] = (ParserFunction)&QAbstractKlipperConsole::on_accessDeleteUser;
    _parserMap[QString("access.users.list")] = (ParserFunction)&QAbstractKlipperConsole::on_accessUsersList;
    _parserMap[QString("access.user.password")] = (ParserFunction)&QAbstractKlipperConsole::on_accessUserPasswordReset;

    //Startup commands to get base information
    _startupSequence.enqueue((StartupFunction)&QAbstractKlipperConsole::clientIdentifier);
    _startupSequence.enqueue((StartupFunction)&QAbstractKlipperConsole::serverInfo);
    _startupSequence.enqueue((StartupFunction)&QAbstractKlipperConsole::machineSystemInfo);
    _startupSequence.enqueue((StartupFunction)&QAbstractKlipperConsole::machineProcStats);
    _startupSequence.enqueue((StartupFunction)&QAbstractKlipperConsole::machinePeripheralsUSB);
    _startupSequence.enqueue((StartupFunction)&QAbstractKlipperConsole::machinePeripheralsSerial);
    _startupSequence.enqueue((StartupFunction)&QAbstractKlipperConsole::machineUpdateStatus);
    _startupSequence.enqueue((StartupFunction)&QAbstractKlipperConsole::serverConfig);
    _startupSequence.enqueue((StartupFunction)&QAbstractKlipperConsole::serverFileRoots);
    _startupSequence.enqueue((StartupFunction)&QAbstractKlipperConsole::serverWebcamList);
    _startupSequence.enqueue((StartupFunction)&QAbstractKlipperConsole::serverAnnouncementsUpdate);
    _startupSequence.enqueue((StartupFunction)&QAbstractKlipperConsole::printerInfo);
    _startupSequence.enqueue((StartupFunction)&QAbstractKlipperConsole::printerObjectsList);
    _startupSequence.enqueue((StartupFunction)&QAbstractKlipperConsole::printerSubscribe);
}

QAbstractKlipperConsole::~QAbstractKlipperConsole()
{

}

Printer *QAbstractKlipperConsole::printer() const
{
    return _printer;
}

void QAbstractKlipperConsole::setPrinter(Printer *printer)
{
    _printer = printer;
}

QString QAbstractKlipperConsole::moonrakerLocation() const
{
    return _moonrakerLocation;
}

bool QAbstractKlipperConsole::isMoonrakerConnected() const
{
    return _isMoonrakerConnected;
}

bool QAbstractKlipperConsole::isKlipperConnected() const
{
    return _isKlipperConnected;
}

bool QAbstractKlipperConsole::isConnected() const
{
    return ((Connected & _state) == Connected);
}

bool QAbstractKlipperConsole::hasState(ConsoleState state)
{
    return ((state & _state) == state);
}

void QAbstractKlipperConsole::addState(QAbstractKlipperConsole::ConsoleState state)
{
    _state = (ConsoleState)(_state | state);

    if(hasState(Connected))
        removeState((ConsoleState)(Offline | Connecting));

    if(hasState(Offline))
        removeState((ConsoleState)(Connected | Connecting));
}

void QAbstractKlipperConsole::removeState(ConsoleState state)
{
    _state = (ConsoleState)(_state & (~state));
}

QGCodeCommandList QAbstractKlipperConsole::gcodeCommands() const
{
    return _gcodeCommands;
}

QStringList QAbstractKlipperConsole::moonrakerFailedComponents() const
{
    return _moonrakerFailedComponents;
}

QStringList QAbstractKlipperConsole::moonrakerComponents() const
{
    return _moonrakerComponents;
}

QGCodeMacroList QAbstractKlipperConsole::gcodeMacros() const
{
    return _gcodeMacros;
}

void QAbstractKlipperConsole::setMoonrakerLocation(const QString &moonrakerLocation)
{
    _moonrakerLocation = moonrakerLocation;
}

QAbstractSocket *QAbstractKlipperConsole::moonrakerSocket() const
{
    return _moonrakerSocket;
}

void QLocalKlipperConsole::sendCommand(QString command, KlipperMessage::MessageOrigin origin)
{
    KlipperMessage message;
    QJsonObject messageObject = message.document();
    messageObject["method"] = command;
    message.setDocument(messageObject);
    message.origin = origin;

    sendCommand(message);
}

void QAbstractKlipperConsole::getFileList(QString directory)
{
    KlipperMessage message;
    QJsonObject messageObject = message.document();
    QJsonObject paramsObject;

    paramsObject["path"] = directory;

    paramsObject["extended"] = true;
    messageObject["method"] = "server.files.get_directory";
    messageObject["params"] = paramsObject;
    message.setDocument(messageObject);

    sendCommand(message);
}

void QAbstractKlipperConsole::deleteFile(QString file)
{
    KlipperMessage message;
    QJsonObject messageObject = message.document();
    QJsonObject paramsObject;

    messageObject["method"] = "server.files.delete_file";

    paramsObject["path"] = file;
    messageObject["params"] = paramsObject;

    message.setDocument(messageObject);

    sendCommand(message);
}

void QAbstractKlipperConsole::deleteFile(KlipperFile file)
{

    KlipperMessage message;
    QJsonObject messageObject = message.document();
    QJsonObject paramsObject;

    messageObject["method"] = "server.files.delete_file";

    paramsObject["path"] = file.fileLocation();
    messageObject["params"] = paramsObject;

    message.setDocument(messageObject);

    sendCommand(message);
}

void QAbstractKlipperConsole::moveFile(QString source, QString destination)
{
    KlipperMessage message;
    QJsonObject messageObject = message.document();
    QJsonObject paramsObject;

    messageObject["method"] = "server.files.move";

    paramsObject["source"] = source;
    paramsObject["dest"] = destination;
    messageObject["params"] = paramsObject;

    message.setDocument(messageObject);

    sendCommand(message);
}

void QAbstractKlipperConsole::copyFile(QString source, QString destination)
{
    KlipperMessage message;
    QJsonObject messageObject = message.document();
    QJsonObject paramsObject;

    messageObject["method"] = "server.files.copy";

    paramsObject["source"] = source;
    paramsObject["dest"] = destination;
    messageObject["params"] = paramsObject;

    message.setDocument(messageObject);

    sendCommand(message);
}

void QAbstractKlipperConsole::createDirectory(QString directory)
{
    KlipperMessage message;
    QJsonObject messageObject = message.document();
    QJsonObject paramsObject;

    messageObject["method"] = "server.files.post_directory";
    paramsObject["path"] = directory;
    messageObject["params"] = paramsObject;

    message.setDocument(messageObject);

    sendCommand(message);
}

void QAbstractKlipperConsole::deleteDirectory(QString directory)
{
    KlipperMessage message;
    QJsonObject messageObject = message.document();
    QJsonObject paramsObject;

    paramsObject["path"] = directory;
    paramsObject["force"] = true;

    messageObject["method"] = "server.files.delete_directory";
    messageObject["params"] = paramsObject;
    message.setDocument(messageObject);

    sendCommand(message);
}

void QAbstractKlipperConsole::startPrint(QString file)
{
    KlipperMessage message;
    QJsonObject messageObject = message.document();
    QJsonObject paramsObject;

    messageObject["method"] = "printer.print.start";

    paramsObject["filename"] = file;
    messageObject["params"] = paramsObject;

    message.setDocument(messageObject);

    _waitForOkId = message.id;

    sendCommand(message);
}

void QAbstractKlipperConsole::pausePrint()
{
    KlipperMessage message;
    QJsonObject messageObject = message.document();

    messageObject["method"] = "printer.print.pause";

    message.setDocument(messageObject);

    _waitForOkId = message.id;

    sendCommand(message);
}

void QAbstractKlipperConsole::resumePrint()
{
    KlipperMessage message;
    QJsonObject messageObject = message.document();

    messageObject["method"] = "printer.print.resume";

    message.setDocument(messageObject);

    _waitForOkId = message.id;

    sendCommand(message);
}

void QAbstractKlipperConsole::cancelPrint()
{
    KlipperMessage message;
    QJsonObject messageObject = message.document();

    messageObject["method"] = "printer.print.cancel";

    message.setDocument(messageObject);

    _waitForOkId = message.id;

    sendCommand(message);
}

void QAbstractKlipperConsole::machineShutdown()
{
    KlipperMessage message;
    QJsonObject messageObject = message.document();

    messageObject["method"] = "machine.shutdown";

    message.setDocument(messageObject);

    sendCommand(message);
}

void QAbstractKlipperConsole::machineReboot()
{
    KlipperMessage message;
    QJsonObject messageObject = message.document();

    messageObject["method"] = "machine.reboot";

    message.setDocument(messageObject);

    sendCommand(message);
}

void QAbstractKlipperConsole::machineSystemInfo()
{
    KlipperMessage message;
    QJsonObject messageObject = message.document();

    messageObject["method"] = "machine.system_info";

    message.setDocument(messageObject);

    sendCommand(message);
}

void QAbstractKlipperConsole::machineServiceRestart(QString service)
{

    KlipperMessage message;
    QJsonObject messageObject = message.document();
    QJsonObject paramsObject;

    messageObject["method"] = "machine.services.restart";

    paramsObject["service"] = service;
    messageObject["params"] = paramsObject;

    message.setDocument(messageObject);

    _waitForOkId = message.id;

    sendCommand(message);
}

void QAbstractKlipperConsole::machineServiceStop(QString service)
{
    KlipperMessage message;
    QJsonObject messageObject = message.document();
    QJsonObject paramsObject;

    paramsObject["service"] = service;
    messageObject["params"] = paramsObject;
    messageObject["method"] = "machine.services.stop";

    message.setDocument(messageObject);

    _waitForOkId = message.id;

    sendCommand(message);
}

void QAbstractKlipperConsole::machineServiceStart(QString service)
{
    KlipperMessage message;
    QJsonObject messageObject = message.document();
    QJsonObject paramsObject;

    paramsObject["service"] = service;
    messageObject["params"] = paramsObject;
    messageObject["method"] = "machine.proc_stats";

    message.setDocument(messageObject);

    _waitForOkId = message.id;

    sendCommand(message);
}

void QAbstractKlipperConsole::machinePeripheralsUSB()
{
    KlipperMessage message;
    QJsonObject messageObject = message.document();
    QJsonObject paramsObject;

    messageObject["params"] = paramsObject;
    messageObject["method"] = "machine.peripherals.usb";

    message.setDocument(messageObject);

    sendCommand(message);
}

void QAbstractKlipperConsole::machinePeripheralsSerial()
{

    KlipperMessage message;
    QJsonObject messageObject = message.document();
    QJsonObject paramsObject;

    messageObject["params"] = paramsObject;
    messageObject["method"] = "machine.peripherals.serial";

    message.setDocument(messageObject);

    sendCommand(message);
}

void QAbstractKlipperConsole::machinePeripheralsVideo()
{
    KlipperMessage message;
    QJsonObject messageObject = message.document();
    QJsonObject paramsObject;

    messageObject["params"] = paramsObject;
    messageObject["method"] = "machine.peripherals.video";

    message.setDocument(messageObject);

    sendCommand(message);
}

void QAbstractKlipperConsole::machinePeripheralsCanbus(qint32 canBus)
{
    KlipperMessage message;
    QJsonObject messageObject = message.document();
    QJsonObject paramsObject;

    QString canBusName = QString("can") + QString::number(canBus);

    paramsObject["interface"] = canBusName;
    messageObject["params"] = paramsObject;
    messageObject["method"] = "machine.peripherals.canbus";

    message.setDocument(messageObject);

    sendCommand(message);
}

void QAbstractKlipperConsole::machineProcStats()
{
    KlipperMessage message;
    QJsonObject messageObject = message.document();
    QJsonObject paramsObject;

    messageObject["params"] = paramsObject;
    messageObject["method"] = "machine.services.start";

    message.setDocument(messageObject);

    sendCommand(message);
}

void QAbstractKlipperConsole::machineUpdateStatus()
{
    QJsonObject paramsObject;
    paramsObject["refresh"] = true;

    QJsonObject messageObject;
    messageObject["method"] = "machine.update.status";
    messageObject["params"] = paramsObject;

    KlipperMessage message;
    message.setDocument(messageObject);

    sendCommand(message);
}

void QAbstractKlipperConsole::machineUpdateFull()
{
    //Generate the root json object
    QJsonObject messageObject;
    messageObject["method"] = "machine.update.full";

    //Add it as the message document to be converted to RPC later
    KlipperMessage message;
    message.setDocument(messageObject);

    //Method only returns ok
    _waitForOkId = message.id;

    sendCommand(message);
}

void QAbstractKlipperConsole::machineUpdateMoonraker()
{
    //Generate the root json object
    QJsonObject messageObject;
    messageObject["method"] = "machine.update.moonraker";

    //Add it as the message document to be converted to RPC later
    KlipperMessage message;
    message.setDocument(messageObject);

    //Method only returns ok
    _waitForOkId = message.id;

    sendCommand(message);
}

void QAbstractKlipperConsole::machineUpdateKlipper()
{
    //Generate the root json object
    QJsonObject messageObject;
    messageObject["method"] = "machine.update.klipper";

    //Add it as the message document to be converted to RPC later
    KlipperMessage message;
    message.setDocument(messageObject);

    //Method only returns ok
    _waitForOkId = message.id;

    sendCommand(message);
}

void QAbstractKlipperConsole::machineUpdateClient(QString client)
{
    //Generate params json
    QJsonObject paramsObject;
    paramsObject["client_name"] = client;

    //Generate the root json object
    QJsonObject messageObject;
    messageObject["method"] = "machine.update.client";
    messageObject["params"] = paramsObject;

    //Add it as the message document to be converted to RPC later
    KlipperMessage message;
    message.setDocument(messageObject);

    //Method only returns ok
    _waitForOkId = message.id;

    sendCommand(message);
}

void QAbstractKlipperConsole::machineUpdateSystem()
{

    //Generate the root json object
    QJsonObject messageObject;
    messageObject["method"] = "machine.update.system";

    //Add it as the message document to be converted to RPC later
    KlipperMessage message;
    message.setDocument(messageObject);

    //Method only returns ok
    _waitForOkId = message.id;

    sendCommand(message);
}

void QAbstractKlipperConsole::machineUpdateRecover(QString name, bool hardRecover)
{
    //Generate params json
    QJsonObject paramsObject;
    paramsObject["name"] = name;
    paramsObject["hard"] = hardRecover;

    //Generate the root json object
    QJsonObject messageObject;
    messageObject["method"] = "machine.update.recover";
    messageObject["params"] = paramsObject;

    //Add it as the message document to be converted to RPC later
    KlipperMessage message;
    message.setDocument(messageObject);

    //Method only returns ok
    _waitForOkId = message.id;

    sendCommand(message);
}

void QAbstractKlipperConsole::machineUpdateRollback(QString name)
{
    //Generate params json
    QJsonObject paramsObject;
    paramsObject["name"] = name;

    //Generate the root json object
    QJsonObject messageObject;
    messageObject["method"] = "machine.update.rollback";
    messageObject["params"] = paramsObject;

    //Add it as the message document to be converted to RPC later
    KlipperMessage message;
    message.setDocument(messageObject);

    //Method only returns ok
    _waitForOkId = message.id;

    sendCommand(message);
}

void QAbstractKlipperConsole::sendGcode(QString gcode)
{
    KlipperMessage message;
    QJsonObject messageObject = message.document();
    QJsonObject paramsObject;

    paramsObject["script"] = gcode;
    messageObject["params"] = paramsObject;
    messageObject["method"] = "printer.gcode.script";

    message.setDocument(messageObject);

    _waitForOkId = message.id;

    sendCommand(message);
}

void QAbstractKlipperConsole::printerInfo()
{

    KlipperMessage message;
    QJsonObject messageObject = message.document();
    QJsonObject paramsObject;

    messageObject["method"] = "printer.info";

    message.setDocument(messageObject);

    sendCommand(message);
}

void QAbstractKlipperConsole::restartKlipper()
{
    KlipperMessage message;
    QJsonObject messageObject = message.document();
    QJsonObject paramsObject;

    messageObject["method"] = "printer.restart";

    message.setDocument(messageObject);

    sendCommand(message);
}

void QAbstractKlipperConsole::restartFirmware()
{
    KlipperMessage message;
    QJsonObject messageObject = message.document();
    QJsonObject paramsObject;

    messageObject["method"] = "printer.firmware_restart";

    message.setDocument(messageObject);

    sendCommand(message);
}

void QAbstractKlipperConsole::printerObjectsList()
{
    KlipperMessage message;
    QJsonObject messageObject = message.document();
    QJsonObject paramsObject;

    messageObject["method"] = "printer.objects.list";

    message.setDocument(messageObject);

    sendCommand(message);
}

void QAbstractKlipperConsole::printerSubscribe()
{
    KlipperMessage message;
    QJsonObject messageObject = message.document();
    QJsonObject paramsObject;
    QJsonObject objectArray;

    //Leave each object null to receive the full report
    foreach(QString object, _subscriptionObjects)
        objectArray[object];

    paramsObject["objects"] = objectArray;

    messageObject["method"] = "printer.objects.subscribe";
    messageObject["params"] = paramsObject;

    message.setDocument(messageObject);

    sendCommand(message);
}

void QAbstractKlipperConsole::printerEmergencyStop()
{
    KlipperMessage message;
    QJsonObject messageObject = message.document();
    QJsonObject paramsObject;

    messageObject["method"] = "printer.emergency_stop";

    message.setDocument(messageObject);

    sendCommand(message);
}

void QAbstractKlipperConsole::printerQueryEndstops()
{
    KlipperMessage message;
    QJsonObject messageObject = message.document();
    QJsonObject paramsObject;

    messageObject["method"] = "printer.query_endstops.status";

    message.setDocument(messageObject);

    sendCommand(message);
}

void QAbstractKlipperConsole::serverInfo()
{
    KlipperMessage message;
    QJsonObject messageObject = message.document();
    QJsonObject paramsObject;

    messageObject["method"] = "server.info";

    message.setDocument(messageObject);

    sendCommand(message);
}

void QAbstractKlipperConsole::serverConfig()
{
    KlipperMessage message;
    QJsonObject messageObject = message.document();
    QJsonObject paramsObject;

    messageObject["method"] = "server.config";

    message.setDocument(messageObject);

    sendCommand(message);
}

void QAbstractKlipperConsole::serverFileRoots()
{
    KlipperMessage message;
    QJsonObject messageObject = message.document();
    QJsonObject paramsObject;

    messageObject["method"] = "server.files.roots";

    message.setDocument(messageObject);

    sendCommand(message);
}

void QAbstractKlipperConsole::serverFilesMetadata(QString fileName)
{
    KlipperMessage message;
    QJsonObject messageObject = message.document();
    QJsonObject paramsObject;

    paramsObject["filename"] = fileName;
    messageObject["params"] = paramsObject;
    messageObject["method"] = "server.files.metadata";

    message.setDocument(messageObject);

    sendCommand(message);
}

void QAbstractKlipperConsole::serverTemperatureStore()
{
    KlipperMessage message;
    QJsonObject messageObject = message.document();
    QJsonObject paramsObject;

    paramsObject["include_monitors"] = false;
    messageObject["method"] = "server.temperature_store";
    messageObject["params"] = paramsObject;

    message.setDocument(messageObject);

    sendCommand(message);
}

void QAbstractKlipperConsole::serverGcodeStore()
{
    KlipperMessage message;
    QJsonObject messageObject = message.document();
    QJsonObject paramsObject;

    paramsObject["include_monitors"] = false;
    messageObject["method"] = "server.gcode_store";
    messageObject["params"] = paramsObject;

    message.setDocument(messageObject);

    sendCommand(message);
}

void QAbstractKlipperConsole::serverLogsRollover()
{
    KlipperMessage message;
    QJsonObject messageObject = message.document();
    messageObject["method"] = "server.logs.rollover";

    message.setDocument(messageObject);

    sendCommand(message);
}

void QAbstractKlipperConsole::serverWebsocketId()
{
    KlipperMessage message;
    QJsonObject messageObject = message.document();
    messageObject["method"] = "server.websocket.id";

    message.setDocument(messageObject);

    sendCommand(message);
}

void QAbstractKlipperConsole::serverWebcamList()
{
    KlipperMessage message;
    QJsonObject messageObject = message.document();
    messageObject["method"] = "server.webcams.list";

    message.setDocument(messageObject);

    sendCommand(message);
}

void QAbstractKlipperConsole::serverWebcamCreate(System::Webcam webcam)
{
    KlipperMessage message;
    QJsonObject messageObject = message.document();
    QJsonObject paramsObject;

    paramsObject["name"] = webcam.name;
    paramsObject["location"] = webcam.location;
    paramsObject["service"] = webcam.service;
    paramsObject["enabled"] = webcam.enabled;
    paramsObject["icon"] = webcam.iconString;
    paramsObject["target_fps"] = webcam.targetFps;
    paramsObject["target_fps_idle"] = webcam.targetFpsIdle;
    paramsObject["stream_url"] = webcam.streamUrl;
    paramsObject["snapshot_url"] = webcam.snapshotUrl;
    paramsObject["flip_horizontal"] = webcam.flipHorizontal;
    paramsObject["flip_vertical"] = webcam.flipVertical;
    paramsObject["rotation"] = webcam.rotation;
    paramsObject["aspect_ratio"] = webcam.aspectRatio;
    paramsObject["source"] = webcam.source;

    messageObject["method"] = "server.webcams.post_item";
    messageObject["params"] = paramsObject;

    message.setDocument(messageObject);

    sendCommand(message);
}

void QAbstractKlipperConsole::serverWebcamUpdate(System::Webcam webcam)
{
    KlipperMessage message;
    QJsonObject messageObject = message.document();
    QJsonObject paramsObject;

    paramsObject["name"] = webcam.name;
    paramsObject["location"] = webcam.location;
    paramsObject["service"] = webcam.service;
    paramsObject["enabled"] = webcam.enabled;
    paramsObject["icon"] = webcam.iconString;
    paramsObject["target_fps"] = webcam.targetFps;
    paramsObject["target_fps_idle"] = webcam.targetFpsIdle;
    paramsObject["stream_url"] = webcam.streamUrl;
    paramsObject["snapshot_url"] = webcam.snapshotUrl;
    paramsObject["flip_horizontal"] = webcam.flipHorizontal;
    paramsObject["flip_vertical"] = webcam.flipVertical;
    paramsObject["rotation"] = webcam.rotation;
    paramsObject["aspect_ratio"] = webcam.aspectRatio;
    paramsObject["source"] = webcam.source;
    paramsObject["uid"] = webcam.uid;

    messageObject["method"] = "server.webcams.post_item";
    messageObject["params"] = paramsObject;

    message.setDocument(messageObject);

    sendCommand(message);
}

void QAbstractKlipperConsole::serverWebcamDelete(System::Webcam webcam)
{
    KlipperMessage message;
    QJsonObject messageObject = message.document();
    QJsonObject paramsObject;

    paramsObject["uid"] = webcam.uid;

    messageObject["method"] = "server.webcams.delete_item";
    messageObject["params"] = paramsObject;

    message.setDocument(messageObject);

    sendCommand(message);
}

void QAbstractKlipperConsole::serverAnnouncementsList(bool includeDismissed)
{
    KlipperMessage message;
    QJsonObject messageObject = message.document();
    QJsonObject paramsObject;

    paramsObject["include_dismissed"] = includeDismissed;

    messageObject["method"] = "server.announcements.list";
    messageObject["params"] = paramsObject;

    message.setDocument(messageObject);

    sendCommand(message);
}

void QAbstractKlipperConsole::serverAnnouncementsUpdate()
{
    KlipperMessage message;
    QJsonObject messageObject = message.document();

    messageObject["method"] = "server.announcements.update";

    message.setDocument(messageObject);

    sendCommand(message);
}

void QAbstractKlipperConsole::serverAnnouncementDismiss(QString entryId, qint64 waketime)
{
    KlipperMessage message;
    QJsonObject messageObject = message.document();
    QJsonObject paramsObject;

    paramsObject["entry_id"] = entryId;

    if(waketime > 0)
        paramsObject["wake_time"] = waketime;

    messageObject["method"] = "server.announcements.dismiss";
    messageObject["params"] = paramsObject;

    message.setDocument(messageObject);

    sendCommand(message);
}

void QAbstractKlipperConsole::serverJobQueueStatus()
{
    KlipperMessage message;
    QJsonObject messageObject = message.document();

    messageObject["method"] = "server.job_queue.status";

    message.setDocument(messageObject);

    sendCommand(message);
}

void QAbstractKlipperConsole::serverJobQueueStart()
{
    QJsonObject messageObject;
    messageObject["method"] = "server.job_queue.start";

    KlipperMessage message;
    message.setDocument(messageObject);

    sendCommand(message);
}

void QAbstractKlipperConsole::serverJobQueuePause()
{
    QJsonObject messageObject;
    messageObject["method"] = "server.job_queue.pause";

    KlipperMessage message;
    message.setDocument(messageObject);

    sendCommand(message);
}

void QAbstractKlipperConsole::serverJobQueueAdd(QStringList filenames)
{
    QJsonArray paramsArray;
    paramsArray = QJsonArray::fromStringList(filenames);

    QJsonObject paramsObject;
    paramsObject["filenames"] = paramsArray;

    QJsonObject messageObject;
    messageObject["method"] = "server.job_queue.post_job";
    messageObject["params"] = paramsObject;

    KlipperMessage message;
    message.setDocument(messageObject);

    sendCommand(message);
}

void QAbstractKlipperConsole::serverJobQueueJump(QString id)
{
    QJsonObject paramsObject;
    paramsObject["job_id"] = id;

    QJsonObject messageObject;
    messageObject["method"] = "server.job_queue.jump";
    messageObject["params"] = paramsObject;

    KlipperMessage message;
    message.setDocument(messageObject);

    sendCommand(message);
}

void QAbstractKlipperConsole::serverJobQueueDelete(QStringList ids)
{
    QJsonArray paramsArray;
    paramsArray = QJsonArray::fromStringList(ids);

    QJsonObject paramsObject;
    paramsObject["job_ids"] = paramsArray;

    QJsonObject messageObject;
    messageObject["method"] = "server.job_queue.delete_job";
    messageObject["params"] = paramsObject;

    KlipperMessage message;
    message.setDocument(messageObject);

    sendCommand(message);
}

void QAbstractKlipperConsole::clientIdentifier()
{
    KlipperMessage message;
    QJsonObject messageObject = message.document();
    QJsonObject paramsObject;

    paramsObject["client_name"] = "FLO Beta";
    paramsObject["version"] = "0.0.1";
    paramsObject["type"] = "other";
    paramsObject["url"] = "n/a";

    messageObject["method"] = "server.connection.identify";
    messageObject["params"] = paramsObject;

    message.setDocument(messageObject);

    sendCommand(message);
}

void QAbstractKlipperConsole::accessLogin(QString username, QString password, QString source)
{
    KlipperMessage message;
    QJsonObject messageObject = message.document();
    QJsonObject paramsObject;

    paramsObject["username"] = username;
    paramsObject["password"] = password;
    paramsObject["source"] = source;

    messageObject["params"] = paramsObject;
    messageObject["method"] = "access.login";

    message.setDocument(messageObject);

    sendCommand(message);
}

void QAbstractKlipperConsole::accessLogout()
{
    KlipperMessage message;
    QJsonObject messageObject = message.document();

    messageObject["method"] = "access.logout";

    message.setDocument(messageObject);

    sendCommand(message);
}

void QAbstractKlipperConsole::accessGetUser()
{
    KlipperMessage message;
    QJsonObject messageObject = message.document();

    messageObject["method"] = "access.get_user";

    message.setDocument(messageObject);

    sendCommand(message);
}

void QAbstractKlipperConsole::accessCreateUser(QString username, QString password)
{
    KlipperMessage message;
    QJsonObject messageObject = message.document();
    QJsonObject paramsObject;

    paramsObject["username"] = username;
    paramsObject["password"] = password;

    messageObject["params"] = paramsObject;
    messageObject["method"] = "access.post_user";

    message.setDocument(messageObject);

    sendCommand(message);
}

void QAbstractKlipperConsole::accessDeleteUser(QString username)
{
    KlipperMessage message;
    QJsonObject messageObject = message.document();
    QJsonObject paramsObject;

    paramsObject["username"] = username;

    messageObject["params"] = paramsObject;
    messageObject["method"] = "access.delete_user";

    message.setDocument(messageObject);

    sendCommand(message);
}

void QAbstractKlipperConsole::accessUsersList()
{
    KlipperMessage message;
    QJsonObject messageObject = message.document();

    messageObject["method"] = "access.users.list";

    message.setDocument(messageObject);

    sendCommand(message);
}

void QAbstractKlipperConsole::accessUserPasswordReset(QString password, QString newPassword)
{
    KlipperMessage message;
    QJsonObject messageObject = message.document();
    QJsonObject paramsObject;

    paramsObject["new_password"] = newPassword;
    paramsObject["password"] = password;

    messageObject["params"] = paramsObject;
    messageObject["method"] = "access.user.password";

    message.setDocument(messageObject);

    sendCommand(message);
}

QAbstractKlipperConsole::ConnectionLocation QAbstractKlipperConsole::connectionLoaction() const
{

}

void QAbstractKlipperConsole::setConnectionLoaction(ConnectionLocation connectionLoaction)
{

}

void QAbstractKlipperConsole::setMoonrakerSocket(QAbstractSocket *moonrakerSocket)
{
    _moonrakerSocket = moonrakerSocket;

    connect(_moonrakerSocket, SIGNAL(readyRead()), this, SLOT(on_moonrakerSocket_readyRead()));
}

void QAbstractKlipperConsole::on_moonrakerSocket_readyRead()
{
    if(_moonrakerSocket->isOpen())
    {
        while(_moonrakerSocket->bytesAvailable() > 0)
        {
            QByteArray incoming = _moonrakerSocket->readAll();
            _dataBuffer += incoming;
        }
    }

    QString okPattern;
    okPattern = QString("[") + QString(_eof) + QString("|][o|O][k|K]");

    QRegularExpression okExpression(okPattern);
    QRegularExpressionMatch okMatch = okExpression.match(QString::fromUtf8(_dataBuffer));

    if(okMatch.hasMatch())
    {
        QString ok = okMatch.captured();

        if(ok.contains(_eof))
            ok.remove(_eof);

        _dataBuffer.replace(ok.toStdString(), "");

        _messageDataQueue.enqueue("ok");
    }
    else if(_dataBuffer.contains((char)0x03))
    {
        int index = _dataBuffer.indexOf((char)0x03);
        QByteArray responseData = _dataBuffer.mid(0, index + 1);
        _dataBuffer.remove(0, index + 1);

        if(responseData.endsWith((char)0x03))
            responseData.remove(responseData.length() - 1, 1);

        _messageDataQueue.enqueue(responseData);

        on_messageReady();
    }
}

void QAbstractKlipperConsole::on_messageReady()
{
    if(_messageDataQueue.isEmpty())
        return;

    QByteArray responseData = _messageDataQueue.dequeue();
    QJsonParseError responseDocumentError;
    QJsonDocument responseDocument(QJsonDocument::fromJson(responseData, &responseDocumentError));
    KlipperMessage origin;

    if(responseDocumentError.error != QJsonParseError::NoError)
    {
        sendError("Invalid response from local socket");
        return;
    }

    KlipperResponse response;
    response.rootObject = responseDocument.object();

    if(responseData == QByteArray("ok"))
    {
        origin = _klipperMessageBuffer[response["id"].toInt()];
        response["request"] = origin.document();
        response["method"] = origin["method"];
        response.origin = (KlipperResponse::ResponseOrigin)_klipperMessageBuffer[response["id"].toInt()].origin;
    }
    else
    {
        if(!response.rootObject.contains("error"))
            response.status = KlipperResponse::OK;

        response.setId(response["id"].toInt());

        response.timestamp = QDateTime::currentDateTime();

        if(!response.rootObject.contains("method"))
        {
            origin = _klipperMessageBuffer[response["id"].toInt()];
            response["request"] = origin.document();
            response["method"] = origin["method"];
            response.origin = (KlipperResponse::ResponseOrigin)_klipperMessageBuffer[response["id"].toInt()].origin;
            _klipperMessageBuffer.remove(response["id"].toInt());
        }
    }

    //For some reason I am getting params returned for status updates.
    //I dont think this is supposed to happen according to the docs.
    if(response.rootObject.contains("params") && !response.rootObject.contains("result"))
    {
        QJsonObject result = response["params"].toArray()[0].toObject();
        result["timecode"] = response["params"].toArray()[0].toDouble();

        response.rootObject.remove("params");
        response.rootObject["result"] = result;
    }
    else if(response.rootObject.contains("result") && response.rootObject["result"].toObject().contains("status"))
    {
        QJsonObject result = response["result"].toObject()["status"].toObject();
        response.rootObject.remove(QString("result"));
        response["result"] = result;
    }

    if(response["method"].toString().startsWith("notify") && response["method"] != QString("notify_status_update") && response["method"] != QString("notify_proc_stat_update"))
    {
        if(response["method"] == QString("notify_klippy_disconnected"))
        {
            if(!_klipperRestartTimer)
            {
                _klipperRestartTimer = new QTimer();

                connect(_klipperRestartTimer, SIGNAL(timeout()), this, SLOT(on_klipperRestartTimer_timeout()));

                _klipperRestartTimer->setInterval(1000);
                _klipperRestartTimer->setSingleShot(false);
                _klipperRestartTimer->start();
            }

            removeState(Connected);
            emit klipperDisconnected();
        }
        else if(response["method"] == QString("notify_klippy_ready"))
        {
            addState(Connected);
            emit klipperConnected();
            printerInfo();
            printerSubscribe();
        }
        else if(response["method"] == QString("notify_filelist_changed"))
        {
            QJsonObject object = response["result"].toObject();
            if(object.contains(QString("action")))
            {
                if(object["action"] == QString("delete_file"))
                {
                    object = object["item"].toObject();

                    QString path = object["path"].toString();
                    QString root = object["root"].toString();

                    if(path.contains(QDir::separator()))
                        path = path.mid(0,path.lastIndexOf(QDir::separator()));
                    else
                        path.clear();

                    path = root + QDir::separator() + path;
                    getFileList(path);
                }
            }
        }
    }
    else if(_parserMap.contains(response["method"].toString()))
    {
        QString key = response["method"].toString();
        ParserFunction parser = _parserMap[key];
        (this->*parser)(response);
    }

    if(response["method"] != QString("notify_proc_stat_update"))
    {
        emit responseReceived(response);

        if(_startupSequence.count())
        {
            StartupFunction function = _startupSequence.dequeue();
            (this->*function)();

            if(!_startupSequence.count())
                emit startup();
        }
    }
}

void QAbstractKlipperConsole::on_klipperRestartTimer_timeout()
{
    serverInfo();
}

void QAbstractKlipperConsole::sendError(QString message)
{

}

void QAbstractKlipperConsole::on_deleteFile(KlipperResponse response)
{

}

void QAbstractKlipperConsole::on_moveFile(KlipperResponse response)
{

}

void QAbstractKlipperConsole::on_copyFile(KlipperResponse response)
{

}

void QAbstractKlipperConsole::on_getFileList(KlipperResponse response)
{
    if(response["result"].isObject())
    {
        QJsonObject originObject = response["request"].toObject();
        QJsonObject result = response["result"].toObject();
        QJsonObject rootInfo = result["root_info"].toObject();
        QJsonArray files = result["files"].toArray();
        QJsonArray directories = result["dirs"].toArray();
        QList<KlipperFile> fileList;

        if(result.contains(QString("disk_usage")))
        {
            QJsonObject driveUsage = result["disk_usage"].toObject();
            _printer->system()->setDriveUsage(driveUsage["used"].toInteger());
            _printer->system()->setDriveCapacity(driveUsage["total"].toInteger());
            _printer->system()->setDriveFree(driveUsage["free"].toInteger());

            emit systemUpdate();
        }

        QString directory = originObject["params"].toObject()["path"].toString();
        QString root = rootInfo["name"].toString();

        if(directory.contains(QString("/")))
        {
            if(directory.endsWith(QString("/")))
                directory = directory.mid(0, directory.length() -1);

            directory.remove(root);

            if(directory.startsWith(QString("/")))
                directory = directory.mid(1, directory.length() -1);

            directory = directory.mid(0, directory.lastIndexOf(QString("/")));
        }
        else
            directory.remove(root);

        foreach(QJsonValueConstRef directoryRef, directories)
        {
            if(directoryRef.isObject())
            {
                QJsonObject directoryObject = directoryRef.toObject();
                KlipperFile directoryListing;
                QString directoryName = directoryObject["dirname"].toString();

                directoryListing.name = directoryName;
                directoryListing.root = root;
                directoryListing.path = directory;
                directoryListing.fileSize = directoryObject["size"].toDouble();
                directoryListing.dateModified = directoryObject["modified"].toDouble();
                directoryListing.type = KlipperFile::Directory;

                fileList.append(directoryListing);
            }
        }

        foreach(QJsonValueConstRef fileRef, files)
        {
            if(fileRef.isObject())
            {
                QJsonObject fileObject = fileRef.toObject();
                KlipperFile file;
                QString fileName = fileObject["filename"].toString();

                fileName.remove(directory);

                file.name = fileName;
                file.fileSize = fileObject["size"].toDouble();
                file.dateModified = fileObject["modified"].toDouble();
                file.root = root;
                file.path = directory;

                if(root == QString("gcodes"))
                    file.type = KlipperFile::GCode;
                else if(root == QString("config"))
                    file.type = KlipperFile::Config;

                fileList.append(file);
            }
        }

        emit directoryListing(root, directory, fileList);
    }
}

void QAbstractKlipperConsole::on_createDirectory(KlipperResponse response)
{
    QJsonObject object = response["result"].toObject();

    if(object.contains(QString("action")))
    {
        if(object["action"] == QString("create_dir"))
        {
            object = object["item"].toObject();

            QString path = object["path"].toString();
            QString root = object["root"].toString();

            if(path.contains(QDir::separator()))
                path = path.mid(path.lastIndexOf(QDir::separator()),path.length() - path.lastIndexOf(QDir::separator()));
            else
                path.clear();

            path = root + QDir::separator() + path;
            getFileList(path);
        }
    }
}

void QAbstractKlipperConsole::on_deleteDirectory(KlipperResponse response)
{
    QJsonObject object = response["result"].toObject();

    if(object.contains(QString("action")))
    {
        if(object["action"] == QString("delete_dir"))
        {
            object = object["item"].toObject();

            QString path = object["path"].toString();
            QString root = object["root"].toString();

            if(path.contains(QDir::separator()))
                path = path.mid(path.lastIndexOf(QDir::separator()),path.length() - path.lastIndexOf(QDir::separator()));
            else
                path.clear();

            path = root + QDir::separator() + path;
            getFileList(path);
        }
    }
}

void QAbstractKlipperConsole::on_startPrint(KlipperResponse response)
{
    printerInfo();
}

void QAbstractKlipperConsole::on_pausePrint(KlipperResponse response)
{
    printerInfo();
}

void QAbstractKlipperConsole::on_resumePrint(KlipperResponse response)
{
    printerInfo();
}

void QAbstractKlipperConsole::on_cancelPrint(KlipperResponse response)
{
    printerInfo();
}

void QAbstractKlipperConsole::on_machineShutdown(KlipperResponse response)
{
}

void QAbstractKlipperConsole::on_machineReboot(KlipperResponse response)
{
}

void QAbstractKlipperConsole::on_machineSystemInfo(KlipperResponse response)
{
    if(response["result"].isObject())
    {
        QJsonObject result = response["result"].toObject();

        if(result.contains("system_info") && result["system_info"].isObject())
        {
            QJsonObject systemInfo = result["system_info"].toObject();

            if(systemInfo.contains("cpu_info") && systemInfo["cpu_info"].isObject())
            {
                QJsonObject cpuInfoObject = systemInfo["cpu_info"].toObject();
                System::CpuInfo cpuInfo = _printer->system()->cpuInfo();

                if(cpuInfoObject.contains("cpu_count"))
                    cpuInfo.cpuCount = cpuInfoObject["cpu_count"].toInt();

                if(cpuInfoObject.contains("bits"))
                {
                    QString bitString = cpuInfoObject["bits"].toString();
                    bitString.remove("bit");

                    cpuInfo.bitCount = (bitString.toInt());
                }

                if(cpuInfoObject.contains("processor"))
                    cpuInfo.processor = (cpuInfoObject["processor"].toString());

                if(cpuInfoObject.contains("cpu_desc"))
                    cpuInfo.description = (cpuInfoObject["cpu_desc"].toString());

                if(cpuInfoObject.contains("serial_number"))
                    cpuInfo.serialNumber = (cpuInfoObject["serial_number"].toString());

                if(cpuInfoObject.contains("hardware_desc"))
                    cpuInfo.hardwareDescription = (cpuInfoObject["hardware_desc"].toString());

                if(cpuInfoObject.contains("model"))
                    cpuInfo.model = (cpuInfoObject["model"].toString());

                if(cpuInfoObject.contains("total_memory"))
                    cpuInfo.totalMemory = (cpuInfoObject["total_memory"].toInt());

                if(cpuInfoObject.contains("memory_units"))
                    cpuInfo.memoryUnits = (cpuInfoObject["memory_units"].toString());

                _printer->system()->setCpuInfo(cpuInfo);
            }

            if(systemInfo.contains("sd_info") && systemInfo["sd_info"].isObject())
            {
                QJsonObject sdInfoObject = systemInfo["sd_info"].toObject();
                System::SdInfo sdInfo = _printer->system()->sdInfo();

                if(sdInfoObject.contains("manufacturer_id"))
                    sdInfo.manufacturerId = (sdInfoObject["manufacturer_id"].toString());

                if(sdInfoObject.contains("manufacturer"))
                    sdInfo.manufacturer = (sdInfoObject["manufacturer"].toString());

                if(sdInfoObject.contains("oem_id"))
                    sdInfo.oemId = (sdInfoObject["oem_id"].toString());

                if(sdInfoObject.contains("product_name"))
                    sdInfo.productName = (sdInfoObject["product_name"].toString());

                if(sdInfoObject.contains("product_revision"))
                    sdInfo.productRevision = (sdInfoObject["product_revision"].toString());

                if(sdInfoObject.contains("serial_number"))
                    sdInfo.serialNumber = (sdInfoObject["serial_number"].toString());

                if(sdInfoObject.contains("manufacturer_date"))
                    sdInfo.manufacturerDate = (sdInfoObject["manufacturer_date"].toString());

                if(sdInfoObject.contains("capacity"))
                    sdInfo.capacityString = (sdInfoObject["capacity"].toString());

                if(sdInfoObject.contains("total_bytes"))
                    sdInfo.totalBytes = (sdInfoObject["total_memory"].toInt());

                _printer->system()->setSdInfo(sdInfo);
            }

            if(systemInfo.contains("distribution") && systemInfo["distribution"].isObject())
            {
                QJsonObject distributionObject = systemInfo["distribution"].toObject();
                System::DistributionInfo distribution = _printer->system()->distributionInfo();

                if(distributionObject.contains("name"))
                    distribution.name = (distributionObject["name"].toString());

                if(distributionObject.contains("id"))
                    distribution.id = (distributionObject["id"].toString());

                if(distributionObject.contains("version"))
                    distribution.version = (distributionObject["version"].toString());

                if(distributionObject.contains("version_parts"))
                {
                    QJsonObject versionParts = distributionObject["version_parts"].toObject();

                    if(versionParts.contains("major"))
                        distribution.versionMajor = (versionParts["major"].toString());
                    if(versionParts.contains("minor"))
                        distribution.versionMinor = (versionParts["minor"].toString());
                    if(versionParts.contains("build_number"))
                        distribution.versionBuildNumber = (versionParts["build_number"].toString());

                }

                if(distributionObject.contains("like"))
                    distribution.style = (distributionObject["like"].toString());

                if(distributionObject.contains("codename"))
                    distribution.codename = (distributionObject["codename"].toString());

                _printer->system()->setDistributionInfo(distribution);
            }

            if(systemInfo.contains("available_services") && systemInfo["available_services"].isArray())
            {
                QJsonArray servicesArray = systemInfo["available_services"].toArray();
                _printer->system()->availableServices().clear();

                for(int i = 0; i < servicesArray.count(); i++)
                    _printer->system()->availableServices() += servicesArray[i].toString();
            }

            if(systemInfo.contains("service_state") && systemInfo["service_state"].isObject())
            {
                QJsonObject serviceState = systemInfo["service_state"].toObject();
                QStringList keys = serviceState.keys();

                _printer->system()->serviceStates().clear();

                foreach(QString key, keys)
                {
                    if(serviceState[key].isObject())
                    {
                        QJsonObject stateObject = serviceState[key].toObject();
                        System::ServiceState state;

                        if(stateObject.contains("active_state"))
                            state.activeState = stateObject["active_state"].toString();

                        if(stateObject.contains("sub_state"))
                            state.subState = stateObject["sub_state"].toString();

                        _printer->system()->serviceStates().insert(key, state);
                    }
                }
            }

            if(systemInfo.contains("network") && systemInfo["network"].isObject())
            {
                QJsonObject networkObject = systemInfo["network"].toObject();
                QStringList keys = networkObject.keys();

                _printer->system()->networkInterfaces().clear();

                foreach(QString key, keys)
                {
                    QJsonObject interfaceObject = networkObject[key].toObject();
                    System::NetworkInterface interface;

                    if(interfaceObject.contains("mac_address"))
                        interface.macAddress = interfaceObject["mac_address"].toString();

                    if(interfaceObject.contains("ip_addresses"))
                    {
                        QJsonArray ipArray = interfaceObject["ip_addresses"].toArray();
                        for(int i = 0; i < ipArray.count(); i++)
                        {
                            QJsonObject ipObject = ipArray[i].toObject();
                            System::NetworkInterface::IpAddress ipAddress;

                            if(ipObject.contains("family"))
                                ipAddress.family = ipObject["family"].toString();

                            if(ipObject.contains("address"))
                                ipAddress.address = ipObject["address"].toString();

                            if(ipObject.contains("is_link_local"))
                                ipAddress.isLinkLocal = ipObject["is_link_local"].toBool();

                            interface.ipAddresses += ipAddress;
                        }
                    }

                    _printer->system()->networkInterfaces().insert(key, interface);
                }
            }

            if(systemInfo.contains("canbus") && systemInfo["canbus"].isObject())
            {
                QJsonObject canbusObject = systemInfo["canbus"].toObject();
                QStringList keys = canbusObject.keys();

                _printer->system()->canBus().clear();

                foreach(QString key, keys)
                {
                    if(canbusObject[key].isObject())
                    {
                        QJsonObject canDeviceObject = canbusObject[key].toObject();
                        System::CanBusDevice canDevice;

                        if(canDeviceObject.contains("tx_queue_len"))
                            canDevice.queueLength = canDeviceObject["tx_queue_len"].toInt();

                        if(canDeviceObject.contains("bitrate"))
                            canDevice.bitrate = canDeviceObject["bitrate"].toInt();

                        if(canDeviceObject.contains("driver"))
                            canDevice.driver = canDeviceObject["driver"].toString();

                        _printer->system()->canBus().insert(key, canDevice);
                    }
                }
            }

            if(systemInfo.contains("python") && systemInfo["python"].isObject())
            {
                QJsonObject pythonObject = systemInfo["python"].toObject();

                if(pythonObject.contains("version_string"))
                    _printer->system()->setPythonVersion(pythonObject["version_string"].toString());
            }
        }
    }
}

void QAbstractKlipperConsole::on_machineServiceRestart(KlipperResponse response)
{

}

void QAbstractKlipperConsole::on_machineServiceStop(KlipperResponse response)
{

}

void QAbstractKlipperConsole::on_machineServiceStart(KlipperResponse response)
{

}

void QAbstractKlipperConsole::on_machineProcStats(KlipperResponse response)
{
    if(response["result"].isObject())
    {
        QJsonObject result = response["result"].toObject();

        System::CpuInfo cpuInfo = _printer->system()->cpuInfo();
        System::MemoryStats memory = _printer->system()->memoryStats();
        System::ThrottleState throttleState = _printer->system()->throttleState();

        //Parse cpu usage status
        if(result.contains("system_cpu_usage"))
        {
            QJsonObject cpuLoadArray = result["system_cpu_usage"].toObject();
            QStringList keys = cpuLoadArray.keys();
            qreal usage = 0;
            cpuInfo.coreUsage.clear();

            foreach(QString key, keys)
            {
                usage += cpuLoadArray[key].toDouble();
                cpuInfo.coreUsage.append(cpuLoadArray[key].toDouble());
            }

            cpuInfo.usage = (usage / cpuInfo.cpuCount);
        }

        if(result.contains("cpu_temp"))
            cpuInfo.temp = result["cpu_temp"].toDouble();

        if(result.contains("throttled_state"))
        {
            QJsonObject throttleObject = result["throttled_state"].toObject();
            throttleState.flags.clear();

            if(throttleObject.contains("bits"))
                throttleState.bits = throttleObject["bits"].toInt();

            if(throttleObject.contains("flags"))
            {
                QJsonArray flagsArray = throttleObject["flags"].toArray();

                for(int i = 0; i < flagsArray.count(); i++)
                    throttleState.flags += flagsArray[i].toString();
            }

        }

        if(result.contains("network"))
        {
            QJsonObject networkLoadObject = result["system_cpu_usage"].toObject();
            QStringList keys = networkLoadObject.keys();

            _printer->system()->networkStats().clear();

            foreach(QString key, keys)
            {
                QJsonObject statObject = networkLoadObject[key].toObject();
                System::NetworkStatsEntry statEntry;

                if(statObject.contains("rx_bytes"))
                    statEntry.rxBytes = statObject["rx_bytes"].toDouble();

                if(statObject.contains("tx_bytes"))
                    statEntry.txBytes = statObject["tx_bytes"].toDouble();

                if(statObject.contains("bandwidth"))
                    statEntry.bandwidth = statObject["bandwidth"].toDouble();

                _printer->system()->networkStats().insert(key, statEntry);
            }
        }

        //Parse memory status
        if(result.contains("system_memory"))
        {
            QJsonObject memoryLoadObject = result["system_memory"].toObject();

            if(memoryLoadObject.contains("total"))
                memory.total = memoryLoadObject["total"].toDouble();

            if(memoryLoadObject.contains("used"))
                memory.used = memoryLoadObject["used"].toDouble();

            memory.average = memory.used / memory.total;
        }

        if(result.contains("system_uptime"))
            _printer->system()->setUptime(result["system_uptime"].toDouble());

        if(result.contains("websocket_connections"))
            _printer->system()->setConnectionCount(result["websocket_connections"].toInt());

        _printer->system()->setCpuInfo(cpuInfo);
        _printer->system()->setMemoryStats(memory);
        _printer->system()->setThrottleState(throttleState);

        emit systemUpdate();
    }
}

void QAbstractKlipperConsole::on_machinePeripheralsUSB(KlipperResponse response)
{
    if(response["result"].isObject())
    {
        QJsonObject result = response["result"].toObject();

        if(result["usb_devices"].isArray())
        {
            QJsonArray usbArray = result["usb_devices"].toArray();
            _printer->system()->usbPeripherals().clear();

            for(int i = 0; i < usbArray.count(); i++)
            {
                QJsonObject usbDeviceObject = usbArray[i].toObject();
                System::UsbPeripheral usbDevice;

                usbDevice.deviceNumber = usbDeviceObject["device_num"].toInt();
                usbDevice.busNumber = usbDeviceObject["bus_num"].toInt();

                usbDevice.location = usbDeviceObject["vendor_id"].toString();
                usbDevice.productId = usbDeviceObject["product_id"].toString();
                usbDevice.manufacturer = usbDeviceObject["manufacturer"].toString();
                usbDevice.product = usbDeviceObject["product"].toString();
                usbDevice.className = usbDeviceObject["class"].toString();
                usbDevice.subclassName = usbDeviceObject["subclass"].toString();
                usbDevice.protocol = usbDeviceObject["protocol"].toString();
                usbDevice.description = usbDeviceObject["description"].toString();


                _printer->system()->usbPeripherals().append(usbDevice);
            }
        }

        emit systemUpdate();
    }
}

void QAbstractKlipperConsole::on_machinePeripheralsSerial(KlipperResponse response)
{
    if(response["result"].isObject())
    {
        QJsonObject result = response["result"].toObject();

        if(result["serial_devices"].isArray())
        {
            QJsonArray usbArray = result["usb_devices"].toArray();
            _printer->system()->usbPeripherals().clear();

            for(int i = 0; i < usbArray.count(); i++)
            {
                QJsonObject usbDeviceObject = usbArray[i].toObject();
                System::SerialPeripheral serialDevice;

                serialDevice.type = usbDeviceObject["device_type"].toString();
                serialDevice.path = usbDeviceObject["device_path"].toString();
                serialDevice.name = usbDeviceObject["device_name"].toString();
                serialDevice.driver = usbDeviceObject["driver_name"].toString();
                serialDevice.hardwarePath = usbDeviceObject["path_by_hardware"].toString();
                serialDevice.pathById = usbDeviceObject["path_by_id"].toString();
                serialDevice.usbLocation = usbDeviceObject["usb_location"].toString();

                _printer->system()->serialPeripherals().append(serialDevice);
            }
        }

        emit systemUpdate();
    }
}

void QAbstractKlipperConsole::on_machinePeripheralsVideo(KlipperResponse response)
{
    if(response["result"].isObject())
    {
        QJsonObject result = response["result"].toObject();

        if(result["v412_devices"].isArray())
        {
            QJsonArray v412DeviceArray = result["v412_devices"].toArray();
            _printer->system()->v412Devices().clear();

            for(int i = 0; i < v412DeviceArray.count(); i++)
            {
                QJsonObject deviceObject = v412DeviceArray[i].toObject();
                System::V412Device v412Device;

                v412Device.name = deviceObject["device_name"].toString();
                v412Device.path = deviceObject["device_path"].toString();
                v412Device.cameraName = deviceObject["camera_name"].toString();
                v412Device.driver = deviceObject["driver_name"].toString();
                v412Device.altName = deviceObject["alt_name"].toString();
                v412Device.hardwareBus = deviceObject["hardware_bus"].toString();
                v412Device.version = deviceObject["version"].toString();
                v412Device.hardwarePath = deviceObject["path_by_hardware"].toString();
                v412Device.pathById = deviceObject["path_by_id"].toString();
                v412Device.usbLocation = deviceObject["usb_location"].toString();

                if(deviceObject["modes"].isArray())
                {
                    QJsonArray modes = deviceObject["modes"].toArray();

                    for(int m = 0; m < modes.count(); m++)
                    {
                        QJsonObject modeObject = modes[i].toObject();
                        QJsonArray modeFlagArray = modeObject["flags"].toArray();
                        QJsonArray resolutionArray = modeObject["resolutions"].toArray();
                        System::V412Device::Mode mode;

                        mode.description = modeObject["description"].toString();
                        mode.format = modeObject["format"].toString();

                        for(int r = 0; r < resolutionArray.count(); r++)
                            mode.resolutions += resolutionArray[r].toString();

                        for(int f = 0; f < modeFlagArray.count(); f++)
                            mode.flags += modeFlagArray[f].toString();
                    }
                }

                if(deviceObject["capabilities"].isArray())
                {
                    QJsonArray capabilities = deviceObject["capabilities"].toArray();

                    for(int c = 0; c < capabilities.count(); c++)
                        v412Device.capabilities += capabilities[c].toString();
                }

                _printer->system()->v412Devices().append(v412Device);
            }
        }

        if(result["libcamera_devices"].isArray())
        {
            QJsonArray cameraArray = result["libcamera_devices"].toArray();
            _printer->system()->libcameraDevices().clear();

            for(int i = 0; i < cameraArray.count(); i++)
            {
                QJsonObject cameraObject = cameraArray[i].toObject();
                QJsonArray modesArray = cameraObject["modes"].toArray();
                System::LibcameraDevice camera;

                camera.id = cameraObject["libcamera_id"].toString();
                camera.model = cameraObject["model"].toString();

                for(int m = 0; m < modesArray.count(); m++)
                {
                    QJsonObject modeObject = modesArray[i].toObject();
                    QJsonArray resolutionArray = modeObject["resolutions"].toArray();
                    System::LibcameraDevice::Mode mode;

                    mode.format = modeObject["format"].toString();

                    for(int r = 0; r < resolutionArray.count(); r++)
                        mode.resolutions += resolutionArray[r].toString();
                }

                _printer->system()->libcameraDevices().append(camera);
            }
        }

        emit systemUpdate();
    }
}

void QAbstractKlipperConsole::on_machinePeripheralsCanbus(KlipperResponse response)
{
    if(response["result"].isObject())
    {
        QJsonObject request = response["request"].toObject();
        QJsonObject params = request["params"].toObject();
        QJsonObject result = response["result"].toObject();

        QString interfaceName = params["interface"].toString();
        interfaceName.remove("can");

        qint32 interfaceNumber = interfaceName.toInt();

        if(result["can_uuids"].isArray())
        {
            QJsonArray canArray = result["can_uuids"].toArray();
            System::CanBus canBus;

            for(int i = 0; i < canArray.count(); i++)
            {
                QJsonObject canObject = canArray[i].toObject();
                System::CanBus::Interface interface;

                interface.application = canObject["application"].toString();
                interface.uuid = canObject["uuid"].toString();
            }

            _printer->system()->canBusses().insert(interfaceNumber, canBus);
        }
    }
}

void QAbstractKlipperConsole::on_machineUpdateStatus(KlipperResponse response)
{
    if(response[QString("result")].isObject())
    {
        //Get the base update state
        QJsonObject result = response[QString("result")].toObject();
        System::UpdateState updateState;

        updateState.busy = result["busy"].toBool();
        updateState.githubLimitResetTime = result["github_limit_reset_time"].toInt();
        updateState.githubRateLimit = result["github_rate_limit"].toInt();
        updateState.githubRequestsRemaining = result["github_requests_remaining"].toInt();

        //Grab the version info
        QJsonObject versionObject = result["version_info"].toObject();
        QStringList keys = versionObject.keys();

        foreach(QString key, keys)
        {
            //System version info
            if(key == QString("system"))
            {
                QJsonObject systemObject = versionObject[key].toObject();
                QJsonArray packageArray = systemObject["package_list"].toArray();

                updateState.systemState.packageCount = systemObject["package_count"].toInt();

                for(int i = 0; i < packageArray.count(); i++)
                    updateState.systemState.packages += packageArray[i].toString();
            }
            //Package states
            else
            {
                QJsonObject packageObject = versionObject[key].toObject();

                QJsonArray commitsArray = packageObject["commits_behind"].toArray();
                QJsonArray tagsArray = packageObject["info_tags"].toArray();
                QJsonArray gitArray = packageObject["git_messages"].toArray();
                QJsonArray warningArray = packageObject["warnings"].toArray();
                QJsonArray anomaliesArray = packageObject["anomalies"].toArray();

                //Package information
                System::UpdateState::PackageState packageState;

                //Strings
                packageState.channel = packageObject["channel"].toString();
                packageState.configuredType = packageObject["configured_type"].toString();
                packageState.detectedType = packageObject["detected_type"].toString();
                packageState.remoteAlias = packageObject["remote_alias"].toString();
                packageState.branch = packageObject["branch"].toString();
                packageState.owner = packageObject["owner"].toString();
                packageState.repoName = packageObject["repo_name"].toString();
                packageState.version = packageObject["version"].toString();
                packageState.remoteVersion = packageObject["remote_version"].toString();
                packageState.rollbackVersion = packageObject["rollback_version"].toString();
                packageState.currentHash = packageObject["current_hash"].toString();
                packageState.remoteHash = packageObject["remote_hash"].toString();
                packageState.fullVersionString = packageObject["full_version_string"].toString();
                packageState.recoveryUrl = packageObject["recovery_url"].toString();
                packageState.remoteUrl = packageObject["remote_url"].toString();

                //Bools
                packageState.debugEnabled = packageObject["debug_enabled"].toBool();
                packageState.isValid = packageObject["is_valid"].toBool();
                packageState.corrupt = packageObject["corrupt"].toBool();
                packageState.isDirty = packageObject["is_dirty"].toBool();
                packageState.detached = packageObject["detached"].toBool();
                packageState.pristine = packageObject["pristine"].toBool();

                //Tags
                for(int i = 0; i < tagsArray.count(); i++)
                    packageState.infoTags += tagsArray[i].toString();

                //Git messages
                for(int i = 0; i < gitArray.count(); i++)
                    packageState.gitMessages += gitArray[i].toString();

                //Warning messages
                for(int i = 0; i < warningArray.count(); i++)
                    packageState.warnings += warningArray[i].toString();

                //Anomalies messages
                for(int i = 0; i < anomaliesArray.count(); i++)
                    packageState.anomalies += anomaliesArray[i].toString();

                //Commits behind information
                for(int i = 0; i < commitsArray.count(); i++)
                {
                    QJsonObject commitObject = commitsArray[i].toObject();
                    System::UpdateState::CommitState commit;

                    commit.sha = commitObject["sha"].toString();
                    commit.author = commitObject["author"].toString();
                    commit.date = commitObject["date"].toString();
                    commit.subject = commitObject["subject"].toString();
                    commit.message = commitObject["message"].toString();
                    commit.tag = commitObject["tag"].toString();

                    packageState.commitsBehind += commit;
                }

                //Add to packages map
                updateState.packageStates.insert(key, packageState);
            }
        }

        emit machineUpdateStatusReceived();
    }
}

void QAbstractKlipperConsole::on_machineUpdateFull(KlipperResponse response)
{
    emit machineUpdatedFull();
}

void QAbstractKlipperConsole::on_machineUpdateMoonraker(KlipperResponse response)
{
    emit machineUpdatedMoonraker();
}

void QAbstractKlipperConsole::on_machineUpdateKlipper(KlipperResponse response)
{
    emit machineUpdatedKlipper();
}

void QAbstractKlipperConsole::on_machineUpdateClient(KlipperResponse response)
{
    emit machineUpdatedClient();
}

void QAbstractKlipperConsole::on_machineUpdateSystem(KlipperResponse response)
{
    emit machineUpdatedSystem();
}

void QAbstractKlipperConsole::on_machineUpdateRecover(KlipperResponse response)
{
    emit machineUpdateRecovered();
}

void QAbstractKlipperConsole::on_machineUpdateRollback(KlipperResponse response)
{
    emit machineUpdateRollbackComplete();
}

void QAbstractKlipperConsole::on_sendGcode(KlipperResponse response)
{
    if(response[QString("result")].isObject())
    {
        QJsonObject result = response[QString("result")].toObject();
    }
}

void QAbstractKlipperConsole::on_printerInfo(KlipperResponse response)
{
    if(response[QString("result")].isObject())
    {
        QJsonObject result = response[QString("result")].toObject();

        if(result.contains(QString("state")))
        {
            QString state = result["state"].toString();

            if(state == QString("ready"))
                _printer->setStatus(Printer::Ready);
            else if(state == QString("error"))
                _printer->setStatus(Printer::Error);
            else if(state == QString("printing"))
                _printer->setStatus(Printer::Printing);
            else if(state == QString("paused"))
                _printer->setStatus(Printer::Paused);
            else if(state == QString("cancelled"))
                _printer->setStatus(Printer::Cancelled);
        }

        if(result.contains(QString("config_file")))
            _printer->setConfigFile(result["config_file"].toString());

        if(result.contains(QString("state_message")))
        {
            _printer->setStatusMessage(result["state_message"].toString());

            if(_printer->status() == Printer::Error)
            {
                QStringList split = _printer->statusMessage().split(QString("\n"),Qt::SkipEmptyParts);

                emit klipperError(split.last(), _printer->statusMessage());
            }
        }
        if(result.contains(QString("software_version")))
            _printer->setFirmwareVersion(result["software_version"].toString());

        if(result.contains(QString("hostname")))
            _printer->system()->setHostname(result["hostname"].toString());

        emit printerUpdate();
        emit systemUpdate();
    }
}

void QAbstractKlipperConsole::on_restartKlipper(KlipperResponse response)
{

}

void QAbstractKlipperConsole::on_restartFirmware(KlipperResponse response)
{

}

void QAbstractKlipperConsole::on_printerObjectsList(KlipperResponse response)
{
    if(response["result"].isObject())
    {
        QJsonObject result = response["result"].toObject();

        if(result["objects"].isArray())
        {
            _subscriptionObjects.clear();
            _macroObjects.clear();

            QJsonArray objectsArray = result["objects"].toArray();
            int count = objectsArray.count();

            for(int i = 0; i < count; i++)
            {
                QString object = objectsArray.at(i).toString();

                if(object.startsWith("gcode_macro"))
                    _macroObjects.append(objectsArray.at(i).toString());
                else
                    _subscriptionObjects.append(objectsArray.at(i).toString());
            }
        }
    }
}

void QAbstractKlipperConsole::on_printerSubscribe(KlipperResponse response)
{
    QJsonObject result = response["result"].toObject();

    //First parse the config file object to construct all printer details
    //    as set in the config
    if(result.contains(QString("configfile")))
    {
        QJsonObject configFileObject = result["configfile"].toObject();

        //Most of the config file is useless at the beta stage
        //    a lot of these will be blank
        if(configFileObject.contains(QString("config")))
        {
            QJsonObject configObject = configFileObject["config"].toObject();
        }
        if(configFileObject.contains(QString("settings")))
        {
            QJsonObject settingsObject = configFileObject["settings"].toObject();

            if(settingsObject.contains(QString("bed_mesh")))
            {
                QJsonObject bedMeshObject = settingsObject["bed_mesh"].toObject();

                Q3DPrintBed::Mesh bedMesh = _printer->bed()->bedMesh();

                if(bedMeshObject.contains("adaptive_margin"))
                    bedMesh.adaptiveMargin = bedMeshObject["adaptive_margin"].toDouble();

                if(bedMeshObject.contains("algorithm"))
                    bedMesh.algorithm = bedMeshObject["algorithm"].toString();

                if(bedMeshObject.contains("bicubic_tension"))
                    bedMesh.tension = bedMeshObject["bicubic_tension"].toDouble();

                if(bedMeshObject.contains("fade_end"))
                    bedMesh.fadeEnd = bedMeshObject["fade_end"].toDouble();

                if(bedMeshObject.contains("fade_start"))
                    bedMesh.fadeStart = bedMeshObject["fade_start"].toDouble();

                if(bedMeshObject.contains("fade_target"))
                    bedMesh.fadeTarget = bedMeshObject["fade_target"].toDouble();

                if(bedMeshObject.contains("horizontal_move_z"))
                    bedMesh.horizontalMoveZ = bedMeshObject["horizontal_move_z"].toDouble();

                if(bedMeshObject.contains("move_check_distance"))
                    bedMesh.moveCheckDistance = bedMeshObject["move_check_distance"].toDouble();

                if(bedMeshObject.contains("speed"))
                    bedMesh.speed = bedMeshObject["speed"].toDouble();

                if(bedMeshObject.contains("split_delta_z"))
                    bedMesh.splitDeltaZ = bedMeshObject["split_delta_z"].toDouble();

                //Parse limits
                QJsonArray meshMaxArray = bedMeshObject["mesh_max"].toArray();
                QJsonArray meshMinArray = bedMeshObject["mesh_min"].toArray();
                QJsonArray probeCountArray = bedMeshObject["probe_count"].toArray();

                bedMesh.maximum.x = meshMaxArray[0].toDouble();
                bedMesh.maximum.y = meshMaxArray[1].toDouble();

                bedMesh.minimum.x = meshMinArray[0].toDouble();
                bedMesh.minimum.y = meshMinArray[1].toDouble();

                bedMesh.probeCount.x = probeCountArray[0].toDouble();
                bedMesh.probeCount.y = probeCountArray[1].toDouble();

                _printer->bed()->setBedMesh(bedMesh);
            }

            //Parse printer settings
            if(settingsObject.contains(QString("printer")))
            {
                QJsonObject printerObject = settingsObject["printer"].toObject();

                if(printerObject.contains("kinematics"))
                    _printer->setKinematics(printerObject["kinematics"].toString());

                if(printerObject.contains("max_accel"))
                    _printer->setMaxAcceleration(printerObject["max_accel"].toDouble());

                if(printerObject.contains("max_velocity"))
                    _printer->setMaxVelocity(printerObject["max_velocity"].toDouble());

                if(printerObject.contains("max_z_accel"))
                    _printer->setMaxZAcceleration(printerObject["max_z_accel"].toDouble());

                if(printerObject.contains("max_z_velocity"))
                    _printer->setMaxZVelocity(printerObject["max_z_velocity"].toDouble());

                if(printerObject.contains("square_corner_velocity"))
                    _printer->setSquareCornerVelocity(printerObject["square_corner_velocity"].toDouble());
            }

            //Parse MCU settings
            if(settingsObject.contains(QString("mcu")))
            {
                QJsonObject mcuObject = settingsObject["mcu"].toObject();
                System::MCU mcu = _printer->system()->mcu();

                if(mcuObject.contains("baud"))
                    mcu.baudRate = mcuObject["baud"].toInt();

                if(mcuObject.contains("max_stepper_error"))
                    mcu.maxStepperError = mcuObject["max_stepper_error"].toDouble();

                if(mcuObject.contains("max_velocity"))
                    mcu.baudRate = mcuObject["baud"].toInt();
            }

            //Parse Safe Z Home settings
            if(settingsObject.contains(QString("safe_z_home")))
            {
                QJsonObject safeZObject = settingsObject["safe_z_home"].toObject();
                System::SafeZHome zHome = _printer->system()->safeZHome();

                if(safeZObject.contains(QString("home_xy_position")))
                {
                    QJsonArray homePositionArray = safeZObject["home_xy_position"].toArray();

                    if(homePositionArray.count() >= 2)
                    {
                        zHome.homeXPosition = homePositionArray[0].toDouble();
                        zHome.homeYPosition = homePositionArray[1].toDouble();
                    }
                }

                zHome.moveToPrevious = safeZObject["move_to_previous"].toBool();

                zHome.speed = safeZObject["speed"].toDouble();
                zHome.zHopSpeed = safeZObject["z_hop"].toDouble();
                zHome.zHop = safeZObject["z_hop_speed"].toDouble();

                _printer->system()->setSafeZHome(zHome);
            }

            //Parse adjustment screw settings
            if(settingsObject.contains(QString("screws_tilt_adjust")))
            {
                QJsonObject screwsTiltObject = settingsObject["screws_tilt_adjust"].toObject();

                QString thread = screwsTiltObject["screw_thread"].toString();
                qreal speed = screwsTiltObject["speed"].toDouble();

                for(int i = 1; ; i++)
                {
                    QString screwString = QString("screw") + QString::number(i);
                    QString screwNameString = screwString + QString("_name");

                    if(!screwsTiltObject.contains(screwString))
                        break;

                    QJsonArray screwArray = screwsTiltObject[screwString].toArray();

                    Q3DPrintBed::AdjustmentScrew *adjustmentScrew = _printer->bed()->adjustmentScrew(screwString);

                    if(adjustmentScrew == nullptr)
                        adjustmentScrew = new Q3DPrintBed::AdjustmentScrew();

                    adjustmentScrew->name = screwsTiltObject[screwNameString].toString();

                    qreal tilt0 = screwArray[0].toDouble();
                    qreal tilt1 = screwArray[1].toDouble();

                    adjustmentScrew->tiltAdjust = QPair<qreal,qreal>(tilt0, tilt1);
                    adjustmentScrew->speed = speed;
                    adjustmentScrew->thread = thread;

                    _printer->bed()->setAdjustmentScrew(screwString, adjustmentScrew);
                }
            }
        }
    }

    //Parse extruders
    for(int index = 0; true; index++)
    {
        QString extruderName = QString("extruder") + ((index > 0) ? QString::number(index) : QString(""));

        if(!response["result"].toObject().contains(extruderName))
            break;

        _printer->extruder(index)->setWatts(_printer->powerProfile()[extruderName]);

        QJsonObject extruder = response["result"].toObject()[extruderName].toObject();
        if(extruder.contains("temperature"))
        {
            qreal temp = extruder["temperature"].toDouble();
            _printer->extruder(index)->setCurrentTemp(temp);
        }
        if(extruder.contains("target"))
        {
            qreal temp = extruder["target"].toDouble();
            _printer->extruder(index)->setTargetTemp(temp);
        }
        if(extruder.contains("pressure_advance"))
        {
            qreal advance = extruder["pressure_advance"].toDouble();
            _printer->extruder(index)->setPressureAdvance(advance);
        }
        if(extruder.contains("smooth_time"))
        {
            qreal smoothing = extruder["smooth_time"].toDouble();
            _printer->extruder(index)->setSmoothTime(smoothing);
        }
        if(extruder.contains("power"))
        {
            qreal power = extruder["power"].toDouble();
            _printer->extruder(index)->setPower(power);
        }
        if(extruder.contains("can_extrude"))
        {
            bool canExtrude = extruder["can_extrude"].toBool();
            _printer->extruder(index)->setCanExtrude(canExtrude);
        }
    }

    //Parse fan status
    if(response["result"].toObject().contains("fan"))
    {
        QJsonObject fan = response["result"].toObject()["fan"].toObject();
        if(fan.contains("speed"))
        {
            double speed =fan["speed"].toDouble();
            _printer->toolhead()->fan()->setSpeed(speed);
        }
        if(fan.contains("rpm"))
        {
            double rpm =fan["rpm"].toDouble();
            _printer->toolhead()->fan()->setRpm(rpm);
        }
    }

    //Parse toolhead status
    if(response["result"].toObject().contains("toolhead"))
    {
        QJsonObject toolhead = response["result"].toObject()["toolhead"].toObject();
        if(toolhead.contains("axis_maximum"))
        {
            if(toolhead["axis_maximum"].isArray())
            {
                qreal x,y,z;
                QJsonArray maxPos = toolhead["axis_maximum"].toArray();
                x = maxPos[0].toDouble();
                y = maxPos[1].toDouble();
                z = maxPos[2].toDouble();

                _printer->toolhead()->setMaxPosition(x,y,z);
            }
        }
        if(toolhead.contains("axis_minimum"))
        {
            if(toolhead["axis_minimum"].isArray())
            {
                qreal x,y,z;
                QJsonArray maxPos = toolhead["axis_minimum"].toArray();
                x = maxPos[0].toDouble();
                y = maxPos[1].toDouble();
                z = maxPos[2].toDouble();

                _printer->toolhead()->setMinPosition(x,y,z);
            }
        }
        if(toolhead.contains("position"))
        {
            if(toolhead["position"].isArray())
            {
                qreal x,y,z,e;
                QJsonArray maxPos = toolhead["position"].toArray();
                x = maxPos[0].toDouble();
                y = maxPos[1].toDouble();
                z = maxPos[2].toDouble();
                e = maxPos[3].toDouble();

                _printer->toolhead()->setDestination(Position(x,y,z,e));
            }
        }
        if(toolhead.contains("homed_axes"))
        {
            if(toolhead["homed_axes"].isString())
            {
                QString homed = toolhead["homed_axes"].toString();

                _printer->toolhead()->setXHomed(homed.contains(QString("x")));
                _printer->toolhead()->setYHomed(homed.contains(QString("y")));
                _printer->toolhead()->setZHomed(homed.contains(QString("z")));
            }
        }
        if(toolhead.contains("estimated_print_time"))
        {
            //in seconds?
            double time = toolhead["estimated_print_time"].toDouble();
            QDateTime date = QDateTime::currentDateTime().addSecs(time);
            _printer->setPrintEndTime(date);
        }
        if(toolhead.contains("extruder"))
        {
            //string
            toolhead.isEmpty();
        }
        if(toolhead.contains("max_accel"))
        {
            _printer->toolhead()->setMaxAcceleration(toolhead["max_accel"].toInt());
        }
        if(toolhead.contains("max_accel_to_decel"))
        {
            _printer->toolhead()->setMaxAccelerationToDeceleration(toolhead["max_accel_to_decel"].toInt());
        }
        if(toolhead.contains("max_velocity"))
        {
            _printer->toolhead()->setMaxVelocity(toolhead["max_velocity"].toInt());
        }
        if(toolhead.contains("print_time"))
        {
        }
        if(toolhead.contains("square_corner_velocity"))
        {
            //double
        }
        if(toolhead.contains("stalls"))
        {
            _printer->toolhead()->setStalls(toolhead["stalls"].toInt());
        }
    }

    //Parse heatbed status
    if(response["result"].toObject().contains("heater_bed"))
    {
        QJsonObject heater = response["result"].toObject()["heater_bed"].toObject();
        if(heater.contains("temperature"))
        {
            double temp = heater["temperature"].toDouble();
            _printer->bed()->setCurrentTemp(temp);
        }
        if(heater.contains("target"))
        {
            double temp = heater["target"].toDouble();
            _printer->bed()->setTargetTemp(temp);
        }
        if(heater.contains("power"))
        {
            double power = heater["power"].toDouble();
            _printer->bed()->setPower(power);
        }
    }

    if(response["result"].toObject().contains("motion_report"))
    {
        QJsonObject motion = response["result"].toObject()["motion_report"].toObject();
        if(motion.contains("live_position"))
        {
            QJsonArray position = motion["live_position"].toArray();
            if(position.count() == 4)
            {
                qreal x = position[0].toDouble();
                qreal y = position[1].toDouble();
                qreal z = position[2].toDouble();
                qreal e = position[3].toDouble();

                _printer->toolhead()->setPosition(x,y,z);
            }
        }
    }

    if(response["result"].toObject().contains("print_stats"))
    {
        QJsonObject printStats = response["result"].toObject()["print_stats"].toObject();

        if(printStats.contains("filename"))
            _printer->currentJob()->setFilename(printStats["filename"].toString());
        if(printStats.contains("total_duration"))
            _printer->currentJob()->setTotalDuration(printStats["total_duration"].toDouble());
        if(printStats.contains("print_duration"))
            _printer->currentJob()->setPrintDuration(printStats["print_duration"].toDouble());
        if(printStats.contains("filament_used"))
            _printer->currentJob()->setFilamentUsed(printStats["filament_used"].toDouble());
        if(printStats.contains("message"))
            _printer->currentJob()->setMessage(printStats["message"].toString());
        if(printStats.contains("info"))
        {
            QJsonObject printInfo = printStats["info"].toObject();

            if(printInfo.contains(QString("total_layer")))
                _printer->currentJob()->setTotalLayers(printInfo["total_layer"].toInt());
            if(printInfo.contains(QString("current_layer")))
                _printer->currentJob()->setCurrentLayer(printInfo["current_layer"].toInt());
        }
        if(printStats.contains("state"))
            _printer->currentJob()->setState(printStats["state"].toString());
    }

    //Parse known G-Code Macros
    foreach (QString object, _macroObjects)
    {
        if(result.contains(QString("gcode_macro ") + object.toLower()))
        {
            QJsonObject entryObject = result[QString("gcode_macro ") + object.toLower()].toObject();

            QGCodeMacro macro;
            macro.macro = object.toUpper();

            if(entryObject.contains(QString("gcode")))
                macro.gcode = entryObject["gcode"].toString();

            if(entryObject.contains(QString("description")))
                macro.description = entryObject["description"].toString();

            //TODO: parse variable entries

            _gcodeMacros += macro;
        }

        emit serverGCodeMacrosUpdated();
    }

    if(result.contains(QString("gcode")))
    {
        QJsonObject gcodeObject = result["gcode"].toObject();
        QJsonObject commandsObject = gcodeObject["commands"].toObject();
        QStringList keys = commandsObject.keys();

        _gcodeCommands.clear();

        foreach (QString key, keys)
        {
            QJsonObject commandObject = commandsObject[key].toObject();

            QGCodeCommand command;
            command.command = key;
            command.help = commandObject["help"].toString();

            _gcodeCommands.append(command);
        }

        emit serverGCodesUpdated();
    }

    if(result.contains(QString("gcode_move")))
    {
        QJsonObject gcodeObject = result["gcode_move"].toObject();

        QGCodeMove move;
        move.absoluteCoordinates = gcodeObject["absolute_coordinates"].toBool();
        move.absoluteExtrude = gcodeObject["absolute_extrude"].toBool();
        move.extrusionFactor = gcodeObject["extrude_factor"].toDouble();
        move.speed = gcodeObject["speed"].toDouble();
        move.speedFactor = gcodeObject["speed_factor"].toDouble();

        //Gcode position
        QJsonArray gcodePositionArray = gcodeObject["gcode_position"].toArray();

        for(int i = 0; i < gcodePositionArray.count(); i++)
        {
            //0 = X, 1 = Y, 2 = Z, 3 = E, 4+ = E#
            if(i == 0)
                move.gcodePosition["x"] = gcodePositionArray[i].toDouble();
            else if(i == 1)
                move.gcodePosition["y"] = gcodePositionArray[i].toDouble();
            else if(i == 2)
                move.gcodePosition["z"] = gcodePositionArray[i].toDouble();
            else if(i == 3)
                move.gcodePosition["e"] = gcodePositionArray[i].toDouble();
            else if(i > 3)
            {
                qint16 extruderNum = (i - 3);
                QString extruderName = QString("e") + QString::number(extruderNum);
                move.gcodePosition[extruderName] = gcodePositionArray[i].toDouble();
            }
        }

        //Homing Origin position
        QJsonArray homingPositionArray = gcodeObject["homing_origin"].toArray();

        for(int i = 0; i < homingPositionArray.count(); i++)
        {
            //0 = X, 1 = Y, 2 = Z, 3 = E, 4+ = E#
            if(i == 0)
                move.homingOrigin["x"] = homingPositionArray[i].toDouble();
            else if(i == 1)
                move.homingOrigin["y"] = homingPositionArray[i].toDouble();
            else if(i == 2)
                move.homingOrigin["z"] = homingPositionArray[i].toDouble();
            else if(i == 3)
                move.homingOrigin["e"] = homingPositionArray[i].toDouble();
            else if(i > 3)
            {
                qint16 extruderNum = (i - 3);
                QString extruderName = QString("e") + QString::number(extruderNum);
                move.homingOrigin[extruderName] = homingPositionArray[i].toDouble();
            }
        }

        //Position
        QJsonArray positionArray = gcodeObject["position"].toArray();

        for(int i = 0; i < positionArray.count(); i++)
        {
            //0 = X, 1 = Y, 2 = Z, 3 = E, 4+ = E#
            if(i == 0)
                move.position["x"] = positionArray[i].toDouble();
            else if(i == 1)
                move.position["y"] = positionArray[i].toDouble();
            else if(i == 2)
                move.position["z"] = positionArray[i].toDouble();
            else if(i == 3)
                move.position["e"] = positionArray[i].toDouble();
            else if(i > 3)
            {
                qint16 extruderNum = (i - 3);
                QString extruderName = QString("e") + QString::number(extruderNum);
                move.position[extruderName] = positionArray[i].toDouble();
            }
        }

        emit printerGCodeMove(move);
    }

    //Parse bed mesh data
    if(result.contains(QString("bed_mesh")))
    {
        Q3DPrintBed::Mesh bedMesh;

        QJsonObject bedMeshObject = result["bed_mesh"].toObject();
        QJsonArray meshMaxArray = bedMeshObject["mesh_max"].toArray();
        QJsonArray meshMinArray = bedMeshObject["mesh_min"].toArray();

        bedMesh.maximum.x = meshMaxArray[0].toDouble();
        bedMesh.maximum.y = meshMaxArray[1].toDouble();

        bedMesh.minimum.x = meshMinArray[0].toDouble();
        bedMesh.minimum.y = meshMinArray[1].toDouble();

        //Parse the 2D array of probed values
        QJsonArray probedArray = bedMeshObject["probed_matrix"].toArray();
        bedMesh.probed.resize(probedArray.count());

        for(int i = 0; i < probedArray.count(); i++)
        {
            QJsonArray probedEntriesArray = probedArray[i].toArray();
            bedMesh.probed[i].resize(probedEntriesArray.count());

            for(int e = 0; e < probedEntriesArray.count(); e++)
            {
                bedMesh.probed[i][e] = probedEntriesArray[e].toDouble();
            }
        }

        //Parse the 2D array of calculated values
        QJsonArray matrixArray = bedMeshObject["mesh_matrix"].toArray();
        bedMesh.matrix.resize(matrixArray.count());

        for(int i = 0; i < matrixArray.count(); i++)
        {
            QJsonArray matrixEntriesArray = matrixArray[i].toArray();
            bedMesh.matrix[i].resize(matrixEntriesArray.count());

            for(int e = 0; e < matrixEntriesArray.count(); e++)
            {
                bedMesh.matrix[i][e] = matrixEntriesArray[e].toDouble();
            }
        }

        //Parse profile data
        QJsonArray profilesArray = bedMeshObject["profiles"].toArray();
        bedMesh.profileName = bedMeshObject["profile_name"].toString();

        for(int i = 0; i < profilesArray.count(); i++)
            bedMesh.profiles += profilesArray[i].toString();

        _printer->bed()->setBedMesh(bedMesh);
    }

    //Parse stepper motor activity
    if(result.contains(QString("stepper_enable")))
    {
        QJsonObject stepperEnabledObject = result["stepper_enable"].toObject();
        QJsonObject steppersObject = stepperEnabledObject["steppers"].toObject();
        QStringList keys = steppersObject.keys();

        foreach(QString key, keys)
        {
            if(!_printer->stepperMotors().contains(key))
                _printer->stepperMotors().insert(key, new QStepperMotor(_printer));

            _printer->stepperMotors()[key]->setEnabled(steppersObject[key].toBool());
        }
    }

    //Parse manual probe status
    if(result.contains(QString("manual_probe")))
    {
        QJsonObject probeObject = result["manual_probe"].toObject();

        Printer::ProbeData probeData = _printer->probeData();

        if(probeObject.contains("is_active"))
            probeData.isManual = probeObject["is_active"].toBool();

        if(probeObject.contains("z_position"))
            probeData.zPosition = probeObject["z_position"].toDouble();

        if(probeObject.contains("z_position_lower"))
            probeData.zPositionLower = probeObject["z_position_lower"].toDouble();

        if(probeObject.contains("z_position_upper"))
            probeData.zPositionUpper = probeObject["z_position_upper"].toDouble();

        probeData.name = "Manual Probe";

        _printer->setProbeData(probeData);
    }

    //Parse probe status
    if(result.contains(QString("probe")))
    {
        QJsonObject probeObject = result["probe"].toObject();

        Printer::ProbeData probeData = _printer->probeData();

        if(probeObject.contains("last_query"))
            probeData.lastQuery = probeObject["last_query"].toBool();

        if(probeObject.contains("last_z_result"))
            probeData.zPosition = probeObject["last_z_result"].toDouble();

        if(probeObject.contains("name"))
            probeData.name = probeObject["name"].toString();

        _printer->setProbeData(probeData);
    }

    //Parse virtual SD card status
    if(result.contains(QString("virtual_sdcard")))
    {
        QJsonObject virtualSDObject = result["virtual_sdcard"].toObject();

        System::VirtualSDCard virtualSDCard = _printer->system()->virtualSDCard();

        if(virtualSDObject.contains("file_path"))
            virtualSDCard.filePath = virtualSDObject["file_path"].toString();

        if(virtualSDObject.contains("file_position"))
            virtualSDCard.filePosition = virtualSDObject["file_position"].toInt();

        if(virtualSDObject.contains("file_size"))
            virtualSDCard.fileSize = virtualSDObject["file_size"].toInt();

        if(virtualSDObject.contains("is_active"))
            virtualSDCard.active = virtualSDObject["is_active"].toBool();

        if(virtualSDObject.contains("progress"))
            virtualSDCard.progress = virtualSDObject["progress"].toDouble();

        _printer->system()->setVirtualSDCard(virtualSDCard);
    }

    //Parse declared fan objects
    foreach(QString key, _subscriptionObjects)
    {
        //Check for heater_fan objects
        if(key.startsWith(QString("heater_fan")))
        {
            if(result.contains(key))
            {
                if(!_printer->fans().contains(key))
                    _printer->fans()[key] = new Fan(_printer);

                QJsonObject fanObject = result[key].toObject();

                if(fanObject.contains(QString("rpm")))
                    _printer->fans()[key]->setRpm(fanObject["rpm"].toDouble());

                if(fanObject.contains(QString("speed")))
                    _printer->fans()[key]->setSpeed(fanObject["speed"].toDouble());

            }
        }

        //Check for controller_fan objects
        else if(key.startsWith(QString("controller_fan")))
        {
            if(result.contains(key))
            {
                if(!_printer->fans().contains(key))
                    _printer->fans()[key] = new Fan(_printer);

                QJsonObject fanObject = result[key].toObject();

                if(fanObject.contains(QString("rpm")))
                    _printer->fans()[key]->setRpm(fanObject["rpm"].toDouble());

                if(fanObject.contains(QString("speed")))
                    _printer->fans()[key]->setSpeed(fanObject["speed"].toDouble());

            }
        }
    }

    //Parse adjustment screw settings
    if(result.contains(QString("screws_tilt_adjust")))
    {
        QJsonObject screwsTiltObject = result["screws_tilt_adjust"].toObject();
        QJsonObject screwsTiltResultsObject = screwsTiltObject["results"].toObject();

        if(screwsTiltResultsObject.contains(QString("error")))
            _printer->bed()->setAdjustmentScrewsError(screwsTiltResultsObject["error"].toBool());

        if(screwsTiltResultsObject.contains(QString("max_deviation")))
            _printer->bed()->setAdjustmentScrewsMaxDeviation(screwsTiltResultsObject["max_deviation"].toDouble());

        for(int i = 1; ; i++)
        {
            QString screwString = QString("screw") + QString::number(i);

            if(!screwsTiltResultsObject.contains(screwString))
                break;

            QJsonObject screwObject = screwsTiltResultsObject[screwString].toObject();

            Q3DPrintBed::AdjustmentScrew *adjustmentScrew = _printer->bed()->adjustmentScrew(screwString);

            if(adjustmentScrew == nullptr)
                adjustmentScrew = new Q3DPrintBed::AdjustmentScrew();

            if(screwObject.contains(QString("adjust")))
                adjustmentScrew->adjustment.amount = screwObject["adjust"].toString();

            if(screwObject.contains(QString("is_base")))
                adjustmentScrew->adjustment.isBase = screwObject["is_base"].toBool();

            if(screwObject.contains(QString("sign")))
            {
                QString sign = screwObject["sign"].toString();
                adjustmentScrew->adjustment.sign = sign;

                if(sign == QString("CW"))
                    adjustmentScrew->adjustment.direction = Q3DPrintBed::AdjustmentScrew::Adjustment::Clockwise;
                else if(sign == QString("CCW"))
                    adjustmentScrew->adjustment.direction = Q3DPrintBed::AdjustmentScrew::Adjustment::CounterClockwise;
            }

            if(screwObject.contains(QString("z")))
                adjustmentScrew->adjustment.z = screwObject["z"].toDouble();

            _printer->bed()->setAdjustmentScrew(screwString, adjustmentScrew);
        }
    }

    if(!hasState(Connected))
    {
        addState(Connected);
        emit printerOnline();
    }

    emit printerUpdate();

    emit printerUpdateReceived(response);
}

void QAbstractKlipperConsole::on_printerEmergencyStop(KlipperResponse response)
{
    if(response["result"].isString())
    {
        QString result = response["result"].toString();

        if(result.toLower() == QString("ok"))
            emit printerEmergencyStopped();
    }
}

void QAbstractKlipperConsole::on_printerQueryEndstops(KlipperResponse response)
{
    if(response["result"].isObject())
    {
        QJsonObject result = response["result"].toObject();

        if(result.contains("x"))
        {
            QString status = result["x"].toString();
            _printer->endstopStatus().setX(status.toLower() == QString("triggered"));
        }

        if(result.contains("y"))
        {
            QString status = result["y"].toString();
            _printer->endstopStatus().setY(status.toLower() == QString("triggered"));
        }

        if(result.contains("z"))
        {
            QString status = result["z"].toString();
            _printer->endstopStatus().setZ(status.toLower() == QString("triggered"));
        }
    }
}

void QAbstractKlipperConsole::on_serverInfo(KlipperResponse response)
{
    if(response["result"].isObject())
    {
        QJsonObject result = response["result"].toObject();

        if(result["klippy_connected"].toBool())
        {
            if(!hasState(Connected))
            {
                if(_klipperRestartTimer)
                {
                    _klipperRestartTimer->stop();
                    delete _klipperRestartTimer;

                    _klipperRestartTimer = nullptr;
                }

                addState(Connected);
                emit klipperConnected();
            }
            if(result["klippy_state"].toString() == "ready")
            {
            }
            else if(result["klippy_state"].toString() == "error")
            {
                addState(Error);
                emit klipperError(QString("Klipper Error"), QString("Moonraker connected, but klipper is not."));
            }
        }
        else
        {
            emit klipperDisconnected();
            emit klipperError(QString("Klipper Disconnected"), QString("Lost connection with Klipper"));
        }

        if(result.contains(QString("warnings")))
        {
            QJsonArray warningArray = result[QString("warnings")].toArray();

            for(int i = 0; i < warningArray.count(); i++)
                emit klipperError(QString("Warning!"), warningArray[i].toString());
        }

        if(result.contains(QString("components")))
        {
            QJsonArray componentsArray = result[QString("components")].toArray();

            for(int i = 0; i < componentsArray.count(); i++)
                _moonrakerComponents += componentsArray[i].toString();
        }

        if(result.contains(QString("failed_components")))
        {
            QJsonArray componentsArray = result[QString("failed_components")].toArray();
            _moonrakerFailedComponents.clear();

            for(int i = 0; i < componentsArray.count(); i++)
                _moonrakerFailedComponents += componentsArray[i].toString();

            if(_moonrakerFailedComponents.count())
            {
                QString message = QString("Moonraker failed to load the following componenets:") + _moonrakerFailedComponents.join(QString(", "));
            }
        }

        emit printerUpdate();
    }
}

void QAbstractKlipperConsole::on_serverConfig(KlipperResponse response)
{
    if(response["result"].isObject())
    {
        QJsonObject result = response["result"].toObject();

        if(result.contains(QString("config")))
        {
            QJsonObject config = result["config"].toObject();


        }
    }
}

void QAbstractKlipperConsole::on_serverFileRoots(KlipperResponse response)
{
    if(response["result"].isArray())
    {
        foreach(QJsonValueConstRef reference, response["result"].toArray())
        {
            if(reference.isObject())
            {
                QJsonObject referenceObject = reference.toObject();
                if(referenceObject.contains(QString("name")))
                {
                    if(referenceObject["name"] == QString("gcodes"))
                    {
                        _printer->setGcodesLocation(referenceObject["path"].toString());
                    }
                    else if(referenceObject["name"] == QString("config"))
                    {
                        _printer->setConfigLocation(referenceObject["path"].toString());
                    }
                    else if(referenceObject["name"] == QString("config_examples"))
                        ;
                    else if(referenceObject["name"] == QString("docs"))
                        ;
                }
            }
        }

        emit printerUpdate();
    }
}

void QAbstractKlipperConsole::on_serverTemperatureStore(KlipperResponse response)
{
    if(response["result"].isObject())
    {
        QJsonObject result = response["result"].toObject();

        for(int index = 0; true; index++)
        {
            QString extruderName = QString("extruder") + ((index > 0) ? QString::number(index) : QString(""));

            if(result.contains(extruderName))
            {
                //The documentation suggests that the count for each of these arrays should be the same
                QJsonArray temperatureValuesArray = result[extruderName].toObject()["temperatures"].toArray();
                QJsonArray targetValuesArray = result[extruderName].toObject()["targets"].toArray();
                QJsonArray powerValuesArray = result[extruderName].toObject()["targets"].toArray();

                int count = temperatureValuesArray.count();

                for(int i = 0; i < count; i++)
                {
                    TemperatureStoreValue storedValue;

                    storedValue.temperature = temperatureValuesArray[i].toDouble();
                    storedValue.target = targetValuesArray[i].toDouble();
                    storedValue.power = powerValuesArray[i].toDouble();

                    _printer->toolhead()->extruder(index)->temperatureStore().append(storedValue);
                }
            }
            else
                break;
        }

        emit printerUpdate();
    }
}

void QAbstractKlipperConsole::on_serverGCodeStore(KlipperResponse response)
{
    if(response["result"].isObject())
    {
        QJsonObject result = response["result"].toObject();

        if(result["gcode_store"].isArray())
        {
            GCodeStore store;

            QJsonArray gCodeEntries = result["gcode_store"].toArray();
            int count = gCodeEntries.count();

            for(int i = 0; i < count; i++)
            {
                GCodeStoreValue gCode;

                QJsonObject gCodeEntry = gCodeEntries.at(i).toObject();

                if(gCodeEntry.contains(QString("message")))
                    gCode.message = gCodeEntry["message"].toString();

                if(gCodeEntry.contains(QString("time")))
                    gCode.time = gCodeEntry["time"].toDouble();

                if(gCodeEntry.contains(QString("type")))
                {
                    if(gCodeEntry["type"] == QString("command"))
                        gCode.type = GCodeStoreValue::Command;
                    else
                        gCode.type = GCodeStoreValue::Response;
                }

                store.append(gCode);
            }

            emit serverGCodeStoreResponse(store);
        }
    }
}

void QAbstractKlipperConsole::on_serverLogsRollover(KlipperResponse response)
{
    if(response["result"].isObject())
    {
        QJsonObject result = response["result"].toObject();

        if(!result["failed"].toObject().isEmpty())
        {
            QJsonObject failures = result["failed"].toObject();

            QJsonObject::Iterator failureIterator = failures.begin();

            while(!failureIterator->isNull())
            {
                QString application = failureIterator.key();
                QString message = failureIterator.value().toString();

                emit klipperError(QString("Could not rollover logfile ") + application, message);
            }
        }
        else
            emit serverLogsRolloverSuccess();
    }
}

void QAbstractKlipperConsole::on_serverWebsocketId(KlipperResponse response)
{
    if(response["result"].isObject())
    {
        QJsonObject result = response["result"].toObject();

        if(result.contains("websocket_id"))
            _printer->clientIdentifier().setWebsocketId(result["websocket_id"].toInt());
    }
}

void QAbstractKlipperConsole::on_serverFilesMetadata(KlipperResponse response)
{
    if(response["result"].isObject())
    {
        QJsonObject result = response["result"].toObject();
        KlipperFile::Metadata metadata;

        metadata.printStartTime = result["print_start_time"].toDouble();
        metadata.jobId = result["job_id"].toInt();
        metadata.size = result["size"].toInt();
        metadata.modified = result["modified"].toDouble();
        metadata.slicer = result["slicer"].toString();
        metadata.slicerVersion = result["slicer_version"].toString();
        metadata.layerHeight = result["layer_height"].toDouble();
        metadata.firstLayerHeight = result["first_layer_height"].toDouble();
        metadata.objectHeight = result["object_height"].toDouble();
        metadata.filamentTotal = result["filament_total"].toDouble();
        metadata.estimatedTime = result["estimated_time"].toInt();
        metadata.firstLayerBedTemp = result["first_layer_bed_temp"].toDouble();
        metadata.firstLayerExtruderTemp = result["first_layer_extr_temp"].toDouble();
        metadata.gcodeStartByte = result["gcode_start_byte"].toInt();
        metadata.gcodeEndByte = result["gcode_end_byte"].toInt();
        metadata.filename = result["filename"].toString();

        QJsonArray thumbnailArray = result["thumbnails"].toArray();

        for(int i = 0; i < thumbnailArray.count(); i++)
        {
            KlipperFile::Metadata::Thumbnail thumbnail;

            thumbnail.height = result["height"].toInt();
            thumbnail.width = result["width"].toInt();
            thumbnail.size = result["size"].toInt();
            thumbnail.relativePath = result["relative_path"].toString();

            metadata.thumbnails.append(thumbnail);
        }

        emit serverMetadataResult(metadata);
    }
}

void QAbstractKlipperConsole::on_serverWebcamList(KlipperResponse response)
{
    if(response["result"].isObject())
    {
        QJsonObject result = response["result"].toObject();
        QJsonArray webcamArray = result["webcams"].toArray();

        _printer->system()->webcams().clear();

        for(int i = 0; i < webcamArray.count(); i++)
        {
            QJsonObject webcamObject = webcamArray[i].toObject();
            System::Webcam webcam;

            webcam.name = webcamObject["name"].toString();
            webcam.location = webcamObject["location"].toString();
            webcam.service = webcamObject["service"].toString();
            webcam.enabled = webcamObject["enabled"].toBool();
            webcam.iconString = webcamObject["icon"].toString();
            webcam.targetFps = webcamObject["target_fps"].toInt();
            webcam.targetFpsIdle = webcamObject["target_fps_idle"].toInt();
            webcam.streamUrl = webcamObject["stream_url"].toString();
            webcam.snapshotUrl = webcamObject["snapshot_url"].toString();
            webcam.flipHorizontal = webcamObject["flip_horizontal"].toBool();
            webcam.flipVertical = webcamObject["flip_vertical"].toBool();
            webcam.rotation = webcamObject["aspect_ratio"].toInt();
            webcam.aspectRatio = webcamObject["aspect_ratio"].toString();
            webcam.source = webcamObject["source"].toString();
            webcam.uid = webcamObject["uid"].toString();

            _printer->system()->webcams().append(webcam);
        }
    }
}

void QAbstractKlipperConsole::on_serverWebcamCreate(KlipperResponse response)
{
    if(response["result"].isObject())
    {
        QJsonObject result = response["result"].toObject();
        QJsonObject webcamObject = result["webcam"].toObject();
        System::Webcam webcam;

        webcam.name = webcamObject["name"].toString();
        webcam.location = webcamObject["location"].toString();
        webcam.service = webcamObject["service"].toString();
        webcam.enabled = webcamObject["enabled"].toBool();
        webcam.iconString = webcamObject["icon"].toString();
        webcam.targetFps = webcamObject["target_fps"].toInt();
        webcam.targetFpsIdle = webcamObject["target_fps_idle"].toInt();
        webcam.streamUrl = webcamObject["stream_url"].toString();
        webcam.snapshotUrl = webcamObject["snapshot_url"].toString();
        webcam.flipHorizontal = webcamObject["flip_horizontal"].toBool();
        webcam.flipVertical = webcamObject["flip_vertical"].toBool();
        webcam.rotation = webcamObject["aspect_ratio"].toInt();
        webcam.aspectRatio = webcamObject["aspect_ratio"].toString();
        webcam.source = webcamObject["source"].toString();
        webcam.uid = webcamObject["uid"].toString();

        bool found = false;

        for(int i = 0; i < _printer->system()->webcams().count(); i++)
        {
            System::Webcam listedCamera = _printer->system()->webcams().at(i);

            if(webcam.uid == listedCamera.uid)
            {
                found = true;
                _printer->system()->webcams().replace(i, webcam);
                break;
            }
        }

        if(!found)
        {
            _printer->system()->webcams().append(webcam);
            emit serverWebcamCreated(webcam);
        }
        else
            emit serverWebcamsListed();
    }
}

void QAbstractKlipperConsole::on_serverWebcamDelete(KlipperResponse response)
{
    if(response["result"].isObject())
    {
        QJsonObject result = response["result"].toObject();
        QJsonObject webcamObject = result["webcam"].toObject();
        System::Webcam webcam;

        webcam.name = webcamObject["name"].toString();
        webcam.location = webcamObject["location"].toString();
        webcam.service = webcamObject["service"].toString();
        webcam.enabled = webcamObject["enabled"].toBool();
        webcam.iconString = webcamObject["icon"].toString();
        webcam.targetFps = webcamObject["target_fps"].toInt();
        webcam.targetFpsIdle = webcamObject["target_fps_idle"].toInt();
        webcam.streamUrl = webcamObject["stream_url"].toString();
        webcam.snapshotUrl = webcamObject["snapshot_url"].toString();
        webcam.flipHorizontal = webcamObject["flip_horizontal"].toBool();
        webcam.flipVertical = webcamObject["flip_vertical"].toBool();
        webcam.rotation = webcamObject["aspect_ratio"].toInt();
        webcam.aspectRatio = webcamObject["aspect_ratio"].toString();
        webcam.source = webcamObject["source"].toString();
        webcam.uid = webcamObject["uid"].toString();

        emit serverWebcamDeleted(webcam);
    }
}

void QAbstractKlipperConsole::on_serverAnnouncementsList(KlipperResponse response)
{
    if(response["result"].isObject())
    {
        QJsonObject result = response["result"].toObject();
        QJsonArray announcementArray = result["entries"].toArray();

        _printer->system()->announcements().clear();

        for(int i = 0; i < announcementArray.count(); i++)
        {
            QJsonObject announcementObject = announcementArray[i].toObject();
            System::Announcement announcement;

            announcement.entryId = announcementObject["entry_id"].toString();
            announcement.url = announcementObject["url"].toString();
            announcement.title = announcementObject["title"].toString();
            announcement.description = announcementObject["description"].toString();
            announcement.priority = announcementObject["priority"].toString();
            announcement.date = announcementObject["date"].toDouble();
            announcement.dismissed = announcementObject["dismissed"].toBool();
            announcement.dateDismissed = announcementObject["date_dismissed"].toDouble();
            announcement.dateDismissedWake = announcementObject["dismiss_wake"].toDouble();
            announcement.source = announcementObject["source"].toString();
            announcement.feed = announcementObject["feed"].toString();

            _printer->system()->announcements().append(announcement);
        }

        emit serverAnnouncementsListed();
    }
}

void QAbstractKlipperConsole::on_serverAnnouncementsUpdate(KlipperResponse response)
{
    if(response["result"].isObject())
    {
        QJsonObject result = response["result"].toObject();

        if(result["modified"].toBool() || _printer->system()->announcements().isEmpty())
            on_serverAnnouncementsList(response);
    }
}

void QAbstractKlipperConsole::on_serverAnnouncementDismissed(KlipperResponse response)
{
    if(response["result"].isObject())
    {
        QJsonObject result = response["result"].toObject();
        QString entryId = result["entry_id"].toString();

        for(int i = 0; i < _printer->system()->announcements().count(); i++)
        {
            System::Announcement announcement = _printer->system()->announcements().at(i);

            if(entryId == announcement.entryId)
            {
                _printer->system()->announcements().remove(i);

                emit serverAnnouncementDismissed(entryId);

                break;
            }
        }
    }
}

void QAbstractKlipperConsole::on_serverJobQueueStatus(KlipperResponse response)
{
    if(response["result"].isObject())
    {
        QJsonObject result = response["result"].toObject();
        QJsonArray jobArray = result["queued_jobs"].toArray();

        System::JobQueue queue = _printer->system()->jobQueue();

        for(int i = 0; i < jobArray.count(); i++)
        {
            QJsonObject jobObject = jobArray[i].toObject();

            System::JobQueue::Job job;
            job.filename = jobObject["filename"].toString();
            job.id = jobObject["job_id"].toString();
            job.timeAdded = jobObject["time_added"].toDouble();
            job.timeInQueue = jobObject["time_in_queue"].toDouble();

            queue.queue.append(job);
        }

        if(result["queue_state"].toString() == QString("loading"))
            queue.queueState = System::JobQueue::Loading;

        else if(result["queue_state"].toString() == QString("paused"))
            queue.queueState = System::JobQueue::Paused;

        else if(result["queue_state"].toString() == QString("starting"))
            queue.queueState = System::JobQueue::Starting;

        else if(result["queue_state"].toString() == QString("ready"))
            queue.queueState = System::JobQueue::Ready;

        else
            queue.queueState = System::JobQueue::Error;

        _printer->system()->setJobQueue(queue);

        emit systemUpdate();
    }
}

void QAbstractKlipperConsole::on_accessLogin(KlipperResponse response)
{
    if(response["result"].isObject())
    {
        QJsonObject result = response["result"].toObject();

        System::AccessDetails accessDetails;
        accessDetails.isLoggedIn = true;
        accessDetails.token = result["token"].toString();
        accessDetails.refreshToken = result["refresh_token"].toString();

        accessDetails.user.username = result["username"].toString();
        accessDetails.user.source = result["source"].toString();

        _printer->system()->setAccessDetails(accessDetails);
    }
}

void QAbstractKlipperConsole::on_accessLogout(KlipperResponse response)
{
    if(response["result"].isObject())
    {
        QJsonObject result = response["result"].toObject();

        System::AccessDetails accessDetails = _printer->system()->accessDetails();
        accessDetails.isLoggedIn = false;
        accessDetails.refreshToken = QString();
        accessDetails.token = QString();

        _printer->system()->setAccessDetails(accessDetails);
    }
}

void QAbstractKlipperConsole::on_accessGetUser(KlipperResponse response)
{
    if(response["result"].isObject())
    {
        QJsonObject result = response["result"].toObject();
        System::AccessDetails accessDetails = _printer->system()->accessDetails();

        accessDetails.user.username = result["username"].toString();
        accessDetails.user.source = result["source"].toString();
        accessDetails.user.createdOn = result["created_on"].toDouble();

        _printer->system()->setAccessDetails(accessDetails);
    }
}

void QAbstractKlipperConsole::on_accessCreateUser(KlipperResponse response)
{
    if(response["result"].isObject())
    {
        QJsonObject result = response["result"].toObject();

        System::AccessDetails accessDetails;
        accessDetails.isLoggedIn = true;
        accessDetails.token = result["token"].toString();
        accessDetails.refreshToken = result["refresh_token"].toString();

        accessDetails.user.username = result["username"].toString();
        accessDetails.user.source = result["source"].toString();

        _printer->system()->setAccessDetails(accessDetails);

        accessGetUser();

        emit accessUserCreated(accessDetails.user);
    }
}

void QAbstractKlipperConsole::on_accessDeleteUser(KlipperResponse response)
{
    if(response["result"].isObject())
    {
        QJsonObject result = response["result"].toObject();
        System::User user;

        user.username = result["username"].toString();
        user.source = result["source"].toString();

        for(int i = 0; i < _printer->system()->userList().count(); i++)
        {
            System::User checkedUser = _printer->system()->userList().at(i);

            if(user.username == checkedUser.username)
            {
                _printer->system()->userList().remove(i);

                emit accessUserDeleted(user);

                break;
            }
        }
    }
}

void QAbstractKlipperConsole::on_accessUsersList(KlipperResponse response)
{
    if(response["result"].isObject())
    {
        QJsonObject result = response["result"].toObject();
        QJsonArray userArray = result["users"].toArray();

        for(int i = 0; i < userArray.count(); i++)
        {
            QJsonObject userObject = userArray[i].toObject();

            System::User user;
            user.username = userObject["username"].toString();
            user.source = userObject["source"].toString();
            user.createdOn = userObject["created_on"].toDouble();
        }

        emit accessUsersListed();
    }
}

void QAbstractKlipperConsole::on_accessUserPasswordReset(KlipperResponse response)
{
    if(response["result"].isObject())
    {
        QJsonObject result = response["result"].toObject();
        System::AccessDetails accessDetails = _printer->system()->accessDetails();

        accessDetails.user.username = result["username"].toString();
        accessDetails.user.source = result["source"].toString();
        accessDetails.user.createdOn = result["created_on"].toDouble();

        _printer->system()->setAccessDetails(accessDetails);

        emit accessUserPasswordResetSuccessful();
    }
}

void QAbstractKlipperConsole::on_clientIdentifier(KlipperResponse response)
{
    if(response["result"].isObject())
    {
        QJsonObject result = response["result"].toObject();

        if(result.contains("connection_id"))
            _printer->clientIdentifier().setWebsocketId(result["connection_id"].toInt());
    }
}
