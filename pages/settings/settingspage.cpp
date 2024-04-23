#include "settingspage.h"
#include "ui_settingspage.h"
#include "../../system/settings.h"
#include "printerlistitem.h"

#include "../../system/printerpool.h"

SettingsPage::SettingsPage(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::SettingsPage)
{
    ui->setupUi(this);
    _printerListWidget = new PrinterListWidget();
    ui->printerListLayout->addWidget(_printerListWidget);
    updatePrinterList();

    connect(_printerListWidget, SIGNAL(itemSelected(PrinterListItem*)), this, SLOT(on_printerListWidget_itemSelected(PrinterListItem*)));
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
        _printerListWidget->addItem(printer);
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
    PrinterPool::addPrinter(definition);
    updatePrinterList();

    delete _addPrinterWizard;
    _addPrinterWizard = nullptr;
    emit(printerAdded(definition));
}

void SettingsPage::on_addPrinterWizardCancelled()
{
    delete _addPrinterWizard;
    _addPrinterWizard = nullptr;
}

void SettingsPage::on_printerListWidget_itemSelected(PrinterListItem *item)
{
    if(item != nullptr)
    {
        ui->editPrinterButton->setEnabled(true);
        ui->removePrinterButton->setEnabled(true);
    }
    else
    {
        ui->editPrinterButton->setEnabled(false);
        ui->removePrinterButton->setEnabled(false);
    }
}

void SettingsPage::on_removePrinterButton_clicked()
{
    if(_printerListWidget->selectedItem() != nullptr)
    {
        ui->editPrinterButton->setEnabled(false);
        ui->removePrinterButton->setEnabled(false);
        PrinterDefinition definition = _printerListWidget->selectedItem()->printerDefinition();
        PrinterPool::removePrinter(definition);
    }
}


void SettingsPage::on_editPrinterButton_clicked()
{
    if(!_editPrinterDialog)
    {
        _editPrinterDialog = new EditPrinterDialog();
        connect(_addPrinterWizard, SIGNAL(finished(int)), this, SLOT(on_addPrinterWizardFinished(int)));
        connect(_addPrinterWizard, SIGNAL(rejected()), this, SLOT(on_addPrinterWizardCancelled()));
    }

    Printer *printer = PrinterPool::getPrinterById(_printerListWidget->selectedItem()->printerDefinition().id);

    _editPrinterDialog->setPrinter(printer);
    _editPrinterDialog->show();
}

