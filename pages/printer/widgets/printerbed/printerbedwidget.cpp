#include "printerbedwidget.h"
#include "ui_printerbedwidget.h"

#include "../../../../system/settings.h"

PrinterBedWidget::PrinterBedWidget(Q3DPrintBed *printerBed, QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::PrinterBedWidget)
{
    ui->setupUi(this);

    setPrinterBed(printerBed);

    QGridLayout *layout = new QGridLayout(ui->adjustmentScrewFrame);
    ui->adjustmentScrewFrame->setLayout(layout);

    _bedTemperatureBar = new CircularProgressBar(this, CircularProgressBar::Temperature);
    _bedTemperatureBar->setMaximum(150);

    ui->bedLayout->addWidget(_bedTemperatureBar);
    setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "DashboardWidget" << "PrinterWidget"));
    ui->bedInfoWidget->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "DashboardSubWidget" << "PrinterSubWidget"));
    ui->adjustmentScrewFrame->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "DashboardSubWidget" << "PrinterSubWidget"));
    ui->bedMeshFrame->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "DashboardSubWidget" << "PrinterSubWidget"));
    ui->titleBar->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "WidgetTitleBar" << "PrinterSubWidget"));
    ui->bedMeshTitleBar->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "SubWidgetTitleBar" << "PrinterSubWidget"));
    ui->adjustmentFrameTitleBar->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "SubWidgetTitleBar" << "PrinterSubWidget"));

    _bedMeshFrame = new BedMeshFrame(_printerBed, ui->bedMeshContent);
    ui->bedMeshContent->layout()->addWidget(_bedMeshFrame);

    _adjustmentScrewFrame = new AdjustmentScrewFrame(_printerBed, ui->adjustmentScrewFrame);
    ui->adjustmentScrewContent->layout()->addWidget(_adjustmentScrewFrame);

    setIcons();
}

PrinterBedWidget::~PrinterBedWidget()
{
    delete _bedTemperatureBar;
    delete ui;
}

void PrinterBedWidget::on_printerBed_update(Q3DPrintBed *printBed)
{
    _bedTemperatureBar->setProgress(printBed->currentTemp());

    ui->bedTargetTempLabel->setText(QString::number(printBed->targetTemp()) + QString("°"));
    ui->bedPowerLabel->setText(QString::number(printBed->power()) + QString(""));
    ui->bedTemperatureLabel->setText(QString::number(printBed->currentTemp()) + QString("°"));
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

    connect(_printerBed->printer(), SIGNAL(printerOnline(Printer*)), this, SLOT(on_printerOnline(Printer*)));
    connect(_printerBed, SIGNAL(updated(Q3DPrintBed*)), this, SLOT(on_printerBed_update(Q3DPrintBed*)));
}

void PrinterBedWidget::setPrintActionsEnabled(bool enabled)
{
}

void PrinterBedWidget::setIcons()
{
    QPixmap pixmap = Settings::getThemeIcon(QString("bed-icon")).pixmap(28,28);
    ui->iconLabel->setPixmap(pixmap);

    pixmap = Settings::getThemeIcon(QString("bed-mesh-icon")).pixmap(18,18);
    ui->bedMeshIconLabel->setPixmap(pixmap);

    pixmap = Settings::getThemeIcon(QString("adjustment-screw-icon")).pixmap(18,18);
    ui->adjustmentScrewIcon->setPixmap(pixmap);
}
