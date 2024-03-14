#ifndef PRINTER_H
#define PRINTER_H

#include <QObject>
#include <QMap>

#include "toolhead.h"
#include "extruder.h"
#include "bed.h"
#include "fan.h"
#include "klipperfile.h"

class Printer
{

    Q_GADGET
public:

    enum Status {
        Ready,
        Printing,
        Paused,
        Cancelled,
        Error
    };

    Printer(QString name = QString("printer"), QString id = QString(""));

    Toolhead *toolhead();
    Extruder *extruder(int index);
    Bed *bed();
    Fan *fan();

    void setName(QString name);
    QString name();

    void setId(QString id);
    QString id();

    void setStatus(Status status);
    Status status();

    void setFirmwareVersion(QString version);
    QString firmwareVersion();

    void setCurrentFile(KlipperFile file);
    KlipperFile currentFile();

    void setStatusMessage(QString message);
    QString statusMessage();

    int extruderCount();

private:
    Toolhead *_toolhead;
    Bed *_bed;
    Fan *_partsFan;
    QString _name;
    QString _id;
    QString _firmwareVersion;
    QString _statusMessage;
    KlipperFile _currentFile;
    QDateTime _printStarted;
    QDateTime _printEnding;
    Status _status = Error;
};

#endif // PRINTER_H
