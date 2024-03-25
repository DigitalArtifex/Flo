#include "printerwidget.h"
#include "ui_printerwidget.h"

#include "../../system/settings.h"

PrinterWidget::PrinterWidget(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::PrinterWidget)
{
    ui->setupUi(this);
    setUiClasses();
}

PrinterWidget::~PrinterWidget()
{
    delete ui;
}

void PrinterWidget::setPrinter(Printer *printer)
{
    _printer = printer;
    connect(_printer,SIGNAL(printerUpdate(Printer*)),this, SLOT(on_printer_update(Printer*)));
    //connect(_printer,SIGNAL(printerUpdate(Printer*)),this, SLOT(on_printer_update(Printer*)));
    connect(_printer,SIGNAL(klipperConnected(Printer*)),this, SLOT(on_printer_klipperConnected(Printer*)));
    connect(_printer,SIGNAL(klipperDisconnected(Printer*)),this, SLOT(on_printer_klipperDisconnected(Printer*)));
    on_printer_update(printer);
}

Printer *PrinterWidget::printer()
{
    return _printer;
}

void PrinterWidget::setUiClasses()
{
    this->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "DashboardWidget" << "PrinterWidget" ));
}

void PrinterWidget::setStyleSheet(QString styleSheet)
{
    QFrame::setStyleSheet(styleSheet);
    QPixmap pixmap;

    if(_printer == nullptr)
        pixmap = Settings::getThemeIcon("printer-icon").pixmap(ui->iconLabel->size());
    else
    {
        switch(_printer->status())
        {
        case Printer::Printing:
            pixmap = Settings::getThemeIcon("printer-printing-icon").pixmap(ui->iconLabel->size());
            this->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "DashboardWidget" << "PrinterWidget" << "Printing" ));
            break;
        case Printer::Cancelled:
            pixmap = Settings::getThemeIcon("printer-error-icon").pixmap(ui->iconLabel->size());
            this->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "DashboardWidget" << "PrinterWidget" << "Cancelled" ));
            break;
        case Printer::Paused:
            pixmap = Settings::getThemeIcon("printer-paused-icon").pixmap(ui->iconLabel->size());
            this->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "DashboardWidget" << "PrinterWidget" << "Paused" ));
            break;
        case Printer::Error:
            pixmap = Settings::getThemeIcon("printer-error-icon").pixmap(ui->iconLabel->size());
            this->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "DashboardWidget" << "PrinterWidget" << "Error" ));
            break;
        case Printer::Ready:
            pixmap = Settings::getThemeIcon("printer-ready-icon").pixmap(ui->iconLabel->size());
            this->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "DashboardWidget" << "PrinterWidget" << "Ready" ));
            break;
        case Printer::Offline:
            pixmap = Settings::getThemeIcon("printer-offline-icon").pixmap(ui->iconLabel->size());
            this->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "DashboardWidget" << "PrinterWidget" << "Offline" ));
            break;
        }
    }
    ui->iconLabel->setPixmap(pixmap);
    ui->quickActionButton->setIcon(Settings::getThemeIcon("menu-icon"));
}

void PrinterWidget::on_printer_update(Printer *printer)
{
    ui->nameLabel->setText(_printer->name());
    ui->etaLabel->setText(QString("ETA: ") + _printer->printEndTime().toString());

    QString statusText;
    QPixmap pixmap;

    switch(_printer->status())
    {
    case Printer::Printing:
        statusText = QString("Printing");
        ui->pausePrintButton->setEnabled(true);
        ui->cancelPrintButton->setEnabled(true);
        ui->restartFirmwareButton->setEnabled(true);
        ui->restartKlipperButton->setEnabled(true);
        pixmap = Settings::getThemeIcon("printer-printing-icon").pixmap(ui->iconLabel->size());
        this->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "DashboardWidget" << "PrinterWidget" << "Printing" ));
        break;
    case Printer::Cancelled:
        statusText = QString("Cancelled");
        ui->pausePrintButton->setEnabled(true);
        ui->cancelPrintButton->setEnabled(false);
        ui->restartFirmwareButton->setEnabled(true);
        ui->restartKlipperButton->setEnabled(true);
        pixmap = Settings::getThemeIcon("printer-error-icon").pixmap(ui->iconLabel->size());
        this->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "DashboardWidget" << "PrinterWidget" << "Cancelled" ));
        break;
    case Printer::Paused:
        statusText = QString("Paused");
        ui->pausePrintButton->setEnabled(true);
        ui->cancelPrintButton->setEnabled(true);
        ui->restartFirmwareButton->setEnabled(true);
        ui->restartKlipperButton->setEnabled(true);
        pixmap = Settings::getThemeIcon("printer-paused-icon").pixmap(ui->iconLabel->size());
        this->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "DashboardWidget" << "PrinterWidget" << "Paused" ));
        break;
    case Printer::Error:
        statusText = QString("Error");
        ui->pausePrintButton->setEnabled(false);
        ui->cancelPrintButton->setEnabled(false);
        ui->restartFirmwareButton->setEnabled(true);
        ui->restartKlipperButton->setEnabled(true);
        pixmap = Settings::getThemeIcon("printer-error-icon").pixmap(ui->iconLabel->size());
        this->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "DashboardWidget" << "PrinterWidget" << "Error" ));
        break;
    case Printer::Ready:
        statusText = QString("Ready");
        pixmap = Settings::getThemeIcon("printer-ready-icon").pixmap(ui->iconLabel->size());
        this->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "DashboardWidget" << "PrinterWidget" << "Ready" ));
        break;
    case Printer::Offline:
        statusText = QString("Offline");
        ui->pausePrintButton->setEnabled(false);
        ui->cancelPrintButton->setEnabled(false);
        ui->restartFirmwareButton->setEnabled(false);
        ui->restartKlipperButton->setEnabled(false);
        pixmap = Settings::getThemeIcon("printer-offline-icon").pixmap(ui->iconLabel->size());
        this->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "DashboardWidget" << "PrinterWidget" << "Offline" ));
        break;
    }

    ui->statusButton->setText(QString("Status: ") + statusText);
    ui->statusMessageEdit->setText(_printer->statusMessage());
    ui->iconLabel->setPixmap(pixmap);
}

void PrinterWidget::on_printer_klipperDisconnected(Printer *printer)
{
    showLoadingScreen();
}

void PrinterWidget::on_printer_klipperConnected(Printer *printer)
{
    hideLoadingScreen();
    ui->quickActionButton->setChecked(false);
}

void PrinterWidget::on_quickActionButton_toggled(bool checked)
{
    if(checked)
        ui->stackedWidget->setCurrentIndex(1);
    else
        ui->stackedWidget->setCurrentIndex(0);
}


void PrinterWidget::on_statusButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}


void PrinterWidget::on_goBackButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void PrinterWidget::on_pausePrintButton_toggled(bool checked)
{
    if(checked)
    {
        ui->pausePrintButton->setText(QString("Resume Print"));
    }
    else
    {
        ui->pausePrintButton->setText(QString("Pause Print"));
    }
}

void PrinterWidget::showLoadingScreen()
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
    _loadingLabel->show();
    _loadingLabel->activateWindow();
    _loadingLabel->raise();
    _loadingLabel->setMovie(_loadingGif);

    _loadingAnimation = new WidgetAnimation(_loadingLabel, WidgetAnimation::Opacity);

    _loadingLabel->setScaledContents(true);
    ui->loadingLabel->setMovie(_loadingGif);
    _loadingGif->start();
    _loadingAnimation->show();

    //ui->stackedWidget->setCurrentIndex(3);
}

void PrinterWidget::hideLoadingScreen()
{
    if(_loadingGif != nullptr)
    {
        connect(_loadingAnimation, SIGNAL(finished()), this, SLOT(on_loadingAnimation_finished()));
        _loadingAnimation->hide();
        //ui->stackedWidget->setCurrentIndex(0);
    }
}


void PrinterWidget::on_restartKlipperButton_clicked()
{
    ui->restartKlipperButton->setEnabled(false);
    ui->restartFirmwareButton->setEnabled(false);
    _printer->console()->restartKlipper();
}

void PrinterWidget::on_loadingAnimation_finished()
{
    _loadingGif->stop();
    delete _loadingGif;
    delete _loadingLabel;
    delete _loadingAnimation;
    _loadingLabel = nullptr;
    _loadingGif = nullptr;
    _loadingAnimation = nullptr;
    on_printer_update(_printer);
}

