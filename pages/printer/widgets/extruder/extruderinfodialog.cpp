#include "extruderinfodialog.h"

ExtruderInfoDialog::ExtruderInfoDialog(QKlipperExtruder *extruder, QWidget *parent)
    : Dialog{parent}
{
    m_extruder = extruder;
    setupUi();
    reset();

    connect(m_extruder, SIGNAL(canExtrudeChanged()), this, SLOT(onCanExtrudeChanged()));
    connect(m_extruder, SIGNAL(controlChanged()), this, SLOT(onControlPinChanged()));
    connect(m_extruder, SIGNAL(currentTempChanged()), this, SLOT(onCurrentTempChanged()));
    connect(m_extruder, SIGNAL(dirPinChanged()), this, SLOT(onDirPinChanged()));
    connect(m_extruder, SIGNAL(enablePinChanged()), this, SLOT(onEnablePinChanged()));
    connect(m_extruder, SIGNAL(extrusionFactorChanged()), this, SLOT(onExtrusionFactorChanged()));
    connect(m_extruder, SIGNAL(filamentDiameterChanged()), this, SLOT(onFilamentDiameterChanged()));
    connect(m_extruder, SIGNAL(fullStepsPerRotationChanged()), this, SLOT(onFullStepsPerRoatationChanged()));
    connect(m_extruder, SIGNAL(gearRatioChanged()), this, SLOT(onGearRatioChanged()));
    connect(m_extruder, SIGNAL(heaterPinChanged()), this, SLOT(onHeaterPinChanged()));
    connect(m_extruder, SIGNAL(inlineResistorChanged()), this, SLOT(onInlineResistorChanged()));
    connect(m_extruder, SIGNAL(instantCornerVelocityChanged()), this, SLOT(onInstantCornerVelocityChanged()));
    connect(m_extruder, SIGNAL(maxExtrudeCrossSectionChanged()), this, SLOT(onMaxExtrudeCrossSectionChanged()));
    connect(m_extruder, SIGNAL(maxExtrudeOnlyAccelerationChanged()), this, SLOT(onMaxExtrudeOnlyAccelerationChanged()));
    connect(m_extruder, SIGNAL(maxExtrudeOnlyDistanceChanged()), this, SLOT(onMaxExtrudeOnlyDistanceChanged()));
    connect(m_extruder, SIGNAL(maxExtrudeOnlyVelocityChanged()), this, SLOT(onMaxExtrudeOnlyVelocityChanged()));
    connect(m_extruder, SIGNAL(maxPowerChanged()), this, SLOT(onMaxPowerChanged()));
    connect(m_extruder, SIGNAL(maxTempChanged()), this, SLOT(onMaxTempChanged()));
    connect(m_extruder, SIGNAL(microstepsChanged()), this, SLOT(onMicrostepsChanged()));
    connect(m_extruder, SIGNAL(minExtrudeTempChanged()), this, SLOT(onMinExtrudeTempChanged()));
    connect(m_extruder, SIGNAL(minTempChanged()), this, SLOT(onMinTempChanged()));
    connect(m_extruder, SIGNAL(nameChanged()), this, SLOT(onNameChanged()));
    connect(m_extruder, SIGNAL(nozzleDiameterChanged()), this, SLOT(onNozzleDiameterChanged()));
    connect(m_extruder, SIGNAL(offsetChanged()), this, SLOT(onOffsetChanged()));
    connect(m_extruder, SIGNAL(pidKDChanged()), this, SLOT(onPidKDChanged()));
    connect(m_extruder, SIGNAL(pidKIChanged()), this, SLOT(onPidKIChanged()));
    connect(m_extruder, SIGNAL(pidKPChanged()), this, SLOT(onPidKPChanged()));
    connect(m_extruder, SIGNAL(powerChanged()), this, SLOT(onPowerChanged()));
    connect(m_extruder, SIGNAL(pressureAdvanceChanged()), this, SLOT(onPressureAdvanceChanged()));
    connect(m_extruder, SIGNAL(pullupResistorChanged()), this, SLOT(onPullupResistorChanged()));
    connect(m_extruder, SIGNAL(pwmCycleChanged()), this, SLOT(onPwmCycleChanged()));
    connect(m_extruder, SIGNAL(rotationDistanceChanged()), this, SLOT(onRotationDistanceChanged()));
    connect(m_extruder, SIGNAL(sensorPinChanged()), this, SLOT(onSensorPinChanged()));
    connect(m_extruder, SIGNAL(sensorTypeChanged()), this, SLOT(onSensorTypeChanged()));
    connect(m_extruder, SIGNAL(smoothTimeChanged()), this, SLOT(onSmoothTimeChanged()));
    connect(m_extruder, SIGNAL(stepPinChanged()), this, SLOT(onStepPinChanged()));
    connect(m_extruder, SIGNAL(targetTempChanged()), this, SLOT(onTargetTempChanged()));
}

ExtruderInfoDialog::~ExtruderInfoDialog()
{
    m_itemMap.clear();
}

void ExtruderInfoDialog::onGearRatioChanged()
{
    if(!m_itemMap.contains("onGearRatioChanged"))
        addTableItem("onGearRatioChanged");

    QString text = QString("Gear Ratio: %1/%2").arg(
        QVariant(m_extruder->gearRatio().first).toString(),
        QVariant(m_extruder->gearRatio().second).toString()
            );

    m_itemMap["onGearRatioChanged"]->setText(text);
}

void ExtruderInfoDialog::onFullStepsPerRoatationChanged()
{
    if(!m_itemMap.contains("onFullStepsPerRoatationChanged"))
        addTableItem("onFullStepsPerRoatationChanged");

    QString text = QString("Full Steps Per Rotation: %1").arg(
        QVariant(m_extruder->fullStepsPerRotation()).toString()
        );

    m_itemMap["onFullStepsPerRoatationChanged"]->setText(text);
}

void ExtruderInfoDialog::onCurrentTempChanged()
{
    if(!m_itemMap.contains("onCurrentTempChanged"))
        addTableItem("onCurrentTempChanged");

    QString text = QString("Current Temp: %1").arg(
        QVariant(m_extruder->currentTemp()).toString()
        );

    m_itemMap["onCurrentTempChanged"]->setText(text);
}

void ExtruderInfoDialog::onTargetTempChanged()
{
    if(!m_itemMap.contains("onCurrentTempChanged"))
        addTableItem("onCurrentTempChanged");

    QString text = QString("Current Temp: %1").arg(
        QVariant(m_extruder->currentTemp()).toString()
        );

    m_itemMap["onCurrentTempChanged"]->setText(text);
}

void ExtruderInfoDialog::onSmoothTimeChanged()
{
    if(!m_itemMap.contains("onSmoothTimeChanged"))
        addTableItem("onSmoothTimeChanged");

    QString text = QString("Smooth Time: %1").arg(
        QVariant(m_extruder->smoothTime()).toString()
        );

    m_itemMap["onSmoothTimeChanged"]->setText(text);
}

void ExtruderInfoDialog::onPressureAdvanceChanged()
{
    if(!m_itemMap.contains("onPressureAdvanceChanged"))
        addTableItem("onPressureAdvanceChanged");

    QString text = QString("Pressure Advance: %1").arg(
        QVariant(m_extruder->pressureAdvance()).toString()
        );

    m_itemMap["onPressureAdvanceChanged"]->setText(text);
}

void ExtruderInfoDialog::onExtrusionFactorChanged()
{
    if(!m_itemMap.contains("onExtrusionFactorChanged"))
        addTableItem("onExtrusionFactorChanged");

    QString text = QString("Extrusion Factor: %1").arg(
        QVariant(m_extruder->extrusionFactor()).toString()
        );

    m_itemMap["onExtrusionFactorChanged"]->setText(text);
}

void ExtruderInfoDialog::onFilamentDiameterChanged()
{
    if(!m_itemMap.contains("onFilamentDiameterChanged"))
        addTableItem("onFilamentDiameterChanged");

    QString text = QString("Filament Diameter: %1").arg(
        QVariant(m_extruder->filamentDiameter()).toString()
        );

    m_itemMap["onFilamentDiameterChanged"]->setText(text);
}

void ExtruderInfoDialog::onNozzleDiameterChanged()
{
    if(!m_itemMap.contains("onNozzleDiameterChanged"))
        addTableItem("onNozzleDiameterChanged");

    QString text = QString("Nozzle Diameter: %1").arg(
        QVariant(m_extruder->nozzleDiameter()).toString()
        );

    m_itemMap["onNozzleDiameterChanged"]->setText(text);
}

void ExtruderInfoDialog::onPowerChanged()
{
    if(!m_itemMap.contains("onPowerChanged"))
        addTableItem("onPowerChanged");

    QString text = QString("Power: %1").arg(
        QVariant(m_extruder->power()).toString()
        );

    m_itemMap["onPowerChanged"]->setText(text);
}

void ExtruderInfoDialog::onInlineResistorChanged()
{
    if(!m_itemMap.contains("onInlineResistorChanged"))
        addTableItem("onInlineResistorChanged");

    QString text = QString("Inline Resistor: %1Ω").arg(
        QVariant(m_extruder->inlineResistor()).toString()
        );

    m_itemMap["onInlineResistorChanged"]->setText(text);
}

void ExtruderInfoDialog::onPullupResistorChanged()
{
    if(!m_itemMap.contains("onPullupResistorChanged"))
        addTableItem("onPullupResistorChanged");

    QString text = QString("Pullup Resistor: %1Ω").arg(
        QVariant(m_extruder->pullupResistor()).toString()
        );

    m_itemMap["onPullupResistorChanged"]->setText(text);
}

void ExtruderInfoDialog::onPwmCycleChanged()
{
    if(!m_itemMap.contains("onPwmCycleChanged"))
        addTableItem("onPwmCycleChanged");

    QString text = QString("PWM Cycle Time: %1").arg(
        QVariant(m_extruder->pwmCycle()).toString()
        );

    m_itemMap["onPwmCycleChanged"]->setText(text);
}

void ExtruderInfoDialog::onRotationDistanceChanged()
{
    if(!m_itemMap.contains("onRotationDistanceChanged"))
        addTableItem("onRotationDistanceChanged");

    QString text = QString("Rotation Distancce: %1").arg(
        QVariant(m_extruder->rotationDistance()).toString()
        );

    m_itemMap["onRotationDistanceChanged"]->setText(text);
}

void ExtruderInfoDialog::onInstantCornerVelocityChanged()
{
    if(!m_itemMap.contains("onInstantCornerVelocityChanged"))
        addTableItem("onInstantCornerVelocityChanged");

    QString text = QString("Instant Corner Velocity: %1").arg(
        QVariant(m_extruder->rotationDistance()).toString()
        );

    m_itemMap["onInstantCornerVelocityChanged"]->setText(text);
}

void ExtruderInfoDialog::onPidKDChanged()
{
    if(!m_itemMap.contains("onPidKDChanged"))
        addTableItem("onPidKDChanged");

    QString text = QString("PID KD: %1").arg(
        QVariant(m_extruder->pidKD()).toString()
        );

    m_itemMap["onPidKDChanged"]->setText(text);
}

void ExtruderInfoDialog::onPidKIChanged()
{
    if(!m_itemMap.contains("onPidKIChanged"))
        addTableItem("onPidKIChanged");

    QString text = QString("PID KI: %1").arg(
        QVariant(m_extruder->pidKI()).toString()
        );

    m_itemMap["onPidKIChanged"]->setText(text);
}

void ExtruderInfoDialog::onPidKPChanged()
{
    if(!m_itemMap.contains("onPidKPChanged"))
        addTableItem("onPidKPChanged");

    QString text = QString("PID KP: %1").arg(
        QVariant(m_extruder->pidKP()).toString()
        );

    m_itemMap["onPidKPChanged"]->setText(text);
}

void ExtruderInfoDialog::onMaxExtrudeCrossSectionChanged()
{
    if(!m_itemMap.contains("onMaxExtrudeCrossSectionChanged"))
        addTableItem("onMaxExtrudeCrossSectionChanged");

    QString text = QString("Max Extrude Cross Section: %1").arg(
        QVariant(m_extruder->maxExtrudeCrossSection()).toString()
        );

    m_itemMap["onMaxExtrudeCrossSectionChanged"]->setText(text);
}

void ExtruderInfoDialog::onMaxExtrudeOnlyAccelerationChanged()
{
    if(!m_itemMap.contains("onMaxExtrudeOnlyAccelerationChanged"))
        addTableItem("onMaxExtrudeOnlyAccelerationChanged");

    QString text = QString("Max Extrude Only Acceleration: %1").arg(
        QVariant(m_extruder->maxExtrudeOnlyAcceleration()).toString()
        );

    m_itemMap["onMaxExtrudeOnlyAccelerationChanged"]->setText(text);
}

void ExtruderInfoDialog::onMaxExtrudeOnlyDistanceChanged()
{
    if(!m_itemMap.contains("onMaxExtrudeOnlyDistanceChanged"))
        addTableItem("onMaxExtrudeOnlyDistanceChanged");

    QString text = QString("Max Extrude Only Distance: %1").arg(
        QVariant(m_extruder->maxExtrudeOnlyDistance()).toString()
        );

    m_itemMap["onMaxExtrudeOnlyDistanceChanged"]->setText(text);
}

void ExtruderInfoDialog::onMaxExtrudeOnlyVelocityChanged()
{
    if(!m_itemMap.contains("onMaxExtrudeOnlyVelocityChanged"))
        addTableItem("onMaxExtrudeOnlyVelocityChanged");

    QString text = QString("Max Extrude Only Velocity: %1").arg(
        QVariant(m_extruder->maxExtrudeOnlyVelocity()).toString()
        );

    m_itemMap["onMaxExtrudeOnlyVelocityChanged"]->setText(text);
}

void ExtruderInfoDialog::onMaxTempChanged()
{
    if(!m_itemMap.contains("onMaxTempChanged"))
        addTableItem("onMaxTempChanged");

    QString text = QString("Max Temperature: %1").arg(
        QVariant(m_extruder->maxTemp()).toString()
        );

    m_itemMap["onMaxTempChanged"]->setText(text);
}

void ExtruderInfoDialog::onMaxPowerChanged()
{
    if(!m_itemMap.contains("onMaxPowerChanged"))
        addTableItem("onMaxPowerChanged");

    QString text = QString("Max Power: %1").arg(
        QVariant(m_extruder->maxPower()).toString()
        );

    m_itemMap["onMaxPowerChanged"]->setText(text);
}

void ExtruderInfoDialog::onMicrostepsChanged()
{
    if(!m_itemMap.contains("onMicrostepsChanged"))
        addTableItem("onMicrostepsChanged");

    QString text = QString("Microsteps: %1").arg(
        QVariant(m_extruder->microsteps()).toString()
        );

    m_itemMap["onMicrostepsChanged"]->setText(text);
}

void ExtruderInfoDialog::onMinExtrudeTempChanged()
{
    if(!m_itemMap.contains("onMinExtrudeTempChanged"))
        addTableItem("onMinExtrudeTempChanged");

    QString text = QString("Min Extrude Temperature: %1").arg(
        QVariant(m_extruder->minExtrudeTemp()).toString()
        );

    m_itemMap["onMinExtrudeTempChanged"]->setText(text);
}

void ExtruderInfoDialog::onMinTempChanged()
{
    if(!m_itemMap.contains("onMinTempChanged"))
        addTableItem("onMinTempChanged");

    QString text = QString("Min Temperature: %1").arg(
        QVariant(m_extruder->minTemp()).toString()
        );

    m_itemMap["onMinTempChanged"]->setText(text);
}

void ExtruderInfoDialog::onCanExtrudeChanged()
{
    if(!m_itemMap.contains("onCanExtrudeChanged"))
        addTableItem("onCanExtrudeChanged");

    QString text = QString("Can Extrude: %1").arg(
        QVariant(m_extruder->canExtrude()).toString()
        );

    m_itemMap["onCanExtrudeChanged"]->setText(text);
}

void ExtruderInfoDialog::onNameChanged()
{
    if(!m_itemMap.contains("onNameChanged"))
        addTableItem("onNameChanged");

    QString text = QString("Name: %1").arg(
        QVariant(m_extruder->name()).toString()
        );

    m_itemMap["onNameChanged"]->setText(text);
}

void ExtruderInfoDialog::onControlPinChanged()
{
    if(!m_itemMap.contains("onControlPinChanged"))
        addTableItem("onControlPinChanged");

    QString text = QString("Control Pin: %1").arg(
        QVariant(m_extruder->control()).toString()
        );

    m_itemMap["onControlPinChanged"]->setText(text);
}

void ExtruderInfoDialog::onDirPinChanged()
{
    if(!m_itemMap.contains("onDirPinChanged"))
        addTableItem("onDirPinChanged");

    QString text = QString("Direction Pin: %1").arg(
        QVariant(m_extruder->dirPin()).toString()
        );

    m_itemMap["onDirPinChanged"]->setText(text);
}

void ExtruderInfoDialog::onEnablePinChanged()
{
    if(!m_itemMap.contains("onEnablePinChanged"))
        addTableItem("onEnablePinChanged");

    QString text = QString("Enable Pin: %1").arg(
        QVariant(m_extruder->enablePin()).toString()
        );

    m_itemMap["onEnablePinChanged"]->setText(text);
}

void ExtruderInfoDialog::onHeaterPinChanged()
{
    if(!m_itemMap.contains("onHeaterPinChanged"))
        addTableItem("onHeaterPinChanged");

    QString text = QString("Heater Pin: %1").arg(
        QVariant(m_extruder->heaterPin()).toString()
        );

    m_itemMap["onHeaterPinChanged"]->setText(text);
}

void ExtruderInfoDialog::onSensorPinChanged()
{
    if(!m_itemMap.contains("onSensorPinChanged"))
        addTableItem("onSensorPinChanged");

    QString text = QString("Sensor Pin: %1").arg(
        QVariant(m_extruder->sensorPin()).toString()
        );

    m_itemMap["onSensorPinChanged"]->setText(text);
}

void ExtruderInfoDialog::onSensorTypeChanged()
{
    if(!m_itemMap.contains("onSensorTypeChanged"))
        addTableItem("onSensorTypeChanged");

    QString text = QString("Sensor Type: %1").arg(
        QVariant(m_extruder->sensorType()).toString()
        );

    m_itemMap["onSensorTypeChanged"]->setText(text);
}

void ExtruderInfoDialog::onStepPinChanged()
{
    if(!m_itemMap.contains("onStepPinChanged"))
        addTableItem("onStepPinChanged");

    QString text = QString("Step Pin: %1").arg(
        QVariant(m_extruder->stepPin()).toString()
        );

    m_itemMap["onStepPinChanged"]->setText(text);
}

void ExtruderInfoDialog::onOffsetChanged()
{
    if(!m_itemMap.contains("onOffsetChanged"))
        addTableItem("onOffsetChanged");

    QString text = QString("Offset: X(%1) Y(%2) Z(%3)").arg(
        QVariant(m_extruder->offset().x()).toString(),
        QVariant(m_extruder->offset().y()).toString(),
        QVariant(m_extruder->offset().z()).toString()
        );

    m_itemMap["onOffsetChanged"]->setText(text);
}

void ExtruderInfoDialog::onPressureAdvanceSmoothTimeChanged()
{
    if(!m_itemMap.contains("onPressureAdvanceSmoothTimeChanged"))
        addTableItem("onPressureAdvanceSmoothTimeChanged");

    QString text = QString("Pressure Advance Smooth Time: %1").arg(
        QVariant(m_extruder->pressureAdvanceSmoothTime()).toString()
        );

    m_itemMap["onPressureAdvanceSmoothTimeChanged"]->setText(text);
}

void ExtruderInfoDialog::addTableItem(const QString &name)
{
    if(!m_itemMap.contains(name))
    {
        int row = m_infoTable->rowCount();

        m_itemMap[name] = new QTableWidgetItem();
        m_infoTable->insertRow(row);
        m_infoTable->setRowHeight(row, 32);
        m_infoTable->setItem(row, 0, m_itemMap[name]);
    }
}

void ExtruderInfoDialog::reset()
{
    onGearRatioChanged();
    onFullStepsPerRoatationChanged();
    onCurrentTempChanged();
    onTargetTempChanged();
    onSmoothTimeChanged();
    onPressureAdvanceChanged();
    onExtrusionFactorChanged();
    onFilamentDiameterChanged();
    onNozzleDiameterChanged();
    onPowerChanged();
    onInlineResistorChanged();
    onPullupResistorChanged();
    onPwmCycleChanged();
    onRotationDistanceChanged();
    onInstantCornerVelocityChanged();
    onPidKDChanged();
    onPidKIChanged();
    onPidKPChanged();
    onMaxExtrudeCrossSectionChanged();
    onMaxExtrudeOnlyAccelerationChanged();
    onMaxExtrudeOnlyDistanceChanged();
    onMaxExtrudeOnlyVelocityChanged();
    onMaxTempChanged();
    onMaxPowerChanged();
    onMinExtrudeTempChanged();
    onMinTempChanged();
    onCanExtrudeChanged();
    onNameChanged();
    onControlPinChanged();
    onDirPinChanged();
    onEnablePinChanged();
    onHeaterPinChanged();
    onSensorPinChanged();
    onSensorTypeChanged();
    onStepPinChanged();
    onOffsetChanged();
    onMicrostepsChanged();
    onPressureAdvanceSmoothTimeChanged();

    m_infoTable->sortItems(0);
}

void ExtruderInfoDialog::setupUi()
{
    setWindowTitle(QString("Extruder '%1' Information").arg(m_extruder->name()));

    m_centralLayout = new QGridLayout(this);
    m_centralLayout->setContentsMargins(0,0,0,0);
    setLayout(m_centralLayout);

    m_infoTable = new QTableWidget(m_centralWidget);
    m_infoTable->setColumnCount(1);
    m_centralLayout->addWidget(m_infoTable);

    m_infoTable->setColumnWidth(0, m_infoTable->viewport()->width());
}

void ExtruderInfoDialog::resizeEvent(QResizeEvent *event)
{
    Dialog::resizeEvent(event);
    m_infoTable->setColumnWidth(0, event->size().width());
}
