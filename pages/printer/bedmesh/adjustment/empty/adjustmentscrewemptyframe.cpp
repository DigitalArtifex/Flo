#include "adjustmentscrewemptyframe.h"

#include "system/settings.h"

AdjustmentScrewEmptyFrame::AdjustmentScrewEmptyFrame(QKlipperPrintBed *bed, QWidget *parent)
    : QFrame(parent)
{
    m_iconLabel = new QLabel(this);
    m_textLabel = new QLabel(this);
    m_textLabel->setText("No Data Found");
    m_textLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    m_homeButton = new QIconButton(this);
    m_homeButton->setIcon(Settings::getThemeIcon("home-icon"));
    m_homeButton->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
    connect(m_homeButton, SIGNAL(clicked()), this, SLOT(on_homeButton_clicked()));

    m_calibrateButton = new QIconButton(this);
    m_calibrateButton->setText("Calibrate");

    connect(m_calibrateButton, SIGNAL(clicked()), this, SLOT(on_calibrateButton_clicked()));

    m_layout = new QHBoxLayout(this);
    m_layout->addWidget(m_iconLabel);
    m_layout->addWidget(m_textLabel);
    m_layout->addWidget(m_homeButton);
    m_layout->addWidget(m_calibrateButton);

    setLayout(m_layout);

    QPixmap pixmap = Settings::getThemeIcon("no-data-icon").pixmap(m_iconLabel->size());
    m_iconLabel->setPixmap(pixmap);

    m_printerBed = bed;
    connect(m_printerBed->printer()->toolhead(), SIGNAL(homing()), this, SLOT(onToolheadHoming()));
    connect(m_printerBed->printer()->toolhead(), SIGNAL(homingFinished()), this, SLOT(onToolheadHomingFinished()));
    connect(m_printerBed->printer()->toolhead(), SIGNAL(isHomedChanged()), this, SLOT(onToolheadHomingFinished()));
}

AdjustmentScrewEmptyFrame::~AdjustmentScrewEmptyFrame()
{
}

void AdjustmentScrewEmptyFrame::setStyleSheet(const QString &styleSheet)
{
    QPixmap pixmap = Settings::getThemeIcon("no-data-icon").pixmap(m_iconLabel->size());
    m_iconLabel->setPixmap(pixmap);

    m_homeButton->setIcon(Settings::getThemeIcon(QString("home-icon")));

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
    m_homeButton->setEnabled(false);
}

void AdjustmentScrewEmptyFrame::onToolheadHomingFinished()
{
    m_textLabel->setText("No Data Found");
    m_calibrateButton->setEnabled(m_printerBed->printer()->toolhead()->isHomed());
    m_homeButton->setEnabled(!m_printerBed->printer()->toolhead()->isHomed());
}

void AdjustmentScrewEmptyFrame::on_homeButton_clicked()
{
    emit calibrating();
    m_printerBed->printer()->toolhead()->home();
}

