#include "printerbedwidget.h"
#include "ui_printerbedwidget.h"

PrinterBedWidget::PrinterBedWidget(Q3DPrintBed *printerBed, QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::PrinterBedWidget)
{
    ui->setupUi(this);

    setPrinterBed(printerBed);

    QGridLayout *layout = new QGridLayout(ui->adjustmentScrewBox);
    ui->adjustmentScrewBox->setLayout(layout);

    _bedTemperatureBar = new CircularProgressBar(this, CircularProgressBar::Temperature);
    _bedTemperatureBar->setMaximum(150);

    ui->bedLayout->addWidget(_bedTemperatureBar);
    setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "DashboardWidget" << "PrinterWidget"));
    ui->bedInfoWidget->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "DashboardSubWidget" << "PrinterSubWidget"));
    ui->adjustmentScrewBox->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "DashboardSubWidget" << "PrinterSubWidget"));
    ui->bedMeshGroupBox->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "DashboardSubWidget" << "PrinterSubWidget"));

    _bedMeshFrame = new BedMeshFrame(_printerBed, ui->bedMeshGroupBox);
    ui->bedMeshGroupBox->layout()->addWidget(_bedMeshFrame);

    _adjustmentScrewFrame = new AdjustmentScrewFrame(_printerBed, ui->adjustmentScrewBox);
    ui->adjustmentScrewBox->layout()->addWidget(_adjustmentScrewFrame);
}

PrinterBedWidget::~PrinterBedWidget()
{
    delete _bedTemperatureBar;
    delete ui;
}

void PrinterBedWidget::on_printerBed_update(Q3DPrintBed *printBed)
{
    _bedTemperatureBar->setProgress(printBed->currentTemp());

    ui->bedTargetTempLabel->setText(QString::number(printBed->targetTemp()) + QString("°C"));
    ui->bedPowerLabel->setText(QString::number(printBed->power()) + QString(""));
    ui->bedTemperatureLabel->setText(QString::number(printBed->currentTemp()) + QString("°C"));
}

void PrinterBedWidget::on_printerOnline(Printer *printer)
{
    Q_UNUSED(printer);
}

Q3DPrintBed *PrinterBedWidget::printerBed() const
{
    return _printerBed;
}

void PrinterBedWidget::setPrinterBed(Q3DPrintBed *printerBed)
{
    if(_printerBed)
    {
        disconnect(_printerBed, SIGNAL(updated(Q3DPrintBed*)), this, SLOT(on_printerBed_update(Q3DPrintBed*)));
        disconnect(_printerBed, SIGNAL(adjustmentScrewsUpdated(Q3DPrintBed*)), this, SLOT(on_printerBed_adjustmentScrewsUpdated(Q3DPrintBed*)));
    }

    _printerBed = printerBed;

    connect(_printerBed, SIGNAL(updated(Q3DPrintBed*)), this, SLOT(on_printerBed_update(Q3DPrintBed*)));
    connect(_printerBed, SIGNAL(adjustmentScrewsUpdated(Q3DPrintBed*)), this, SLOT(on_printerBed_adjustmentScrewsUpdated(Q3DPrintBed*)));

    connect(_printerBed->printer(), SIGNAL(printerOnline(Printer*)), this, SLOT(on_printerOnline(Printer*)));
}

void PrinterBedWidget::setPrintActionsEnabled(bool enabled)
{
}
