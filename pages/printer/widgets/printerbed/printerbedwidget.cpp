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

    m_bedTemperatureBar = new CircularProgressBar(this, CircularProgressBar::Temperature);
    m_bedTemperatureBar->setMaximum(150);

    ui->bedLayout->addWidget(m_bedTemperatureBar);
    setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "DashboardWidget" << "PrinterWidget"));
    ui->bedInfoWidget->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "DashboardSubWidget" << "PrinterSubWidget"));
    ui->adjustmentScrewFrame->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "DashboardSubWidget" << "PrinterSubWidget"));
    ui->bedMeshFrame->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "DashboardSubWidget" << "PrinterSubWidget"));
    ui->titleBar->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "WidgetTitleBar" << "PrinterSubWidget"));
    ui->bedMeshTitleBar->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "SubWidgetTitleBar" << "PrinterSubWidget"));
    ui->adjustmentFrameTitleBar->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "SubWidgetTitleBar" << "PrinterSubWidget"));

    ui->settingsTitleBar->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "SubWidgetTitleBar"));
    ui->settingsTitleBar->setProperty("page", QVariant::fromValue<QStringList>( QStringList() << "PrinterOverview"));
    ui->bedSettingsWidget->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "DashboardSubWidget" << "PrinterSubWidget"));

    m_bedMeshFrame = new BedMeshFrame(m_printerBed, ui->bedMeshContent);
    ui->bedMeshContent->layout()->addWidget(m_bedMeshFrame);

    m_adjustmentScrewFrame = new AdjustmentScrewFrame(m_printerBed, ui->adjustmentScrewFrame);
    ui->adjustmentScrewContent->layout()->addWidget(m_adjustmentScrewFrame);

    setIcons();
}

PrinterBedWidget::~PrinterBedWidget()
{
    delete m_bedTemperatureBar;
    delete m_adjustmentScrewFrame;
    delete m_bedMeshFrame;
    delete ui;
}

void PrinterBedWidget::on_printerBed_update(Q3DPrintBed *printBed)
{
    m_bedTemperatureBar->setProgress(printBed->currentTemp());

    ui->bedTargetTempLabel->setText(QString::number(printBed->targetTemp()) + QString("°"));
    ui->bedPowerLabel->setText(QString::number(printBed->power()) + QString(""));
    ui->bedTemperatureLabel->setText(QString::number(printBed->currentTemp()) + QString("°"));

    if(!m_targetTempEdited)
        ui->targetTempSpinBox->setValue(printBed->targetTemp());
}

void PrinterBedWidget::on_printerOnline(Printer *printer)
{
    Q_UNUSED(printer);
}

Q3DPrintBed *PrinterBedWidget::printerBed() const
{
    return m_printerBed;
}

void PrinterBedWidget::setPrinterBed(Q3DPrintBed *printerBed)
{
    if(m_printerBed)
    {
        disconnect(m_printerBed, SIGNAL(updated(Q3DPrintBed*)), this, SLOT(on_printerBed_update(Q3DPrintBed*)));
        disconnect(m_printerBed, SIGNAL(adjustmentScrewsUpdated(Q3DPrintBed*)), this, SLOT(on_printerBed_adjustmentScrewsUpdated(Q3DPrintBed*)));
    }

    m_printerBed = printerBed;

    connect(m_printerBed->printer(), SIGNAL(printerOnline(Printer*)), this, SLOT(on_printerOnline(Printer*)));
    connect(m_printerBed, SIGNAL(updated(Q3DPrintBed*)), this, SLOT(on_printerBed_update(Q3DPrintBed*)));
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

    pixmap = Settings::getThemeIcon("settings-icon").pixmap(18,18);
    ui->settingsFrameIcon->setPixmap(pixmap);

    pixmap = Settings::getThemeIcon("temperature-icon").pixmap(18,18);
    ui->targetTemperatureIconLabel->setPixmap(pixmap);
}

void PrinterBedWidget::on_applyButton_clicked()
{
    m_printerBed->setTargetTemp(ui->targetTempSpinBox->value());
    m_targetTempEdited = false;
}

void PrinterBedWidget::on_resetButton_clicked()
{
    ui->targetTempSpinBox->setValue(m_printerBed->targetTemp());
    m_targetTempEdited = false;
}


void PrinterBedWidget::on_targetTempSpinBox_valueChanged(double arg1)
{
    bool changed = (arg1 != m_printerBed->targetTemp());
    m_targetTempEdited = changed;
    ui->resetButton->setEnabled(changed);
    ui->applyButton->setEnabled(changed);
}

