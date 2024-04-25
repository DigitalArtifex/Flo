#include "addprinterwizard.h"
#include "ui_addprinterwizard.h"

#include "../../../system/settings.h"

AddPrinterWizard::AddPrinterWizard(QWidget *parent) :
    QWizard(parent),
    ui(new Ui::AddPrinterWizard)
{
    ui->setupUi(this);

    _printer = new Printer();

    _addPage = new AddPrinterPage(this);
    this->addPage(_addPage);

    _extruderPage = new AddExtrudersPage(this);
    addPage(_extruderPage);

    _validatePage = new ValidatePrinterPage(this);
    this->addPage(_validatePage);
}

AddPrinterWizard::~AddPrinterWizard()
{
    delete _addPage;
    delete _extruderPage;
    delete _validatePage;

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
            _extruderPage->setDefinition(_definition);
        }
        else if(currentId() == 1)
        {
            _definition = _extruderPage->definition();
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

