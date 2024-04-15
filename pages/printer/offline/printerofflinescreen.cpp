#include "printerofflinescreen.h"
#include "ui_printerofflinescreen.h"

#include "../../../system/settings.h"

PrinterOfflineScreen::PrinterOfflineScreen(QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::PrinterOfflineScreen)
{
    ui->setupUi(this);

    setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "Page"));
}

PrinterOfflineScreen::~PrinterOfflineScreen()
{
    delete ui;
}
