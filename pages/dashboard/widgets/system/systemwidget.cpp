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
    this->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "DashboardWidget" << "Disconnected" << "ConnectionStatus" ));
}

void SystemWidget::setPrinter(Printer *printer)
{
    if(m_printer != nullptr)
        disconnect(m_printer,SIGNAL(systemUpdate(Printer*)), this, SLOT(on_printer_systemUpdate(Printer*)));

    m_printer = printer;
    connect(m_printer,SIGNAL(systemUpdate(Printer*)), this, SLOT(on_printer_systemUpdate(Printer*)));
    connect(m_printer,SIGNAL(klipperConnected(Printer*)),this, SLOT(on_printer_klipperConnected(Printer*)));
    connect(m_printer,SIGNAL(klipperDisconnected(Printer*)),this, SLOT(on_printer_klipperDisconnected(Printer*)));
}

void SystemWidget::setStyleSheet(QString styleSheet)
{
    QFrame::setStyleSheet(styleSheet);

    QPixmap pixmap;

    pixmap = Settings::getThemeIcon("dashboard").pixmap(ui->systemIcon->size());
    ui->systemIcon->setPixmap(pixmap);
}


void SystemWidget::on_printer_systemUpdate(Printer *printer)
{
    qDebug() << "System Update";
    m_systemCpuLoadProgressBar->setProgress(printer->system()->cpuInfo().usage);

    m_systemMemoryLoadProgressBar->setMaximum(printer->system()->memoryStats().total);
    m_systemMemoryLoadProgressBar->setProgress(printer->system()->memoryStats().used);

    QString memoryCapacityString("System Memory: ");
    qreal capacity = printer->system()->memoryStats().total;
    QString capacityLabel;
    convertBytes(capacity, capacityLabel);
    memoryCapacityString += QString::number(capacity, 'f', 2);
    memoryCapacityString += capacityLabel;
    ui->memoryCapacityLabel->setText(memoryCapacityString);

    QString memoryAvailableString("Available Memory: ");
    qreal available = printer->system()->memoryStats().total - printer->system()->memoryStats().used;
    QString availableLabel;
    convertBytes(available, availableLabel);
    memoryAvailableString += QString::number(available, 'f', 2);
    memoryAvailableString += availableLabel;
    ui->memoryAvailableLabel->setText(memoryAvailableString);


    //Need to find a different way to determine drive space
    /*
    QString driveFreeString("Drive Free: ");
    QString driveFreeValueString;
    qreal driveFree = printer->system()->driveFree();
    convertDriveBytes(driveFree, driveFreeValueString);
    driveFreeString = driveFreeString + QString::number(driveFree) + driveFreeValueString;
    ui->driveFreeLabel->setText(driveFreeString);

    QString driveUsedString("Drive Used: ");
    QString driveUsedValueString;
    qreal driveUsed = printer->system()->driveUsage();
    convertDriveBytes(driveUsed, driveUsedValueString);
    driveUsedString = driveUsedString + QString::number(driveUsed) + driveUsedValueString;
    ui->driveUsedLabel->setText(driveUsedString);
    QString driveCapacityString("Drive Capacity: ");
    QString driveCapacityValueString;
    qreal driveCapacity = printer->system()->driveCapacity();
    convertDriveBytes(driveCapacity, driveCapacityValueString);
    driveCapacityString = driveCapacityString + QString::number(driveCapacity) + driveUsedValueString;
    ui->driveCapacityLabel->setText(driveCapacityString);

    */
    ui->hostnameLabel->setText(QString("Hostname: ") + printer->system()->hostname());
    ui->cpuInfoLabel->setText(m_printer->system()->cpuInfo().description);
}

void SystemWidget::on_printer_klipperDisconnected(Printer *printer)
{
    showLoadingScreen();
}

void SystemWidget::on_printer_klipperConnected(Printer *printer)
{
    hideLoadingScreen();
}

void SystemWidget::on_loadingAnimation_finished()
{
    m_loadingGif->stop();

    delete m_loadingGif;
    delete m_loadingLabel;
    delete m_loadingAnimation;

    m_loadingLabel = nullptr;
    m_loadingGif = nullptr;
    m_loadingAnimation = nullptr;
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
        delete m_loadingGif;
    if(m_loadingLabel != nullptr)
        delete m_loadingLabel;
    if(m_loadingAnimation != nullptr)
        delete m_loadingAnimation;

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
