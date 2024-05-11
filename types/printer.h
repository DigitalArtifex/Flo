#ifndef PRINTER_H
#define PRINTER_H

#include <QObject>
#include <QTimer>
#include <QMap>
#include <QDir>

#include "toolhead.h"
#include "extruder.h"
#include "bed.h"
#include "fan.h"
#include "klipperfile.h"
#include "system.h"
#include "printjob.h"
#include "chamber.h"

#include "qsteppermotor.h"

//#include "../klipperconsole.h"
#include "console/qabstractklipperconsole.h"
#include "console/qlocalklipperconsole.h"

#include "printerdefinition.h"
#include "gcode/qgcodestore.h"
#include "clientidentifier.h"
#include "endstopstatus.h"

class Printer: public QObject
{

    Q_OBJECT
public:
    enum ConnectionLocation
    {
        LocationLocal,
        LocationRemote,
        LocationRemoteHttp
    };

    enum Status
    {
        Ready = 0x00000001,
        Error = 0x00000010,
        Printing = 0x00010000,
        Paused = (Ready | Printing),
        Cancelled = (Error | Printing),
        Offline = 0x10000000
    };

    struct ProbeData
    {
        QString name;

        bool isManual = false;
        bool lastQuery = false;

        qreal zPosition = 0;
        qreal zPositionLower = 0;
        qreal zPositionUpper = 0;
    };

    Printer(QString name = QString("printer"), QString id = QString(""));
    Printer(PrinterDefinition definition, QObject *parent = nullptr);
    ~Printer();

    Toolhead *toolhead();
    Extruder *extruder(int index);
    Q3DPrintBed *bed();
    Fan *fan();
    System *system();

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
    void update(PrinterDefinition definition);

    int extruderCount();

    QAbstractKlipperConsole *console();

    void connectMoonraker();

    PrintJob *currentJob();

    QString gcodesLocation() ;
    void setGcodesLocation(const QString &gcodesLocation);

    QString configLocation() ;
    void setConfigLocation(const QString &configLocation);

    QString instanceLocation() ;
    void setInstanceLocation(const QString &instanceLocation);

    QString apiKey() ;
    void setApiKey(const QString &apiKey);

    void getFiles(QString root, QString directory);

    QMap<QString, qreal> powerProfile() ;

    Chamber *chamber() ;
    void setChamber(Chamber *chamber);

    bool isAutoConnect() ;
    bool isDefaultPrinter() ;

    GCodeStore gCodeStore() ;

    ClientIdentifier clientIdentifier() ;

    EndstopStatus endstopStatus() ;

    QGCodeMove gcodeMove() ;

    QMap<QString, QStepperMotor*> &stepperMotors();

    ProbeData probeData() ;
    void setProbeData(const ProbeData &probeData);

    QMap<QString, Fan *> &fans() ;
    void setFans(const QMap<QString, Fan *> &fans);

signals:
    void systemUpdate(Printer *printer);
    void printerUpdate(Printer *printer);
    void printerOnline(Printer *printer);
    void printerError(QString title, QString message, Printer *printer);
    void klipperConnected(Printer *printer);
    void klipperDisconnected(Printer *printer);
    void moonrakerConnected(Printer *printer);

    void startup(Printer *printer);

    void connectionTimeout(Printer *printer);

    void directoryListing(QString root, QString directory, QList<KlipperFile> files, Printer *printer);

    void gcodeMove(Printer *printer, QGCodeMove move);

private slots:
    void on_klipperConnected();
    void on_klipperDisconnected();
    void on_moonrakerConnected();
    void on_printerUpdate();
    void on_systemUpdate();

    void on_connectionTimer_timeout();
    void on_console_responseReceived(KlipperResponse response);
    void on_console_klipperError(QString error, QString message);
    void on_console_directoryListing(QString root, QString directory, QList<KlipperFile> files);
    void on_console_startup();

    virtual void on_console_gcodeMove(QGCodeMove &move);

private:
    Toolhead *_toolhead = nullptr;
    Q3DPrintBed *_bed = nullptr;
    Chamber *_chamber = nullptr;
    Fan *_partsFan = nullptr;

    QMap<QString,qreal> _powerProfile;
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

    QTimer *_connectionTimer = nullptr;

    bool _autoConnect = true;
    bool _defaultPrinter = false;

    KlipperFile _currentFile;
    QDateTime _printStarted;
    QDateTime _printEnding;

    Status _status = Offline;
    ConnectionLocation _connectionLocation = LocationLocal;

    QAbstractKlipperConsole *_console = nullptr;

    System *_system;
    PrintJob *_printJob;

    GCodeStore                               _gCodeStore;
    QGCodeMove                               _gcodeMove;
    ClientIdentifier                         _clientIdentifier;

    EndstopStatus                            _endstopStatus;

    QMap<QString,QStepperMotor*>             _stepperMotors;

    ProbeData                                _probeData;

    QMap<QString,Fan*>                       _fans;
};

typedef QList<Printer*> PrinterList;

#endif // PRINTER_H
