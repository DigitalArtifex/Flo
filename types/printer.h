#ifndef PRINTER_H
#define PRINTER_H

#include <QObject>
#include <QMap>

#include "toolhead.h"
#include "extruder.h"
#include "bed.h"
#include "fan.h"
#include "klipperfile.h"

#include "../klipperconsole.h"
#include "printerdefinition.h"

class Printer: public QObject
{

    Q_OBJECT
public:

    enum Status {
        Ready,
        Printing,
        Paused,
        Cancelled,
        Error
    };

    Printer(QString name = QString("printer"), QString id = QString(""));
    Printer(PrinterDefinition definition);
    ~Printer();

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

    void setPrintEndTime(QDateTime time);
    QDateTime printEndTime();

    void setMoonrakerLocation(QString location);
    QString moonrakerLocation();

    void setKlipperLocation(QString location);
    QString klipperLocation();

    void setConfigFile(QString file);
    QString configFile();

    PrinterDefinition definition();

    int extruderCount();

    KlipperConsole *console();

    void connectMoonraker();

signals:
    void printerUpdate(Printer *printer);
    void klipperConnected(Printer *printer);
    void moonrakerConnected(Printer *printer);
    void printerOnline(Printer *printer);

private slots:
    void on_klipperConnected();
    void on_moonrakerConnected();
    void on_printerUpdate(Printer *printer);

private:
    Toolhead *_toolhead = nullptr;
    Bed *_bed = nullptr;
    Fan *_partsFan = nullptr;
    QString _name;
    QString _id;
    QString _firmwareVersion;
    QString _statusMessage;
    QString _moonrakerLocation;
    QString _klipperLocation;
    QString _gcodesLocation;
    QString _configLocation;
    QString _instanceLocation;
    QString _configFile;
    QString _apiKey;

    bool _autoConnect = true;
    bool _defaultPrinter = false;

    KlipperFile _currentFile;
    QDateTime _printStarted;
    QDateTime _printEnding;
    Status _status = Error;

    KlipperConsole *_console = nullptr;
};

typedef QList<Printer*> PrinterList;

#endif // PRINTER_H
