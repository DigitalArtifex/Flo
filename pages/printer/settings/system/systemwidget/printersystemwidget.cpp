#include "printersystemwidget.h"

PrinterSystemWidget::PrinterSystemWidget(QKlipperInstance *instance, QWidget *parent)
    : CardWidget{CardWidget::SubWidget, parent}
{
    setupUi();

    setTitle("System");

    m_system = instance->system();

    //connect(m_system, SIGNAL(updated()), this, SLOT(onSystemMemoryStatsChanged()));
    connect(m_system, SIGNAL(cpuInfoChanged()), this, SLOT(onSystemCpuInfoChanged()));
    connect(m_system, SIGNAL(sdInfoChanged()), this, SLOT(sdInfoUpdateEvent()));
    connect(m_system->memoryStats(), SIGNAL(totalChanged()), this, SLOT(onSystemMemoryStatsChanged()));
    connect(m_system->memoryStats(), SIGNAL(usedChanged()), this, SLOT(onSystemMemoryStatsChanged()));
}

PrinterSystemWidget::~PrinterSystemWidget()
{
    if(m_centralLayout)
        m_centralLayout->deleteLater();
    if(m_centralWidget)
        m_centralLayout->deleteLater();
}

void PrinterSystemWidget::systemUpdateEvent()
{
}

void PrinterSystemWidget::setupUi()
{
    setFixedSize(540, 320);

    m_centralWidget = new QWidget(this);
    m_centralLayout = new QHBoxLayout(m_centralWidget);
    m_centralWidget->setLayout(m_centralLayout);
    setCentralWidget(m_centralWidget);

    //Setup CPU group box
    m_cpuGroupBox = new QGroupBox(this);
    m_cpuGroupBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    m_cpuLayout = new QVBoxLayout(m_cpuGroupBox);
    m_cpuGroupBox->setTitle(QString("CPU Status"));
    m_cpuGroupBox->setFixedWidth(250);

    //CPU instrument cluster layout
    m_cpuClusterLayout = new QHBoxLayout(m_cpuGroupBox);
    m_cpuLayout->addLayout(m_cpuClusterLayout);

    //CPU Usage Progress bar
    m_cpuProgress = new CircularProgressBar(m_cpuGroupBox, CircularProgressBar::Percent);
    m_cpuProgress->setFixedSize(100,100);
    m_cpuProgress->setFontSize(10);
    m_cpuClusterLayout->addWidget(m_cpuProgress);

    m_cpuLayout->addItem(new QSpacerItem(0, 0, QSizePolicy::Ignored, QSizePolicy::Expanding));

    //Name label
    m_cpuNameLabel = new QLabel(m_cpuGroupBox);
    m_cpuNameLabel->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    m_cpuNameLabel->setWordWrap(true);
    m_cpuLayout->addWidget(m_cpuNameLabel);

    //Count label
    m_cpuCountLabel = new QLabel(m_cpuGroupBox);
    m_cpuCountLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    m_cpuLayout->addWidget(m_cpuCountLabel);

    m_cpuGroupBox->setLayout(m_cpuLayout);
    m_centralLayout->addWidget(m_cpuGroupBox);

    //Setup Temperature group box
    //m_temperatureGroupBox = new QGroupBox(this);
    //m_temperatureGroupBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    //m_temperatureGroupBox->setTitle(QString("CPU Temperature"));

    //Temperature Progress bar
    m_temperatureProgress = new CircularProgressBar(m_temperatureGroupBox, CircularProgressBar::Temperature);
    m_temperatureProgress->setFixedSize(100,100);
    m_temperatureProgress->setFontSize(10);
    m_cpuClusterLayout->addWidget(m_temperatureProgress);

    //Current label
    m_temperatureLabel = new QLabel(m_temperatureGroupBox);
    m_temperatureLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    m_cpuLayout->addWidget(m_temperatureLabel);

    //Peak label
    m_peakTemperatureLabel = new QLabel(m_temperatureGroupBox);
    m_peakTemperatureLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    m_cpuLayout->addWidget(m_peakTemperatureLabel);

    m_cpuLayout->addItem(new QSpacerItem(0, 0, QSizePolicy::Ignored, QSizePolicy::Expanding));

    //Setup memory group box
    m_memoryGroupBox = new QGroupBox(this);
    m_memoryGroupBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    m_memoryLayout = new QVBoxLayout(m_memoryGroupBox);
    m_memoryGroupBox->setTitle(QString("Memory"));
    m_memoryGroupBox->setFixedWidth(125);

    //memory Usage Progress bar
    m_memoryProgress = new CircularProgressBar(m_memoryGroupBox, CircularProgressBar::Percent);
    m_memoryProgress->setFixedSize(100,100);
    m_memoryProgress->setFontSize(10);
    m_memoryLayout->addWidget(m_memoryProgress);

    m_memoryLayout->addItem(new QSpacerItem(0, 0, QSizePolicy::Ignored, QSizePolicy::Expanding));

    //Capacity label
    m_memoryCapacityLabel = new QLabel(m_memoryGroupBox);
    m_memoryCapacityLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    m_memoryLayout->addWidget(m_memoryCapacityLabel);

    //Used label
    m_memoryUsedLabel = new QLabel(m_memoryGroupBox);
    m_memoryUsedLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    m_memoryLayout->addWidget(m_memoryUsedLabel);

    //Available label
    m_memoryAvailableLabel = new QLabel(m_memoryGroupBox);
    m_memoryAvailableLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    m_memoryLayout->addWidget(m_memoryAvailableLabel);

    m_memoryLayout->addItem(new QSpacerItem(0, 0, QSizePolicy::Ignored, QSizePolicy::Expanding));

    m_memoryGroupBox->setLayout(m_memoryLayout);
    m_centralLayout->addWidget(m_memoryGroupBox);

    //Setup SD group box
    m_sdGroupBox = new QGroupBox(this);
    m_sdGroupBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    m_sdLayout = new QVBoxLayout(m_sdGroupBox);
    m_sdGroupBox->setTitle(QString("File System"));
    m_sdGroupBox->setFixedWidth(125);

    //SD Usage Progress bar
    m_sdProgress = new CircularProgressBar(m_sdGroupBox, CircularProgressBar::Percent);
    m_sdProgress->setFixedSize(100,100);
    m_sdProgress->setFontSize(10);
    m_sdLayout->addWidget(m_sdProgress);

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
}

void PrinterSystemWidget::sdInfoUpdateEvent()
{
    m_sdInfo = m_system->sdInfo();

    m_sdProgress->setMaximum(m_sdInfo.totalBytes());
    m_sdProgress->setProgress(m_sdInfo.usedBytes());

    qreal capacity = m_sdInfo.totalBytes();
    QString capacityLabel;
    convertBytes(capacity, capacityLabel);

    QString memoryCapacityString = QString("Capacity: %1 %2").arg(QString::number(capacity, 'f', 2)).arg(capacityLabel);
    m_sdCapacityLabel->setText(memoryCapacityString);

    qreal available = m_sdInfo.availableBytes();
    QString availableLabel;
    convertBytes(available, availableLabel);

    QString memoryAvailableString = QString("Available: %1 %2").arg(QString::number(available, 'f', 2)).arg(availableLabel);
    m_sdAvailableLabel->setText(memoryAvailableString);

    qreal used = m_sdInfo.usedBytes();
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

    m_cpuProgress->setProgress(m_system->cpuInfo().usage());
    m_temperatureProgress->setProgress(m_system->cpuInfo().temp());
}

void PrinterSystemWidget::onSystemMemoryStatsChanged()
{
    m_memoryProgress->setMaximum(m_system->memoryStats()->total());
    m_memoryProgress->setProgress(m_system->memoryStats()->used());

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
