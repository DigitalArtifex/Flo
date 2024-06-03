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

    _printBed = bed;
    connect(_printBed,SIGNAL(updated(Q3DPrintBed*)), this, SLOT(on_printBed_updated(Q3DPrintBed*)));
}

BedMeshEmptyFrame::~BedMeshEmptyFrame()
{
    delete ui;
}

void BedMeshEmptyFrame::on_printBed_updated(Q3DPrintBed *bed)
{
    Q_UNUSED(bed);

    if(_printBed->printer()->toolhead()->isHomed())
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
    _printBed->printer()->toolhead()->homeAll();
}

