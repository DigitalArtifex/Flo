#include "bedmeshemptyframe.h"
#include "ui_bedmeshemptyframe.h"

#include "system/settings.h"

BedMeshEmptyFrame::BedMeshEmptyFrame(QKlipperPrintBed *bed, QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::BedMeshEmptyFrame)
{
    ui->setupUi(this);

    m_printerBed = bed;
    connect(m_printerBed->printer()->toolhead(), SIGNAL(isHomingChanged()), this, SLOT(onToolheadHomingChanged()));
    connect(m_printerBed->printer()->toolhead(), SIGNAL(isHomedChanged()), this, SLOT(onToolheadHomingChanged()));

    setupIcons();
}

BedMeshEmptyFrame::~BedMeshEmptyFrame()
{
    delete ui;
}

void BedMeshEmptyFrame::setupIcons()
{
    QPixmap pixmap = Settings::getThemeIcon("no-data").pixmap(ui->iconLabel->size());
    ui->iconLabel->setPixmap(pixmap);
}

void BedMeshEmptyFrame::setStyleSheet(const QString &styleSheet)
{
    setupIcons();
    QFrame::setStyleSheet(styleSheet);
}

void BedMeshEmptyFrame::onToolheadHomingChanged()
{
    if(m_printerBed->printer()->toolhead()->isHoming())
        ui->label->setText("Homing Toolhead");
    else
        ui->label->setText("No Data Found");
}

void BedMeshEmptyFrame::on_homeButton_clicked()
{
    m_printerBed->printer()->toolhead()->home();
}

void BedMeshEmptyFrame::on_calibrateButton_clicked()
{
    m_printerBed->calibrateBedMesh();
}

