#include "systemwidget.h"
#include "ui_systemwidget.h"

#include "../../../../system/settings.h"

SystemWidget::SystemWidget(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::SystemWidget)
{
    ui->setupUi(this);

    _systemCpuLoadProgressBar = new CircularProgressBar(this);
    _systemMemoryLoadProgressBar = new CircularProgressBar(this);
    _systemTemperatureProgressBar = new CircularProgressBar(this);
    ui->systemMemoryLoadLayout->addWidget(_systemMemoryLoadProgressBar);
    ui->systemCpuLoadLayout->addWidget(_systemCpuLoadProgressBar);
    ui->systemTemperatureLayout->addWidget(_systemTemperatureProgressBar);

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
    if(_printer != nullptr)
        disconnect(_printer,SIGNAL(systemUpdate(Printer*)), this, SLOT(on_printer_systemUpdate(Printer*)));

    _printer = printer;
    connect(_printer,SIGNAL(systemUpdate(Printer*)), this, SLOT(on_printer_systemUpdate(Printer*)));
    connect(_printer,SIGNAL(klipperConnected(Printer*)),this, SLOT(on_printer_klipperConnected(Printer*)));
    connect(_printer,SIGNAL(klipperDisconnected(Printer*)),this, SLOT(on_printer_klipperDisconnected(Printer*)));
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
    _systemCpuLoadProgressBar->setProgress(printer->system()->cpuLoad());
    _systemMemoryLoadProgressBar->setMaximum(printer->system()->memoryCapacity());
    _systemMemoryLoadProgressBar->setProgress(printer->system()->memoryUsage());

    QString memoryCapacityString("System Memory: ");
    qreal capacity = printer->system()->memoryCapacity();
    QString capacityLabel;
    convertBytes(capacity, capacityLabel);
    memoryCapacityString += QString::number(capacity);
    memoryCapacityString += capacityLabel;
    ui->memoryCapacityLabel->setText(memoryCapacityString);

    QString memoryAvailableString("Available Memory: ");
    qreal available = printer->system()->memoryCapacity() - printer->system()->memoryUsage();
    QString availableLabel;
    convertBytes(available, availableLabel);
    memoryAvailableString += QString::number(available);
    memoryAvailableString += availableLabel;
    ui->memoryAvailableLabel->setText(memoryAvailableString);

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

    ui->hostnameLabel->setText(QString("Hostname: ") + printer->system()->hostname());
    ui->cpuInfoLabel->setText(_printer->system()->cpuInfo().description);
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
    _loadingGif->stop();

    delete _loadingGif;
    delete _loadingLabel;
    delete _loadingAnimation;

    _loadingLabel = nullptr;
    _loadingGif = nullptr;
    _loadingAnimation = nullptr;
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
    if(_loadingGif != nullptr)
        delete _loadingGif;
    if(_loadingLabel != nullptr)
        delete _loadingLabel;
    if(_loadingAnimation != nullptr)
        delete _loadingAnimation;

    _loadingGif = new QMovie(":/images/images/loading_widget.gif");
    _loadingLabel = new QLabel(this);
    _loadingLabel->setMinimumWidth(this->width());
    _loadingLabel->setMinimumHeight(this->height());
    _loadingLabel->setScaledContents(true);
    _loadingLabel->setMovie(_loadingGif);
    _loadingLabel->show();
    _loadingLabel->activateWindow();
    _loadingLabel->raise();

    _loadingAnimation = new WidgetAnimation(_loadingLabel, WidgetAnimation::Opacity);
    _loadingGif->start();
    _loadingAnimation->show();
}

void SystemWidget::hideLoadingScreen()
{
    if(_loadingGif != nullptr)
    {
        connect(_loadingAnimation, SIGNAL(finished()), this, SLOT(on_loadingAnimation_finished()));
        _loadingAnimation->hide();
    }
}
