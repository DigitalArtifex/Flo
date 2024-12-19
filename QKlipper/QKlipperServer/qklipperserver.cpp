#include "qklipperserver.h"
#include "QKlipper/QKlipperConsole/qklipperconsole.h"

QKlipperServer::QKlipperServer(QObject *parent)
    : QObject{parent}
{
    m_gcodeStore = new QKlipperGCodeStore(this);
    m_jobQueue = new QKlipperJobQueue(this);
}

QKlipperServer::~QKlipperServer()
{
    if(m_gcodeStore)
        m_gcodeStore->deleteLater();

    if(m_jobQueue)
        m_jobQueue->deleteLater();

    foreach(QKlipperFile *file, m_fileSystem)
    {
        if(file)
        {
            file->deleteLater();
            file = nullptr;
        }
    }
}

QString QKlipperServer::moonrakerLocation() const
{
    return m_moonrakerLocation;
}

void QKlipperServer::setMoonrakerLocation(const QString &moonrakerLocation)
{
    if (m_moonrakerLocation == moonrakerLocation)
        return;

    m_moonrakerLocation = moonrakerLocation;
    emit moonrakerLocationChanged();
}

void QKlipperServer::resetMoonrakerLocation()
{
    setMoonrakerLocation({}); // TODO: Adapt to use your actual default value
}

QString QKlipperServer::klipperLocation() const
{
    return m_klipperLocation;
}

void QKlipperServer::setKlipperLocation(const QString &klipperLocation)
{
    if (m_klipperLocation == klipperLocation)
        return;
    m_klipperLocation = klipperLocation;
    emit klipperLocationChanged();
}

void QKlipperServer::resetKlipperLocation()
{
    setKlipperLocation({}); // TODO: Adapt to use your actual default value
}

QString QKlipperServer::gcodesLocation() const
{
    return m_gcodesLocation;
}

void QKlipperServer::setGcodesLocation(const QString &gcodesLocation)
{
    if (m_gcodesLocation == gcodesLocation)
        return;

    m_gcodesLocation = gcodesLocation;

    if(!m_gcodesLocation.endsWith("/"))
        m_gcodesLocation += "/";

    emit gcodesLocationChanged();
}

void QKlipperServer::resetGcodesLocation()
{
    setGcodesLocation({}); // TODO: Adapt to use your actual default value
}

QString QKlipperServer::configLocation() const
{
    return m_configLocation;
}

void QKlipperServer::setConfigLocation(const QString &configLocation)
{
    if (m_configLocation == configLocation)
        return;

    m_configLocation = configLocation;

    if(!m_configLocation.endsWith("/"))
        m_configLocation += "/";

    emit configLocationChanged();
}

void QKlipperServer::resetConfigLocation()
{
    setConfigLocation({}); // TODO: Adapt to use your actual default value
}

QString QKlipperServer::instanceLocation() const
{
    return m_instanceLocation;
}

void QKlipperServer::setInstanceLocation(const QString &instanceLocation)
{
    if (m_instanceLocation == instanceLocation)
        return;

    m_instanceLocation = instanceLocation;

    if(!m_instanceLocation.endsWith(QDir::separator()))
        m_instanceLocation += QDir::separator();

    emit instanceLocationChanged();
}

void QKlipperServer::resetInstanceLocation()
{
    setInstanceLocation({}); // TODO: Adapt to use your actual default value
}

QString QKlipperServer::apiKey() const
{
    return m_apiKey;
}

void QKlipperServer::setApiKey(const QString &apiKey)
{
    if (m_apiKey == apiKey)
        return;

    m_apiKey = apiKey;
    emit apiKeyChanged();
}

void QKlipperServer::resetApiKey()
{
    setApiKey({}); // TODO: Adapt to use your actual default value
}

QString QKlipperServer::address() const
{
    QString address = QString("http://%1:%2").arg(m_address, QString::number(m_port));
    return address;
}

QString QKlipperServer::websocketAddress() const
{
    if(m_connectionType == Remote)
    {
        QString websocket = QString("ws://%1:%2/websocket").arg(m_address, QString::number(m_port));
        return websocket;
    }
    else if(m_connectionType == Local)
    {
        QString websocket = m_instanceLocation + QString("/comms/moonraker.sock");
        return websocket;
    }

    return QString();
}

QString QKlipperServer::bridgeAddress() const
{
    if(m_connectionType == Remote)
    {
        QString websocket = QString("ws://%1:%2/klippysocket?token=%3").arg(m_address, QString::number(m_port), m_apiKey);
        return websocket;
    }
    else if(m_connectionType == Local)
    {
        QString websocket = m_instanceLocation + QString("/comms/klippy.sock");
        return websocket;
    }

    return QString();
}

void QKlipperServer::setAddress(const QString &address)
{
    if (m_address == address)
        return;

    m_address = address;

    if(m_address.startsWith("http://"))
        m_address = m_address.remove(0, 7);

    emit addressChanged();
}

void QKlipperServer::resetAddress()
{
    setAddress({}); // TODO: Adapt to use your actual default value
}

void QKlipperServer::setGcodeStore(QKlipperGCodeStore *gcodeStore)
{
    if (m_gcodeStore == gcodeStore)
        return;

    if(m_gcodeStore)
        m_gcodeStore->deleteLater();

    m_gcodeStore = gcodeStore;
    emit gcodeStoreChanged();
}

void QKlipperServer::setGcodeStoreValue(const QKlipperGCodeStoreValue &value)
{
    if(m_gcodeStore->values().contains(value))
        return;

    m_gcodeStore->setValue(value);
}

void QKlipperServer::resetGcodeStore()
{
    setGcodeStore(new QKlipperGCodeStore());
}

QKlipperServer::ConnectionType QKlipperServer::connectionType() const
{
    return m_connectionType;
}

void QKlipperServer::setConnectionType(ConnectionType connectionType)
{
    if (m_connectionType == connectionType)
        return;

    m_connectionType = connectionType;
    emit connectionTypeChanged();
}

void QKlipperServer::resetConnectionType()
{
    setConnectionType(None);
}

QList<QKlipperUser> QKlipperServer::userList() const
{
    return m_userList;
}

void QKlipperServer::setUserList(const QList<QKlipperUser> &userList)
{
    m_userList.clear();
    emit userListChanged();

    m_userList = userList;
    emit userListChanged();
}

void QKlipperServer::addUser(const QKlipperUser &user)
{
    m_userList.append(user);
    emit userListChanged();
}

void QKlipperServer::deleteUser(const QKlipperUser &user)
{
    m_userList.removeAll(user);
    emit userListChanged();
}

QKlipperAccessDetails QKlipperServer::accessDetails() const
{
    return m_accessDetails;
}

void QKlipperServer::setAccessDetails(QKlipperAccessDetails &accessDetails)
{
    if (m_accessDetails == accessDetails)
        return;

    m_accessDetails = accessDetails;
    emit accessDetailsChanged();
}

QString QKlipperServer::websocketId() const
{
    return m_websocketId;
}

void QKlipperServer::setWebsocketId(const QString &websocketId)
{
    if (m_websocketId == websocketId)
        return;

    m_websocketId = websocketId;
    emit websocketIdChanged();
}

QString QKlipperServer::connectionId() const
{
    return m_connectionId;
}

void QKlipperServer::setConnectionId(const QString &connectionId)
{
    if (m_connectionId == connectionId)
        return;

    m_connectionId = connectionId;
    emit connectionIdChanged();
}

QStringList QKlipperServer::availableObjects() const
{
    return m_availableObjects;
}

void QKlipperServer::setAvailableObjects(const QStringList &availableObjects)
{
    if (m_availableObjects == availableObjects)
        return;

    m_availableObjects = availableObjects;
    emit availableObjectsChanged();
}

QStringList QKlipperServer::gcodeMacroObjects() const
{
    return m_gcodeMacroObjects;
}

void QKlipperServer::setGcodeMacroObjects(const QStringList &gcodeMacroObjects)
{
    if (m_gcodeMacroObjects == gcodeMacroObjects)
        return;
    m_gcodeMacroObjects = gcodeMacroObjects;
    emit gcodeMacroObjectsChanged();
}

QKlipperGCodeMacroList QKlipperServer::gcodeMacros() const
{
    return m_gcodeMacros;
}

void QKlipperServer::setGcodeMacros(const QKlipperGCodeMacroList &gcodeMacros)
{
    bool changed = false;

    foreach(QKlipperGCodeMacro macro, gcodeMacros)
    {
        if(!m_gcodeMacros.contains(macro))
        {
            changed = true;
            break;
        }
    }

    if(!changed)
        return;

    m_gcodeMacros = gcodeMacros;
    emit gcodeMacrosChanged();
}

void QKlipperServer::setGcodeMacro(const QKlipperGCodeMacro &gcodeMacro)
{
    if(m_gcodeMacros.contains(gcodeMacro))
        return;

    m_gcodeMacros.append(gcodeMacro);
    emit gcodeMacrosChanged();
}

QStringList QKlipperServer::warnings() const
{
    return m_warnings;
}

void QKlipperServer::setWarnings(const QStringList &warnings)
{
    if (m_warnings == warnings)
        return;
    m_warnings = warnings;
    emit warningsChanged();
}

void QKlipperServer::setWarning(const QString &warning)
{
    if(m_warnings.contains(warning))
        return;

    m_warnings.append(warning);
    emit warningsChanged();
}

QStringList QKlipperServer::components() const
{
    return m_components;
}

void QKlipperServer::setComponents(const QStringList &components)
{
    if (m_components == components)
        return;
    m_components = components;
    emit componentsChanged();
}

QStringList QKlipperServer::failedComponents() const
{
    return m_failedComponents;
}

void QKlipperServer::setFailedComponents(const QStringList &failedComponents)
{
    if (m_failedComponents == failedComponents)
        return;
    m_failedComponents = failedComponents;
    emit failedComponentsChanged();
}

void QKlipperServer::setFile(QKlipperFile *file)
{
    if(m_fileSystem.contains(file->root() + QString('/') + file->uri()))
        return;

    m_fileSystem.insert(file->root() + QString('/') + file->uri(), file);
    emit fileSystemChanged();
}

void QKlipperServer::setFileMetadata(QString uri, const QKlipperMetadata &metadata)
{
    if(m_fileSystem.contains(uri))
        m_fileSystem[uri]->setMetadata(metadata);
}

QKlipperAnnouncementList QKlipperServer::announcements() const
{
    return m_announcements;
}

void QKlipperServer::setAnnouncements(const QKlipperAnnouncementList &announcements)
{
    bool changed = false;

    foreach(QKlipperAnnouncement announcement, announcements)
    {
        if(!m_announcements.contains(announcement))
        {
            changed = true;
            break;
        }
    }

    if(!changed)
        return;

    m_announcements = announcements;
    emit announcementsChanged();
}

QKlipperJobQueue *QKlipperServer::jobQueue() const
{
    return m_jobQueue;
}

void QKlipperServer::setJobQueue(QKlipperJobQueue *jobQueue)
{
    if (m_jobQueue == jobQueue)
        return;

    m_jobQueue = jobQueue;
    emit jobQueueChanged();
}

QMap<QString, QKlipperFile *> QKlipperServer::fileSystem() const
{
    return m_fileSystem;
}

QKlipperFileList QKlipperServer::fileList(const QString &directory) const
{
    QKlipperFileList fileList;
    QKlipperFileList dirList;

    QMapIterator<QString, QKlipperFile*> iterator(m_fileSystem);

    while(iterator.hasNext())
    {
        iterator.next();

        QString directoryKey = iterator.key();

        if(directoryKey.contains("/"))
        {
            directoryKey = directoryKey.left(directoryKey.lastIndexOf("/") + 1);
        }

        if(directoryKey == directory)
        {
            if(iterator.value()->fileType() == QKlipperFile::Directory)
                dirList += iterator.value();
            else
                fileList += iterator.value();
        }
    }

    dirList += fileList;

    return dirList;
}

QKlipperFile *QKlipperServer::file(QString uri)
{
    if(m_fileSystem.contains(uri))
        return m_fileSystem[uri];

    return nullptr;
}

void QKlipperServer::setFileSystem(const QMap<QString, QKlipperFile *> &fileSystem)
{
    if (m_fileSystem == fileSystem)
        return;

    m_fileSystem = fileSystem;
    emit fileSystemChanged();
}

void QKlipperServer::setFileList(const QString &directory, QKlipperFileList files)
{
    foreach(QKlipperFile *file, files)
    {
        m_fileSystem[directory + file->filename()] = file;
    }

    emit fileListChanged(directory);
}

QKlipperClientIdentifier QKlipperServer::clientIdentifier() const
{
    return m_clientIdentifier;
}

void QKlipperServer::setClientIdentifier(const QKlipperClientIdentifier &clientIdentifier)
{
    if (m_clientIdentifier == clientIdentifier)
        return;

    m_clientIdentifier = clientIdentifier;
    emit clientIdentifierChanged();
}

qint16 QKlipperServer::port() const
{
    return m_port;
}

void QKlipperServer::setPort(qint16 port)
{
    if (m_port == port)
        return;

    m_port = port;
    emit portChanged();
}

QKlipperGCodeStore *QKlipperServer::gcodeStore() const
{
    return m_gcodeStore;
}
