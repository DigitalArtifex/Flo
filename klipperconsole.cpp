#include "klipperconsole.h"
#include "types/printer.h"
#include "system/settings.h"

KlipperConsole::KlipperConsole(Printer *printer, QObject *parent) : QObject(parent)
{
    _printer = printer;

    klipperSocket = new QLocalSocket(parent);
    connect(klipperSocket, SIGNAL(readyRead()), this, SLOT(on_klipperSocket_readyRead()));

    _klipperRestartTimer = new QTimer(parent);
    _klipperRestartTimer->setInterval(3000);
    connect(_klipperRestartTimer, SIGNAL(timeout()), this, SLOT(on_klipperRestartTimer_timeout()));
}

KlipperConsole::~KlipperConsole()
{
    if(klipperSocket->isOpen())
    {
        //TODO proper shutdown
        klipperSocket->close();
    }

    delete messageReadTimer;
    delete _messageParseTimer;
}

void KlipperConsole::shutdown()
{
    _shutdown = true;
}

void KlipperConsole::sendCommand(QString command, KlipperMessage::MessageOrigin origin)
{
    KlipperMessage message;
    QJsonObject messageObject = message.document();
    messageObject["method"] = command;
    message.setDocument(messageObject);
    message.origin = origin;

    sendCommand(message);
}

void KlipperConsole::sendCommand(KlipperMessage message)
{
    if(message.commandLock && !commandLocked)
    {
        commandLocked = true;
        lockId = message.id;
        emit(commandLock());
    }

    QByteArray document = message.toRpc(QJsonDocument::Compact);
    klipperMessageBuffer[message["id"].toInt()] = message;
    qint64 length = klipperSocket->write(document);

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

void KlipperConsole::setMoonrakerLocation(QString location)
{
    _moonrakerLocation = location;
}

void KlipperConsole::connectKlipper()
{
    if(klipperSocket->isOpen())
        return;

    _startup = true;
    klipperSocket->setServerName(_moonrakerLocation);
    klipperSocket->connectToServer();

    if(!klipperSocket->waitForConnected())
    {
        qDebug() << QString("Failed to connect to moonraker");
        sendError("Could not connect to local socket");
        return;
    }

    _moonrakerConnected = true;
    emit(moonrakerConnected());

    //Startup commands to get base information
    clientIdentifier();
    serverInfo();
    serverConfig();
    serverFileRoots();
    printerInfo();
    printerSubscribe();
}

void KlipperConsole::disconnectKlipper()
{

}

void KlipperConsole::loadPresets()
{
    qDebug() << "Presets";

    QDir presetDir(QString(Settings::get("system.preset_location").toString()));

    if(!presets.isEmpty())
        presets.empty();

    if(presetDir.exists())
    {
        QDirIterator directoryIterator(presetDir.absolutePath(), QDir::Dirs | QDir::NoSymLinks | QDir::NoDotAndDotDot, QDirIterator::Subdirectories);

        while(directoryIterator.hasNext())
        {
            directoryIterator.next();

            QDir subdirectory(presetDir.absolutePath() + QDir::separator() + directoryIterator.fileName());
            QStringList subdirectoryFiles = subdirectory.entryList(QStringList() << "*.json" << "*.JSON",QDir::Files);

            if(subdirectoryFiles.isEmpty())
                continue;

            foreach(QString subdirectoryFile, subdirectoryFiles)
            {
                //Load the JSON information
                QFile documentFile(subdirectory.absolutePath() + QDir::separator() + subdirectoryFile);

                qDebug() << ">> " + subdirectory.absolutePath() + QDir::separator() + subdirectoryFile;

                if(!documentFile.open(QFile::ReadOnly))
                    continue;

                QJsonParseError documentError;
                QJsonDocument document = QJsonDocument::fromJson(documentFile.readAll(), &documentError);

                documentFile.close();

                //TODO: Error log
                if(documentError.error != QJsonParseError::NoError)
                    continue;

                QJsonObject documentObject = document.object();

                ConsolePreset preset;
                preset.file = subdirectory.absolutePath() + QDir::separator() + subdirectoryFile;
                preset.icon = documentObject["icon"].toString();
                preset.name = documentObject["name"].toString();
                preset.type = documentObject["type"].toString();

                presets[documentObject["name"].toString()] = preset;
            }
        }
    }
}

QList<ConsolePreset> KlipperConsole::getPresetList()
{
    return presets.values();
}

void KlipperConsole::sendPreset(QString key, KlipperMessage::MessageOrigin origin)
{
    //Load the JSON information
    QFile documentFile(presets[key].file);

    if(!documentFile.open(QFile::ReadOnly))
        return;

    QJsonParseError documentError;
    QJsonDocument document = QJsonDocument::fromJson(documentFile.readAll(), &documentError);

    documentFile.close();

    //TODO: Error log
    if(documentError.error != QJsonParseError::NoError)
        return;

    QJsonObject documentObject = document.object();
    QJsonObject presetObject = documentObject["preset"].toObject();

    KlipperMessage presetMessage;
    presetMessage.origin = origin;
    presetMessage.setDocument(presetObject);

    sendCommand(presetMessage);
}

void KlipperConsole::getFileList(QString directory)
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

void KlipperConsole::deleteFile(QString file)
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

void KlipperConsole::deleteFile(KlipperFile file)
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

QString KlipperConsole::downloadFile(KlipperFile file)
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

bool KlipperConsole::uploadFile(QString root, QString directory, QString name, QByteArray data)
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

void KlipperConsole::moveFile(QString source, QString destination)
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

void KlipperConsole::copyFile(QString source, QString destination)
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

void KlipperConsole::createDirectory(QString directory)
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

void KlipperConsole::deleteDirectory(QString directory)
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

void KlipperConsole::startPrint(QString file)
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

void KlipperConsole::pausePrint()
{
    KlipperMessage message;
    QJsonObject messageObject = message.document();

    messageObject["method"] = "printer.print.pause";

    message.setDocument(messageObject);

    sendCommand(message);
}

void KlipperConsole::resumePrint()
{
    KlipperMessage message;
    QJsonObject messageObject = message.document();

    messageObject["method"] = "printer.print.resume";

    message.setDocument(messageObject);

    sendCommand(message);
}

void KlipperConsole::cancelPrint()
{
    KlipperMessage message;
    QJsonObject messageObject = message.document();

    messageObject["method"] = "printer.print.cancel";

    message.setDocument(messageObject);

    sendCommand(message);
}

void KlipperConsole::machineShutdown()
{
    KlipperMessage message;
    QJsonObject messageObject = message.document();

    messageObject["method"] = "machine.shutdown";

    message.setDocument(messageObject);

    sendCommand(message);
}

void KlipperConsole::machineReboot()
{
    KlipperMessage message;
    QJsonObject messageObject = message.document();

    messageObject["method"] = "machine.reboot";

    message.setDocument(messageObject);

    sendCommand(message);
}

void KlipperConsole::serviceRestart(QString service)
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

void KlipperConsole::serviceStop(QString service)
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

void KlipperConsole::serviceStart(QString service)
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

void KlipperConsole::sendGcode(QString gcode)
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

void KlipperConsole::printerInfo()
{

    KlipperMessage message;
    QJsonObject messageObject = message.document();
    QJsonObject paramsObject;

    messageObject["method"] = "printer.info";

    message.setDocument(messageObject);

    sendCommand(message);
}

void KlipperConsole::restartKlipper()
{
    KlipperMessage message;
    QJsonObject messageObject = message.document();
    QJsonObject paramsObject;

    messageObject["method"] = "printer.restart";

    message.setDocument(messageObject);

    sendCommand(message);
}

void KlipperConsole::restartFirmware()
{
    KlipperMessage message;
    QJsonObject messageObject = message.document();
    QJsonObject paramsObject;

    messageObject["method"] = "printer.firmware_restart";

    message.setDocument(messageObject);

    sendCommand(message);
}

void KlipperConsole::printerSubscribe()
{
    KlipperMessage message;
    QJsonObject messageObject = message.document();
    QJsonObject paramsObject;
    QJsonObject objectArray;

    objectArray["toolhead"];
    objectArray["extruder"];
    objectArray["bed_mesh"];
    objectArray["heater_bed"];
    objectArray["fan"];
    objectArray["gcode_move"];
    //This needs to be expanded to fans in the config file
    objectArray["heater_fan heatbreak_cooling_fan"];
    objectArray["motion_report"];

    paramsObject["objects"] = objectArray;

    messageObject["method"] = "printer.objects.subscribe";
    messageObject["params"] = paramsObject;

    message.setDocument(messageObject);

    sendCommand(message);
}

void KlipperConsole::serverInfo()
{
    KlipperMessage message;
    QJsonObject messageObject = message.document();
    QJsonObject paramsObject;

    messageObject["method"] = "server.info";

    message.setDocument(messageObject);

    sendCommand(message);
}

void KlipperConsole::serverConfig()
{
    KlipperMessage message;
    QJsonObject messageObject = message.document();
    QJsonObject paramsObject;

    messageObject["method"] = "server.config";

    message.setDocument(messageObject);

    sendCommand(message);
}

void KlipperConsole::serverFileRoots()
{
    KlipperMessage message;
    QJsonObject messageObject = message.document();
    QJsonObject paramsObject;

    messageObject["method"] = "server.files.roots";

    message.setDocument(messageObject);

    sendCommand(message);
}

void KlipperConsole::clientIdentifier()
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

void KlipperConsole::sendError(QString message)
{
    KlipperResponse response;
    response.status = KlipperResponse::FAIL;
    QJsonObject messageObject;
    QJsonObject errorObject;

    errorObject["message"] = message;
    errorObject["code"] = -1;
    messageObject["error"] = errorObject;

    response.setDocument(messageObject);

    on_messageReceived(response);
}

KlipperConsole::ConnectionLocation KlipperConsole::connectionLoaction() const
{
    return _connectionLoaction;
}

void KlipperConsole::setConnectionLoaction(ConnectionLocation connectionLoaction)
{
    _connectionLoaction = connectionLoaction;
}

void KlipperConsole::on_messageReceived(KlipperResponse message)
{
    emit(responseReceived(message));

    if(commandLocked)
    {
        commandLocked = false;
        emit(commandUnlock());
    }
}

void KlipperConsole::on_klipperSocket_readyRead()
{
    if(klipperSocket->isOpen())
    {
        while(klipperSocket->bytesAvailable() > 0)
            messageBuffer += klipperSocket->readAll();
    }

    if(messageBuffer.contains((char)0x03))
    {
        int index = messageBuffer.indexOf((char)0x03);
        QByteArray responseData = messageBuffer.mid(0, index + 1);
        messageBuffer.remove(0, index + 1);

        if(responseData.endsWith((char)0x03))
            responseData.remove(responseData.length() - 1, 1);

        messageQueue.enqueue(responseData);

        QtConcurrent::run([this]{
            on_messageParse();
        });
    }
}

void KlipperConsole::on_messageParse()
{
    if(messageQueue.isEmpty())
        return;

    QByteArray responseData = messageQueue.dequeue();
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
        origin = klipperMessageBuffer[response["id"].toInt()];
        response["method"] = origin["method"];
        response.origin = (KlipperResponse::ResponseOrigin)klipperMessageBuffer[response["id"].toInt()].origin;
        klipperMessageBuffer.remove(response["id"].toInt());
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
        emit(systemUpdate());
    }
    else if(response["method"] == QString("server.info"))
    {
        QJsonObject result = response["result"].toObject();

        if(result["klippy_connected"].toBool())
        {
            if(!_klipperConnected)
            {
                _klipperConnected = true;
                _klipperRestartTimer->stop();
                emit(klipperConnected());
            }
            if(result["klippy_state"].toString() == "ready")
            {
            }
            else if(result["klippy_state"].toString() == "error")
            {
                emit klipperError(result["error"].toString(), result["message"].toString());
            }

        }
        else
        {
            _klipperConnected = false;
            _klipperRestartTimer->start();
            emit(klipperDisconnected());
        }
    }
    else if(response["method"] == QString("notify_status_update") || response["method"] == QString("printer.objects.subscribe"))
    {
        if(!_printerConnected)
        {
            _printerConnected = true;
            emit(printerOnline());
        }
        //Parse extruders
        for(int index = 0; true; index++)
        {
            QString extruderName = QString("extruder");

            if(index > 0)
                extruderName += QString::number(index);

            if(!response["result"].toObject().contains(extruderName))
                break;

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
            }
            if(toolhead.contains("max_accel"))
            {
                //double
            }
            if(toolhead.contains("max_accel_to_decel"))
            {
                //double
            }
            if(toolhead.contains("max_velocity"))
            {
                //double
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
                //int
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

        emit(printerUpdate());

        emit(printerUpdateReceived(response));
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
    else if(response["method"] == QString("server.files.post_directory"))
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
    else if(response["method"] == QString("server.files.delete_directory"))
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
    else if(response["method"] == QString("server.files.roots"))
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
        }

        emit(printerUpdate());
    }
    else if(response["method"] == QString("server.files.list"))
    {
        if(response["result"].isArray())
        {
            QJsonArray files = response["result"].toArray();
            QList<KlipperFile> fileList;

            foreach(QJsonValueConstRef fileRef, files)
            {
                if(fileRef.isObject())
                {
                    QJsonObject fileObject = fileRef.toObject();
                    KlipperFile file;
                    file.name = fileObject["path"].toString();
                    file.fileSize = fileObject["size"].toDouble();
                    file.dateModified = fileObject["modified"].toDouble();
                    fileList.append(file);
                }
            }

            emit(fileListReceived(fileList));
        }
    }
    else if(response["method"] == QString("server.files.get_directory"))
    {
        if(response["result"].isObject())
        {
            QJsonObject originObject = origin.document();
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
    else if(response["method"] == QString("notify_klippy_disconnected"))
    {
        _klipperConnected = false;
        _klipperRestartTimer->start();

        emit(klipperDisconnected());
    }
    else if(response["method"] == QString("notify_klippy_ready"))
    {
        _klipperConnected = true;
        _klipperRestartTimer->stop();
        emit(klipperConnected());
        printerSubscribe();
    }
    else if(response["method"] == QString("printer.info"))
    {
        QJsonObject result = response["result"].toObject();
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
            _printer->setStatusMessage(result["state_message"].toString());
        if(result.contains(QString("software_version")))
            _printer->setFirmwareVersion(result["software_version"].toString());

        if(result.contains(QString("cpu_info")))
            _printer->system()->setCpuInfo(result["cpu_info"].toString());
        if(result.contains(QString("hostname")))
            _printer->system()->setHostname(result["hostname"].toString());

        if(_startup)
        {
            _startup = false;
            emit(printerFound());
        }

        emit printerUpdate();
        emit systemUpdate();
    }

    if(response["method"] != QString("notify_proc_stat_update"))
        emit responseReceived(response);

    if(response["id"] == lockId)
    {
        commandLocked = false;
        lockId = 0;
        emit commandUnlock();
    }
}

void KlipperConsole::on_klipperRestartTimer_timeout()
{
    serverInfo();
}
