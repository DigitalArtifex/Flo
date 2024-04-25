#include "addprinterwizard.h"
#include "ui_addprinterwizard.h"

#include "../../../system/settings.h"

AddPrinterWizard::AddPrinterWizard(QWidget *parent) :
    QWizard(parent),
    ui(new Ui::AddPrinterWizard)
{
    ui->setupUi(this);
    _addPage = new AddPrinterPage(this);
    this->addPage(_addPage);

    _validatePage = new ValidatePrinterPage(this);
    this->addPage(_validatePage);
}

AddPrinterWizard::~AddPrinterWizard()
{
    delete ui;
}

bool AddPrinterWizard::validateCurrentPage()
{
    bool valid = QWizard::validateCurrentPage();
    if(valid)
    {
        if(currentId() == 0)
        {
            _definition = _addPage->definition();
            _validatePage->setDefinition(_definition);
        }
    }
    return valid;
}

PrinterDefinition AddPrinterWizard::definition()
{
    _definition = _validatePage->definition();
    return _definition;
}

void AddPrinterWizard::next()
{
}

