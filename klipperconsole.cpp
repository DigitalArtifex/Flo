#include "klipperconsole.h"
#include "types/printer.h"
#include "system/settings.h"

KlipperConsole::KlipperConsole(Printer *parent)
{
    this->klipperSocket = new QLocalSocket();

    _klipperRestartTimer = new QTimer();
    _klipperRestartTimer->setInterval(3000);
    connect(_klipperRestartTimer, SIGNAL(timeout()), this, SLOT(on_klipperRestartTimer_timeout()));

    _printer = parent;
}

KlipperConsole::~KlipperConsole()
{
    if(this->klipperSocket->isOpen())
    {
        //TODO proper shutdown
        this->klipperSocket->close();
    }

    delete messageReadTimer;
    delete _messageParseTimer;
}

void KlipperConsole::sendCommand(QString command, KlipperMessage::MessageOrigin origin)
{
    KlipperMessage message;
    QJsonObject messageObject = message.document();
    messageObject["method"] = command;
    message.setDocument(messageObject);
    message.origin = origin;

    this->sendCommand(message);
}

void KlipperConsole::sendCommand(KlipperMessage message)
{
    if(message.commandLock && !this->commandLocked)
    {
        this->commandLocked = true;
        this->lockId = message.id;
        emit(commandLock());
    }

    QByteArray document = message.toRpc(QJsonDocument::Compact);
    klipperMessageBuffer[message["id"].toInt()] = message;
    this->klipperSocket->write(document);
    emit(commandSent(message.toRpc(QJsonDocument::Indented)));
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

    if(this->messageReadTimer == NULL)
    {
        messageReadTimer = new QTimer(this);
        messageReadTimer->setTimerType(Qt::CoarseTimer);
        messageReadTimer->setInterval(50);

        connect(messageReadTimer, SIGNAL(timeout()), this, SLOT(on_messageReadTimer()));

        messageReadTimer->start();
    }

    if(this->_messageParseTimer == nullptr)
    {
        _messageParseTimer = new QTimer(this);
        _messageParseTimer->setTimerType(Qt::CoarseTimer);
        _messageParseTimer->setInterval(60);

        connect(_messageParseTimer, SIGNAL(timeout()), this, SLOT(on_messageParseTimer()));

        _messageParseTimer->start();
    }

    this->klipperSocket->connectToServer();

    if(!this->klipperSocket->waitForConnected())
    {
        this->sendError("Could not connect to local socket");
        return;
    }

    _moonrakerConnected = true;
    emit(moonrakerConnected());

    //Startup commands to get base information
    this->sendPreset("Client Identifier");
    serverInfo();
    serverConfig();
    serverFileRoots();
    printerInfo();
    this->sendPreset("sub.toolhead");
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

    emit(fileDirectoryChanged(directory));
    this->sendCommand(message);
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

    this->sendCommand(message);
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

    this->sendCommand(message);
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

    this->sendCommand(message);
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

    this->sendCommand(message);
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

    this->sendCommand(message);
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

    this->sendCommand(message);
}

void KlipperConsole::pausePrint()
{
    KlipperMessage message;
    QJsonObject messageObject = message.document();

    messageObject["method"] = "printer.print.pause";

    message.setDocument(messageObject);

    this->sendCommand(message);
}

void KlipperConsole::resumePrint()
{
    KlipperMessage message;
    QJsonObject messageObject = message.document();

    messageObject["method"] = "printer.print.resume";

    message.setDocument(messageObject);

    this->sendCommand(message);
}

void KlipperConsole::cancelPrint()
{
    KlipperMessage message;
    QJsonObject messageObject = message.document();

    messageObject["method"] = "printer.print.cancel";

    message.setDocument(messageObject);

    this->sendCommand(message);
}

void KlipperConsole::machineShutdown()
{
    KlipperMessage message;
    QJsonObject messageObject = message.document();

    messageObject["method"] = "machine.shutdown";

    message.setDocument(messageObject);

    this->sendCommand(message);
}

void KlipperConsole::machineReboot()
{
    KlipperMessage message;
    QJsonObject messageObject = message.document();

    messageObject["method"] = "machine.reboot";

    message.setDocument(messageObject);

    this->sendCommand(message);
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

    this->sendCommand(message);
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

    this->sendCommand(message);
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

    this->sendCommand(message);
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

    this->sendCommand(message);
}

void KlipperConsole::printerInfo()
{

    KlipperMessage message;
    QJsonObject messageObject = message.document();
    QJsonObject paramsObject;

    messageObject["method"] = "printer.info";

    message.setDocument(messageObject);

    this->sendCommand(message);
}

void KlipperConsole::restartKlipper()
{
    KlipperMessage message;
    QJsonObject messageObject = message.document();
    QJsonObject paramsObject;

    messageObject["method"] = "printer.restart";

    message.setDocument(messageObject);

    this->sendCommand(message);
}

void KlipperConsole::restartFirmware()
{
    KlipperMessage message;
    QJsonObject messageObject = message.document();
    QJsonObject paramsObject;

    messageObject["method"] = "printer.firmware_restart";

    message.setDocument(messageObject);

    this->sendCommand(message);
}

void KlipperConsole::serverInfo()
{
    KlipperMessage message;
    QJsonObject messageObject = message.document();
    QJsonObject paramsObject;

    messageObject["method"] = "server.info";

    message.setDocument(messageObject);

    this->sendCommand(message);
}

void KlipperConsole::serverConfig()
{
    KlipperMessage message;
    QJsonObject messageObject = message.document();
    QJsonObject paramsObject;

    messageObject["method"] = "server.config";

    message.setDocument(messageObject);

    this->sendCommand(message);
}

void KlipperConsole::serverFileRoots()
{
    KlipperMessage message;
    QJsonObject messageObject = message.document();
    QJsonObject paramsObject;

    messageObject["method"] = "server.files.roots";

    message.setDocument(messageObject);

    this->sendCommand(message);
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

    this->on_messageReceived(response);
}

void KlipperConsole::on_messageReceived(KlipperResponse message)
{
    emit(responseReceived(message));

    if(this->commandLocked)
    {
        this->commandLocked = false;
        emit(commandUnlock());
    }
}

void KlipperConsole::on_messageReadTimer()
{
    if(this->klipperSocket->isOpen())
    {
        while(this->klipperSocket->bytesAvailable() > 0)
            this->messageBuffer += this->klipperSocket->readAll();
    }

    if(messageBuffer.contains((char)0x03))
    {
        int index = messageBuffer.indexOf((char)0x03);
        QByteArray responseData = messageBuffer.mid(0, index + 1);
        messageBuffer.remove(0, index + 1);

        if(responseData.endsWith((char)0x03))
            responseData.remove(responseData.length() - 1, 1);

        messageQueue.enqueue(responseData);
    }
}

void KlipperConsole::on_messageParseTimer()
{
    if(messageQueue.isEmpty())
        return;

    QByteArray responseData = messageQueue.dequeue();
    QJsonParseError responseDocumentError;
    QJsonDocument responseDocument(QJsonDocument::fromJson(responseData, &responseDocumentError));

    if(responseDocumentError.error != QJsonParseError::NoError)
    {
        this->sendError("Invalid response from local socket");
        return;
    }

    KlipperResponse response;
    response.rootObject = responseDocument.object();

    if(!response.rootObject.contains("error"))
        response.status = KlipperResponse::OK;

    response.timestamp = QDateTime::currentDateTime();

    if(!response.rootObject.contains("method"))
    {
        response["method"] = klipperMessageBuffer[response["id"].toInt()]["method"];
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

                    if(homed.contains(QString("x")))
                        _printer->toolhead()->setXHomed(true);
                    else
                        _printer->toolhead()->setXHomed(false);

                    if(homed.contains(QString("y")))
                        _printer->toolhead()->setYHomed(true);
                    else
                        _printer->toolhead()->setYHomed(false);

                    if(homed.contains(QString("z")))
                        _printer->toolhead()->setZHomed(true);
                    else
                        _printer->toolhead()->setZHomed(false);
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
                //in seconds?
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
                this->getFileList(path);
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
                this->getFileList(path);
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
                this->getFileList(path);
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
                            Settings::set(QString("system.klipper.gcode_location"), referenceObject["path"].toString());
                        }
                        else if(referenceObject["name"] == QString("config"))
                        {
                            Settings::set(QString("system.klipper.config_location"), referenceObject["path"].toString());
                        }
                        else if(referenceObject["name"] == QString("config_examples"))
                        {
                            Settings::set(QString("system.klipper.config_examples_location"), referenceObject["path"].toString());
                        }
                        else if(referenceObject["name"] == QString("docs"))
                        {
                            Settings::set(QString("system.klipper.docs_location"), referenceObject["path"].toString());
                        }
                    }
                }
            }

            Settings::save();
        }

        this->getFileList(QString("gcodes"));
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
                    file.fileLocation = fileObject["path"].toString();
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
            QJsonObject result = response["result"].toObject();
            QJsonArray files = result["files"].toArray();
            QJsonArray directories = result["dirs"].toArray();
            QList<KlipperFile> fileList;

            foreach(QJsonValueConstRef directoryRef, directories)
            {
                if(directoryRef.isObject())
                {
                    QJsonObject directoryObject = directoryRef.toObject();
                    KlipperFile directory;
                    directory.fileLocation = directoryObject["dirname"].toString();
                    directory.fileSize = directoryObject["size"].toDouble();
                    directory.dateModified = directoryObject["modified"].toDouble();
                    directory.type = KlipperFile::Directory;
                    fileList.append(directory);
                }
            }

            foreach(QJsonValueConstRef fileRef, files)
            {
                if(fileRef.isObject())
                {
                    QJsonObject fileObject = fileRef.toObject();
                    KlipperFile file;
                    file.fileLocation = fileObject["filename"].toString();
                    file.fileSize = fileObject["size"].toDouble();
                    file.dateModified = fileObject["modified"].toDouble();
                    file.type = KlipperFile::GCode;
                    fileList.append(file);
                }
            }

            emit(fileListReceived(fileList));
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
        this->sendPreset("sub.toolhead");
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

        emit(printerUpdate());
        emit(systemUpdate());
    }

    if(response["method"] != QString("notify_proc_stat_update"))
        emit(responseReceived(response));

    if(response["id"] == this->lockId)
    {
        this->commandLocked = false;
        this->lockId = 0;
        emit(commandUnlock());
    }
}

void KlipperConsole::on_klipperRestartTimer_timeout()
{
    serverInfo();
}
