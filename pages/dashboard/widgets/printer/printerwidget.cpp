#include "printerwidget.h"
#include "ui_printerwidget.h"

#include "system/settings.h"

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
    setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "DashboardWidget" << "PrinterWidget" ));

    ui->menuPage->layout()->addItem(new QSpacerItem(0, 0, QSizePolicy::Ignored, QSizePolicy::Expanding));

    m_cancelPrintButton = new QIconButton(ui->menuPage);
    m_cancelPrintButton->setText("Cancel Print");
    m_cancelPrintButton->setFixedSize(200, 35);
    m_cancelPrintButton->setPixmap(Settings::getThemeIcon("stop-icon").pixmap(16,16));
    ui->menuPage->layout()->addWidget(m_cancelPrintButton);

    m_pausePrintButton = new QIconButton(ui->menuPage);
    m_pausePrintButton->setText("Resume Print");
    m_pausePrintButton->setFixedSize(200, 35);
    m_pausePrintButton->setPixmap(Settings::getThemeIcon("pause-icon").pixmap(16,16));
    ui->menuPage->layout()->addWidget(m_pausePrintButton);

    ui->menuPage->layout()->addItem(new QSpacerItem(0, 0, QSizePolicy::Ignored, QSizePolicy::Expanding));

    m_restartFirmwareButton = new QIconButton(ui->menuPage);
    m_restartFirmwareButton->setText("Restart Firmware");
    m_restartFirmwareButton->setFixedSize(200, 35);
    m_restartFirmwareButton->setPixmap(Settings::getThemeIcon("firmware-icon").pixmap(16,16));
    ui->menuPage->layout()->addWidget(m_restartFirmwareButton);

    m_restartKlipperButton = new QIconButton(ui->menuPage);
    m_restartKlipperButton->setText("Restart Klipper");
    m_restartKlipperButton->setFixedSize(200, 35);
    m_restartKlipperButton->setPixmap(Settings::getThemeIcon("restart-icon").pixmap(16,16));
    ui->menuPage->layout()->addWidget(m_restartKlipperButton);

    ui->menuPage->layout()->addItem(new QSpacerItem(0, 0, QSizePolicy::Ignored, QSizePolicy::Expanding));
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
        m_pausePrintButton->setEnabled(true);
        m_cancelPrintButton->setEnabled(true);
        m_restartFirmwareButton->setEnabled(true);
        m_restartKlipperButton->setEnabled(true);
        pixmap = Settings::getThemeIcon("printer-printing-icon").pixmap(ui->iconLabel->size());
        this->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "DashboardWidget" << "PrinterWidget" << "Printing" ));
        break;
    case Printer::Cancelled:
        statusText = QString("Cancelled");
        m_pausePrintButton->setEnabled(true);
        m_cancelPrintButton->setEnabled(false);
        m_restartFirmwareButton->setEnabled(true);
        m_restartKlipperButton->setEnabled(true);
        pixmap = Settings::getThemeIcon("printer-error-icon").pixmap(ui->iconLabel->size());
        this->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "DashboardWidget" << "PrinterWidget" << "Cancelled" ));
        break;
    case Printer::Paused:
        statusText = QString("Paused");
        m_pausePrintButton->setEnabled(true);
        m_cancelPrintButton->setEnabled(true);
        m_restartFirmwareButton->setEnabled(true);
        m_restartKlipperButton->setEnabled(true);
        pixmap = Settings::getThemeIcon("printer-paused-icon").pixmap(ui->iconLabel->size());
        this->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "DashboardWidget" << "PrinterWidget" << "Paused" ));
        break;
    case Printer::Error:
        statusText = QString("Error");
        m_pausePrintButton->setEnabled(false);
        m_cancelPrintButton->setEnabled(false);
        m_restartFirmwareButton->setEnabled(true);
        m_restartKlipperButton->setEnabled(true);
        pixmap = Settings::getThemeIcon("printer-error-icon").pixmap(ui->iconLabel->size());
        this->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "DashboardWidget" << "PrinterWidget" << "Error" ));
        break;
    case Printer::Ready:
        statusText = QString("Ready");
        m_pausePrintButton->setEnabled(false);
        m_cancelPrintButton->setEnabled(false);
        m_restartFirmwareButton->setEnabled(true);
        m_restartKlipperButton->setEnabled(true);
        pixmap = Settings::getThemeIcon("printer-ready-icon").pixmap(ui->iconLabel->size());
        this->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "DashboardWidget" << "PrinterWidget" << "Ready" ));
        break;
    case Printer::Offline:
        statusText = QString("Offline");
        m_pausePrintButton->setEnabled(false);
        m_cancelPrintButton->setEnabled(false);
        m_restartFirmwareButton->setEnabled(true);
        m_restartKlipperButton->setEnabled(true);
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
        m_pausePrintButton->setText(QString("Resume Print"));
        m_pausePrintButton->setPixmap(Settings::getThemeIcon("resume-icon").pixmap(16,16));
    }
    else if(m_printer->status() == Printer::Paused)
    {
        m_printer->resume();
        m_pausePrintButton->setText(QString("Pause Print"));
        m_pausePrintButton->setPixmap(Settings::getThemeIcon("pause-icon").pixmap(16,16));
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
    m_restartKlipperButton->setEnabled(false);
    m_restartFirmwareButton->setEnabled(false);
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
    m_restartKlipperButton->setEnabled(false);
    m_restartFirmwareButton->setEnabled(false);
    m_printer->console()->restartFirmware();
}

