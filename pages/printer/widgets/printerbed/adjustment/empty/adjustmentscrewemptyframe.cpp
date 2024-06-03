#include "adjustmentscrewemptyframe.h"
#include "ui_adjustmentscrewemptyframe.h"

#include "../../../../../../system/settings.h"

AdjustmentScrewEmptyFrame::AdjustmentScrewEmptyFrame(Q3DPrintBed *bed, QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::AdjustmentScrewEmptyFrame)
{
    ui->setupUi(this);

    QPixmap pixmap = Settings::getThemeIcon("no-data-icon").pixmap(ui->iconLabel->size());
    ui->iconLabel->setPixmap(pixmap);

    ui->homeButton->setIcon(Settings::getThemeIcon(QString("home-icon")));

    _printerBed = bed;
    connect(_printerBed, SIGNAL(updated(Q3DPrintBed*)), this, SLOT(on_printerBed_updated(Q3DPrintBed*)));
    connect(_printerBed->printer()->toolhead(), SIGNAL(updated()), this, SLOT(on_toolhead_updated()));
}

AdjustmentScrewEmptyFrame::~AdjustmentScrewEmptyFrame()
{

    delete ui;
}

void AdjustmentScrewEmptyFrame::setStyleSheet(QString &styleSheet)
{
    QFrame::setStyleSheet(styleSheet);

    QPixmap pixmap = Settings::getThemeIcon("empty-list-icon").pixmap(ui->iconLabel->size());
    ui->iconLabel->setPixmap(pixmap);
}

void AdjustmentScrewEmptyFrame::setCalibrationEnabled(bool enabled)
{
    ui->calibrateButton->setEnabled(enabled);
}

void AdjustmentScrewEmptyFrame::on_calibrateButton_clicked()
{
    ui->calibrateButton->setEnabled(false);
    _printerBed->calibrateAdjustmentScrews();
}

void AdjustmentScrewEmptyFrame::on_printerBed_updated(Q3DPrintBed *bed)
{
    Q_UNUSED(bed);
}

void AdjustmentScrewEmptyFrame::on_toolhead_updated()
{
    if(_printerBed->printer()->toolhead()->isHomed())
    {
        ui->calibrateButton->setEnabled(true);
        ui->homeButton->setEnabled(false);
    }
    else
    {
        ui->calibrateButton->setEnabled(false);
        ui->homeButton->setEnabled(true);
    }
}


void AdjustmentScrewEmptyFrame::on_homeButton_clicked()
{
    _printerBed->printer()->toolhead()->homeAll();
}

