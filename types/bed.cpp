#include "bed.h"
#include "printer.h"

Q3DPrintBed::Q3DPrintBed(Printer *printer, Type type, QObject *parent)
    : QObject(parent)
{
    _printer = printer;

    if(type == NonHeated)
        _watts = 0;
}

long Q3DPrintBed::timeRunning()
{
    return _startTime.secsTo(QDateTime::currentDateTime());
}

qreal Q3DPrintBed::currentTemp() const
{
    return _currentTemp;
}

qreal Q3DPrintBed::targetTemp() const
{
    return _targetTemp;
}

qreal Q3DPrintBed::power() const
{
    return _power;
}

qreal Q3DPrintBed::watts() const
{
    return _watts;
}

void Q3DPrintBed::setWatts(qreal watts)
{
    _watts = watts;

    emit updated(this);
}

Q3DPrintBed::Mesh Q3DPrintBed::bedMesh() const
{
    return _bedMesh;
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

bool Q3DPrintBed::tiltAdjustError() const
{
    return _tiltAdjustError;
}

bool Q3DPrintBed::adjustmentScrewsError() const
{
    return _adjustmentScrewsError;
}

qreal Q3DPrintBed::adjustmentScrewsMaxDeviation() const
{
    return _adjustmentScrewsMaxDeviation;
}

QMap<QString, Q3DPrintBed::AdjustmentScrew*> Q3DPrintBed::adjustmentScrews() const
{
    return _adjustmentScrews;
}

bool Q3DPrintBed::hasAdjustmentScrewResult() const
{
    return _hasAdjustmentScrewResult;
}

void Q3DPrintBed::calibrateAdjustmentScrews()
{
    _hasAdjustmentScrewResult = false;
    emit adjustmentScrewsCalibrating();

    QString gcode("SCREWS_TILT_CALCULATE");
    _printer->console()->sendGcode(gcode);
}

void Q3DPrintBed::calibrateBedMesh()
{
    _bedMeshCalibrating = true;
    emit bedMeshCalibrating();

    QString gcode("BED_MESH_CALIBRATE");
    _printer->console()->sendGcode(gcode);
}

Printer *Q3DPrintBed::printer() const
{
    return _printer;
}

void Q3DPrintBed::setPrinter(Printer *printer)
{
    _printer = printer;
}

void Q3DPrintBed::update()
{
    emit updated(this);
}

Q3DPrintBed::Type Q3DPrintBed::type() const
{
    return _type;
}

void Q3DPrintBed::updateAdjustmentScrews(const QMap<QString, AdjustmentScrew *> &adjustmentScrews)
{
    _adjustmentScrews = adjustmentScrews;

    foreach(AdjustmentScrew* screw, _adjustmentScrews)
    {
        if(screw->adjustment.direction != AdjustmentScrew::Adjustment::NotSet)
            _hasAdjustmentScrewResult = true;
        else
            _hasAdjustmentScrewResult = false;
    }

    emit adjustmentScrewsCalibrated();
}

void Q3DPrintBed::updateBedMesh(const Mesh mesh)
{
    _bedMesh = mesh;

    emit bedMeshCalibrated();
}
