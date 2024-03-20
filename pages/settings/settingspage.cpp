 #include "settingspage.h"
#include "ui_settingspage.h"
#include "../../settings.h"
#include "printerlistitem.h"

SettingsPage::SettingsPage(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::SettingsPage)
{
    ui->setupUi(this);
    _printerListWidget = new PrinterListWidget();
    ui->printerListLayout->addWidget(_printerListWidget);
    updatePrinterList();
}

SettingsPage::~SettingsPage()
{
    delete ui;
}

void SettingsPage::updatePrinterList()
{
    PrinterDefinitionList printers = Settings::printers();

    foreach(PrinterDefinition printer, printers)
    {
        PrinterListItem *item = new PrinterListItem();
        item->setPrinterDefinition(printer);
        item->setMinimumHeight(50);
        _printerListWidget->addItem(item);
    }
}

void SettingsPage::on_addPrinterButton_clicked()
{
    if(_addPrinterWizard == nullptr)
    {
        _addPrinterWizard = new AddPrinterWizard(this);
        connect(_addPrinterWizard, SIGNAL(finished(int)), this, SLOT(on_addPrinterWizardFinished(int)));
        connect(_addPrinterWizard, SIGNAL(rejected()), this, SLOT(on_addPrinterWizardCancelled()));
    }

    _addPrinterWizard->show();
}

void SettingsPage::on_addPrinterWizardFinished(int result)
{
    PrinterDefinition definition = _addPrinterWizard->definition();
    Settings::addPrinter(definition);
    updatePrinterList();

    delete _addPrinterWizard;
    _addPrinterWizard = nullptr;
}

void SettingsPage::on_addPrinterWizardCancelled()
{
    delete _addPrinterWizard;
    _addPrinterWizard = nullptr;
}
