#include "printerbedinfodialog.h"

PrinterBedInfoDialog::PrinterBedInfoDialog(QKlipperPrintBed *bed, QWidget *parent) :
    Dialog(parent)
{
    m_printBed = bed;

    setupUi();

    connect(m_printBed, SIGNAL(currentTempChanged()), this, SLOT(onCurrentTempChanged()));
    connect(m_printBed, SIGNAL(hasBedMeshResultChanged()), this, SLOT(onHasBedMeshResultChanged()));
    connect(m_printBed, SIGNAL(hasAdjustmentScrewResultChanged()), this, SLOT(onHasAdjustmentScrewResultChanged()));
    connect(m_printBed, SIGNAL(heaterPinChanged()), this, SLOT(onHeaterPinChanged()));
    connect(m_printBed, SIGNAL(inlineResistorChanged()), this, SLOT(onInlineResistorChanged()));
    connect(m_printBed, SIGNAL(maxPowerChanged()), this, SLOT(onMaxPowerChanged()));
    connect(m_printBed, SIGNAL(maxTempChanged()), this, SLOT(onMaxTempChanged()));
    connect(m_printBed, SIGNAL(minTempChanged()), this, SLOT(onMinTempChanged()));
    connect(m_printBed, SIGNAL(pidKDChanged()), this, SLOT(onPidKDChanged()));
    connect(m_printBed, SIGNAL(pidKIChanged()), this, SLOT(onPidKIChanged()));
    connect(m_printBed, SIGNAL(pidKPChanged()), this, SLOT(onPidKPChanged()));
    connect(m_printBed, SIGNAL(powerChanged()), this, SLOT(onPowerChanged()));
    connect(m_printBed, SIGNAL(pullupResistorChanged()), this, SLOT(onPullupResistorChanged()));
    connect(m_printBed, SIGNAL(pwmCycleTimeChanged()), this, SLOT(onPwmCycleTimeChanged()));
    connect(m_printBed, SIGNAL(sensorPinChanged()), this, SLOT(onSensorPinChanged()));
    connect(m_printBed, SIGNAL(sensorTypeChanged()), this, SLOT(onSensorTypeChanged()));
    connect(m_printBed, SIGNAL(smoothTimeChanged()), this, SLOT(onSmoothTimeChanged()));
    connect(m_printBed, SIGNAL(targetTempChanged()), this, SLOT(onTargetTempChanged()));
    connect(m_printBed, SIGNAL(tiltAdjustErrorChanged()), this, SLOT(onTiltAdjustErrorChanged()));
}

PrinterBedInfoDialog::~PrinterBedInfoDialog()
{

}

void PrinterBedInfoDialog::setupUi()
{
    setWindowTitle("Printer Bed Information");

    //m_centralWidget = new QWidget(this);
    m_centralLayout = new QGridLayout(this);
    m_centralLayout->setContentsMargins(0,0,0,0);
    setLayout(m_centralLayout);

    m_infoTable = new QTableWidget(m_centralWidget);
    m_infoTable->setColumnCount(1);
    m_centralLayout->addWidget(m_infoTable);

    //setFixedSize(640,320);

    m_infoTable->setColumnWidth(0, m_infoTable->viewport()->width());

    int row = 0;

    //Current temp
    QString currentTempText =
        QString("Current Temperature: %1°C").arg(
            QString::number(m_printBed->currentTemp())
        );

    QTableWidgetItem *currentTempItem = new QTableWidgetItem(currentTempText);
    currentTempItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    m_infoTable->insertRow(row);
    m_infoTable->setRowHeight(row, 32);
    m_infoTable->setItem(row, 0, currentTempItem);
    row++;

    m_itemMap.insert("currentTempItem", currentTempItem);

    //bed mesh result
    QString hasBedMeshResultText =
        QString("Has bed mesh result: %1").arg(
            QVariant(m_printBed->hasBedMeshResult()).toString()
            );

    QTableWidgetItem *hasBedMeshResultItem = new QTableWidgetItem(hasBedMeshResultText);
    hasBedMeshResultItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    m_infoTable->insertRow(row);
    m_infoTable->setRowHeight(row, 32);
    m_infoTable->setItem(row, 0, hasBedMeshResultItem);
    row++;

    m_itemMap.insert("hasBedMeshResultItem", hasBedMeshResultItem);

    //adjustment screw result
    QString hasAdjustmentScrewResultText =
        QString("Has adjustment screw result: %1").arg(
            QVariant(m_printBed->hasAdjustmentScrewResult()).toString()
            );

    QTableWidgetItem *hasAdjustmentScrewResultItem = new QTableWidgetItem(hasAdjustmentScrewResultText);
    hasAdjustmentScrewResultItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    m_infoTable->insertRow(row);
    m_infoTable->setRowHeight(row, 32);
    m_infoTable->setItem(row, 0, hasAdjustmentScrewResultItem);
    row++;

    m_itemMap.insert("hasAdjustmentScrewResultItem", hasAdjustmentScrewResultItem);

    //heater pin
    QString heaterPinText =
        QString("Heater Pin: %1").arg(
            QVariant(m_printBed->heaterPin()).toString()
            );

    QTableWidgetItem *heaterPinItem = new QTableWidgetItem(heaterPinText);
    heaterPinItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    m_infoTable->insertRow(row);
    m_infoTable->setRowHeight(row, 32);
    m_infoTable->setItem(row, 0, heaterPinItem);
    row++;

    m_itemMap.insert("heaterPinItem", heaterPinItem);

    //inlineResistor pin
    QString inlineResistorText =
        QString("Inline Resistor: %1").arg(
            QVariant(m_printBed->inlineResistor()).toString()
            );

    QTableWidgetItem *inlineResistorItem = new QTableWidgetItem(inlineResistorText);
    inlineResistorItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    m_infoTable->insertRow(row);
    m_infoTable->setRowHeight(row, 32);
    m_infoTable->setItem(row, 0, inlineResistorItem);
    row++;

    m_itemMap.insert("inlineResistorItem", inlineResistorItem);

    //maxPower value
    QString maxPowerText =
        QString("Max Power: %1").arg(
            QVariant(m_printBed->maxPower()).toString()
            );

    QTableWidgetItem *maxPowerItem = new QTableWidgetItem(maxPowerText);
    maxPowerItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    m_infoTable->insertRow(row);
    m_infoTable->setRowHeight(row, 32);
    m_infoTable->setItem(row, 0, maxPowerItem);
    row++;

    m_itemMap.insert("maxPowerItem", maxPowerItem);

    //maxTemp value
    QString maxTempText =
        QString("Max Temperature: %1°C").arg(
            QVariant(m_printBed->maxTemp()).toString()
            );

    QTableWidgetItem *maxTempItem = new QTableWidgetItem(maxTempText);
    maxTempItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    m_infoTable->insertRow(row);
    m_infoTable->setRowHeight(row, 32);
    m_infoTable->setItem(row, 0, maxTempItem);
    row++;

    m_itemMap.insert("maxTempItem", maxTempItem);

    //minTemp value
    QString minTempText =
        QString("Min Temperature: %1°C").arg(
            QVariant(m_printBed->minTemp()).toString()
            );

    QTableWidgetItem *minTempItem = new QTableWidgetItem(minTempText);
    minTempItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    m_infoTable->insertRow(row);
    m_infoTable->setRowHeight(row, 32);
    m_infoTable->setItem(row, 0, minTempItem);
    row++;

    m_itemMap.insert("minTempItem", minTempItem);

    //pidKD value
    QString pidKDText =
        QString("PID KD: %1").arg(
            QVariant(m_printBed->pidKD()).toString()
            );

    QTableWidgetItem *pidKDItem = new QTableWidgetItem(pidKDText);
    pidKDItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    m_infoTable->insertRow(row);
    m_infoTable->setRowHeight(row, 32);
    m_infoTable->setItem(row, 0, pidKDItem);
    row++;

    m_itemMap.insert("pidKDItem", pidKDItem);

    //pidKI value
    QString pidKIText =
        QString("PID KI: %1").arg(
            QVariant(m_printBed->pidKI()).toString()
            );

    QTableWidgetItem *pidKIItem = new QTableWidgetItem(pidKIText);
    pidKIItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    m_infoTable->insertRow(row);
    m_infoTable->setRowHeight(row, 32);
    m_infoTable->setItem(row, 0, pidKIItem);
    row++;

    m_itemMap.insert("pidKIItem", pidKIItem);

    //pidKP value
    QString pidKPText =
        QString("PID KP: %1").arg(
            QVariant(m_printBed->pidKP()).toString()
            );

    QTableWidgetItem *pidKPItem = new QTableWidgetItem(pidKPText);
    pidKPItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    m_infoTable->insertRow(row);
    m_infoTable->setRowHeight(row, 32);
    m_infoTable->setItem(row, 0, pidKPItem);
    row++;

    m_itemMap.insert("pidKPItem", pidKPItem);

    //power value
    QString powerText =
        QString("Power: %1").arg(
            QVariant(m_printBed->power()).toString()
            );

    QTableWidgetItem *powerItem = new QTableWidgetItem(powerText);
    powerItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    m_infoTable->insertRow(row);
    m_infoTable->setRowHeight(row, 32);
    m_infoTable->setItem(row, 0, powerItem);
    row++;

    m_itemMap.insert("powerItem", powerItem);

    //pullupResistor value
    QString pullupResistorText =
        QString("Pullup Resistor: %1").arg(
            QVariant(m_printBed->pullupResistor()).toString()
            );

    QTableWidgetItem *pullupResistorItem = new QTableWidgetItem(pullupResistorText);
    pullupResistorItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    m_infoTable->insertRow(row);
    m_infoTable->setRowHeight(row, 32);
    m_infoTable->setItem(row, 0, pullupResistorItem);
    row++;

    m_itemMap.insert("pullupResistorItem", pullupResistorItem);

    //pwmCycleTime value
    QString pwmCycleTimeText =
        QString("PWM Cycle Time: %1").arg(
            QVariant(m_printBed->pwmCycleTime()).toString()
            );

    QTableWidgetItem *pwmCycleTimeItem = new QTableWidgetItem(pwmCycleTimeText);
    pwmCycleTimeItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    m_infoTable->insertRow(row);
    m_infoTable->setRowHeight(row, 32);
    m_infoTable->setItem(row, 0, pwmCycleTimeItem);
    row++;

    m_itemMap.insert("pwmCycleTimeItem", pwmCycleTimeItem);

    //sensorPin value
    QString sensorPinText =
        QString("Sensor Pin: %1").arg(
            QVariant(m_printBed->sensorPin()).toString()
            );

    QTableWidgetItem *sensorPinItem = new QTableWidgetItem(sensorPinText);
    sensorPinItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    m_infoTable->insertRow(row);
    m_infoTable->setRowHeight(row, 32);
    m_infoTable->setItem(row, 0, sensorPinItem);
    row++;

    m_itemMap.insert("sensorPinItem", sensorPinItem);

    //sensorType value
    QString sensorTypeText =
        QString("Sensor Type: %1").arg(
            QVariant(m_printBed->sensorType()).toString()
            );

    QTableWidgetItem *sensorTypeItem = new QTableWidgetItem(sensorTypeText);
    sensorTypeItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    m_infoTable->insertRow(row);
    m_infoTable->setRowHeight(row, 32);
    m_infoTable->setItem(row, 0, sensorTypeItem);
    row++;

    m_itemMap.insert("sensorTypeItem", sensorTypeItem);

    //smoothTime value
    QString smoothTimeText =
        QString("Smooth Time: %1").arg(
            QVariant(m_printBed->smoothTime()).toString()
            );

    QTableWidgetItem *smoothTimeItem = new QTableWidgetItem(smoothTimeText);
    smoothTimeItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    m_infoTable->insertRow(row);
    m_infoTable->setRowHeight(row, 32);
    m_infoTable->setItem(row, 0, smoothTimeItem);
    row++;

    m_itemMap.insert("smoothTimeItem", smoothTimeItem);

    //targetTemp value
    QString targetTempText =
        QString("Target Temp: %1°C").arg(
            QVariant(m_printBed->targetTemp()).toString()
            );

    QTableWidgetItem *targetTempItem = new QTableWidgetItem(targetTempText);
    targetTempItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    m_infoTable->insertRow(row);
    m_infoTable->setRowHeight(row, 32);
    m_infoTable->setItem(row, 0, targetTempItem);
    row++;

    m_itemMap.insert("targetTempItem", targetTempItem);

    //tiltAdjustError value
    QString tiltAdjustErrorText =
        QString("Tilt Adjust Error: %1").arg(
            QVariant(m_printBed->tiltAdjustError()).toString()
            );

    QTableWidgetItem *tiltAdjustErrorItem = new QTableWidgetItem(tiltAdjustErrorText);
    tiltAdjustErrorItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    m_infoTable->insertRow(row);
    m_infoTable->setRowHeight(row, 32);
    m_infoTable->setItem(row, 0, tiltAdjustErrorItem);
    row++;

    m_itemMap.insert("tiltAdjustErrorItem", tiltAdjustErrorItem);
}

void PrinterBedInfoDialog::onCurrentTempChanged()
{
    //Current temp
    QString currentTempText =
        QString("Current Temperature: %1°C").arg(
            QString::number(m_printBed->currentTemp())
            );

    m_itemMap["currentTempItem"]->setText(currentTempText);
}

void PrinterBedInfoDialog::onHasBedMeshResultChanged()
{
    //bed mesh result
    QString hasBedMeshResultText =
        QString("Has bed mesh result: %1").arg(
            QVariant(m_printBed->hasBedMeshResult()).toString()
            );

    m_itemMap["hasBedMeshResultItem"]->setText(hasBedMeshResultText);
}

void PrinterBedInfoDialog::onHasAdjustmentScrewResultChanged()
{
    //adjustment screw result
    QString hasAdjustmentScrewResultText =
        QString("Has adjustment screw result: %1").arg(
            QVariant(m_printBed->hasAdjustmentScrewResult()).toString()
            );

    m_itemMap["hasAdjustmentScrewResultItem"]->setText(hasAdjustmentScrewResultText);
}

void PrinterBedInfoDialog::onHeaterPinChanged()
{
    //heater pin
    QString heaterPinText =
        QString("Heater Pin: %1").arg(
            QVariant(m_printBed->heaterPin()).toString()
            );

    m_itemMap["heaterPinItem"]->setText(heaterPinText);
}

void PrinterBedInfoDialog::onInlineResistorChanged()
{
    //inlineResistor pin
    QString inlineResistorText =
        QString("Inline Resistor: %1").arg(
            QVariant(m_printBed->inlineResistor()).toString()
            );

    m_itemMap["heaterPinItem"]->setText(inlineResistorText);
}

void PrinterBedInfoDialog::onMaxPowerChanged()
{
    //maxPower value
    QString maxPowerText =
        QString("Max Power: %1").arg(
            QVariant(m_printBed->maxPower()).toString()
            );

    m_itemMap["maxPowerItem"]->setText(maxPowerText);
}

void PrinterBedInfoDialog::onMaxTempChanged()
{
    //maxTemp value
    QString maxTempText =
        QString("Max Temperature: %1°C").arg(
            QVariant(m_printBed->maxTemp()).toString()
            );

    m_itemMap["maxTempItem"]->setText(maxTempText);
}

void PrinterBedInfoDialog::onMinTempChanged()
{
    //minTemp value
    QString minTempText =
        QString("Min Temperature: %1°C").arg(
            QVariant(m_printBed->minTemp()).toString()
            );

    m_itemMap["minTempItem"]->setText(minTempText);
}

void PrinterBedInfoDialog::onPidKDChanged()
{
    //pidKD value
    QString pidKDText =
        QString("PID KD: %1").arg(
            QVariant(m_printBed->pidKD()).toString()
            );

    m_itemMap["pidKDItem"]->setText(pidKDText);
}

void PrinterBedInfoDialog::onPidKIChanged()
{
    //pidKD value
    QString pidKIText =
        QString("PID KI: %1").arg(
            QVariant(m_printBed->pidKI()).toString()
            );

    m_itemMap["pidKIItem"]->setText(pidKIText);
}

void PrinterBedInfoDialog::onPidKPChanged()
{
    //pidKP value
    QString pidKPText =
        QString("PID KP: %1").arg(
            QVariant(m_printBed->pidKP()).toString()
            );

    m_itemMap["pidKPItem"]->setText(pidKPText);
}

void PrinterBedInfoDialog::onPowerChanged()
{
    //power value
    QString powerText =
        QString("Power: %1").arg(
            QVariant(m_printBed->power()).toString()
            );

    m_itemMap["powerItem"]->setText(powerText);
}

void PrinterBedInfoDialog::onPullupResistorChanged()
{
    //pullupResistor value
    QString pullupResistorText =
        QString("Pullup Resistor: %1").arg(
            QVariant(m_printBed->pullupResistor()).toString()
            );

    m_itemMap["pullupResistorItem"]->setText(pullupResistorText);
}

void PrinterBedInfoDialog::onPwmCycleTimeChanged()
{
    //pwmCycleTime value
    QString pwmCycleTimeText =
        QString("PWM Cycle Time: %1").arg(
            QVariant(m_printBed->pwmCycleTime()).toString()
            );

    m_itemMap["pwmCycleTimeItem"]->setText(pwmCycleTimeText);
}

void PrinterBedInfoDialog::onSensorPinChanged()
{
    //sensorPin value
    QString sensorPinText =
        QString("Sensor Pin: %1").arg(
            QVariant(m_printBed->sensorPin()).toString()
            );

    m_itemMap["sensorPinItem"]->setText(sensorPinText);
}

void PrinterBedInfoDialog::onSensorTypeChanged()
{
    //sensorType value
    QString sensorTypeText =
        QString("Sensor Type: %1").arg(
            QVariant(m_printBed->sensorType()).toString()
            );

    m_itemMap["sensorTypeItem"]->setText(sensorTypeText);
}

void PrinterBedInfoDialog::onSmoothTimeChanged()
{
    //smoothTime value
    QString smoothTimeText =
        QString("Smooth Time: %1").arg(
            QVariant(m_printBed->smoothTime()).toString()
            );

    m_itemMap["smoothTimeItem"]->setText(smoothTimeText);
}

void PrinterBedInfoDialog::onTargetTempChanged()
{
    //targetTemp value
    QString targetTempText =
        QString("Target Temp: %1°C").arg(
            QVariant(m_printBed->targetTemp()).toString()
            );

    m_itemMap["targetTempItem"]->setText(targetTempText);
}

void PrinterBedInfoDialog::onTiltAdjustErrorChanged()
{
    //tiltAdjustError value
    QString tiltAdjustErrorText =
        QString("Tilt Adjust Error: %1").arg(
            QVariant(m_printBed->tiltAdjustError()).toString()
            );

    m_itemMap["tiltAdjustErrorItem"]->setText(tiltAdjustErrorText);
}

void PrinterBedInfoDialog::resizeEvent(QResizeEvent *event)
{
    Dialog::resizeEvent(event);
    m_infoTable->setColumnWidth(0, event->size().width());
}
