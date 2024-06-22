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

    m_printerBed = bed;
    connect(m_printerBed->printer()->toolhead(), SIGNAL(updated()), this, SLOT(on_toolhead_updated()));
    connect(m_printerBed->printer()->toolhead(), SIGNAL(homing()), this, SLOT(on_toolhead_homing()));
    connect(m_printerBed->printer()->toolhead(), SIGNAL(homed()), this, SLOT(on_toolhead_homed()));
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
    m_printerBed->calibrateAdjustmentScrews();
}

void AdjustmentScrewEmptyFrame::on_toolhead_updated()
{
    if(m_printerBed->printer()->toolhead()->isHomed())
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

void AdjustmentScrewEmptyFrame::on_toolhead_homing()
{
    ui->label->setText("Homing Toolhead");
}

void AdjustmentScrewEmptyFrame::on_toolhead_homed()
{
    ui->label->setText("No Data Found");
}


void AdjustmentScrewEmptyFrame::on_homeButton_clicked()
{
    emit calibrating();

    m_printerBed->printer()->toolhead()->homeAll();
}

