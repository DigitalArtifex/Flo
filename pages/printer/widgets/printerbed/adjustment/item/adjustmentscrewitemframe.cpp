#include "adjustmentscrewitemframe.h"
#include "ui_adjustmentscrewitemframe.h"

#include "../../../../../../system/settings.h"

AdjustmentScrewItemFrame::AdjustmentScrewItemFrame(QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::AdjustmentScrewItemFrame)
{
    ui->setupUi(this);
}

AdjustmentScrewItemFrame::~AdjustmentScrewItemFrame()
{
    setParent(nullptr);
    //_adjustmentScrew = nullptr;
    delete ui;
}

Q3DPrintBed::AdjustmentScrew *AdjustmentScrewItemFrame::adjustmentScrew() const
{
    return nullptr;//_adjustmentScrew;
}

void AdjustmentScrewItemFrame::setAdjustmentScrew(Q3DPrintBed::AdjustmentScrew *adjustmentScrew)
{
    //_adjustmentScrew = adjustmentScrew;

    ui->adjustmentLabel->setText(adjustmentScrew->adjustment.amount);
    ui->screwNameLabel->setText(adjustmentScrew->name);

    QPixmap pixmap;

    switch(adjustmentScrew->adjustment.direction)
    {
    case Q3DPrintBed::AdjustmentScrew::Adjustment::Clockwise:
        pixmap = Settings::getThemeIcon(QString("clockwise-icon")).pixmap(ui->iconLabel->size());
        break;
    case Q3DPrintBed::AdjustmentScrew::Adjustment::CounterClockwise:
        pixmap = Settings::getThemeIcon(QString("counter-clockwise-icon")).pixmap(ui->iconLabel->size());
        break;
    }

    ui->iconLabel->setPixmap(pixmap);
}
