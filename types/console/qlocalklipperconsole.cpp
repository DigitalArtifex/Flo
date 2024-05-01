#include "qlocalklipperconsole.h"
#include "../../system/settings.h"

QLocalKlipperConsole::QLocalKlipperConsole(Printer *printer, QObject *parent)
    : QAbstractKlipperConsole(printer,parent)
{
    _printer = printer;

    QLocalSocket *socket = new QLocalSocket(parent);
    setMoonrakerSocket((QAbstractSocket*)socket);

    addState(Startup);

    //Startup commands to get base information
    _startupSequence.enqueue((StartupFunction)&QLocalKlipperConsole::clientIdentifier);
    _startupSequence.enqueue((StartupFunction)&QLocalKlipperConsole::serverInfo);
    _startupSequence.enqueue((StartupFunction)&QLocalKlipperConsole::serverConfig);
    _startupSequence.enqueue((StartupFunction)&QLocalKlipperConsole::serverFileRoots);
    _startupSequence.enqueue((StartupFunction)&QLocalKlipperConsole::printerInfo);
    _startupSequence.enqueue((StartupFunction)&QLocalKlipperConsole::printerSubscribe);
}

QLocalKlipperConsole::~QLocalKlipperConsole()
{
    if(_moonrakerSocket->isOpen())
    {
        //TODO proper shutdown
        _moonrakerSocket->close();
    }
}

void QLocalKlipperConsole::shutdown()
{
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

void QLocalKlipperConsole::sendCommand(KlipperMessage message)
{
    QByteArray document = message.toRpc(QJsonDocument::Compact);
    _klipperMessageBuffer[message["id"].toInt()] = message;
    qint64 length = _moonrakerSocket->write(document);

    if(length != document.length())
    {
        qDebug() << QString("Failed to write data") << length << document.length();
    }

    QFile file(QDir::homePath() + QDir::separator() + QString("poop.test"));
    if(file.open(QFile::ReadWrite | QFile::Append))
    {
        file.write(message.toRpc(QJsonDocument::Indented));
        file.close();
    }

    emit commandSent(message);
}

void QLocalKlipperConsole::setMoonrakerLocation(QString location)
{
    _moonrakerLocation = location;
}

void QLocalKlipperConsole::connectToMoonraker()
{
    if(_moonrakerSocket->isOpen())
        return;

    addState(Connecting);

    ((QLocalSocket*)_moonrakerSocket)->setServerName(_moonrakerLocation);
    ((QLocalSocket*)_moonrakerSocket)->connectToServer();

    if(!((QLocalSocket*)_moonrakerSocket)->waitForConnected())
    {
        qDebug() << QString("Failed to connect to moonraker");
        sendError("Could not connect to local socket");
        return;
    }

    _isMoonrakerConnected = true;
    emit moonrakerConnected();

    if(_startupSequence.count())
    {
        StartupFunction function = _startupSequence.dequeue();
        (this->*function)();
    }
}

void QLocalKlipperConsole::disconnectKlipper()
{
    ((QLocalSocket*)_moonrakerSocket)->disconnectFromServer();
    ((QLocalSocket*)_moonrakerSocket)->waitForDisconnected();

    emit klipperDisconnected();
}

void QLocalKlipperConsole::getFileList(QString directory)
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

void QLocalKlipperConsole::deleteFile(QString file)
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

void QLocalKlipperConsole::deleteFile(KlipperFile file)
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

QString QLocalKlipperConsole::downloadFile(KlipperFile file)
{
    if(_connectionLoaction == LocationLocal)
    {
        QString rootLocation;

        if(file.type == KlipperFile::GCode)
            rootLocation = _printer->gcodesLocation();
        else if(file.type == KlipperFile::Config)
            rootLocation = _printer->configLocation();

        QFile localFile(rootLocation + QDir::separator() + file.fileLocation());
        QString localFileData;

        if(localFile.open(QFile::ReadOnly))
        {
            localFileData = localFile.readAll();
            localFile.close();
        }

        return localFileData;
    }

    return QString();
}

bool QLocalKlipperConsole::uploadFile(QString root, QString directory, QString name, QByteArray data)
{
    if(_connectionLoaction == LocationLocal)
    {
        QString rootLocation;
        QString localFileLocation;

        if(directory.endsWith(QDir::separator()))
            directory.removeLast();

        if(root == QString("gcodes"))
            rootLocation = _printer->gcodesLocation();
        else if(root == QString("config"))
            rootLocation = _printer->configLocation();

        if(directory.isEmpty())
            localFileLocation = rootLocation + QDir::separator() + name;
        else
            localFileLocation = rootLocation + QDir::separator() + directory + QDir::separator() + name;

        if(QFile::exists(localFileLocation))
            QFile::moveToTrash(localFileLocation);

        QFile localFile(localFileLocation);
        QString localFileData;

        if(localFile.open(QFile::WriteOnly))
        {
            localFile.write(data);
            localFile.close();
        }

        return true;
    }

    return false;
}

void QLocalKlipperConsole::moveFile(QString source, QString destination)
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

void QLocalKlipperConsole::copyFile(QString source, QString destination)
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

void QLocalKlipperConsole::createDirectory(QString directory)
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

void QLocalKlipperConsole::deleteDirectory(QString directory)
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

void QLocalKlipperConsole::startPrint(QString file)
{
    KlipperMessage message;
    QJsonObject messageObject = message.document();
    QJsonObject paramsObject;

    messageObject["method"] = "printer.print.start";

    paramsObject["filename"] = file;
    messageObject["params"] = paramsObject;

    message.setDocument(messageObject);

    sendCommand(message);
}

void QLocalKlipperConsole::pausePrint()
{
    KlipperMessage message;
    QJsonObject messageObject = message.document();

    messageObject["method"] = "printer.print.pause";

    message.setDocument(messageObject);

    sendCommand(message);
}

void QLocalKlipperConsole::resumePrint()
{
    KlipperMessage message;
    QJsonObject messageObject = message.document();

    messageObject["method"] = "printer.print.resume";

    message.setDocument(messageObject);

    sendCommand(message);
}

void QLocalKlipperConsole::cancelPrint()
{
    KlipperMessage message;
    QJsonObject messageObject = message.document();

    messageObject["method"] = "printer.print.cancel";

    message.setDocument(messageObject);

    sendCommand(message);
}

void QLocalKlipperConsole::machineShutdown()
{
    KlipperMessage message;
    QJsonObject messageObject = message.document();

    messageObject["method"] = "machine.shutdown";

    message.setDocument(messageObject);

    sendCommand(message);
}

void QLocalKlipperConsole::machineReboot()
{
    KlipperMessage message;
    QJsonObject messageObject = message.document();

    messageObject["method"] = "machine.reboot";

    message.setDocument(messageObject);

    sendCommand(message);
}

void QLocalKlipperConsole::serviceRestart(QString service)
{
    KlipperMessage message;
    QJsonObject messageObject = message.document();
    QJsonObject paramsObject;

    messageObject["method"] = "machine.services.restart";

    paramsObject["service"] = service;
    messageObject["params"] = paramsObject;

    message.setDocument(messageObject);

    sendCommand(message);
}

void QLocalKlipperConsole::serviceStop(QString service)
{
    KlipperMessage message;
    QJsonObject messageObject = message.document();
    QJsonObject paramsObject;

    messageObject["method"] = "machine.services.stop";

    paramsObject["service"] = service;
    messageObject["params"] = paramsObject;

    message.setDocument(messageObject);

    sendCommand(message);
}

void QLocalKlipperConsole::serviceStart(QString service)
{
    KlipperMessage message;
    QJsonObject messageObject = message.document();
    QJsonObject paramsObject;

    messageObject["method"] = "machine.services.start";

    paramsObject["service"] = service;
    messageObject["params"] = paramsObject;

    message.setDocument(messageObject);

    sendCommand(message);
}

void QLocalKlipperConsole::sendGcode(QString gcode)
{
    KlipperMessage message;
    QJsonObject messageObject = message.document();
    QJsonObject paramsObject;

    messageObject["method"] = "printer.gcode.script";

    paramsObject["script"] = gcode;
    messageObject["params"] = paramsObject;

    message.setDocument(messageObject);

    sendCommand(message);
}

void QLocalKlipperConsole::printerInfo()
{

    KlipperMessage message;
    QJsonObject messageObject = message.document();
    QJsonObject paramsObject;

    messageObject["method"] = "printer.info";

    message.setDocument(messageObject);

    sendCommand(message);
}

void QLocalKlipperConsole::restartKlipper()
{
    KlipperMessage message;
    QJsonObject messageObject = message.document();
    QJsonObject paramsObject;

    messageObject["method"] = "printer.restart";

    message.setDocument(messageObject);

    sendCommand(message);
}

void QLocalKlipperConsole::restartFirmware()
{
    KlipperMessage message;
    QJsonObject messageObject = message.document();
    QJsonObject paramsObject;

    messageObject["method"] = "printer.firmware_restart";

    message.setDocument(messageObject);

    sendCommand(message);
}

void QLocalKlipperConsole::printerSubscribe()
{
    KlipperMessage message;
    QJsonObject messageObject = message.document();
    QJsonObject paramsObject;
    QJsonObject objectArray;

    objectArray["toolhead"];

    for(int i = 0; i < _printer->toolhead()->extruderCount(); i++)
    {
        QString extruderName = QString("extruder") + ((i > 0) ? QString::number(i) : QString(""));
        objectArray[extruderName];
    }

    objectArray["bed_mesh"];
    objectArray["heater_bed"];
    objectArray["fan"];
    objectArray["gcode_move"];
    objectArray["print_stats"];
    //This needs to be expanded to fans in the config file
    objectArray["heater_fan heatbreak_cooling_fan"];
    objectArray["motion_report"];

    paramsObject["objects"] = objectArray;

    messageObject["method"] = "printer.objects.subscribe";
    messageObject["params"] = paramsObject;

    message.setDocument(messageObject);

    sendCommand(message);
}

void QLocalKlipperConsole::serverInfo()
{
    KlipperMessage message;
    QJsonObject messageObject = message.document();
    QJsonObject paramsObject;

    messageObject["method"] = "server.info";

    message.setDocument(messageObject);

    sendCommand(message);
}

void QLocalKlipperConsole::serverConfig()
{
    KlipperMessage message;
    QJsonObject messageObject = message.document();
    QJsonObject paramsObject;

    messageObject["method"] = "server.config";

    message.setDocument(messageObject);

    sendCommand(message);
}

void QLocalKlipperConsole::serverFileRoots()
{
    KlipperMessage message;
    QJsonObject messageObject = message.document();
    QJsonObject paramsObject;

    messageObject["method"] = "server.files.roots";

    message.setDocument(messageObject);

    sendCommand(message);
}

void QLocalKlipperConsole::clientIdentifier()
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

QLocalKlipperConsole::ConnectionLocation QLocalKlipperConsole::connectionLoaction() const
{
    return _connectionLoaction;
}

void QLocalKlipperConsole::setConnectionLoaction(ConnectionLocation connectionLoaction)
{
    _connectionLoaction = connectionLoaction;
}
