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

    _bedPage = new AddBedPage(this);
    addPage(_bedPage);

    _validatePage = new ValidatePrinterPage(this);
    this->addPage(_validatePage);
}

AddPrinterWizard::~AddPrinterWizard()
{
    delete _addPage;
    delete _extruderPage;
    delete _bedPage;
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
            _bedPage->setDefinition(_definition);
        }
        else if(currentId() == 2)
        {
            _definition = _bedPage->definition();
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

