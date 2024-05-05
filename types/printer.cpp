#include "printer.h"

Printer::Printer(QString name, QString id) : QObject(nullptr)
{

}

Printer::Printer(PrinterDefinition definition, QObject *parent) : QObject(parent)
{
    _name = definition.name;
    _klipperLocation = definition.klipperLocation;
    _moonrakerLocation = definition.moonrakerLocation;
    _instanceLocation = definition.instanceLocation;
    _id = definition.id;
    _gcodesLocation = definition.gcodeLocation;
    _configLocation = definition.configLocation;
    _configFile = definition.configFile;
    _autoConnect = definition.autoConnect;
    _defaultPrinter = definition.defaultPrinter;
    _apiKey = definition.apiKey;
    _powerProfile = definition.powerProfile;

    _toolhead = new Toolhead();
    _bed = new Bed();
    _bed->setWatts(_powerProfile["bed"]);
    _chamber = new Chamber();
    _chamber->setWatts(_powerProfile["chamber"]);
    _partsFan = new Fan();

    if(_connectionLocation == LocationLocal)
        _console = new QLocalKlipperConsole(this, parent);

    _system = new System(this);
    _printJob = new PrintJob(this);

    for(int i = 0; i < definition.extruderCount; i++)
    {
        QString extruderName = QString("extruder") + ((i > 0) ? QString::number(i) : QString(""));
        _toolhead->extruder(i)->setWatts(definition.powerProfile[extruderName]);
    }

    _console->setMoonrakerLocation(_moonrakerLocation);

    connect(_console, SIGNAL(moonrakerConnected()), this, SLOT(on_moonrakerConnected()));
    connect(_console, SIGNAL(klipperConnected()), this, SLOT(on_klipperConnected()));
    connect(_console, SIGNAL(klipperDisconnected()), this, SLOT(on_klipperDisconnected()));
    connect(_console, SIGNAL(printerUpdate()), this, SLOT(on_printerUpdate()));
    connect(_console, SIGNAL(systemUpdate()), this, SLOT(on_systemUpdate()));
    connect(_console, SIGNAL(klipperError(QString,QString)), this, SLOT(on_console_klipperError(QString,QString)));
    connect(_console, SIGNAL(directoryListing(QString,QString,QList<KlipperFile>)), this, SLOT(on_console_directoryListing(QString,QString,QList<KlipperFile>)));
    connect(_console,SIGNAL(startup()),this,SLOT(on_console_startup()));
}

Printer::~Printer()
{
    delete _toolhead;
    delete _bed;
    delete _partsFan;
    delete _console;
}

Toolhead *Printer::toolhead()
{
    return _toolhead;
}

Extruder *Printer::extruder(int index)
{
    return _toolhead->extruder(index);
}

void Printer::setName(QString name)
{
    _name = name;
}

QString Printer::name()
{
    return _name;
}

void Printer::setId(QString id)
{
    _id = id;
}

QString Printer::id()
{
    return _id;
}

void Printer::setStatus(Status status)
{
    _status = status;
}

Printer::Status Printer::status()
{
    return _status;
}

void Printer::setFirmwareVersion(QString version)
{
    _firmwareVersion = version;
}

QString Printer::firmwareVersion()
{
    return _firmwareVersion;
}

void Printer::setCurrentFile(KlipperFile file)
{
    _currentFile = file;
}

KlipperFile Printer::currentFile()
{
    return _currentFile;
}

void Printer::setStatusMessage(QString message)
{
    _statusMessage = message;
}

QString Printer::statusMessage()
{
    return _statusMessage;
}

void Printer::setPrintEndTime(QDateTime time)
{
    _printEnding = time;
}

QDateTime Printer::printEndTime()
{
    return _printEnding;
}

void Printer::setMoonrakerLocation(QString location)
{
    _moonrakerLocation = location;
}

QString Printer::moonrakerLocation()
{
    return _moonrakerLocation;
}

void Printer::setKlipperLocation(QString location)
{
    _klipperLocation = location;
}

QString Printer::klipperLocation()
{
    return _klipperLocation;
}

void Printer::setConfigFile(QString file)
{
    _configFile = file;
}

QString Printer::configFile()
{
    return _configFile;
}

PrinterDefinition Printer::definition()
{
    PrinterDefinition definition;
    definition.defaultPrinter = _defaultPrinter;
    definition.autoConnect = _autoConnect;
    definition.apiKey = _apiKey;
    definition.configFile = _configFile;
    definition.gcodeLocation = _gcodesLocation;
    definition.instanceLocation = _instanceLocation;
    definition.configLocation = _configLocation;
    definition.klipperLocation = _klipperLocation;
    definition.moonrakerLocation = _moonrakerLocation;
    definition.id = _id;
    definition.name = _name;

    definition.powerProfile["chamber"] = _chamber->watts();
    definition.powerProfile["bed"] = _bed->watts();

    for(int i = 0; i < _toolhead->extruderCount(); i++)
    {
        QString extruderName = QString("extruder") + ((i > 0) ? QString::number(i) : QString(""));
        definition.powerProfile[extruderName] = _toolhead->extruder(i)->watts();
    }

    definition.extruderCount = _toolhead->extruderCount();

    return definition;
}

void Printer::update(PrinterDefinition definition)
{
    _name = definition.name;
    _klipperLocation = definition.klipperLocation;
    _id = definition.id;
    _gcodesLocation = definition.gcodeLocation;
    _configLocation = definition.configLocation;
    _configFile = definition.configFile;
    _autoConnect = definition.autoConnect;
    _defaultPrinter = definition.defaultPrinter;
    _apiKey = definition.apiKey;
    _powerProfile = definition.powerProfile;

    _bed->setWatts(_powerProfile["bed"]);
    _chamber->setWatts(_powerProfile["chamber"]);

    for(int i = 0; i < _toolhead->extruderCount(); i++)
    {
        QString extruderName = QString("extruder") + ((i > 0) ? QString::number(i) : QString(""));
        _toolhead->extruder(i)->setWatts(definition.powerProfile[extruderName]);
    }

    if(_moonrakerLocation != definition.moonrakerLocation)
    {
        _moonrakerLocation = definition.moonrakerLocation;
        _instanceLocation = definition.instanceLocation;

        _status = Offline;

        emit printerUpdate(this);

        _console->disconnectKlipper();
        _console->connectToMoonraker();
    }
    else
        emit printerUpdate(this);
}

int Printer::extruderCount()
{
    return _toolhead->extruderCount();
}

QAbstractKlipperConsole *Printer::console()
{
    return _console;
}

void Printer::connectMoonraker()
{
    connect(_console, SIGNAL(printerUpdate()), this, SLOT(on_printerUpdate()));
    connect(_console,SIGNAL(responseReceived(KlipperResponse)), this, SLOT(on_console_responseReceived(KlipperResponse)));
    _console->setMoonrakerLocation(_moonrakerLocation);
    //_console->start();
    _console->connectToMoonraker();
}

PrintJob *Printer::currentJob()
{
    return _printJob;
}

Bed *Printer::bed()
{
    return _bed;
}

Fan *Printer::fan()
{
    return _partsFan;
}

System *Printer::system()
{
    return _system;
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

EndstopStatus Printer::endstopStatus() const
{
    return _endstopStatus;
}

ClientIdentifier Printer::clientIdentifier() const
{
    return _clientIdentifier;
}

GCodeStore Printer::gCodeStore() const
{
    return _gCodeStore;
}

bool Printer::isAutoConnect() const
{
    return _autoConnect;
}

bool Printer::isDefaultPrinter() const
{
    return _defaultPrinter;
}

Chamber *Printer::chamber() const
{
    return _chamber;
}

void Printer::setChamber(Chamber *chamber)
{
    _chamber = chamber;
}

QMap<QString, qreal> Printer::powerProfile() const
{
    return _powerProfile;
}

QString Printer::apiKey() const
{
    return _apiKey;
}

void Printer::setApiKey(const QString &apiKey)
{
    _apiKey = apiKey;
}

void Printer::getFiles(QString root, QString directory)
{
    if(directory.isEmpty())
        _console->getFileList(root);
    else
        _console->getFileList(root + QString("/") + directory);
}

QString Printer::instanceLocation() const
{
    return _instanceLocation;
}

void Printer::setInstanceLocation(const QString &instanceLocation)
{
    _instanceLocation = instanceLocation + ((instanceLocation.endsWith(QDir::separator())) ? QString("") : QDir::separator());
    _gcodesLocation = instanceLocation + QString("gcodes");
    _configLocation = instanceLocation + QString("config");
    _klipperLocation = instanceLocation + QString("comms") + QDir::separator() + QString("klippy.sock");
    _moonrakerLocation = instanceLocation + QString("comms") + QDir::separator() + QString("moonraker.sock");
}

QString Printer::configLocation() const
{
    return _configLocation;
}

void Printer::setConfigLocation(const QString &configLocation)
{
    _configLocation = configLocation;
}

QString Printer::gcodesLocation() const
{
    return _gcodesLocation;
}

void Printer::setGcodesLocation(const QString &gcodesLocation)
{
    _gcodesLocation = gcodesLocation;
}
