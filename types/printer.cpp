#include "printer.h"

Printer::Printer(QString name, QString id)
{
    _name = name;
    _id = id;

    _toolhead = new Toolhead();
    _bed = new Bed();
    _partsFan = new Fan();
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

int Printer::extruderCount()
{
    return _toolhead->extruderCount();
}

Bed *Printer::bed()
{
    return _bed;
}

Fan *Printer::fan()
{
    return _partsFan;
}
