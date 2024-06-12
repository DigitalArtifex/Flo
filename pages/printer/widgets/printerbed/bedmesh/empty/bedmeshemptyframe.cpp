#include "bedmeshemptyframe.h"
#include "ui_bedmeshemptyframe.h"

#include "../../../../../../system/settings.h"

BedMeshEmptyFrame::BedMeshEmptyFrame(Q3DPrintBed *bed, QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::BedMeshEmptyFrame)
{
    ui->setupUi(this);
    ui->homeButton->setIcon(Settings::getThemeIcon(QString("home-icon")));

    QPixmap pixmap = Settings::getThemeIcon("no-data-icon").pixmap(ui->iconLabel->size());
    ui->iconLabel->setPixmap(pixmap);

    _printerBed = bed;
    connect(_printerBed->printer()->toolhead(), SIGNAL(updated()), this, SLOT(on_toolhead_updated()));
    connect(_printerBed->printer()->toolhead(), SIGNAL(homing()), this, SLOT(on_toolhead_homing()));
    connect(_printerBed->printer()->toolhead(), SIGNAL(homed()), this, SLOT(on_toolhead_homed()));
}

BedMeshEmptyFrame::~BedMeshEmptyFrame()
{
    delete ui;
}

void BedMeshEmptyFrame::on_toolhead_homing()
{
    ui->label->setText("Homing Toolhead");
}

void BedMeshEmptyFrame::on_toolhead_homed()
{
    ui->label->setText("No Data Found");
}

void BedMeshEmptyFrame::on_toolhead_updated()
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

void BedMeshEmptyFrame::on_homeButton_clicked()
{
    _printerBed->printer()->toolhead()->homeAll();
}


void BedMeshEmptyFrame::on_calibrateButton_clicked()
{
    _printerBed->calibrateBedMesh();
}

