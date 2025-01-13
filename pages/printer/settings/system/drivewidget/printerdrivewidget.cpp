#include "printerdrivewidget.h"
#include "system/settings.h"

PrinterDriveWidget::PrinterDriveWidget(QKlipperPrinter *system, QWidget *parent)
    : CardWidget{CardType::SubWidget, parent}
{
    m_system = system;
    m_mcu = m_system->mcu();

    setupUi();
}

void PrinterDriveWidget::setStyleSheet(const QString &styleSheet)
{
    setIcon(Settings::getThemeIcon("mcu"));

    m_mcuAverageProgressBar->setIcon(
        Settings::getThemeIcon(
            "cpu",
            QColor(Settings::get("theme/icon-color").toString())
            )
        );

    CardWidget::setStyleSheet(styleSheet);
}

void PrinterDriveWidget::setupUi()
{
    setTitle("MCU");
    setIcon(Settings::getThemeIcon("mcu"));
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

    m_mcuAverageProgressBar = new QGaugeWidget(m_progressWidget);
    m_mcuAverageProgressBar->setFontSize(10);
    m_mcuAverageProgressBar->setFixedSize(100,100);
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

    onPrinterMcuWakeTimeChanged();
    onPrinterMcuFirmwareVersionChanged();
    onPrinterMcuHardwareVersionChanged();
    onPrinterMcuTaskAverageChanged();
    onPrinterMcuFrequencyChanged();

    connect(m_system->mcu(), SIGNAL(awakeChanged()), this, SLOT(onPrinterMcuWakeTimeChanged()));
    connect(m_system->mcu(), SIGNAL(firmwareVersionChanged()), this, SLOT(onPrinterMcuFirmwareVersionChanged()));
    connect(m_system->mcu(), SIGNAL(frequencyChanged()), this, SLOT(onPrinterMcuFrequencyChanged()));
    connect(m_system->mcu(), SIGNAL(hardwareVersionChanged()), this, SLOT(onPrinterMcuHardwareVersionChanged()));
    connect(m_system->mcu(), SIGNAL(taskAverageChanged()), this, SLOT(onPrinterMcuTaskAverageChanged()));
    connect(m_system, SIGNAL(mcuChanged()), this, SLOT(onPrinterMcuChanged()));
}

void PrinterDriveWidget::onPrinterMcuWakeTimeChanged()
{
    m_wakeTimeLabel->setText(QString("Wake Time: %1").arg(QString::number(m_mcu->awake(), 'f', 4)));
}

void PrinterDriveWidget::onPrinterMcuFirmwareVersionChanged()
{
    m_firmwareLabel->setText(QString("Firmware: %1").arg(m_mcu->firmwareVersion()));
}

void PrinterDriveWidget::onPrinterMcuHardwareVersionChanged()
{
    m_hardwareLabel->setText(QString("Hardware: %1").arg(m_mcu->hardwareVersion()));
}

void PrinterDriveWidget::onPrinterMcuTaskAverageChanged()
{
    m_mcuAverageProgressBar->setValue(m_mcu->taskAverage());
}

void PrinterDriveWidget::onPrinterMcuFrequencyChanged()
{
    m_frequencyLabel->setText(QString("Frequency: %1MHz").arg(QString::number((((qreal)m_mcu->frequency() / 1024) / 1024), 'f', 2)));
}

void PrinterDriveWidget::onPrinterMcuChanged()
{
    m_mcu = m_system->mcu();
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
