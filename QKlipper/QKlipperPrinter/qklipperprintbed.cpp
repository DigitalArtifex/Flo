#include "qklipperprintbed.h"

#include "../QKlipperConsole/qklipperconsole.h"

QKlipperPrintBed::QKlipperPrintBed(QObject *parent)
    : QObject{parent}
{
    m_bedMesh = new QKlipperPrintBedMesh(this);
}

QKlipperPrintBed::~QKlipperPrintBed()
{
    if(m_bedMesh)
        m_bedMesh->deleteLater();

    foreach(QKlipperAdjustmentScrew *screw, m_adjustmentScrews)
        screw->deleteLater();
}

qreal QKlipperPrintBed::currentTemp() const
{
    return m_currentTemp;
}

void QKlipperPrintBed::setCurrentTemp(qreal currentTemp)
{
    if (qFuzzyCompare(m_currentTemp, currentTemp))
        return;

    m_currentTemp = currentTemp;
    emit currentTempChanged();
}

qreal QKlipperPrintBed::targetTemp() const
{
    return m_targetTemp;
}

void QKlipperPrintBed::setTargetTemp(qreal targetTemp)
{
    //M140 sets bed temp without waiting
    QString gcode = QString("M140 S") + QString::number(targetTemp);

    //send the G-Code
    m_console->printerGcodeScript(gcode);
}

void QKlipperPrintBed::calibratePid(qreal target)
{
    emit pidCalibrating();

    //set to relative movement
    QString gcode = QString("PID_CALIBRATE HEATER=%1 TARGET=%2").arg("heater_bed", QString::number(target));

    //run calibration
    m_console->printerGcodeScript(gcode);

    emit pidCalibratingFinished();
}

void QKlipperPrintBed::calibrateAdjustmentScrews()
{
    setHasAdjustmentScrewResult(false);
    emit adjustmentScrewsCalibrating();

    QString gcode("SCREWS_TILT_CALCULATE");
    m_console->printerGcodeScript(gcode);

    emit adjustmentScrewsCalibratingFinished();
}

void QKlipperPrintBed::calibrateBedMesh()
{
    setHasBedMeshResult(false);
    m_bedMesh->setReportedProbePoints(0);

    emit bedMeshCalibrating();

    QString gcode("BED_MESH_CALIBRATE");
    m_console->printerGcodeScript(gcode);

    emit bedMeshCalibratingFinished();
}

void QKlipperPrintBed::setTargetTempData(qreal targetTemp)
{
    if (qFuzzyCompare(m_targetTemp, targetTemp))
        return;

    m_targetTemp = targetTemp;
    emit targetTempChanged();
}

qreal QKlipperPrintBed::power() const
{
    return m_power;
}

void QKlipperPrintBed::setPower(qreal power)
{
    if (qFuzzyCompare(m_power, power))
        return;

    m_power = power;
    emit powerChanged();
}

qreal QKlipperPrintBed::watts() const
{
    return m_watts;
}

void QKlipperPrintBed::setWatts(qreal watts)
{
    if (qFuzzyCompare(m_watts, watts))
        return;

    m_watts = watts;
    emit wattsChanged();
}

qreal QKlipperPrintBed::maxWatts() const
{
    return m_maxWatts;
}

void QKlipperPrintBed::setMaxWatts(qreal maxWatts)
{
    if (qFuzzyCompare(m_maxWatts, maxWatts))
        return;

    m_maxWatts = maxWatts;
    emit maxWattsChanged();
}

qreal QKlipperPrintBed::inlineResistor() const
{
    return m_inlineResistor;
}

void QKlipperPrintBed::setInlineResistor(qreal inlineResistor)
{
    if (qFuzzyCompare(m_inlineResistor, inlineResistor))
        return;

    m_inlineResistor = inlineResistor;
    emit inlineResistorChanged();
}

qreal QKlipperPrintBed::maxPower() const
{
    return m_maxPower;
}

void QKlipperPrintBed::setMaxPower(qreal maxPower)
{
    if (qFuzzyCompare(m_maxPower, maxPower))
        return;

    m_maxPower = maxPower;
    emit maxPowerChanged();
}

qreal QKlipperPrintBed::maxTemp() const
{
    return m_maxTemp;
}

void QKlipperPrintBed::setMaxTemp(qreal maxTemp)
{
    if (qFuzzyCompare(m_maxTemp, maxTemp))
        return;

    m_maxTemp = maxTemp;
    emit maxTempChanged();
}

qreal QKlipperPrintBed::minTemp() const
{
    return m_minTemp;
}

void QKlipperPrintBed::setMinTemp(qreal minTemp)
{
    if (qFuzzyCompare(m_minTemp, minTemp))
        return;

    m_minTemp = minTemp;
    emit minTempChanged();
}

qreal QKlipperPrintBed::pidKD() const
{
    return m_pidKD;
}

void QKlipperPrintBed::setPidKD(qreal pidKD)
{
    if (qFuzzyCompare(m_pidKD, pidKD))
        return;

    m_pidKD = pidKD;
    emit pidKDChanged();
}

qreal QKlipperPrintBed::pidKI() const
{
    return m_pidKI;
}

void QKlipperPrintBed::setPidKI(qreal pidKI)
{
    if (qFuzzyCompare(m_pidKI, pidKI))
        return;

    m_pidKI = pidKI;
    emit pidKIChanged();
}

qreal QKlipperPrintBed::pidKP() const
{
    return m_pidKP;
}

void QKlipperPrintBed::setPidKP(qreal pidKP)
{
    if (qFuzzyCompare(m_pidKP, pidKP))
        return;

    m_pidKP = pidKP;
    emit pidKPChanged();
}

qreal QKlipperPrintBed::pullupResistor() const
{
    return m_pullupResistor;
}

void QKlipperPrintBed::setPullupResistor(qreal pullupResistor)
{
    if (qFuzzyCompare(m_pullupResistor, pullupResistor))
        return;

    m_pullupResistor = pullupResistor;
    emit pullupResistorChanged();
}

qreal QKlipperPrintBed::pwmCycleTime() const
{
    return m_pwmCycleTime;
}

void QKlipperPrintBed::setPwmCycleTime(qreal pwmCycleTime)
{
    if (qFuzzyCompare(m_pwmCycleTime, pwmCycleTime))
        return;

    m_pwmCycleTime = pwmCycleTime;
    emit pwmCycleTimeChanged();
}

qreal QKlipperPrintBed::smoothTime() const
{
    return m_smoothTime;
}

void QKlipperPrintBed::setSmoothTime(qreal smoothTime)
{
    if (qFuzzyCompare(m_smoothTime, smoothTime))
        return;

    m_smoothTime = smoothTime;
    emit smoothTimeChanged();
}

QDateTime QKlipperPrintBed::startTime() const
{
    return m_startTime;
}

void QKlipperPrintBed::setStartTime(const QDateTime &startTime)
{
    if (m_startTime == startTime)
        return;
    m_startTime = startTime;
    emit startTimeChanged();
}

QKlipperPrintBedMesh *QKlipperPrintBed::bedMesh() const
{
    return m_bedMesh;
}

void QKlipperPrintBed::setBedMesh(QKlipperPrintBedMesh *bedMesh)
{
    if (m_bedMesh == bedMesh)
        return;
    m_bedMesh = bedMesh;
    emit bedMeshChanged();
}

QMap<QString, QKlipperAdjustmentScrew *> QKlipperPrintBed::adjustmentScrews() const
{
    return m_adjustmentScrews;
}

QKlipperAdjustmentScrew *QKlipperPrintBed::adjustmentScrew(const QString &name)
{
    if(m_adjustmentScrews.contains(name))
        return m_adjustmentScrews[name];

    return nullptr;
}

void QKlipperPrintBed::setAdjustmentScrews(const QMap<QString, QKlipperAdjustmentScrew *> &adjustmentScrews)
{
    if (m_adjustmentScrews == adjustmentScrews)
        return;

    m_adjustmentScrews = adjustmentScrews;
    emit adjustmentScrewsChanged();
}

void QKlipperPrintBed::setAdjustmentScrew(QString name, QKlipperAdjustmentScrew *adjustmentScrew)
{
    if(m_adjustmentScrews.contains(name))
    {
        if(m_adjustmentScrews[name] == adjustmentScrew)
            return;

        QKlipperAdjustmentScrew *screw = m_adjustmentScrews[name];
        m_adjustmentScrews.remove(name);

        screw->deleteLater();
        screw = nullptr;
    }

    m_adjustmentScrews[name] = adjustmentScrew;
    emit adjustmentScrewsChanged();
}

bool QKlipperPrintBed::adjustmentScrewsError() const
{
    return m_adjustmentScrewsError;
}

void QKlipperPrintBed::setAdjustmentScrewsError(bool adjustmentScrewsError)
{
    if (m_adjustmentScrewsError == adjustmentScrewsError)
        return;
    m_adjustmentScrewsError = adjustmentScrewsError;
    emit adjustmentScrewsErrorChanged();
}

bool QKlipperPrintBed::hasAdjustmentScrewResult() const
{
    return m_hasAdjustmentScrewResult;
}

void QKlipperPrintBed::setHasAdjustmentScrewResult(bool hasAdjustmentScrewResult)
{
    if (m_hasAdjustmentScrewResult == hasAdjustmentScrewResult)
        return;
    m_hasAdjustmentScrewResult = hasAdjustmentScrewResult;
    emit hasAdjustmentScrewResultChanged();
}

bool QKlipperPrintBed::hasBedMeshResult() const
{
    return m_hasBedMeshResult;
}

void QKlipperPrintBed::setHasBedMeshResult(bool hasBedMeshResult)
{
    if (m_hasBedMeshResult == hasBedMeshResult)
        return;
    m_hasBedMeshResult = hasBedMeshResult;
    emit hasBedMeshResultChanged();
}

bool QKlipperPrintBed::isAdjustmentScrewsCalibrating() const
{
    return m_adjustmentScrewsCalibrating;
}

void QKlipperPrintBed::setAdjustmentScrewsCalibrating(bool adjustmentScrewsCalibrating)
{
    if (m_adjustmentScrewsCalibrating == adjustmentScrewsCalibrating)
        return;
    m_adjustmentScrewsCalibrating = adjustmentScrewsCalibrating;
    emit adjustmentScrewsCalibratingChanged();
}

bool QKlipperPrintBed::isBedMeshCalibrating() const
{
    return m_bedMeshCalibrating;
}

void QKlipperPrintBed::setBedMeshCalibrating(bool bedMeshCalibrating)
{
    if (m_bedMeshCalibrating == bedMeshCalibrating)
        return;

    m_bedMeshCalibrating = bedMeshCalibrating;
    emit bedMeshCalibratingChanged();
}

qreal QKlipperPrintBed::adjustmentScrewsMaxDeviation() const
{
    return m_adjustmentScrewsMaxDeviation;
}

void QKlipperPrintBed::setAdjustmentScrewsMaxDeviation(qreal adjustmentScrewsMaxDeviation)
{
    if (qFuzzyCompare(m_adjustmentScrewsMaxDeviation, adjustmentScrewsMaxDeviation))
        return;
    m_adjustmentScrewsMaxDeviation = adjustmentScrewsMaxDeviation;
    emit adjustmentScrewsMaxDeviationChanged();
}

bool QKlipperPrintBed::tiltAdjustError() const
{
    return m_tiltAdjustError;
}

void QKlipperPrintBed::setTiltAdjustError(bool tiltAdjustError)
{
    if (m_tiltAdjustError == tiltAdjustError)
        return;
    m_tiltAdjustError = tiltAdjustError;
    emit tiltAdjustErrorChanged();
}

QKlipperPrinter *QKlipperPrintBed::printer() const
{
    return qobject_cast<QKlipperPrinter*>(parent());
}

void QKlipperPrintBed::setPrinter(QKlipperPrinter *printer)
{
    if (m_printer == printer)
        return;
    m_printer = printer;
    emit printerChanged();
}

QKlipperConsole *QKlipperPrintBed::console() const
{
    return m_console;
}

void QKlipperPrintBed::setConsole(QKlipperConsole *console)
{
    if (m_console == console)
        return;
    m_console = console;
    emit consoleChanged();
}

QString QKlipperPrintBed::control() const
{
    return m_control;
}

void QKlipperPrintBed::setControl(const QString &control)
{
    if (m_control == control)
        return;
    m_control = control;
    emit controlChanged();
}

QString QKlipperPrintBed::sensorPin() const
{
    return m_sensorPin;
}

void QKlipperPrintBed::setSensorPin(const QString &sensorPin)
{
    if (m_sensorPin == sensorPin)
        return;
    m_sensorPin = sensorPin;
    emit sensorPinChanged();
}

QKlipperPrintBed::Type QKlipperPrintBed::type() const
{
    return m_type;
}

void QKlipperPrintBed::setType(Type type)
{
    if (m_type == type)
        return;
    m_type = type;
    emit typeChanged();
}

QString QKlipperPrintBed::heaterPin() const
{
    return m_heaterPin;
}

void QKlipperPrintBed::setHeaterPin(const QString &heaterPin)
{
    if (m_heaterPin == heaterPin)
        return;
    m_heaterPin = heaterPin;
    emit heaterPinChanged();
}

QString QKlipperPrintBed::sensorType() const
{
    return m_sensorType;
}

void QKlipperPrintBed::setSensorType(const QString &sensorType)
{
    if (m_sensorType == sensorType)
        return;
    m_sensorType = sensorType;
    emit sensorTypeChanged();
}
