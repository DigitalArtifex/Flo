#include "addbedpage.h"
#include "ui_addbedpage.h"

AddBedPage::AddBedPage(QWidget *parent)
    : QWizardPage(parent)
    , ui(new Ui::AddBedPage)
{
    ui->setupUi(this);
}

AddBedPage::~AddBedPage()
{
    delete ui;
}

void AddBedPage::reset()
{
    ui->bedPowerSpinBox->setValue(_definition.powerProfile[QString("bed")]);
}

void AddBedPage::apply()
{
    _definition.powerProfile[QString("bed")] = ui->bedPowerSpinBox->value();
}

void AddBedPage::on_heatedBedCheckbox_stateChanged(int arg1)
{
    ui->bedPowerSpinBox->setEnabled((bool)arg1);
}

PrinterDefinition AddBedPage::definition() const
{
    return _definition;
}

void AddBedPage::setDefinition(PrinterDefinition definition)
{
    _definition = definition;
}

bool AddBedPage::validate()
{
    apply();
    return true;
}

