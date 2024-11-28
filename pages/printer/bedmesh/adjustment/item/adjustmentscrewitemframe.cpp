#include "adjustmentscrewitemframe.h"

#include "system/settings.h"

AdjustmentScrewItemFrame::AdjustmentScrewItemFrame(QWidget *parent)
    : QFrame(parent)
{
    setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "AdjustmentScrewItem"));

    m_iconLabel = new QLabel(this);
    m_screwNameLabel = new QLabel(this);
    m_adjustmentLabel = new QLabel(this);

    m_layout = new QHBoxLayout(this);
    m_layout->addWidget(m_iconLabel);
    m_layout->addWidget(m_adjustmentLabel);
    m_layout->addWidget(m_screwNameLabel);

    setLayout(m_layout);
}

AdjustmentScrewItemFrame::~AdjustmentScrewItemFrame()
{
}

QKlipperAdjustmentScrew *AdjustmentScrewItemFrame::adjustmentScrew() const
{
    return m_adjustmentScrew;
}

void AdjustmentScrewItemFrame::setAdjustmentScrew(QKlipperAdjustmentScrew *adjustmentScrew)
{
    m_adjustmentScrew = adjustmentScrew;

    m_screwNameLabel->setText(m_adjustmentScrew->name());
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
            pixmap = Settings::getThemeIcon(QString("clockwise-icon")).pixmap(m_iconLabel->size());
            break;
        case QKlipperAdjustmentScrew::Adjustment::CounterClockwise:
            pixmap = Settings::getThemeIcon(QString("counter-clockwise-icon")).pixmap(m_iconLabel->size());
            break;
    }

    m_iconLabel->setPixmap(pixmap);
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

    m_adjustmentLabel->setText(m_adjustmentScrew->adjustment().amount);
    setupIcons();
}
