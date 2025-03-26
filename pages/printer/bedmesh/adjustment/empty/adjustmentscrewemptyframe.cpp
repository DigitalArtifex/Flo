#include "adjustmentscrewemptyframe.h"

#include "flo/settings.h"

AdjustmentScrewEmptyFrame::AdjustmentScrewEmptyFrame(QWidget *parent)
    : QFrame(parent)
{
    m_iconLabel = new QLabel(this);
    m_textLabel = new QLabel(this);

    m_textLabel->setText("No Data Found");
    m_textLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    m_layout = new QHBoxLayout(this);
    m_layout->addWidget(m_iconLabel);
    m_layout->addWidget(m_textLabel);

    setLayout(m_layout);

    QPixmap pixmap = Settings::getThemeIcon("no-data").pixmap(m_iconLabel->size());
    m_iconLabel->setPixmap(pixmap);
}

AdjustmentScrewEmptyFrame::~AdjustmentScrewEmptyFrame()
{
    if(m_layout)
        delete m_layout;
}

void AdjustmentScrewEmptyFrame::changeEvent(QEvent *event)
{
    if(event->type() == QEvent::StyleChange)
        setIcons();
}

void AdjustmentScrewEmptyFrame::setIcons()
{
    QPixmap pixmap = Settings::getThemeIcon("no-data").pixmap(m_iconLabel->size());
    m_iconLabel->setPixmap(pixmap);
}

