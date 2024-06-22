#include "qlocalklipperconsole.h"
#include "../../system/settings.h"

QLocalKlipperConsole::QLocalKlipperConsole(Printer *printer, QObject *parent)
    : QAbstractKlipperConsole(printer,parent)
{
    m_printer = printer;

    QLocalSocket *socket = new QLocalSocket(parent);
    setMoonrakerSocket((QAbstractSocket*)socket);

    addState(Startup);
}

QLocalKlipperConsole::~QLocalKlipperConsole()
{
    if(m_moonrakerSocket->isOpen())
    {
        //TODO proper shutdown
        m_moonrakerSocket->close();
    }
}

void QLocalKlipperConsole::shutdown()
{
}

void QLocalKlipperConsole::sendCommand(KlipperMessage message)
{
    QByteArray document = message.toRpc(QJsonDocument::Compact);
    m_klipperMessageBuffer[message["id"].toInt()] = message;
    qint64 length = m_moonrakerSocket->write(document);

    if(length != document.length())
    {
        qDebug() << QString("Failed to write data") << length << document.length();
    }

    emit commandSent(message);
}

void QLocalKlipperConsole::connectToMoonraker()
{
    if(m_moonrakerSocket->isOpen())
        return;

    addState(Connecting);

    ((QLocalSocket*)m_moonrakerSocket)->setServerName(m_moonrakerLocation);
    ((QLocalSocket*)m_moonrakerSocket)->connectToServer();

    if(!((QLocalSocket*)m_moonrakerSocket)->waitForConnected())
    {
        qDebug() << QString("Failed to connect to moonraker");
        sendError("Could not connect to local socket");
        return;
    }

    m_isMoonrakerConnected = true;
    emit moonrakerConnected();

    if(m_startupSequence.count())
    {
        StartupFunction function = m_startupSequence.dequeue();
        (this->*function)();
    }
}

void QLocalKlipperConsole::disconnectKlipper()
{
    ((QLocalSocket*)m_moonrakerSocket)->disconnectFromServer();
    ((QLocalSocket*)m_moonrakerSocket)->waitForDisconnected();

    emit klipperDisconnected();
}



QString QLocalKlipperConsole::downloadFile(KlipperFile file)
{
    if(m_connectionLoaction == LocationLocal)
    {
        QString rootLocation;

        if(file.type == KlipperFile::GCode)
            rootLocation = m_printer->gcodesLocation();
        else if(file.type == KlipperFile::Config)
            rootLocation = m_printer->configLocation();

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
    if(m_connectionLoaction == LocationLocal)
    {
        QString rootLocation;
        QString localFileLocation;

        if(directory.endsWith(QDir::separator()))
            directory.removeLast();

        if(root == QString("gcodes"))
            rootLocation = m_printer->gcodesLocation();
        else if(root == QString("config"))
            rootLocation = m_printer->configLocation();

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
