#include "printersystemwidget.h"
#include "flo/settings.h"

PrinterSystemWidget::PrinterSystemWidget(QKlipperInstance *instance, QWidget *parent)
    : CardWidget{CardType::SubWidget, parent}
{

    m_system = instance->system();
    m_printer = instance->printer();
    m_mcu = m_printer->mcu();

    setupUi();

    setTitle("System");

    connect(m_system, SIGNAL(cpuInfoChanged()), this, SLOT(onSystemCpuInfoChanged()));
    connect(m_system, SIGNAL(sdInfoChanged()), this, SLOT(sdInfoUpdateEvent()));
    connect(m_system->memoryStats(), SIGNAL(totalChanged()), this, SLOT(onSystemMemoryStatsChanged()));
    connect(m_system->memoryStats(), SIGNAL(usedChanged()), this, SLOT(onSystemMemoryStatsChanged()));
    connect(m_system, SIGNAL(driveCapacityChanged()), this, SLOT(sdInfoUpdateEvent()));
    connect(m_system, SIGNAL(driveFreeChanged()), this, SLOT(sdInfoUpdateEvent()));
    connect(m_system, SIGNAL(driveUsageChanged()), this, SLOT(sdInfoUpdateEvent()));
}

PrinterSystemWidget::~PrinterSystemWidget()
{
    // if(m_centralLayout)
    //     m_centralLayout->deleteLater();
    if(m_centralWidget)
        m_centralLayout->deleteLater();
}

void PrinterSystemWidget::setIcons()
{
    setIcon(Settings::getThemeIcon("service"));

    m_cpuProgress->setIcon(
        Settings::getThemeIcon(
            "cpu",
            QColor(Settings::get("theme/icon-color").toString())
            )
        );

    m_memoryProgress->setIcon(
        Settings::getThemeIcon(
            "memory",
            QColor(Settings::get("theme/icon-color-alt1").toString())
            )
        );

    m_sdProgress->setIcon(
        Settings::getThemeIcon(
            "hard-drive",
            QColor(Settings::get("theme/icon-color-alt2").toString())
            )
        );

    m_temperatureProgress->setIcon(
        Settings::getThemeIcon(
            "temperature",
            QColor(Settings::get("theme/icon-color-alt").toString())
            )
        );

    m_mcuAverageProgressBar->setIcon(
        Settings::getThemeIcon(
            "cpu",
            QColor(Settings::get("theme/icon-color").toString())
            )
        );
}

void PrinterSystemWidget::systemUpdateEvent()
{
}

void PrinterSystemWidget::setupUi()
{
    //setFixedSize(540, 320);
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    m_centralWidget = new QWidget(this);
    m_centralLayout = new QGridLayout(m_centralWidget);
    m_centralWidget->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    m_centralWidget->setLayout(m_centralLayout);
    setCentralWidget(m_centralWidget);

    //Setup CPU group box
    m_cpuGroupBox = new QGroupBox(this);
    m_cpuGroupBox->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    m_cpuLayout = new QGridLayout(m_cpuGroupBox);
    m_cpuGroupBox->setTitle(QString("CPU Status"));
    //m_cpuGroupBox->setFixedWidth(256);

    //CPU instrument cluster layout
    m_cpuClusterLayout = new QHBoxLayout(m_cpuGroupBox);
    m_cpuLayout->addLayout(m_cpuClusterLayout, 0, 0, 4, 1);

    //CPU Usage Progress bar
    m_cpuProgress = new QGaugeWidget(m_cpuGroupBox, QGaugeWidget::Percent);
    m_cpuProgress->setFixedSize(100,100);
    m_cpuProgress->setFontSize(10);
    m_cpuClusterLayout->addWidget(m_cpuProgress, 0, Qt::AlignCenter);

    //m_cpuLayout->addItem(new QSpacerItem(0, 0, QSizePolicy::Ignored, QSizePolicy::Expanding));

    //Name label
    m_cpuNameLabel = new QAccentLabel(m_cpuGroupBox);
    m_cpuNameLabel->setAccentColor(Settings::get("theme/accent-color").toString());
    m_cpuNameLabel->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    // m_cpuNameLabel->setWordWrap(true);
    m_cpuLayout->addWidget(m_cpuNameLabel, 0, 1, Qt::AlignLeft);

    //Count label
    m_cpuCountLabel = new QAccentLabel(m_cpuGroupBox);
    m_cpuCountLabel->setAccentColor(Settings::get("theme/accent-color2").toString());
    m_cpuCountLabel->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    m_cpuLayout->addWidget(m_cpuCountLabel, 1, 1, Qt::AlignLeft);

    m_cpuGroupBox->setLayout(m_cpuLayout);
    m_centralLayout->addWidget(m_cpuGroupBox, 0, 0, 1, 1);

    //Temperature Progress bar
    m_temperatureProgress = new QGaugeWidget(m_temperatureGroupBox, QGaugeWidget::Temperature);
    m_temperatureProgress->setFixedSize(100,100);
    m_temperatureProgress->setFontSize(10);
    m_cpuClusterLayout->addWidget(m_temperatureProgress);

    //Current label
    m_temperatureLabel = new QAccentLabel(m_temperatureGroupBox);
    m_temperatureLabel->setAccentColor(Settings::get("theme/accent-color3").toString());
    m_temperatureLabel->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    m_cpuLayout->addWidget(m_temperatureLabel, 2, 1, Qt::AlignLeft);

    //Peak label
    m_peakTemperatureLabel = new QAccentLabel(m_temperatureGroupBox);
    m_peakTemperatureLabel->setAccentColor(Settings::get("theme/accent-color4").toString());
    m_peakTemperatureLabel->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    m_cpuLayout->addWidget(m_peakTemperatureLabel, 3, 1, Qt::AlignLeft);

    //m_cpuLayout->addItem(new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding));

    //Setup memory group box
    m_memoryGroupBox = new QGroupBox(this);
    m_memoryGroupBox->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    m_memoryLayout = new QGridLayout(m_memoryGroupBox);
    m_memoryGroupBox->setTitle(QString("Memory"));

    //memory Usage Progress bar
    m_memoryProgress = new QGaugeWidget(m_memoryGroupBox, QGaugeWidget::Percent);
    m_memoryProgress->setFixedSize(100,100);
    m_memoryProgress->setFontSize(10);
    m_memoryLayout->addWidget(m_memoryProgress, 0, 0, 5, 1);

    m_memoryLayout->addItem(new QSpacerItem(108, 0, QSizePolicy::Fixed, QSizePolicy::Fixed), 0, 1);
    m_memoryLayout->addItem(new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding), 0, 2);
    //Capacity label
    m_memoryCapacityLabel = new QAccentLabel(m_memoryGroupBox);
    m_memoryCapacityLabel->setAccentColor(Settings::get("theme/accent-color").toString());
    m_memoryCapacityLabel->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    m_memoryLayout->addWidget(m_memoryCapacityLabel, 1, 2);

    //Used label
    m_memoryUsedLabel = new QAccentLabel(m_memoryGroupBox);
    m_memoryUsedLabel->setAccentColor(Settings::get("theme/accent-color2").toString());
    m_memoryUsedLabel->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    m_memoryLayout->addWidget(m_memoryUsedLabel, 2, 2);

    //Available label
    m_memoryAvailableLabel = new QAccentLabel(m_memoryGroupBox);
    m_memoryAvailableLabel->setAccentColor(Settings::get("theme/accent-color3").toString());
    m_memoryAvailableLabel->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    m_memoryLayout->addWidget(m_memoryAvailableLabel, 3, 2);

    m_memoryLayout->addItem(new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding), 4, 1);

    m_memoryGroupBox->setLayout(m_memoryLayout);
    m_centralLayout->addWidget(m_memoryGroupBox, 1, 0, 1, 1);

    //Setup SD group box
    m_sdGroupBox = new QGroupBox(this);
    m_sdGroupBox->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    m_sdLayout = new QGridLayout(m_sdGroupBox);
    m_sdGroupBox->setTitle(QString("File System"));

    //SD Usage Progress bar
    m_sdProgress = new QGaugeWidget(m_sdGroupBox, QGaugeWidget::Percent);
    m_sdProgress->setFixedSize(100,100);
    m_sdProgress->setFontSize(10);
    m_sdLayout->addWidget(m_sdProgress, 0, 0, Qt::AlignCenter);

    m_sdLayout->addItem(new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding), 1, 0);

    //Capacity label
    m_sdCapacityLabel = new QAccentLabel(m_sdGroupBox);
    m_sdCapacityLabel->setAccentColor(Settings::get("theme/accent-color").toString());
    m_sdCapacityLabel->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    m_sdLayout->addWidget(m_sdCapacityLabel, 2, 0, Qt::AlignLeft);

    //Used label
    m_sdUsedLabel = new QAccentLabel(m_sdGroupBox);
    m_sdUsedLabel->setAccentColor(Settings::get("theme/accent-color2").toString());
    m_sdUsedLabel->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    m_sdLayout->addWidget(m_sdUsedLabel, 3, 0, Qt::AlignLeft);

    //Available label
    m_sdAvailableLabel = new QAccentLabel(m_sdGroupBox);
    m_sdAvailableLabel->setAccentColor(Settings::get("theme/accent-color3").toString());
    m_sdAvailableLabel->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    m_sdLayout->addWidget(m_sdAvailableLabel, 4, 0, Qt::AlignLeft);

    m_sdLayout->addItem(new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding), 5, 0);

    m_sdGroupBox->setLayout(m_sdLayout);
    m_centralLayout->addWidget(m_sdGroupBox, 0, 1, 2, 1);

    setIcon(Settings::getThemeIcon("system"));




    m_mcuGroupBox = new QGroupBox(this);
    m_mcuGroupBox->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    m_mcuGroupBox->setTitle(QString("MCU"));

    m_mcuLayout = new QVBoxLayout(m_mcuGroupBox);
    m_mcuGroupBox->setLayout(m_mcuLayout);

    m_mcuProgressWidget = new QWidget(this);
    m_mcuProgressWidget->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    m_mcuProgressLayout = new QHBoxLayout(m_mcuProgressWidget);

    //m_mcuProgressLayout->addItem(new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Ignored));

    m_mcuAverageProgressBar = new QGaugeWidget(m_mcuProgressWidget);
    m_mcuAverageProgressBar->setFontSize(10);
    m_mcuAverageProgressBar->setFixedSize(100,100);
    m_mcuProgressLayout->addWidget(m_mcuAverageProgressBar);

    //m_mcuProgressLayout->addItem(new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Ignored));

    m_mcuLayout->addWidget(m_mcuProgressWidget);
    m_mcuLayout->addItem(new QSpacerItem(0, 0, QSizePolicy::Ignored, QSizePolicy::Expanding));

    //Capacity label
    m_wakeTimeLabel = new QAccentLabel(m_mcuGroupBox);
    m_wakeTimeLabel->setAccentColor(Settings::get("theme/accent-color").toString());
    m_wakeTimeLabel->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    m_mcuLayout->addWidget(m_wakeTimeLabel);

    //Available label
    m_firmwareLabel = new QAccentLabel(m_mcuGroupBox);
    m_firmwareLabel->setAccentColor(Settings::get("theme/accent-color2").toString());
    m_firmwareLabel->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    m_mcuLayout->addWidget(m_firmwareLabel);

    //Available label
    m_hardwareLabel = new QAccentLabel(m_mcuGroupBox);
    m_hardwareLabel->setAccentColor(Settings::get("theme/accent-color3").toString());
    m_hardwareLabel->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    m_mcuLayout->addWidget(m_hardwareLabel);

    //Used label
    m_frequencyLabel = new QAccentLabel(m_mcuGroupBox);
    m_frequencyLabel->setAccentColor(Settings::get("theme/accent-color4").toString());
    m_frequencyLabel->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    m_mcuLayout->addWidget(m_frequencyLabel);

    m_mcuLayout->addItem(new QSpacerItem(0, 0, QSizePolicy::Ignored, QSizePolicy::Expanding));

    m_centralLayout->addWidget(m_mcuGroupBox,0,2,2,1);
    // m_centralWidget->setLayout(m_centralLayout);
    // setCentralWidget(m_centralWidget);

    onPrinterMcuWakeTimeChanged();
    onPrinterMcuFirmwareVersionChanged();
    onPrinterMcuHardwareVersionChanged();
    onPrinterMcuTaskAverageChanged();
    onPrinterMcuFrequencyChanged();

    connect(m_printer->mcu(), SIGNAL(awakeChanged()), this, SLOT(onPrinterMcuWakeTimeChanged()));
    connect(m_printer->mcu(), SIGNAL(firmwareVersionChanged()), this, SLOT(onPrinterMcuFirmwareVersionChanged()));
    connect(m_printer->mcu(), SIGNAL(frequencyChanged()), this, SLOT(onPrinterMcuFrequencyChanged()));
    connect(m_printer->mcu(), SIGNAL(hardwareVersionChanged()), this, SLOT(onPrinterMcuHardwareVersionChanged()));
    connect(m_printer->mcu(), SIGNAL(taskAverageChanged()), this, SLOT(onPrinterMcuTaskAverageChanged()));
    connect(m_printer, SIGNAL(mcuChanged()), this, SLOT(onPrinterMcuChanged()));
}

void PrinterSystemWidget::sdInfoUpdateEvent()
{
    m_sdProgress->setMaximum(m_system->driveCapacity());
    m_sdProgress->setValue(m_system->driveUsage());

    qreal capacity = m_system->driveCapacity() / 1024;
    QString capacityLabel;
    convertBytes(capacity, capacityLabel);

    QString memoryCapacityString = QString("Capacity: %1 %2").arg(QString::number(capacity, 'f', 2)).arg(capacityLabel);
    m_sdCapacityLabel->setText(memoryCapacityString);

    qreal available = m_system->driveFree() / 1024;
    QString availableLabel;
    convertBytes(available, availableLabel);

    QString memoryAvailableString = QString("Available: %1 %2").arg(QString::number(available, 'f', 2)).arg(availableLabel);
    m_sdAvailableLabel->setText(memoryAvailableString);

    qreal used = m_system->driveUsage() / 1024;
    QString usedLabel;
    convertBytes(used, usedLabel);

    QString memoryUsedString = QString("Used: %1 %2").arg(QString::number(used, 'f', 2)).arg(usedLabel);
    m_sdUsedLabel->setText(memoryUsedString);
}

void PrinterSystemWidget::onSystemCpuInfoChanged()
{
    if(m_system->cpuInfo().temp() > m_peakTemperature)
        m_peakTemperature = m_system->cpuInfo().temp();

    QString cpuName;
    QString cpuType;

    if(!m_system->cpuInfo().model().isEmpty())
        cpuName = QString("%1").arg(m_system->cpuInfo().model());
    else if(!m_system->cpuInfo().description().isEmpty())
        cpuName = QString("%1").arg(m_system->cpuInfo().description());

    cpuName = QString("Processor: %1...").arg(cpuName.left(16));

    if(!m_system->cpuInfo().processor().isEmpty())
        cpuType = QString("Type: %1").arg(m_system->cpuInfo().processor());

    QString cpuCount = QString("Cores: %1").arg(m_system->cpuInfo().cpuCount());
    QString peakTemperature = QString("Peak Temperature: %1°C").arg(QString::number(m_peakTemperature, 'f', 2));

    m_cpuCountLabel->setText(cpuCount);
    m_cpuNameLabel->setText(cpuName);
    m_temperatureLabel->setText(cpuType);
    m_peakTemperatureLabel->setText(peakTemperature);

    m_cpuProgress->setValue(m_system->cpuInfo().usage());
    m_temperatureProgress->setValue(m_system->cpuInfo().temp());
}

void PrinterSystemWidget::onSystemMemoryStatsChanged()
{
    m_memoryProgress->setMaximum(m_system->memoryStats()->total());
    m_memoryProgress->setValue(m_system->memoryStats()->used());

    qreal capacity = m_system->memoryStats()->total();
    QString capacityLabel;
    convertBytes(capacity, capacityLabel);

    QString memoryCapacityString = QString("Capacity : %1 %2").arg(QString::number(capacity, 'f', 2)).arg(capacityLabel);
    m_memoryCapacityLabel->setText(memoryCapacityString);

    qreal available = m_system->memoryStats()->total() - m_system->memoryStats()->used();
    QString availableLabel;
    convertBytes(available, availableLabel);

    QString memoryAvailableString = QString("Available : %1 %2").arg(QString::number(available, 'f', 2)).arg(availableLabel);
    m_memoryAvailableLabel->setText(memoryAvailableString);

    qreal used = m_system->memoryStats()->used();
    QString usedLabel;
    convertBytes(used, usedLabel);

    QString memoryUsedString = QString("Used : %1 %2").arg(QString::number(used, 'f', 2)).arg(usedLabel);
    m_memoryUsedLabel->setText(memoryUsedString);
}

void PrinterSystemWidget::onPrinterMcuWakeTimeChanged()
{
    m_wakeTimeLabel->setText(QString("Wake Time: %1").arg(QString::number(m_mcu->awake(), 'f', 4)));
}

void PrinterSystemWidget::onPrinterMcuFirmwareVersionChanged()
{
    m_firmwareLabel->setText(QString("Firmware: %1").arg(m_mcu->firmwareVersion()));
}

void PrinterSystemWidget::onPrinterMcuHardwareVersionChanged()
{
    m_hardwareLabel->setText(QString("Hardware: %1").arg(m_mcu->hardwareVersion()));
}

void PrinterSystemWidget::onPrinterMcuTaskAverageChanged()
{
    m_mcuAverageProgressBar->setValue(m_mcu->taskAverage());
}

void PrinterSystemWidget::onPrinterMcuFrequencyChanged()
{
    m_frequencyLabel->setText(QString("Frequency: %1MHz").arg(QString::number((((qreal)m_mcu->frequency() / 1024) / 1024), 'f', 2)));
}

void PrinterSystemWidget::onPrinterMcuChanged()
{
    m_mcu = m_printer->mcu();
}

void PrinterSystemWidget::convertDriveBytes(qreal &bytes, QString &label)
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

void PrinterSystemWidget::convertBytes(qreal &bytes, QString &label)
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

void PrinterSystemWidget::changeEvent(QEvent *event)
{
    if(event->type() == QEvent::StyleChange)
        setIcons();

    CardWidget::changeEvent(event);
}
