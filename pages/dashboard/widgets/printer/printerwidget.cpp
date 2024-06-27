#include "printerwidget.h"
#include "ui_printerwidget.h"

#include "../../../../system/settings.h"

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
    m_printer = printer;
    connect(m_printer,SIGNAL(printerUpdate(Printer*)),this, SLOT(on_printer_update(Printer*)));
    connect(m_printer,SIGNAL(klipperConnected(Printer*)),this, SLOT(on_printer_klipperConnected(Printer*)));
    connect(m_printer,SIGNAL(klipperDisconnected(Printer*)),this, SLOT(on_printer_klipperDisconnected(Printer*)));
    on_printer_update(printer);
}

Printer *PrinterWidget::printer()
{
    return m_printer;
}

void PrinterWidget::setUiClasses()
{
    this->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "DashboardWidget" << "PrinterWidget" ));
}

void PrinterWidget::setStyleSheet(QString styleSheet)
{
    QFrame::setStyleSheet(styleSheet);
    QPixmap pixmap;

    if(m_printer == nullptr)
        pixmap = Settings::getThemeIcon("printer-icon").pixmap(ui->iconLabel->size());
    else
    {
        switch(m_printer->status())
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
    ui->nameLabel->setText(m_printer->name());
    ui->etaLabel->setText(QString("ETA: ") + m_printer->printEndTime().toString());

    QString statusText;
    QPixmap pixmap;

    switch(m_printer->status())
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
        ui->pausePrintButton->setEnabled(false);
        ui->cancelPrintButton->setEnabled(false);
        ui->restartFirmwareButton->setEnabled(true);
        ui->restartKlipperButton->setEnabled(true);
        pixmap = Settings::getThemeIcon("printer-ready-icon").pixmap(ui->iconLabel->size());
        this->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "DashboardWidget" << "PrinterWidget" << "Ready" ));
        break;
    case Printer::Offline:
        statusText = QString("Offline");
        ui->pausePrintButton->setEnabled(false);
        ui->cancelPrintButton->setEnabled(false);
        ui->restartFirmwareButton->setEnabled(true);
        ui->restartKlipperButton->setEnabled(true);
        pixmap = Settings::getThemeIcon("printer-offline-icon").pixmap(ui->iconLabel->size());
        this->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "DashboardWidget" << "PrinterWidget" << "Offline" ));
        break;
    }

    ui->statusButton->setText(QString("Status: ") + statusText);
    ui->statusMessageEdit->setText(m_printer->statusMessage());
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
    if(checked && m_printer->status() == Printer::Printing)
    {
        m_printer->pause();
        ui->pausePrintButton->setText(QString("Resume Print"));
    }
    else if(m_printer->status() == Printer::Paused)
    {
        m_printer->resume();
        ui->pausePrintButton->setText(QString("Pause Print"));
    }
}

void PrinterWidget::showLoadingScreen()
{
    if(m_loadingGif != nullptr)
        delete m_loadingGif;
    if(m_loadingLabel != nullptr)
        delete m_loadingLabel;
    if(m_loadingAnimation != nullptr)
        delete m_loadingAnimation;

    setGraphicsEffect(nullptr);

    m_loadingGif = new QMovie(":/images/loading_widget.gif");
    m_loadingLabel = new QLabel(this);
    m_loadingLabel->setMinimumWidth(this->width());
    m_loadingLabel->setMinimumHeight(this->height());
    m_loadingLabel->show();
    m_loadingLabel->activateWindow();
    m_loadingLabel->raise();
    m_loadingLabel->setMovie(m_loadingGif);

    m_loadingAnimation = new WidgetAnimation(m_loadingLabel, WidgetAnimation::Opacity);

    m_loadingLabel->setScaledContents(true);
    ui->loadingLabel->setMovie(m_loadingGif);
    m_loadingGif->start();
    m_loadingAnimation->show();
}

void PrinterWidget::hideLoadingScreen()
{
    if(m_loadingGif != nullptr)
    {
        connect(m_loadingAnimation, SIGNAL(finished()), this, SLOT(on_loadingAnimation_finished()));
        m_loadingAnimation->hide();
    }
}


void PrinterWidget::on_restartKlipperButton_clicked()
{
    ui->restartKlipperButton->setEnabled(false);
    ui->restartFirmwareButton->setEnabled(false);
    m_printer->console()->restartKlipper();
}

void PrinterWidget::on_loadingAnimation_finished()
{
    m_loadingGif->stop();

    if(m_loadingGif)
    {
        delete m_loadingGif;
        m_loadingGif = nullptr;
    }

    if(m_loadingLabel)
    {
        delete m_loadingLabel;
        m_loadingLabel = nullptr;
    }

    if(m_loadingAnimation)
    {
        delete m_loadingAnimation;
        m_loadingAnimation = nullptr;
    }

    on_printer_update(m_printer);
}


void PrinterWidget::on_restartFirmwareButton_clicked()
{
    ui->restartKlipperButton->setEnabled(false);
    ui->restartFirmwareButton->setEnabled(false);
    m_printer->console()->restartFirmware();
}

