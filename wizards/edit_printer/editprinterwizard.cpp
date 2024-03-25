#include "editprinterwizard.h"
#include "ui_editprinterwizard.h"

EditPrinterWizard::EditPrinterWizard(QWidget *parent) :
    QWizard(parent),
    ui(new Ui::EditPrinterWizard)
{
    ui->setupUi(this);
}

EditPrinterWizard::~EditPrinterWizard()
{
    delete ui;
}
