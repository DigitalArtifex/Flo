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
    _partsFan = new Fan();
    _console = new KlipperConsole(this, parent);
    _system = new System(this);

    _console->setMoonrakerLocation(_moonrakerLocation);

    connect(_console, SIGNAL(moonrakerConnected()), this, SLOT(on_moonrakerConnected()));
    connect(_console, SIGNAL(klipperConnected()), this, SLOT(on_klipperConnected()));
    connect(_console, SIGNAL(klipperDisconnected()), this, SLOT(on_klipperDisconnected()));
    connect(_console, SIGNAL(printerUpdate()), this, SLOT(on_printerUpdate()));
    connect(_console, SIGNAL(systemUpdate()), this, SLOT(on_systemUpdate()));
    connect(_console, SIGNAL(klipperError(QString,QString)), this, SLOT(on_console_klipperError(QString,QString)));
    connect(_console, SIGNAL(directoryListing(QString,QString,QList<KlipperFile>)), this, SLOT(on_console_directoryListing(QString,QString,QList<KlipperFile>)));
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

    return definition;
}

int Printer::extruderCount()
{
    return _toolhead->extruderCount();
}

KlipperConsole *Printer::console()
{
    return _console;
}

void Printer::connectMoonraker()
{
    connect(_console, SIGNAL(printerUpdate()), this, SLOT(on_printerUpdate()));
    connect(_console,SIGNAL(responseReceived(KlipperResponse)), this, SLOT(on_console_responseReceived(KlipperResponse)));
    _console->loadPresets();
    _console->setMoonrakerLocation(_moonrakerLocation);
    //_console->start();
    _console->connectKlipper();
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
    _instanceLocation = instanceLocation;
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
