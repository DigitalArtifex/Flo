/*
 * QKlipper - A Qt library for the Klipper/Moonraker API
 * Copyright (C) 2024 James Dudeck
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of  MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef QKLIPPERPRINTER_H
#define QKLIPPERPRINTER_H

#include <QObject>
#include <QTimer>
#include <QDateTime>

#include "../QKlipperFile/qklipperfile.h"
#include "../QKlipperSystem/qklippersystem.h"
#include "../QKlipperServer/qklipperserver.h"

#include "qklipperprobedata.h"
#include "qklippertoolhead.h"
#include "qklipperchamber.h"
#include "qklipperfan.h"
#include "qklipperprintbed.h"
#include "qklippersteppermotor.h"

#include "qklippergcodemove.h"
#include "qklipperendstopstatus.h"
#include "qklippermcu.h"

#include "qklippersafezhome.h"
#include "qklipperextruder.h"

#include "qklippergcodemove.h"

class QKlipperConsole;

//!  QKlipperPrinter class
/*!
  This class provides information and methods for the klipper printer object
*/
class QKlipperPrinter : public QObject
{
    Q_OBJECT

    friend QKlipperConsole;
public:

    enum Status
    {
        Ready =      0b00000001,
        Error =      0b00000010,
        Paused =     0b00000100,
        Cancelled =  0b00001000,
        Printing =   0b00010000,
        Offline =    0b10000000,
        Connecting = 0b01000000
    };

    explicit QKlipperPrinter(QObject *parent = nullptr);
    ~QKlipperPrinter();

    QKlipperToolHead *toolhead() const;

    QKlipperPrintBed *bed() const;

    QKlipperChamber *chamber() const;

    QMap<QString, qreal> powerProfile() const;

    QString name() const;

    QString id() const;

    QString firmwareVersion() const;

    QString statusMessage() const;

    QString configFile() const;

    QString kinematics() const;

    QString color() const;

    qreal maxAcceleration() const;

    qreal maxVelocity() const;

    qreal maxZAcceleration() const;

    qreal maxZVelocity() const;

    qreal squareCornerVelocity() const;

    qreal printTime() const;

    bool autoConnect() const;

    bool defaultPrinter() const;

    QDateTime printStarted() const;

    QDateTime printEnding() const;

    Status status() const;

    QKlipperConsole *console() const;

    QKlipperPrintJob *printJob() const;

    QKlipperGCodeStore *gCodeStore() const;

    QKlipperMCU *mcu() const;

    QKlipperFile *currentFile() const;

    QKlipperSafeZHome safeZHome() const;

    QKlipperExtruder *extruder(const QString &name);

    QMap<QString, QKlipperFan *> fans() const;
    QKlipperFan *fan(const QString &name) const;

    QKlipperGCodeMove gcodeMove() const;

    QMap<QString, QKlipperStepperMotor *> stepperMotors() const;
    QKlipperStepperMotor *stepperMotor(const QString &name);

    QKlipperProbeData probeData() const;

    QKlipperEndstopStatus endstopStatus() const;

    void pause();
    void resume();
    void cancel();
    void start(QKlipperFile *file);

    qreal watts();

    bool hasChamber() const;

    qreal minimumCruiseRatio() const;

public slots:

    void setHasChamber(bool hasChamber);

    void setMinimumCruiseRatio(qreal minimumCruiseRatio);

private slots:

    void setPowerProfile(const QMap<QString, qreal> &powerProfile);

    void setName(const QString &name);

    void setId(const QString &id);

    void setFirmwareVersion(const QString &firmwareVersion);

    void setStatusMessage(const QString &statusMessage);

    void setConfigFile(const QString &configFile);

    void setKinematics(const QString &kinematics);

    void setColor(const QString &color);

    void setMaxAcceleration(qreal maxAcceleration);

    void setMaxVelocity(qreal maxVelocity);

    void setMaxZAcceleration(qreal maxZAcceleration);

    void setMaxZVelocity(qreal maxZVelocity);

    void setSquareCornerVelocity(qreal squareCornerVelocity);

    void setPrintTime(qreal printTime);

    void setAutoConnect(bool autoConnect);

    void setDefaultPrinter(bool defaultPrinter);

    void setPrintStarted(const QDateTime &printStarted);

    void setPrintEnding(const QDateTime &printEnding);

    void setStatus(Status status);

    void setConsole(QKlipperConsole *console);

    void setPrintJob(QKlipperPrintJob *printJob);

    void setMcu(QKlipperMCU *mcu);

    void setCurrentFile(QKlipperFile *currentFile);

    void setSafeZHome(QKlipperSafeZHome safeZHome);

    void setExtruder(QString name, QKlipperExtruder *extruder);

    void setFans(const QMap<QString, QKlipperFan *> &fans);
    void setFan(const QString &name, QKlipperFan *fan);

    void setGcodeMove(const QKlipperGCodeMove &gcodeMove);

    void setStepperMotors(const QMap<QString, QKlipperStepperMotor *> &stepperMotors);
    void setStepperMotor(const QString &name, QKlipperStepperMotor* motor);

    void setProbeData(const QKlipperProbeData &probeData);

    void setEndstopStatus(const QKlipperEndstopStatus &endstopStatus);

    void fakePrintTimeout();

signals:

    void powerProfileChanged();

    void nameChanged();

    void idChanged();

    void firmwareVersionChanged();

    void statusMessageChanged();

    void configFileChanged();

    void kinematicsChanged();

    void colorChanged();

    void maxAccelerationChanged();

    void maxVelocityChanged();

    void maxZAccelerationChanged();

    void maxZVelocityChanged();

    void squareCornerVelocityChanged();

    void printTimeChanged();

    void autoConnectChanged();

    void defaultPrinterChanged();

    void printStartedChanged();

    void printEndingChanged();

    void statusChanged();

    void printJobChanged();

    void gCodeStoreChanged();

    void mcuChanged();

    void currentFileChanged();

    void safeZHomeChanged();

    void fansChanged();

    void gcodeMoveChanged();

    void stepperMotorsChanged();

    void probeDataChanged();

    void endstopStatusChanged();

    void hasChamberChanged();

    void minimumCruiseRatioChanged();

private:
    QTimer *m_fakePrintTimer = nullptr;
    QKlipperToolHead                                *m_toolhead = nullptr;
    QKlipperPrintBed                                *m_bed = nullptr;
    QKlipperChamber                                 *m_chamber = nullptr;
    QKlipperMCU                                     *m_mcu = nullptr;

    QMap<QString,qreal>                              m_powerProfile;

    QString                                          m_name;
    QString                                          m_id;
    QString                                          m_firmwareVersion;
    QString                                          m_statusMessage;
    QString                                          m_configFile;
    QString                                          m_kinematics;
    QString                                          m_color;

    qreal                                            m_maxAcceleration = 0;
    qreal                                            m_maxVelocity = 0;
    qreal                                            m_maxZAcceleration = 0;
    qreal                                            m_maxZVelocity = 0;
    qreal                                            m_squareCornerVelocity = 0;
    qreal                                            m_printTime = 0;
    qreal                                            m_minimumCruiseRatio = 0;

    QTimer                                          *m_connectionTimer = nullptr;

    bool                                             m_autoConnect = true;
    bool                                             m_defaultPrinter = false;

    QKlipperFile                                    *m_currentFile = nullptr;
    QDateTime                                        m_printStarted;
    QDateTime                                        m_printEnding;

    Status                                           m_status = Offline;

    QKlipperConsole                                 *m_console = nullptr;

    QKlipperPrintJob                                *m_printJob = nullptr;

    QKlipperGCodeStore                              *m_gCodeStore = nullptr;
    QKlipperGCodeMove                                m_gcodeMove;

    QKlipperEndstopStatus                            m_endstopStatus;

    QMap<QString,QKlipperStepperMotor*>              m_stepperMotors;

    QKlipperProbeData                                m_probeData;

    QMap<QString,QKlipperFan*>                       m_fans;

    QKlipperSafeZHome                                m_safeZHome;
    bool                                             m_hasChamber = false;

    Q_PROPERTY(qreal minimumCruiseRatio READ minimumCruiseRatio WRITE setMinimumCruiseRatio NOTIFY
                   minimumCruiseRatioChanged FINAL)
};

#endif // QKLIPPERPRINTER_H
