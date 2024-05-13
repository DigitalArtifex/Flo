#include "bed.h"

Q3DPrintBed::Q3DPrintBed(Type type, QObject *parent)
    : QObject(parent)
{

}

long Q3DPrintBed::timeRunning()
{
    return _startTime.secsTo(QDateTime::currentDateTime());
}

qreal Q3DPrintBed::currentTemp() const
{
    return _currentTemp;
}

void Q3DPrintBed::setCurrentTemp(qreal currentTemp)
{
    _currentTemp = currentTemp;
}

qreal Q3DPrintBed::targetTemp() const
{
    return _targetTemp;
}

void Q3DPrintBed::setTargetTemp(qreal targetTemp)
{
    _targetTemp = targetTemp;
}

qreal Q3DPrintBed::power() const
{
    return _power;
}

void Q3DPrintBed::setPower(qreal power)
{
    _power = power;
}

qreal Q3DPrintBed::watts() const
{
    return _watts;
}

void Q3DPrintBed::setWatts(qreal watts)
{
    _watts = watts;
}

Q3DPrintBed::Mesh Q3DPrintBed::bedMesh() const
{
    return _bedMesh;
}

void Q3DPrintBed::setBedMesh(const Mesh &bedMesh)
{
    _bedMesh = bedMesh;

    emit meshUpdated(this);
}

/*!
 * \brief Q3DPrintBed::adjustmentScrew
 * \param key - the name of the screw object
 * \return The adjustment screw object if it exists, otherwise returns nullptr
 */
Q3DPrintBed::AdjustmentScrew *Q3DPrintBed::adjustmentScrew(QString &key) const
{
    if(_adjustmentScrews.contains(key))
        return _adjustmentScrews[key];
    else
        return nullptr;
}

void Q3DPrintBed::setAdjustmentScrew(QString &key, AdjustmentScrew *screw)
{
    _adjustmentScrews[key] = screw;
}

bool Q3DPrintBed::tiltAdjustError() const
{
    return _tiltAdjustError;
}

void Q3DPrintBed::setTiltAdjustError(bool tiltAdjustError)
{
    _tiltAdjustError = tiltAdjustError;
}

bool Q3DPrintBed::adjustmentScrewsError() const
{
    return _adjustmentScrewsError;
}

void Q3DPrintBed::setAdjustmentScrewsError(bool adjustmentScrewsError)
{
    _adjustmentScrewsError = adjustmentScrewsError;
}

qreal Q3DPrintBed::adjustmentScrewsMaxDeviation() const
{
    return _adjustmentScrewsMaxDeviation;
}

void Q3DPrintBed::setAdjustmentScrewsMaxDeviation(qreal adjustmentScrewsMaxDeviations)
{
    _adjustmentScrewsMaxDeviation = adjustmentScrewsMaxDeviations;
}
