#include "printerupdatingscreen.h"
#include "ui_printerupdatingscreen.h"

PrinterUpdatingScreen::PrinterUpdatingScreen(QKlipperUpdateManager *manager, QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::PrinterUpdatingScreen)
{
    ui->setupUi(this);
    m_manager = manager;
    connect(manager, SIGNAL(currentStateMessageChanged()), this, SLOT(onUpdateSystemStateTextChanged()));
}

PrinterUpdatingScreen::~PrinterUpdatingScreen()
{
    delete ui;
}

void PrinterUpdatingScreen::onUpdateSystemStateTextChanged()
{
    ui->throbberWidget->setText(QString("Updating"));
    ui->textEdit->append(m_manager->currentStateMessage());
}
