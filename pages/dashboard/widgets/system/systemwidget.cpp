#include "systemwidget.h"
#include "ui_systemwidget.h"

#include "../../../../system/settings.h"

SystemWidget::SystemWidget(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::SystemWidget)
{
    ui->setupUi(this);

    m_systemCpuLoadProgressBar = new CircularProgressBar(this);
    m_systemMemoryLoadProgressBar = new CircularProgressBar(this);
    m_systemTemperatureProgressBar = new CircularProgressBar(this, CircularProgressBar::Temperature);

    ui->systemMemoryLoadLayout->addWidget(m_systemMemoryLoadProgressBar);
    ui->systemCpuLoadLayout->addWidget(m_systemCpuLoadProgressBar);
    ui->systemTemperatureLayout->addWidget(m_systemTemperatureProgressBar);

    setUiClasses();
}

SystemWidget::~SystemWidget()
{
    delete ui;
}

void SystemWidget::setUiClasses()
{
    this->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "Widget" << "Disconnected" << "ConnectionStatus" ));
}

void SystemWidget::setPrinter(QKlipperInstance *printer)
{
    if(m_instance != nullptr)
    {
        disconnect(m_instance->system(),SIGNAL(cpuInfoChanged()), this, SLOT(onSystemCpuInfoChanged()));
        disconnect(m_instance->system(),SIGNAL(hostnameChanged()), this, SLOT(onSystemHostnameChanged()));
        disconnect(m_instance->system()->memoryStats(), SIGNAL(averageChanged()), this, SLOT(onSystemMemoryStatsChanged()));
        disconnect(m_instance->system()->memoryStats(), SIGNAL(totalChanged()), this, SLOT(onSystemMemoryStatsChanged()));
        disconnect(m_instance->system()->memoryStats(), SIGNAL(usedChanged()), this, SLOT(onSystemMemoryStatsChanged()));
    }

    m_instance = printer;

    connect(m_instance->system(),SIGNAL(cpuInfoChanged()), this, SLOT(onSystemCpuInfoChanged()));
    connect(m_instance->system(),SIGNAL(hostnameChanged()), this, SLOT(onSystemHostnameChanged()));
    connect(m_instance->system()->memoryStats(), SIGNAL(averageChanged()), this, SLOT(onSystemMemoryStatsChanged()));
    connect(m_instance->system()->memoryStats(), SIGNAL(totalChanged()), this, SLOT(onSystemMemoryStatsChanged()));
    connect(m_instance->system()->memoryStats(), SIGNAL(usedChanged()), this, SLOT(onSystemMemoryStatsChanged()));

    onSystemCpuInfoChanged();
    onSystemHostnameChanged();
    onSystemMemoryStatsChanged();
}

void SystemWidget::setStyleSheet(QString styleSheet)
{
    QFrame::setStyleSheet(styleSheet);

    QPixmap pixmap;

    pixmap = Settings::getThemeIcon("dashboard").pixmap(ui->systemIcon->size());
    ui->systemIcon->setPixmap(pixmap);
}

void SystemWidget::on_printer_klipperDisconnected(QKlipperInstance *printer)
{
    showLoadingScreen();
}

void SystemWidget::on_printer_klipperConnected(QKlipperInstance *printer)
{
    hideLoadingScreen();
}

void SystemWidget::on_loadingAnimation_finished()
{
    m_loadingGif->stop();

    m_loadingGif->deleteLater();
    m_loadingLabel->deleteLater();
    m_loadingAnimation->deleteLater();

    m_loadingLabel = nullptr;
    m_loadingGif = nullptr;
    m_loadingAnimation = nullptr;
}

void SystemWidget::onSystemMemoryStatsChanged()
{
    m_systemMemoryLoadProgressBar->setMaximum(m_instance->system()->memoryStats()->total());
    m_systemMemoryLoadProgressBar->setProgress(m_instance->system()->memoryStats()->used());

    QString memoryCapacityString("System Memory: ");
    qreal capacity = m_instance->system()->memoryStats()->total();
    QString capacityLabel;
    convertBytes(capacity, capacityLabel);
    memoryCapacityString += QString::number(capacity, 'f', 2);
    memoryCapacityString += capacityLabel;
    ui->memoryCapacityLabel->setText(memoryCapacityString);

    QString memoryAvailableString("Available Memory: ");
    qreal available = m_instance->system()->memoryStats()->total() - m_instance->system()->memoryStats()->used();
    QString availableLabel;
    convertBytes(available, availableLabel);
    memoryAvailableString += QString::number(available, 'f', 2);
    memoryAvailableString += availableLabel;
    ui->memoryAvailableLabel->setText(memoryAvailableString);
}

void SystemWidget::onSystemCpuInfoChanged()
{
    m_systemCpuLoadProgressBar->setProgress(m_instance->system()->cpuInfo().usage());
    ui->cpuInfoLabel->setText(m_instance->system()->cpuInfo().description());
}

void SystemWidget::onSystemHostnameChanged()
{
    ui->hostnameLabel->setText(QString("Hostname: ") + m_instance->system()->hostname());
}

void SystemWidget::convertBytes(qreal &bytes, QString &label)
{
    label = QString(" Kilobytes");

    if(bytes >= 1024)
    {
        bytes /= 1024;
        label = QString(" Megabytes");

        if(bytes >= 1024)
        {
            bytes /= 1024;
            label = QString(" Gigabytes");
        }

        if(bytes >= 1024)
        {
            bytes /= 1024;
            label = QString(" Terabytes");
        }
    }
}

void SystemWidget::convertDriveBytes(qreal &bytes, QString &label)
{
    label = QString(" Bytes");

    if(bytes >= 1024)
    {
        bytes /= 1024;
        label = QString(" Kilobytes");

        if(bytes >= 1024)
        {
            bytes /= 1024;
            label = QString(" Gigabytes");
        }

        if(bytes >= 1024)
        {
            bytes /= 1024;
            label = QString(" Gigabytes");
        }

        if(bytes >= 1024)
        {
            bytes /= 1024;
            label = QString(" Terabytes");
        }
    }
}

void SystemWidget::showLoadingScreen()
{
    if(m_loadingGif != nullptr)
        m_loadingGif->deleteLater();
    if(m_loadingLabel != nullptr)
        m_loadingLabel->deleteLater();
    if(m_loadingAnimation != nullptr)
        m_loadingAnimation->deleteLater();

    m_loadingGif = new QMovie(":/images/loading_widget.gif");
    m_loadingLabel = new QLabel(this);
    m_loadingLabel->setMinimumWidth(this->width());
    m_loadingLabel->setMinimumHeight(this->height());
    m_loadingLabel->setScaledContents(true);
    m_loadingLabel->setMovie(m_loadingGif);
    m_loadingLabel->show();
    m_loadingLabel->activateWindow();
    m_loadingLabel->raise();

    m_loadingAnimation = new WidgetAnimation(m_loadingLabel, WidgetAnimation::Opacity);
    m_loadingGif->start();
    m_loadingAnimation->show();
}

void SystemWidget::hideLoadingScreen()
{
    if(m_loadingGif != nullptr)
    {
        connect(m_loadingAnimation, SIGNAL(finished()), this, SLOT(on_loadingAnimation_finished()));
        m_loadingAnimation->hide();
    }
}
