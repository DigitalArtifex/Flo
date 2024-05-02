#include "qabstractklipperconsole.h"

#include "../printer.h"

QAbstractKlipperConsole::QAbstractKlipperConsole(Printer *printer, QObject *parent)
{
    _parserMap[QString("server.connection.identify")] = (ParserFunction)&QAbstractKlipperConsole::on_clientIdentifier;
    _parserMap[QString("server.info")] = (ParserFunction)&QAbstractKlipperConsole::on_serverInfo;
    _parserMap[QString("notify_status_update")] = (ParserFunction)&QAbstractKlipperConsole::on_printerSubscribe;
    _parserMap[QString("printer.objects.subscribe")] = (ParserFunction)&QAbstractKlipperConsole::on_printerSubscribe;
    _parserMap[QString("server.files.post_directory")] = (ParserFunction)&QAbstractKlipperConsole::on_createDirectory;
    _parserMap[QString("server.files.delete_directory")] = (ParserFunction)&QAbstractKlipperConsole::on_deleteDirectory;
    _parserMap[QString("server.files.roots")] = (ParserFunction)&QAbstractKlipperConsole::on_serverFileRoots;
    _parserMap[QString("server.files.get_directory")] = (ParserFunction)&QAbstractKlipperConsole::on_getFileList;
    _parserMap[QString("server.temperature_store")] = (ParserFunction)&QAbstractKlipperConsole::on_serverTemperatureStore;
    _parserMap[QString("server.files.list")] = (ParserFunction)&QAbstractKlipperConsole::on_getFileList;
    _parserMap[QString("printer.info")] = (ParserFunction)&QAbstractKlipperConsole::on_printerInfo;
}

QAbstractKlipperConsole::~QAbstractKlipperConsole()
{

}

void QAbstractKlipperConsole::connectToMoonraker()
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

    sendCommand(message);
}

void QAbstractKlipperConsole::pausePrint()
{
    KlipperMessage message;
    QJsonObject messageObject = message.document();

    messageObject["method"] = "printer.print.pause";

    message.setDocument(messageObject);

    sendCommand(message);
}

void QAbstractKlipperConsole::resumePrint()
{
    KlipperMessage message;
    QJsonObject messageObject = message.document();

    messageObject["method"] = "printer.print.resume";

    message.setDocument(messageObject);

    sendCommand(message);
}

void QAbstractKlipperConsole::cancelPrint()
{
    KlipperMessage message;
    QJsonObject messageObject = message.document();

    messageObject["method"] = "printer.print.cancel";

    message.setDocument(messageObject);

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

void QAbstractKlipperConsole::serviceRestart(QString service)
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

void QAbstractKlipperConsole::serviceStop(QString service)
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

void QAbstractKlipperConsole::serviceStart(QString service)
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

void QAbstractKlipperConsole::sendGcode(QString gcode)
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

void QAbstractKlipperConsole::printerSubscribe()
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

void QAbstractKlipperConsole::serverLogsRollover()
{
    KlipperMessage message;
    QJsonObject messageObject = message.document();
    messageObject["method"] = "server.logs.rollover";

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
            _dataBuffer += _moonrakerSocket->readAll();
    }

    if(_dataBuffer.contains((char)0x03))
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

    if(!response.rootObject.contains("error"))
        response.status = KlipperResponse::OK;

    response.setId(response["id"].toInt());

    response.timestamp = QDateTime::currentDateTime();

    if(!response.rootObject.contains("method"))
    {
        origin = _klipperMessageBuffer[response["id"].toInt()];
        response["message"] = origin.document();
        response["method"] = origin["method"];
        response.origin = (KlipperResponse::ResponseOrigin)_klipperMessageBuffer[response["id"].toInt()].origin;
        _klipperMessageBuffer.remove(response["id"].toInt());
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

    if(response["method"].toString().startsWith("notify") && response["method"] != QString("notify_status_update"))
    {
        if(response["method"] == QString("notify_proc_stat_update"))
        {
            //Parse heatbed status
            if(response["result"].toObject().contains("system_cpu_usage"))
            {
                int cpuCount = 0;
                QJsonObject cpuLoadArray = response["result"].toObject()["system_cpu_usage"].toObject();

                QJsonObject::Iterator cpuIterator;
                QList<qreal> cpus;

                for(cpuIterator = cpuLoadArray.begin(); cpuIterator != cpuLoadArray.end(); cpuIterator++)
                {
                    cpus.append(cpuIterator->toDouble());
                    cpuCount++;
                }
                _printer->system()->setCpuCount(cpuCount);
                _printer->system()->setCpuList(cpus);
            }

            //Parse heatbed status
            if(response["result"].toObject().contains("system_memory"))
            {
                QJsonObject memoryLoadObject = response["result"].toObject()["system_memory"].toObject();
                _printer->system()->setMemoryCapacity(memoryLoadObject["total"].toDouble());
                _printer->system()->setMemoryUsage(memoryLoadObject["used"].toDouble());
            }
            emit systemUpdate();
        }
        else if(response["method"] == QString("notify_klippy_disconnected"))
        {
            removeState(Connected);
            emit klipperDisconnected();
        }
        else if(response["method"] == QString("notify_klippy_ready"))
        {
            addState(Connected);
            emit klipperConnected();
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
        }
    }
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
        QJsonObject originObject = response["message"].toObject();
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

}

void QAbstractKlipperConsole::on_pausePrint(KlipperResponse response)
{

}

void QAbstractKlipperConsole::on_resumePrint(KlipperResponse response)
{

}

void QAbstractKlipperConsole::on_cancelPrint(KlipperResponse response)
{

}

void QAbstractKlipperConsole::on_machineShutdown(KlipperResponse response)
{

}

void QAbstractKlipperConsole::on_machineReboot(KlipperResponse response)
{

}

void QAbstractKlipperConsole::on_serviceRestart(KlipperResponse response)
{

}

void QAbstractKlipperConsole::on_serviceStop(KlipperResponse response)
{

}

void QAbstractKlipperConsole::on_serviceStart(KlipperResponse response)
{

}

void QAbstractKlipperConsole::on_sendGcode(KlipperResponse response)
{

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

        if(result.contains(QString("cpu_info")))
            _printer->system()->setCpuInfo(result["cpu_info"].toString());
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

void QAbstractKlipperConsole::on_printerSubscribe(KlipperResponse response)
{
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

    //Parse toolhead status
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

    if(!hasState(Connected))
    {
        addState(Connected);

        emit printerOnline();
    }

    emit printerUpdate();

    emit printerUpdateReceived(response);
}

void QAbstractKlipperConsole::on_serverInfo(KlipperResponse response)
{
    QJsonObject result = response["result"].toObject();

    if(result["klippy_connected"].toBool())
    {
        if(!hasState(Connected))
        {
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

    emit printerUpdate();
}

void QAbstractKlipperConsole::on_serverConfig(KlipperResponse response)
{

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
            }
        }
    }
}

void QAbstractKlipperConsole::on_clientIdentifier(KlipperResponse response)
{
    qDebug() << QString("Client ID");
}
