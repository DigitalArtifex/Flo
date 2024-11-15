/*!
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

#ifndef QKLIPPERPRINTBED_H
#define QKLIPPERPRINTBED_H

#include <QObject>
#include <QMap>
#include <QDateTime>

#include "qklipperprintbedmesh.h"
#include "qklipperadjustmentscrew.h"

class QKlipperPrinter;
class QKlipperConsole;

//!  QKlipperPrintBed class
/*!
  This class is responsible for the actual communication to the klipper instance via moonraker.
  It provides methods for the moonraker API for controlling and querying aspects of the klipper
  instance.

  Prior to connecting, it is required to pass instance references to QKlipperPrinter, QKlipperSystem
  and QKlipperServer that have been setup and configured.
*/
class QKlipperPrintBed : public QObject
{
    Q_OBJECT
    friend QKlipperConsole;
    friend QKlipperPrinter;
public:
    enum Type
    {
        Heated,
        NonHeated
    };

    /*!
     * Constructor
     *
     * \param parent The parent object
     */
    explicit QKlipperPrintBed(QObject *parent = nullptr);

    /*!
     * Destructor
     */
    ~QKlipperPrintBed();

    qreal currentTemp() const;

    qreal targetTemp() const;

    qreal power() const;

    qreal watts() const;

    qreal maxWatts() const;

    qreal inlineResistor() const;

    qreal maxPower() const;

    qreal maxTemp() const;

    qreal minTemp() const;

    qreal pidKD() const;

    qreal pidKI() const;

    qreal pidKP() const;

    qreal pullupResistor() const;

    qreal pwmCycleTime() const;

    qreal smoothTime() const;

    QDateTime startTime() const;

    QKlipperPrintBedMesh *bedMesh() const;

    QMap<QString, QKlipperAdjustmentScrew *> adjustmentScrews() const;
    QKlipperAdjustmentScrew *adjustmentScrew(const QString &name);

    bool adjustmentScrewsError() const;

    bool hasAdjustmentScrewResult() const;

    bool hasBedMeshResult() const;

    bool isAdjustmentScrewsCalibrating() const;

    bool isBedMeshCalibrating() const;

    qreal adjustmentScrewsMaxDeviation() const;

    bool tiltAdjustError() const;

    QKlipperPrinter *printer() const;

    QKlipperConsole *console() const;

    QString control() const;

    QString sensorPin() const;

    Type type() const;

    QString heaterPin() const;

    QString sensorType() const;

public slots:
    /*!
     * Sends a gcode script to set the requested temperature
     *
     * \param targetTemp The value (in Celsius) to set (0-maxTemp)
     */
    void setTargetTemp(qreal targetTemp);

    /*!
     * Sends a gcode script to calibrate the extruder at the target temperature.
     *
     * \param target The temperature to use in the PID calibration
     */
    void calibratePid(qreal target);

    /*!
     * Sends a gcode script to probe the bed corners to determine adjustment values
     */
    void calibrateAdjustmentScrews();

    /*!
     * Sends a gcode script to probe the entire bed to generate the bed mesh
     */
    void calibrateBedMesh();

    void setMaxWatts(qreal maxWatts);

private slots:
    void setCurrentTemp(qreal currentTemp);

    void setTargetTempData(qreal targetTemp);

    void setPower(qreal power);

    void setWatts(qreal watts);

    void setInlineResistor(qreal inlineResistor);

    void setMaxPower(qreal maxPower);

    void setMaxTemp(qreal maxTemp);

    void setMinTemp(qreal minTemp);

    void setPidKD(qreal pidKD);

    void setPidKI(qreal pidKI);

    void setPidKP(qreal pidKP);

    void setPullupResistor(qreal pullupResistor);

    void setPwmCycleTime(qreal pwmCycleTime);

    void setSmoothTime(qreal smoothTime);

    void setStartTime(const QDateTime &startTime);

    void setBedMesh(QKlipperPrintBedMesh *bedMesh);

    void setAdjustmentScrews(const QMap<QString, QKlipperAdjustmentScrew *> &adjustmentScrews);
    void setAdjustmentScrew(QString name, QKlipperAdjustmentScrew *adjustmentScrew);

    void setAdjustmentScrewsError(bool adjustmentScrewsError);

    void setHasAdjustmentScrewResult(bool hasAdjustmentScrewResult);

    void setHasBedMeshResult(bool hasBedMeshResult);

    void setAdjustmentScrewsCalibrating(bool adjustmentScrewsCalibrating);

    void setBedMeshCalibrating(bool bedMeshCalibrating);

    void setAdjustmentScrewsMaxDeviation(qreal adjustmentScrewsMaxDeviation);

    void setTiltAdjustError(bool tiltAdjustError);

    void setPrinter(QKlipperPrinter *printer);

    void setConsole(QKlipperConsole *console);

    void setControl(const QString &control);

    void setSensorPin(const QString &sensorPin);

    void setType(Type type);

    void setHeaterPin(const QString &heaterPin);

    void setSensorType(const QString &sensorType);

signals:

    void currentTempChanged();
    void targetTempChanged();
    void powerChanged();
    void wattsChanged();
    void maxWattsChanged();
    void inlineResistorChanged();
    void maxPowerChanged();
    void maxTempChanged();
    void minTempChanged();
    void pidKDChanged();
    void pidKIChanged();
    void pidKPChanged();
    void pullupResistorChanged();
    void pwmCycleTimeChanged();
    void smoothTimeChanged();
    void startTimeChanged();
    void bedMeshChanged();
    void adjustmentScrewsChanged();
    void adjustmentScrewsErrorChanged();
    void hasAdjustmentScrewResultChanged();
    void hasBedMeshResultChanged();
    void adjustmentScrewsCalibratingChanged();
    void bedMeshCalibratingChanged();
    void adjustmentScrewsMaxDeviationChanged();
    void tiltAdjustErrorChanged();
    void printerChanged();
    void consoleChanged();
    void controlChanged();
    void sensorPinChanged();
    void typeChanged();

    void heaterPinChanged();

    void sensorTypeChanged();

    void adjustmentScrewsCalibrating();
    void adjustmentScrewsCalibratingFinished();
    void bedMeshCalibrating();
    void bedMeshCalibratingFinished();

private:
    qreal m_currentTemp = 0;
    qreal m_targetTemp = 0;
    qreal m_power = 0;
    qreal m_watts = 0;
    qreal m_maxWatts = 0;
    qreal m_inlineResistor = 0;
    qreal m_maxPower = 0;
    qreal m_maxTemp= 0;
    qreal m_minTemp = 0;
    qreal m_pidKD = 0;
    qreal m_pidKI = 0;
    qreal m_pidKP = 0;
    qreal m_pullupResistor = 0;
    qreal m_pwmCycleTime = 0;
    qreal m_smoothTime = 0;

    QDateTime m_startTime;

    QKlipperPrintBedMesh *m_bedMesh;

    QMap<QString, QKlipperAdjustmentScrew*>  m_adjustmentScrews;
    bool                                     m_adjustmentScrewsError = false;
    bool                                     m_hasAdjustmentScrewResult = false;
    bool                                     m_hasBedMeshResult = false;
    bool                                     m_adjustmentScrewsCalibrating = false;
    bool                                     m_bedMeshCalibrating = false;
    qreal                                    m_adjustmentScrewsMaxDeviation = 0;

    bool                                     m_tiltAdjustError = false;

    QKlipperPrinter                         *m_printer = nullptr;
    QKlipperConsole                         *m_console = nullptr;

    QString                                  m_control;
    QString                                  m_heaterPin;
    QString                                  m_sensorPin;
    QString                                  m_sensorType;

    Type                                     m_type = NonHeated;
};

Q_DECLARE_METATYPE(QKlipperPrintBed::Type)
#endif // QKLIPPERPRINTBED_H
