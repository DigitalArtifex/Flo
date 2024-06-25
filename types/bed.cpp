#include "bed.h"
#include "printer.h"

Q3DPrintBed::Q3DPrintBed(Printer *printer, Type type, QObject *parent)
    : QObject(parent)
{
    m_printer = printer;

    if(type == NonHeated)
        m_watts = 0;
}

long Q3DPrintBed::timeRunning()
{
    return m_startTime.secsTo(QDateTime::currentDateTime());
}

qreal Q3DPrintBed::currentTemp() const
{
    return m_currentTemp;
}

qreal Q3DPrintBed::targetTemp() const
{
    return m_targetTemp;
}

qreal Q3DPrintBed::power() const
{
    return m_power;
}

qreal Q3DPrintBed::watts() const
{
    return (m_watts * m_power);
}

Q3DPrintBed::Mesh Q3DPrintBed::bedMesh() const
{
    return m_bedMesh;
}

/*!
 * \brief Q3DPrintBed::adjustmentScrew
 * \param key - the name of the screw object
 * \return The adjustment screw object if it exists, otherwise returns nullptr
 */
Q3DPrintBed::AdjustmentScrew *Q3DPrintBed::adjustmentScrew(QString &key) const
{
    if(m_adjustmentScrews.contains(key))
        return m_adjustmentScrews[key];
    else
        return nullptr;
}

bool Q3DPrintBed::tiltAdjustError() const
{
    return m_tiltAdjustError;
}

bool Q3DPrintBed::adjustmentScrewsError() const
{
    return m_adjustmentScrewsError;
}

qreal Q3DPrintBed::adjustmentScrewsMaxDeviation() const
{
    return m_adjustmentScrewsMaxDeviation;
}

QMap<QString, Q3DPrintBed::AdjustmentScrew*> Q3DPrintBed::adjustmentScrews() const
{
    return m_adjustmentScrews;
}

bool Q3DPrintBed::hasAdjustmentScrewResult() const
{
    return m_hasAdjustmentScrewResult;
}

void Q3DPrintBed::calibrateAdjustmentScrews()
{
    m_hasAdjustmentScrewResult = false;
    emit adjustmentScrewsCalibrating();

    QString gcode("SCREWS_TILT_CALCULATE");
    m_printer->console()->sendGcode(gcode);
}

void Q3DPrintBed::calibrateBedMesh()
{
    m_bedMeshCalibrating = true;
    emit bedMeshCalibrating();

    QString gcode("BED_MESH_CALIBRATE");
    m_printer->console()->sendGcode(gcode);
}

Printer *Q3DPrintBed::printer() const
{
    return m_printer;
}

void Q3DPrintBed::setPrinter(Printer *printer)
{
    m_printer = printer;
}

void Q3DPrintBed::update()
{
    emit updated(this);
}

Q3DPrintBed::Type Q3DPrintBed::type() const
{
    return m_type;
}

void Q3DPrintBed::updateAdjustmentScrews(const QMap<QString, AdjustmentScrew *> &adjustmentScrews)
{
    m_adjustmentScrews = adjustmentScrews;

    foreach(AdjustmentScrew* screw, m_adjustmentScrews)
    {
        if(screw->adjustment.direction != AdjustmentScrew::Adjustment::NotSet)
            m_hasAdjustmentScrewResult = true;
        else
            m_hasAdjustmentScrewResult = false;
    }

    emit adjustmentScrewsCalibrated();
}

void Q3DPrintBed::updateBedMesh(const Mesh mesh)
{
    m_bedMesh = mesh;

    emit bedMeshCalibrated();
}

qreal Q3DPrintBed::maxWatts() const
{
    return m_maxWatts;
}

void Q3DPrintBed::setMaxWatts(qreal maxWatts)
{
    m_maxWatts = maxWatts;
}
