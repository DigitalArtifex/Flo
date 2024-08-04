#include "printerdrivewidget.h"

PrinterDriveWidget::PrinterDriveWidget(System *system, QWidget *parent)
    : CardWidget{CardWidget::SubWidget, parent}
{
    m_system = system;

    setupUi();

    connect(system, SIGNAL(mcuChanged()), this, SLOT(systemMCUChanged()));
}

void PrinterDriveWidget::setupUi()
{
    setTitle("MCU");
    setFixedWidth(160);

    m_centralWidget = new QWidget(this);
    m_centralLayout = new QHBoxLayout(m_centralWidget);
    m_centralWidget->setLayout(m_centralLayout);
    setCentralWidget(m_centralWidget);

    m_sdGroupBox = new QGroupBox(this);
    m_sdGroupBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    m_sdLayout = new QVBoxLayout(m_sdGroupBox);
    m_sdGroupBox->setTitle(QString("Drive"));

    m_sdLayout = new QVBoxLayout(m_sdGroupBox);
    m_sdLayout->addItem(new QSpacerItem(0, 0, QSizePolicy::Ignored, QSizePolicy::Expanding));

    //Capacity label
    m_sdCapacityLabel = new QLabel(m_sdGroupBox);
    m_sdCapacityLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    m_sdLayout->addWidget(m_sdCapacityLabel);

    //Used label
    m_sdUsedLabel = new QLabel(m_sdGroupBox);
    m_sdUsedLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    m_sdLayout->addWidget(m_sdUsedLabel);

    //Available label
    m_sdAvailableLabel = new QLabel(m_sdGroupBox);
    m_sdAvailableLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    m_sdLayout->addWidget(m_sdAvailableLabel);

    m_sdLayout->addItem(new QSpacerItem(0, 0, QSizePolicy::Ignored, QSizePolicy::Expanding));

    m_sdGroupBox->setLayout(m_sdLayout);
    m_centralLayout->addWidget(m_sdGroupBox);

    setCentralWidget(m_centralWidget);
}

void PrinterDriveWidget::systemMCUChanged()
{
    m_mcu = m_system->mcu();

    m_sdCapacityLabel->setText(m_mcu.serial);
}

void PrinterDriveWidget::convertDriveBytes(qreal &bytes, QString &label)
{
    label = QString("B");

    if(bytes >= 1024)
    {
        bytes /= 1024;
        label = QString("KB");

        if(bytes >= 1024)
        {
            bytes /= 1024;
            label = QString("MB");
        }

        if(bytes >= 1024)
        {
            bytes /= 1024;
            label = QString("GB");
        }

        if(bytes >= 1024)
        {
            bytes /= 1024;
            label = QString("TB");
        }
    }
}

void PrinterDriveWidget::convertBytes(qreal &bytes, QString &label)
{
    label = QString("KB");

    if(bytes >= 1024)
    {
        bytes /= 1024;
        label = QString("MB");

        if(bytes >= 1024)
        {
            bytes /= 1024;
            label = QString("GB");
        }

        if(bytes >= 1024)
        {
            bytes /= 1024;
            label = QString("TB");
        }
    }
}
