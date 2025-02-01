#include "probedmeshemptyframe.h"
#include "ui_probedmeshemptyframe.h"

#include "flo/settings.h"

ProbedMeshEmptyFrame::ProbedMeshEmptyFrame(QKlipperPrintBed *bed, QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::ProbedMeshEmptyFrame)
{
    ui->setupUi(this);

    m_printerBed = bed;
    connect(m_printerBed->printer()->toolhead(), SIGNAL(isHomingChanged()), this, SLOT(onToolheadHomingChanged()));
    connect(m_printerBed->printer()->toolhead(), SIGNAL(isHomedChanged()), this, SLOT(onToolheadHomingChanged()));

    setupIcons();
}

ProbedMeshEmptyFrame::~ProbedMeshEmptyFrame()
{
    delete ui;
}

void ProbedMeshEmptyFrame::setupIcons()
{
    QPixmap pixmap = Settings::getThemeIcon("no-data").pixmap(ui->iconLabel->size());
    ui->iconLabel->setPixmap(pixmap);
}

void ProbedMeshEmptyFrame::setStyleSheet(const QString &styleSheet)
{
    setupIcons();
    QFrame::setStyleSheet(styleSheet);
}

void ProbedMeshEmptyFrame::onToolheadHomingChanged()
{
    if(m_printerBed->printer()->toolhead()->isHoming())
        ui->label->setText("Homing Toolhead");
    else
        ui->label->setText("No Data Found");
}

void ProbedMeshEmptyFrame::on_homeButton_clicked()
{
    m_printerBed->printer()->toolhead()->home();
}

void ProbedMeshEmptyFrame::on_calibrateButton_clicked()
{
    m_printerBed->calibrateBedMesh();
}

