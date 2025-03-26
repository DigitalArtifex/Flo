#include "adjustmentscrewitemframe.h"

#include "flo/settings.h"

AdjustmentScrewItemFrame::AdjustmentScrewItemFrame(QKlipperAdjustmentScrew *screw, QWidget *parent)
    : QFrame(parent)
{
    setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "SubWidget"));

    m_iconLabel = new QLabel(this);
    m_iconLabel->setFixedSize(32,32);
    m_screwNameLabel = new QLabel(this);
    m_adjustmentLabel = new QLabel(this);

    m_layout = new QHBoxLayout(this);
    m_layout->addWidget(m_iconLabel);
    m_layout->addWidget(m_adjustmentLabel);
    m_layout->addWidget(m_screwNameLabel);

    setLayout(m_layout);
    setAdjustmentScrew(screw);
    setupIcons();
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
            pixmap = Settings::getThemeIcon(QString("clockwise")).pixmap(m_iconLabel->size());
            break;
        case QKlipperAdjustmentScrew::Adjustment::CounterClockwise:
            pixmap = Settings::getThemeIcon(QString("counter-clockwise")).pixmap(m_iconLabel->size());
            break;
    }

    m_iconLabel->setPixmap(pixmap);
}

void AdjustmentScrewItemFrame::changeEvent(QEvent *event)
{
    if(event->type() == QEvent::StyleChange)
        setupIcons();

    QFrame::changeEvent(event);
}

void AdjustmentScrewItemFrame::onAdjustmentScrewAmountChanged()
{
    if(!m_adjustmentScrew)
        return;

    m_adjustmentLabel->setText(m_adjustmentScrew->adjustment().amount);
    setupIcons();
}
