#include "addprinterwizard.h"
#include "ui_addprinterwizard.h"

#include "../../../system/settings.h"

AddPrinterWizard::AddPrinterWizard(QWidget *parent) :
    QWizard(parent),
    ui(new Ui::AddPrinterWizard)
{
    ui->setupUi(this);

    m_printer = new Printer();

    m_addPage = new AddPrinterPage(this);
    this->addPage(m_addPage);

    m_extruderPage = new AddExtrudersPage(this);
    addPage(m_extruderPage);

    m_bedPage = new AddBedPage(this);
    addPage(m_bedPage);

    m_validatePage = new ValidatePrinterPage(this);
    this->addPage(m_validatePage);
}

AddPrinterWizard::~AddPrinterWizard()
{
    delete m_addPage;
    delete m_extruderPage;
    delete m_bedPage;
    delete m_validatePage;

    delete ui;
}

bool AddPrinterWizard::validateCurrentPage()
{
    bool valid = QWizard::validateCurrentPage();

    if(valid)
    {
        if(currentId() == 0)
        {
            m_definition = m_addPage->definition();
            m_extruderPage->setDefinition(m_definition);
        }
        else if(currentId() == 1)
        {
            m_extruderPage->apply();
            m_definition = m_extruderPage->definition();
            m_bedPage->setDefinition(m_definition);
        }
        else if(currentId() == 2)
        {
            m_bedPage->apply();
            m_definition = m_bedPage->definition();
            m_validatePage->setDefinition(m_definition);
        }
    }

    return valid;
}

PrinterDefinition AddPrinterWizard::definition()
{
    m_definition = m_validatePage->definition();
    return m_definition;
}

void AddPrinterWizard::next()
{
}

