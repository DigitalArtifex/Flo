#include "adjustmentscrewemptyframe.h"

#include "flo/settings.h"

AdjustmentScrewEmptyFrame::AdjustmentScrewEmptyFrame(QKlipperPrintBed *bed, QWidget *parent)
    : QFrame(parent)
{
    m_iconLabel = new QLabel(this);
    m_textLabel = new QLabel(this);
    m_textLabel->setText("No Data Found");
    m_textLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    connect(m_calibrateButton, SIGNAL(clicked()), this, SLOT(on_calibrateButton_clicked()));

    m_layout = new QHBoxLayout(this);
    m_layout->addWidget(m_iconLabel);
    m_layout->addWidget(m_textLabel);

    setLayout(m_layout);

    QPixmap pixmap = Settings::getThemeIcon("no-data").pixmap(m_iconLabel->size());
    m_iconLabel->setPixmap(pixmap);

    m_printerBed = bed;

    QKlipperPrinter *printer = qobject_cast<QKlipperPrinter*>(m_printerBed->parent());

    if(printer)
    {
        connect(printer->toolhead(), SIGNAL(homing()), this, SLOT(onToolheadHoming()));
        connect(printer->toolhead(), SIGNAL(homingFinished()), this, SLOT(onToolheadHomingFinished()));
        connect(printer->toolhead(), SIGNAL(isHomedChanged()), this, SLOT(onToolheadHomingFinished()));
    }
}

AdjustmentScrewEmptyFrame::~AdjustmentScrewEmptyFrame()
{
}

void AdjustmentScrewEmptyFrame::setStyleSheet(const QString &styleSheet)
{
    QPixmap pixmap = Settings::getThemeIcon("no-data").pixmap(m_iconLabel->size());
    m_iconLabel->setPixmap(pixmap);

    QFrame::setStyleSheet(styleSheet);
}

void AdjustmentScrewEmptyFrame::setCalibrationEnabled(bool enabled)
{
    m_calibrateButton->setEnabled(enabled);
}

void AdjustmentScrewEmptyFrame::on_calibrateButton_clicked()
{
    m_calibrateButton->setEnabled(false);
    m_homeButton->setEnabled(false);
    m_printerBed->calibrateAdjustmentScrews();
}

void AdjustmentScrewEmptyFrame::onToolheadHoming()
{
    m_textLabel->setText("Homing Toolhead");
}

void AdjustmentScrewEmptyFrame::onToolheadHomingFinished()
{
    m_textLabel->setText("No Data Found");
}

void AdjustmentScrewEmptyFrame::on_homeButton_clicked()
{
    emit calibrating();

    QKlipperPrinter *printer = qobject_cast<QKlipperPrinter*>(m_printerBed->parent());

    if(printer)
    printer->toolhead()->home();
}

