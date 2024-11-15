#include "adjustmentscrewemptyframe.h"
#include "ui_adjustmentscrewemptyframe.h"

#include "../../../../../../system/settings.h"

AdjustmentScrewEmptyFrame::AdjustmentScrewEmptyFrame(QKlipperPrintBed *bed, QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::AdjustmentScrewEmptyFrame)
{
    ui->setupUi(this);

    QPixmap pixmap = Settings::getThemeIcon("no-data-icon").pixmap(ui->iconLabel->size());
    ui->iconLabel->setPixmap(pixmap);

    ui->homeButton->setIcon(Settings::getThemeIcon(QString("home-icon")));

    m_printerBed = bed;
    connect(m_printerBed->printer()->toolhead(), SIGNAL(homing()), this, SLOT(onToolheadHoming()));
    connect(m_printerBed->printer()->toolhead(), SIGNAL(homingFinished()), this, SLOT(onToolheadHomingFinished()));
    connect(m_printerBed->printer()->toolhead(), SIGNAL(isHomedChanged()), this, SLOT(onToolheadHomingFinished()));
}

AdjustmentScrewEmptyFrame::~AdjustmentScrewEmptyFrame()
{
    delete ui;
}

void AdjustmentScrewEmptyFrame::setStyleSheet(const QString &styleSheet)
{
    QPixmap pixmap = Settings::getThemeIcon("no-data-icon").pixmap(ui->iconLabel->size());
    ui->iconLabel->setPixmap(pixmap);

    ui->homeButton->setIcon(Settings::getThemeIcon(QString("home-icon")));

    QFrame::setStyleSheet(styleSheet);
}

void AdjustmentScrewEmptyFrame::setCalibrationEnabled(bool enabled)
{
    ui->calibrateButton->setEnabled(enabled);
}

void AdjustmentScrewEmptyFrame::on_calibrateButton_clicked()
{
    ui->calibrateButton->setEnabled(false);
    ui->homeButton->setEnabled(false);
    m_printerBed->calibrateAdjustmentScrews();
}

void AdjustmentScrewEmptyFrame::onToolheadHoming()
{
    ui->label->setText("Homing Toolhead");
    ui->homeButton->setEnabled(false);
}

void AdjustmentScrewEmptyFrame::onToolheadHomingFinished()
{
    ui->label->setText("No Data Found");
    ui->calibrateButton->setEnabled(m_printerBed->printer()->toolhead()->isHomed());
    ui->homeButton->setEnabled(!m_printerBed->printer()->toolhead()->isHomed());
}

void AdjustmentScrewEmptyFrame::on_homeButton_clicked()
{
    emit calibrating();
    m_printerBed->printer()->toolhead()->home();
}

