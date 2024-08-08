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
    setFixedSize(220, 320);

    m_centralWidget = new QWidget(this);
    m_centralLayout = new QHBoxLayout(m_centralWidget);

    m_sdGroupBox = new QGroupBox(this);
    m_sdGroupBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    m_sdGroupBox->setTitle(QString("Status"));

    m_sdLayout = new QVBoxLayout(m_sdGroupBox);
    m_sdGroupBox->setLayout(m_sdLayout);

    m_progressWidget = new QWidget(this);
    m_progressLayout = new QHBoxLayout(m_progressWidget);

    m_progressLayout->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Ignored));

    m_mcuAverageProgressBar = new CircularProgressBar(m_progressWidget);
    m_mcuAverageProgressBar->setFontSize(10);
    m_progressLayout->addWidget(m_mcuAverageProgressBar);

    m_progressLayout->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Ignored));

    m_sdLayout->addWidget(m_progressWidget);
    m_sdLayout->addItem(new QSpacerItem(0, 0, QSizePolicy::Ignored, QSizePolicy::Expanding));

    //Capacity label
    m_wakeTimeLabel = new QLabel(m_sdGroupBox);
    m_wakeTimeLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    m_sdLayout->addWidget(m_wakeTimeLabel);

    //Available label
    m_firmwareLabel = new QLabel(m_sdGroupBox);
    m_firmwareLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    m_sdLayout->addWidget(m_firmwareLabel);

    //Available label
    m_hardwareLabel = new QLabel(m_sdGroupBox);
    m_hardwareLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    m_sdLayout->addWidget(m_hardwareLabel);

    //Used label
    m_frequencyLabel = new QLabel(m_sdGroupBox);
    m_frequencyLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    m_sdLayout->addWidget(m_frequencyLabel);

    m_sdLayout->addItem(new QSpacerItem(0, 0, QSizePolicy::Ignored, QSizePolicy::Expanding));

    m_centralLayout->addWidget(m_sdGroupBox);
    m_centralWidget->setLayout(m_centralLayout);
    setCentralWidget(m_centralWidget);

    systemMCUChanged();
}

void PrinterDriveWidget::systemMCUChanged()
{
    m_mcu = m_system->mcu();

    m_wakeTimeLabel->setText(QString("Wake Time: %1").arg(QString::number(m_mcu.awake, 'f', 2)));
    m_frequencyLabel->setText(QString("Frequency: %1MHz").arg(QString::number(((m_mcu.frequency / 1024) / 1024), 'f', 2)));
    m_firmwareLabel->setText(QString("Firmware: %1").arg(m_mcu.firmwareVersion));
    m_hardwareLabel->setText(QString("Hardware: %1").arg(m_mcu.hardwareVersion));

    m_mcuAverageProgressBar->setProgress(m_mcu.taskAverage);
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
