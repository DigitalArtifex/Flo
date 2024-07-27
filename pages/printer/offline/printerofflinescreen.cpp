#include "printerofflinescreen.h"
#include "ui_printerofflinescreen.h"

#include "../../../system/settings.h"

PrinterOfflineScreen::PrinterOfflineScreen(Printer *printer, QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::PrinterOfflineScreen)
{
    ui->setupUi(this);

    connect(printer->console(), SIGNAL(startupProgress(QString,qreal)), this, SLOT(printerConnectingProgressEvent(QString,qreal)));
    connect(printer->console(), SIGNAL(moonrakerConnected()), this, SLOT(printerConnectingEvent()));

    setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "PopupOverlay"));

    QPixmap pixmap = Settings::getThemeIcon(QString("no-connection-icon")).pixmap(64,64);
    ui->printerOfflineIcon->setPixmap(pixmap);

    pixmap = Settings::getThemeIcon(QString("connect-icon")).pixmap(24,24);
    m_connectButton = new QIconButton(this);
    m_connectButton->setFixedHeight(35);
    m_connectButton->setText(QString("Connect to ") + printer->name());
    m_connectButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    ui->gridLayout->removeWidget(ui->progressBar);
    ui->gridLayout->addWidget(m_connectButton, ui->gridLayout->rowCount(), 0, 1, 3);
    ui->gridLayout->addWidget(ui->progressBar, ui->gridLayout->rowCount(), 0, 1, 3);
    ui->progressBar->setVisible(false);
}

PrinterOfflineScreen::~PrinterOfflineScreen()
{
    delete ui;
}

void PrinterOfflineScreen::setStyleSheet(QString &styleSheet)
{
    QFrame::setStyleSheet(styleSheet);
}

void PrinterOfflineScreen::printerConnectingEvent()
{
    m_connectButton->setVisible(false);
    ui->progressBar->setVisible(true);
}

void PrinterOfflineScreen::printerConnectingProgressEvent(QString title, qreal progress)
{
    m_connectButton->setVisible(false);
    ui->progressBar->setVisible(true);

    ui->label->setText(title);
    ui->progressBar->setValue(((int)(progress * 100)));

    qDebug() << progress;
}
