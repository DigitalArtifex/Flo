#include "printer.h"

Printer::Printer(QString name, QString id) : QObject(nullptr)
{
    _name = name;
    _id = id;

    _toolhead = new Toolhead();
    _bed = new Bed();
    _partsFan = new Fan();
    _console = new KlipperConsole(this);

    connect(_console, SIGNAL(moonrakerConnected()), this, SLOT(on_moonrakerConnected()));
    connect(_console, SIGNAL(klipperConnected()), this, SLOT(on_klipperConnected()));
}

Printer::Printer(PrinterDefinition definition)
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

    _toolhead = new Toolhead();
    _bed = new Bed();
    _partsFan = new Fan();
    _console = new KlipperConsole(this);

    _console->setMoonrakerLocation(_moonrakerLocation);

    connect(_console, SIGNAL(moonrakerConnected()), this, SLOT(on_moonrakerConnected()));
    connect(_console, SIGNAL(klipperConnected()), this, SLOT(on_klipperConnected()));
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
    connect(_console, SIGNAL(printerUpdate(Printer*)), this, SLOT(on_printerUpdate(Printer*)));
    _console->setMoonrakerLocation(_moonrakerLocation);
    _console->connectKlipper();
}

Bed *Printer::bed()
{
    return _bed;
}

Fan *Printer::fan()
{
    return _partsFan;
}

void Printer::on_klipperConnected()
{
    emit(klipperConnected(this));
}

void Printer::on_moonrakerConnected()
{
    emit(moonrakerConnected(this));
}

void Printer::on_printerUpdate(Printer *printer)
{
    emit(printerUpdate(this));
}
