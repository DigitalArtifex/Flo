#include "adjustmentscrewitemframe.h"
#include "ui_adjustmentscrewitemframe.h"

#include "../../../../../../system/settings.h"

AdjustmentScrewItemFrame::AdjustmentScrewItemFrame(QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::AdjustmentScrewItemFrame)
{
    ui->setupUi(this);

    setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "AdjustmentScrewItem"));
}

AdjustmentScrewItemFrame::~AdjustmentScrewItemFrame()
{
    delete ui;
}

QKlipperAdjustmentScrew *AdjustmentScrewItemFrame::adjustmentScrew() const
{
    return m_adjustmentScrew;
}

void AdjustmentScrewItemFrame::setAdjustmentScrew(QKlipperAdjustmentScrew *adjustmentScrew)
{
    m_adjustmentScrew = adjustmentScrew;

    ui->screwNameLabel->setText(m_adjustmentScrew->name());
    onAdjustmentScrewAmountChanged();

    QObject::connect(m_adjustmentScrew, SIGNAL(adjustmentChanged()), this, SLOT(onAdjustmentScrewAmountChanged()));
}

void AdjustmentScrewItemFrame::setupIcons()
{
    QPixmap pixmap;

    switch(m_adjustmentScrew->adjustment().direction)
    {
        case QKlipperAdjustmentScrew::Adjustment::NotSet:
        case QKlipperAdjustmentScrew::Adjustment::Clockwise:
            pixmap = Settings::getThemeIcon(QString("clockwise-icon")).pixmap(ui->iconLabel->size());
            break;
        case QKlipperAdjustmentScrew::Adjustment::CounterClockwise:
            pixmap = Settings::getThemeIcon(QString("counter-clockwise-icon")).pixmap(ui->iconLabel->size());
            break;
    }

    ui->iconLabel->setPixmap(pixmap);
}

void AdjustmentScrewItemFrame::setStyleSheet(const QString &styleSheet)
{
    setupIcons();

    QFrame::setStyleSheet(styleSheet);
}

void AdjustmentScrewItemFrame::onAdjustmentScrewAmountChanged()
{
    if(!m_adjustmentScrew)
        return;

    ui->adjustmentLabel->setText(m_adjustmentScrew->adjustment().amount);
    setupIcons();
}
