#include "printerwidget.h"
#include "ui_printerwidget.h"

#include "flo/settings.h"

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

void PrinterWidget::setPrinter(QKlipperInstance *printer)
{
    //set the instance
    m_instance = printer;

    //update the gui
    onInstanceNameChanged();
    onPrinterStatusChanged();
    onPrinterPrintEndingChanged();

    //connect to signals
    connect(m_instance,SIGNAL(nameChanged()),this, SLOT(onInstanceNameChanged()));
    connect(m_instance->printer(),SIGNAL(statusChanged()),this, SLOT(onPrinterStatusChanged()));
    connect(m_instance->printer(),SIGNAL(statusMessageChanged()),this, SLOT(onPrinterStatusMessageChanged()));
    connect(m_instance->printer(),SIGNAL(printEndingChanged()),this, SLOT(onPrinterPrintEndingChanged()));
}

QKlipperInstance *PrinterWidget::printer()
{
    return m_instance;
}

void PrinterWidget::setUiClasses()
{
    setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "Widget" << "PrinterWidget" ));

    ui->menuPage->layout()->addItem(new QSpacerItem(0, 0, QSizePolicy::Ignored, QSizePolicy::Expanding));

    m_cancelPrintButton = new QIconButton(ui->menuPage);
    m_cancelPrintButton->setText("Cancel Print");
    m_cancelPrintButton->setFixedSize(200, 35);
    m_cancelPrintButton->setIcon(Settings::getThemeIcon("stop"));
    ui->menuPage->layout()->addWidget(m_cancelPrintButton);

    m_pausePrintButton = new QIconButton(ui->menuPage);
    m_pausePrintButton->setText("Resume Print");
    m_pausePrintButton->setFixedSize(200, 35);
    m_pausePrintButton->setIcon(Settings::getThemeIcon("pause"));
    ui->menuPage->layout()->addWidget(m_pausePrintButton);

    ui->menuPage->layout()->addItem(new QSpacerItem(0, 0, QSizePolicy::Ignored, QSizePolicy::Expanding));

    m_restartFirmwareButton = new QIconButton(ui->menuPage);
    m_restartFirmwareButton->setText("Restart Firmware");
    m_restartFirmwareButton->setFixedSize(200, 35);
    m_restartFirmwareButton->setIcon(Settings::getThemeIcon("firmware"));
    ui->menuPage->layout()->addWidget(m_restartFirmwareButton);

    m_restartKlipperButton = new QIconButton(ui->menuPage);
    m_restartKlipperButton->setText("Restart Klipper");
    m_restartKlipperButton->setFixedSize(200, 35);
    m_restartKlipperButton->setIcon(Settings::getThemeIcon("restart"));
    ui->menuPage->layout()->addWidget(m_restartKlipperButton);

    ui->menuPage->layout()->addItem(new QSpacerItem(0, 0, QSizePolicy::Ignored, QSizePolicy::Expanding));
}

void PrinterWidget::setStyleSheet(QString styleSheet)
{
    QPixmap pixmap;

    onPrinterStatusChanged();

    ui->quickActionButton->setIcon(Settings::getThemeIcon("menu"));
    QFrame::setStyleSheet(styleSheet);
}

void PrinterWidget::on_printer_klipperDisconnected(QKlipperInstance *printer)
{
    Q_UNUSED(printer)
    showLoadingScreen();
}

void PrinterWidget::on_printer_klipperConnected(QKlipperInstance *printer)
{
    Q_UNUSED(printer)
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
    if(checked && m_instance->printer()->status() == QKlipperPrinter::Printing)
    {
        m_instance->printer()->pause();
        m_pausePrintButton->setText(QString("Resume Print"));
        m_pausePrintButton->setIcon(Settings::getThemeIcon("resume"));
    }
    else if(m_instance->printer()->status() == QKlipperPrinter::Paused)
    {
        m_instance->printer()->resume();
        m_pausePrintButton->setText(QString("Pause Print"));
        m_pausePrintButton->setIcon(Settings::getThemeIcon("pause"));
    }
}

void PrinterWidget::showLoadingScreen()
{
    if(m_loadingGif != nullptr)
        m_loadingGif->deleteLater();
    if(m_loadingLabel != nullptr)
        m_loadingLabel->deleteLater();

    setGraphicsEffect(nullptr);

    m_loadingGif = new QMovie(":/images/loading_widget.gif");
    m_loadingLabel = new QLabel(this);
    m_loadingLabel->setMinimumWidth(this->width());
    m_loadingLabel->setMinimumHeight(this->height());
    m_loadingLabel->show();
    m_loadingLabel->activateWindow();
    m_loadingLabel->raise();
    m_loadingLabel->setMovie(m_loadingGif);

    m_loadingLabel->setScaledContents(true);
    ui->loadingLabel->setMovie(m_loadingGif);
    m_loadingGif->start();
    on_loadingAnimation_finished();
}

void PrinterWidget::hideLoadingScreen()
{
}


void PrinterWidget::on_restartKlipperButton_clicked()
{
    m_restartKlipperButton->setEnabled(false);
    m_restartFirmwareButton->setEnabled(false);
    m_instance->printer()->console()->restartKlipper();
}

void PrinterWidget::on_loadingAnimation_finished()
{
    m_loadingGif->stop();

    if(m_loadingGif)
    {
        m_loadingGif->deleteLater();
        m_loadingGif = nullptr;
    }

    if(m_loadingLabel)
    {
        m_loadingLabel->deleteLater();
        m_loadingLabel = nullptr;
    }
}


void PrinterWidget::on_restartFirmwareButton_clicked()
{
    m_restartKlipperButton->setEnabled(false);
    m_restartFirmwareButton->setEnabled(false);
    m_instance->printer()->console()->restartFirmware();
}

void PrinterWidget::onPrinterStatusChanged()
{
    QString statusText;
    QPixmap pixmap;
    QColor color;

    switch(m_instance->printer()->status())
    {
    case QKlipperPrinter::Printing:
        statusText = QString("Printing");
        m_pausePrintButton->setEnabled(true);
        m_cancelPrintButton->setEnabled(true);
        m_restartFirmwareButton->setEnabled(true);
        m_restartKlipperButton->setEnabled(true);

        color = QColor::fromString(Settings::get("theme/icon-warning-color").toString());

        pixmap = Settings::getThemeIcon(QString("printer"), color).pixmap(64,64);
        this->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "Widget" << "PrinterWidget" << "Printing" ));
        break;
    case QKlipperPrinter::Cancelled:
        statusText = QString("Cancelled");
        m_pausePrintButton->setEnabled(true);
        m_cancelPrintButton->setEnabled(false);
        m_restartFirmwareButton->setEnabled(true);
        m_restartKlipperButton->setEnabled(true);

        color = QColor::fromString(Settings::get("theme/icon-error-color").toString());

        pixmap = Settings::getThemeIcon(QString("printer-error"), color).pixmap(64,64);
        this->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "Widget" << "PrinterWidget" << "Cancelled" ));
        break;
    case QKlipperPrinter::Paused:
        statusText = QString("Paused");
        m_pausePrintButton->setEnabled(true);
        m_cancelPrintButton->setEnabled(true);
        m_restartFirmwareButton->setEnabled(true);
        m_restartKlipperButton->setEnabled(true);

        color = QColor::fromString(Settings::get("theme/icon-warning-color").toString());

        pixmap = Settings::getThemeIcon(QString("printer"), color).pixmap(64,64);
        this->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "Widget" << "PrinterWidget" << "Paused" ));
        break;
    case QKlipperPrinter::Error:
        statusText = QString("Error");
        m_pausePrintButton->setEnabled(false);
        m_cancelPrintButton->setEnabled(false);
        m_restartFirmwareButton->setEnabled(true);
        m_restartKlipperButton->setEnabled(true);

        color = QColor::fromString(Settings::get("theme/icon-error-color").toString());

        pixmap = Settings::getThemeIcon(QString("printer-error"), color).pixmap(64,64);
        this->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "Widget" << "PrinterWidget" << "Error" ));
        break;
    case QKlipperPrinter::Ready:
        statusText = QString("Ready");
        m_pausePrintButton->setEnabled(false);
        m_cancelPrintButton->setEnabled(false);
        m_restartFirmwareButton->setEnabled(true);
        m_restartKlipperButton->setEnabled(true);
        pixmap = Settings::getThemeIcon(QString("printer")).pixmap(64,64);
        this->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "Widget" << "PrinterWidget" << "Ready" ));
        break;
    case QKlipperPrinter::Connecting:
        statusText = QString("Connecting");
        m_pausePrintButton->setEnabled(false);
        m_cancelPrintButton->setEnabled(false);
        m_restartFirmwareButton->setEnabled(true);
        m_restartKlipperButton->setEnabled(true);

        color = QColor::fromString(Settings::get("theme/icon-disabled-color").toString());

        pixmap = Settings::getThemeIcon(QString("printer"), color).pixmap(64,64);
        this->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "Widget" << "PrinterWidget" << "Offline" ));
        break;
    case QKlipperPrinter::Offline:
    default:
        statusText = QString("Offline");
        m_pausePrintButton->setEnabled(false);
        m_cancelPrintButton->setEnabled(false);
        m_restartFirmwareButton->setEnabled(true);
        m_restartKlipperButton->setEnabled(true);

        color = QColor::fromString(Settings::get("theme/icon-disabled-color").toString());

        pixmap = Settings::getThemeIcon(QString("printer-no-connection"), color).pixmap(64,64);
        this->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "Widget" << "PrinterWidget" << "Offline" ));
        break;
    }

    ui->statusButton->setText(QString("Status: ") + statusText);
    ui->statusMessageEdit->setText(m_instance->printer()->statusMessage());
    ui->iconLabel->setPixmap(pixmap);
}

void PrinterWidget::onInstanceNameChanged()
{
    ui->nameLabel->setText(m_instance->name());
}

void PrinterWidget::onPrinterPrintEndingChanged()
{
    if(m_instance->printer()->status() == QKlipperPrinter::Printing)
        ui->etaLabel->setText(QString("ETA: ") + m_instance->printer()->printEnding().toString());
}

void PrinterWidget::onPrinterStatusMessageChanged()
{
    ui->statusMessageEdit->setText(m_instance->printer()->statusMessage());
}
