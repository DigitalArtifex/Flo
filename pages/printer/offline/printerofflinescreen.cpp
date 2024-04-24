#include "printerofflinescreen.h"
#include "ui_printerofflinescreen.h"

#include "../../../system/settings.h"

PrinterOfflineScreen::PrinterOfflineScreen(QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::PrinterOfflineScreen)
{
    ui->setupUi(this);

    setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "PopupOverlay"));

    QPixmap pixmap = Settings::getThemeIcon(QString("no-connection-icon")).pixmap(64,64);
    ui->printerOfflineIcon->setPixmap(pixmap);
}

PrinterOfflineScreen::~PrinterOfflineScreen()
{
    delete ui;
}

void PrinterOfflineScreen::setStyleSheet(QString &styleSheet)
{
    QFrame::setStyleSheet(styleSheet);
}
