#include "printerofflinescreen.h"
#include "ui_printerofflinescreen.h"

#include "../../../system/settings.h"

PrinterOfflineScreen::PrinterOfflineScreen(QKlipperInstance *printer, QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::PrinterOfflineScreen)
{
    ui->setupUi(this);

    m_instance = printer;
    connect(printer->console(), SIGNAL(startupSequenceProgressChanged()), this, SLOT(printerConnectingProgressChanged()));
    connect(printer->console(), SIGNAL(startupSequenceTextChanged()), this, SLOT(printerConnectingTextChanged()));
    connect(printer->console(), SIGNAL(connectionStateChanged()), this, SLOT(printerConnectingEvent()));

    setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "PopupOverlay"));

    QPixmap pixmap = Settings::getThemeIcon(QString("no-connection-icon")).pixmap(100,100);
    ui->printerOfflineIcon->setPixmap(pixmap);

    m_connectButton = new QIconButton(this);
    m_connectButton->setFixedHeight(50);
    m_connectButton->setIcon(Settings::getThemeIcon(QString("connect-icon")));
    m_connectButton->setText(QString("Connect to ") + printer->name());
    m_connectButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    connect(m_connectButton, SIGNAL(clicked()), this, SLOT(onConnectPrinterButtonPressed()));

    ui->gridLayout->removeWidget(ui->progressBar);
    ui->gridLayout->addWidget(m_connectButton, ui->gridLayout->rowCount(), 0, 1, 3);
    ui->gridLayout->addWidget(ui->progressBar, ui->gridLayout->rowCount(), 0, 1, 3);
    ui->progressBar->setVisible(false);
    ui->progressBar->setValue(0);
}

PrinterOfflineScreen::~PrinterOfflineScreen()
{
    delete ui;
}

void PrinterOfflineScreen::setStyleSheet(QString &styleSheet)
{
    QPixmap pixmap = Settings::getThemeIcon(QString("no-connection-icon")).pixmap(100,100);
    ui->printerOfflineIcon->setPixmap(pixmap);

    m_connectButton->setIcon(Settings::getThemeIcon(QString("connect-icon")));

    QFrame::setStyleSheet(styleSheet);
}

void PrinterOfflineScreen::setText(const QString &text)
{
    ui->label->setText(text);
}

void PrinterOfflineScreen::setIcon(const QIcon &icon)
{
    m_icon = icon;
    ui->printerOfflineIcon->setPixmap(m_icon.pixmap(ui->printerOfflineIcon->size()));
}

void PrinterOfflineScreen::printerConnectingEvent()
{
    if(m_instance->console()->hasConnectionState(QKlipperConsole::Syncronized))
    {
        m_connectButton->setVisible(false);
        ui->progressBar->setVisible(false);

        if(isVisible())
            hide();
    }
    else if(m_instance->console()->hasConnectionState(QKlipperConsole::Connecting))
    {
        m_connectButton->setVisible(false);
        ui->progressBar->setVisible(true);

        if(!isVisible())
            show();
    }
}

void PrinterOfflineScreen::printerConnectingProgressChanged()
{
    int progress = ((int)(m_instance->console()->startupSequenceProgress() * 100));
    ui->progressBar->setValue(progress);
}

void PrinterOfflineScreen::printerConnectingTextChanged()
{
    ui->label->setText(m_instance->console()->startupSequenceText());
}

void PrinterOfflineScreen::onConnectPrinterButtonPressed()
{
    if(m_instance && !m_instance->isConnected())
    {
        m_connectButton->setEnabled(false);
        m_connectButton->setText("Connecting");
        m_instance->connect();
        ui->progressBar->setValue(0);
    }
}
