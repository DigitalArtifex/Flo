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

    friend class QAbstractKlipperConsole;
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

    bool isOnline() const;

    GCodeStore gCodeStore() ;

    ClientIdentifier clientIdentifier() ;

    EndstopStatus endstopStatus() ;

    QGCodeMove gcodeMove() ;

    QMap<QString, QStepperMotor*> &stepperMotors();

    ProbeData probeData() ;
    void setProbeData(const ProbeData &probeData);

    QMap<QString, Fan *> &fans() ;
    void setFans(const QMap<QString, Fan *> &fans);

    QString kinematics() const;
    void setKinematics(const QString &kinematics);

    qreal maxAcceleration() const;
    void setMaxAcceleration(qreal maxAcceleration);

    qreal maxVelocity() const;
    void setMaxVelocity(qreal maxVelocity);

    qreal maxZAcceleration() const;
    void setMaxZAcceleration(qreal maxZAcceleration);

    qreal maxZVelocity() const;
    void setMaxZVelocity(qreal maxZVelocity);

    qreal squareCornerVelocity() const;
    void setSquareCornerVelocity(qreal squareCornerVelocity);

    void pause();
    void resume();

    qreal watts() const;

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
    //For use by QAbstractKlipperConsole
    void                                     emitUpdate();

    Toolhead                                *m_toolhead = nullptr;
    Q3DPrintBed                             *m_bed = nullptr;
    Chamber                                 *m_chamber = nullptr;
    Fan                                     *m_partsFan = nullptr;

    QMap<QString,qreal>                      m_powerProfile;

    QString                                  m_name;
    QString                                  m_id;
    QString                                  m_firmwareVersion;
    QString                                  m_statusMessage;
    QString                                  m_moonrakerLocation;
    QString                                  m_klipperLocation;
    QString                                  m_gcodesLocation;
    QString                                  m_configLocation;
    QString                                  m_instanceLocation;
    QString                                  m_configFile;
    QString                                  m_apiKey;
    QString                                  m_kinematics;

    qreal                                    m_maxAcceleration = 0;
    qreal                                    m_maxVelocity = 0;
    qreal                                    m_maxZAcceleration = 0;
    qreal                                    m_maxZVelocity = 0;
    qreal                                    m_squareCornerVelocity = 0;
    qreal                                    m_printTime = 0;

    QTimer                                  *m_connectionTimer = nullptr;

    bool                                     m_autoConnect = true;
    bool                                     m_defaultPrinter = false;

    KlipperFile                              m_currentFile;
    QDateTime                                m_printStarted;
    QDateTime                                m_printEnding;

    Status                                   m_status = Offline;
    ConnectionLocation m_connectionLocation = LocationLocal;

    QAbstractKlipperConsole                 *m_console = nullptr;

    System                                  *m_system;
    PrintJob                                *m_printJob;

    GCodeStore                               m_gCodeStore;
    QGCodeMove                               m_gcodeMove;
    ClientIdentifier                         m_clientIdentifier;

    EndstopStatus                            m_endstopStatus;

    QMap<QString,QStepperMotor*>             m_stepperMotors;

    ProbeData                                m_probeData;

    QMap<QString,Fan*>                       m_fans;

};

typedef QList<Printer*> PrinterList;

#endif // PRINTER_H
