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
    _startupSequence.enqueue((StartupFunction)&QLocalKlipperConsole::printerObjectsList);
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
