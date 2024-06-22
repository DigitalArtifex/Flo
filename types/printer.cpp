#include "printer.h"

Printer::Printer(QString name, QString id) : QObject(nullptr)
{

}

Printer::Printer(PrinterDefinition definition, QObject *parent) : QObject(parent)
{
    m_name = definition.name;
    m_klipperLocation = definition.klipperLocation;
    m_moonrakerLocation = definition.moonrakerLocation;
    m_instanceLocation = definition.instanceLocation;
    m_id = definition.id;
    m_gcodesLocation = definition.gcodeLocation;
    m_configLocation = definition.configLocation;
    m_configFile = definition.configFile;
    m_autoConnect = definition.autoConnect;
    m_defaultPrinter = definition.defaultPrinter;
    m_apiKey = definition.apiKey;
    m_powerProfile = definition.powerProfile;

    m_toolhead = new Toolhead(this);
    m_bed = new Q3DPrintBed(this);
    m_bed->setWatts(m_powerProfile["bed"]);
    m_chamber = new Chamber();
    m_chamber->setWatts(m_powerProfile["chamber"]);
    m_partsFan = new Fan(this);

    if(m_connectionLocation == LocationLocal)
        m_console = new QLocalKlipperConsole(this, parent);

    m_system = new System(this);
    m_printJob = new PrintJob(this);

    for(int i = 0; i < definition.extruderCount; i++)
    {
        QString extruderName = QString("extruder") + ((i > 0) ? QString::number(i) : QString(""));
        m_toolhead->extruder(i)->m_extruderNumber = i;
        m_toolhead->extruder(i)->m_watts = definition.powerProfile[extruderName];
    }

    m_console->setMoonrakerLocation(m_moonrakerLocation);

    connect(m_console, SIGNAL(moonrakerConnected()), this, SLOT(on_moonrakerConnected()));
    connect(m_console, SIGNAL(klipperConnected()), this, SLOT(on_klipperConnected()));
    connect(m_console, SIGNAL(klipperDisconnected()), this, SLOT(on_klipperDisconnected()));
    connect(m_console, SIGNAL(printerUpdate()), this, SLOT(on_printerUpdate()));
    connect(m_console, SIGNAL(systemUpdate()), this, SLOT(on_systemUpdate()));
    connect(m_console, SIGNAL(klipperError(QString,QString)), this, SLOT(on_console_klipperError(QString,QString)));
    connect(m_console, SIGNAL(directoryListing(QString,QString,QList<KlipperFile>)), this, SLOT(on_console_directoryListing(QString,QString,QList<KlipperFile>)));
    connect(m_console,SIGNAL(startup()),this,SLOT(on_console_startup()));
}

Printer::~Printer()
{
    delete m_toolhead;
    delete m_bed;
    delete m_partsFan;
    delete m_console;
}

Toolhead *Printer::toolhead()
{
    return m_toolhead;
}

Extruder *Printer::extruder(int index)
{
    return m_toolhead->extruder(index);
}

void Printer::setName(QString name)
{
    m_name = name;
}

QString Printer::name()
{
    return m_name;
}

void Printer::setId(QString id)
{
    m_id = id;
}

QString Printer::id()
{
    return m_id;
}

void Printer::setStatus(Status status)
{
    m_status = status;
}

Printer::Status Printer::status()
{
    return m_status;
}

void Printer::setFirmwareVersion(QString version)
{
    m_firmwareVersion = version;
}

QString Printer::firmwareVersion()
{
    return m_firmwareVersion;
}

void Printer::setCurrentFile(KlipperFile file)
{
    m_currentFile = file;
}

KlipperFile Printer::currentFile()
{
    return m_currentFile;
}

void Printer::setStatusMessage(QString message)
{
    m_statusMessage = message;
}

QString Printer::statusMessage()
{
    return m_statusMessage;
}

void Printer::setPrintEndTime(QDateTime time)
{
    m_printEnding = time;
}

QDateTime Printer::printEndTime()
{
    return m_printEnding;
}

void Printer::setMoonrakerLocation(QString location)
{
    m_moonrakerLocation = location;
}

QString Printer::moonrakerLocation()
{
    return m_moonrakerLocation;
}

void Printer::setKlipperLocation(QString location)
{
    m_klipperLocation = location;
}

QString Printer::klipperLocation()
{
    return m_klipperLocation;
}

void Printer::setConfigFile(QString file)
{
    m_configFile = file;
}

QString Printer::configFile()
{
    return m_configFile;
}

PrinterDefinition Printer::definition()
{
    PrinterDefinition definition;
    definition.defaultPrinter = m_defaultPrinter;
    definition.autoConnect = m_autoConnect;
    definition.apiKey = m_apiKey;
    definition.configFile = m_configFile;
    definition.gcodeLocation = m_gcodesLocation;
    definition.instanceLocation = m_instanceLocation;
    definition.configLocation = m_configLocation;
    definition.klipperLocation = m_klipperLocation;
    definition.moonrakerLocation = m_moonrakerLocation;
    definition.id = m_id;
    definition.name = m_name;

    definition.powerProfile["chamber"] = m_chamber->watts();
    definition.powerProfile["bed"] = m_bed->watts();

    for(int i = 0; i < m_toolhead->extruderCount(); i++)
    {
        QString extruderName = QString("extruder") + ((i > 0) ? QString::number(i) : QString(""));
        definition.powerProfile[extruderName] = m_toolhead->extruder(i)->watts();
    }

    definition.extruderCount = m_toolhead->extruderCount();

    return definition;
}

void Printer::update(PrinterDefinition definition)
{
    m_name = definition.name;
    m_klipperLocation = definition.klipperLocation;
    m_id = definition.id;
    m_gcodesLocation = definition.gcodeLocation;
    m_configLocation = definition.configLocation;
    m_configFile = definition.configFile;
    m_autoConnect = definition.autoConnect;
    m_defaultPrinter = definition.defaultPrinter;
    m_apiKey = definition.apiKey;
    m_powerProfile = definition.powerProfile;

    m_bed->setWatts(m_powerProfile["bed"]);
    m_chamber->setWatts(m_powerProfile["chamber"]);

    for(int i = 0; i < m_toolhead->extruderCount(); i++)
    {
        QString extruderName = QString("extruder") + ((i > 0) ? QString::number(i) : QString(""));
        m_toolhead->extruder(i)->m_watts = definition.powerProfile[extruderName];
    }

    if(m_moonrakerLocation != definition.moonrakerLocation)
    {
        m_moonrakerLocation = definition.moonrakerLocation;
        m_instanceLocation = definition.instanceLocation;

        m_status = Offline;

        emit printerUpdate(this);

        m_console->disconnectKlipper();
        m_console->connectToMoonraker();
    }
    else
        emit printerUpdate(this);
}

int Printer::extruderCount()
{
    return m_toolhead->extruderCount();
}

QAbstractKlipperConsole *Printer::console()
{
    return m_console;
}

void Printer::connectMoonraker()
{
    connect(m_console, SIGNAL(printerUpdate()), this, SLOT(on_printerUpdate()));
    connect(m_console,SIGNAL(responseReceived(KlipperResponse)), this, SLOT(on_console_responseReceived(KlipperResponse)));
    m_console->setMoonrakerLocation(m_moonrakerLocation);
    //_console->start();
    m_console->connectToMoonraker();
}

PrintJob *Printer::currentJob()
{
    return m_printJob;
}

Q3DPrintBed *Printer::bed()
{
    return m_bed;
}

Fan *Printer::fan()
{
    return m_partsFan;
}

System *Printer::system()
{
    return m_system;
}

void Printer::on_klipperConnected()
{
    emit klipperConnected(this);
}

void Printer::on_klipperDisconnected()
{
    emit klipperDisconnected(this);
}

void Printer::on_moonrakerConnected()
{
    emit moonrakerConnected(this);
}

void Printer::on_printerUpdate()
{
    emit printerUpdate(this);
}

void Printer::on_systemUpdate()
{
    emit systemUpdate(this);
}

void Printer::on_connectionTimer_timeout()
{

}

void Printer::on_console_responseReceived(KlipperResponse response)
{
}

void Printer::on_console_klipperError(QString error, QString message)
{
    emit printerError(error, message, this);
}

void Printer::on_console_directoryListing(QString root, QString directory, QList<KlipperFile> files)
{
    emit directoryListing(root, directory, files, this);
}

void Printer::on_console_startup()
{
    emit startup(this);
}

void Printer::on_console_gcodeMove(QGCodeMove &move)
{
    emit gcodeMove(this, move);
}

void Printer::emitUpdate()
{
    emit printerUpdate(this);
}

qreal Printer::squareCornerVelocity() const
{
    return m_squareCornerVelocity;
}

void Printer::setSquareCornerVelocity(qreal squareCornerVelocity)
{
    m_squareCornerVelocity = squareCornerVelocity;
}

qreal Printer::maxZVelocity() const
{
    return m_maxZVelocity;
}

void Printer::setMaxZVelocity(qreal maxZVelocity)
{
    m_maxZVelocity = maxZVelocity;
}

qreal Printer::maxZAcceleration() const
{
    return m_maxZAcceleration;
}

void Printer::setMaxZAcceleration(qreal maxZAcceleration)
{
    m_maxZAcceleration = maxZAcceleration;
}

qreal Printer::maxVelocity() const
{
    return m_maxVelocity;
}

void Printer::setMaxVelocity(qreal maxVelocity)
{
    m_maxVelocity = maxVelocity;
}

qreal Printer::maxAcceleration() const
{
    return m_maxAcceleration;
}

void Printer::setMaxAcceleration(qreal maxAcceleration)
{
    m_maxAcceleration = maxAcceleration;
}

QString Printer::kinematics() const
{
    return m_kinematics;
}

void Printer::setKinematics(const QString &kinematics)
{
    m_kinematics = kinematics;
}

QMap<QString, Fan *> &Printer::fans()
{
    return m_fans;
}

void Printer::setFans(const QMap<QString, Fan *> &fans)
{
    m_fans = fans;
}

Printer::ProbeData Printer::probeData()
{
    return m_probeData;
}

void Printer::setProbeData(const ProbeData &probeData)
{
    m_probeData = probeData;
}

QMap<QString, QStepperMotor *> &Printer::stepperMotors()
{
    return m_stepperMotors;
}

QGCodeMove Printer::gcodeMove()
{
    return m_gcodeMove;
}

EndstopStatus Printer::endstopStatus()
{
    return m_endstopStatus;
}

ClientIdentifier Printer::clientIdentifier()
{
    return m_clientIdentifier;
}

GCodeStore Printer::gCodeStore()
{
    return m_gCodeStore;
}

bool Printer::isAutoConnect()
{
    return m_autoConnect;
}

bool Printer::isDefaultPrinter()
{
    return m_defaultPrinter;
}

bool Printer::isOnline() const
{
    return ((m_status != Error) && (m_status != Offline));
}

Chamber *Printer::chamber()
{
    return m_chamber;
}

void Printer::setChamber(Chamber *chamber)
{
    m_chamber = chamber;
}

QMap<QString, qreal> Printer::powerProfile()
{
    return m_powerProfile;
}

QString Printer::apiKey()
{
    return m_apiKey;
}

void Printer::setApiKey(const QString &apiKey)
{
    m_apiKey = apiKey;
}

void Printer::getFiles(QString root, QString directory)
{
    if(directory.isEmpty())
        m_console->getFileList(root);
    else
        m_console->getFileList(root + QString("/") + directory);
}

QString Printer::instanceLocation()
{
    return m_instanceLocation;
}

void Printer::setInstanceLocation(const QString &instanceLocation)
{
    m_instanceLocation = instanceLocation + ((instanceLocation.endsWith(QDir::separator())) ? QString("") : QDir::separator());
    m_gcodesLocation = instanceLocation + QString("gcodes");
    m_configLocation = instanceLocation + QString("config");
    m_klipperLocation = instanceLocation + QString("comms") + QDir::separator() + QString("klippy.sock");
    m_moonrakerLocation = instanceLocation + QString("comms") + QDir::separator() + QString("moonraker.sock");
}

QString Printer::configLocation()
{
    return m_configLocation;
}

void Printer::setConfigLocation(const QString &configLocation)
{
    m_configLocation = configLocation;
}

QString Printer::gcodesLocation()
{
    return m_gcodesLocation;
}

void Printer::setGcodesLocation(const QString &gcodesLocation)
{
    m_gcodesLocation = gcodesLocation;
}
