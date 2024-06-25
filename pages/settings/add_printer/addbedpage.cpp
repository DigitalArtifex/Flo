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
    ui->bedPowerSpinBox->setValue(m_definition.powerProfile[QString("bed")]);
}

void AddBedPage::apply()
{
    m_definition.powerProfile[QString("bed")] = ui->bedPowerSpinBox->value();

    qDebug() << "Bed page " << m_definition.powerProfile;
}

void AddBedPage::on_heatedBedCheckbox_stateChanged(int arg1)
{
    ui->bedPowerSpinBox->setEnabled((bool)arg1);
}

PrinterDefinition AddBedPage::definition() const
{
    return m_definition;
}

void AddBedPage::setDefinition(PrinterDefinition definition)
{
    m_definition = definition;
}

bool AddBedPage::validate()
{
    apply();
    return true;
}

