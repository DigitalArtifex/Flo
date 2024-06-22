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
    m_printerListWidget = new PrinterListWidget();
    ui->printerListLayout->addWidget(m_printerListWidget);
    updatePrinterList();

    m_themeSettingsPage = new ThemeSettingsPage(this);

    ui->tabWidget->setTabVisible(0, false);
    ui->tabWidget->setTabVisible(1, false);
    ui->tabWidget->setTabVisible(2, false);
    ui->tabWidget->setCurrentIndex(0);

    ui->themeTab->setLayout(new QVBoxLayout());
    ui->themeTab->layout()->setContentsMargins(0,0,0,0);
    ui->themeTab->layout()->setSpacing(0);
    ui->themeTab->layout()->addWidget(m_themeSettingsPage);

    connect(m_printerListWidget, SIGNAL(itemSelected(PrinterListItem*)), this, SLOT(on_printerListWidget_itemSelected(PrinterListItem*)));
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
        m_printerListWidget->addItem(printer);
    }
}

void SettingsPage::on_addPrinterButton_clicked()
{
    if(m_addPrinterWizard == nullptr)
    {
        m_addPrinterWizard = new AddPrinterWizard(this);
        connect(m_addPrinterWizard, SIGNAL(finished(int)), this, SLOT(on_addPrinterWizardFinished(int)));
        connect(m_addPrinterWizard, SIGNAL(rejected()), this, SLOT(on_addPrinterWizardCancelled()));
    }

    m_addPrinterWizard->show();
}

void SettingsPage::on_addPrinterWizardFinished(int result)
{
    PrinterDefinition definition = m_addPrinterWizard->definition();
    PrinterPool::addPrinter(definition);
    updatePrinterList();

    delete m_addPrinterWizard;
    m_addPrinterWizard = nullptr;
    emit(printerAdded(definition));
}

void SettingsPage::on_addPrinterWizardCancelled()
{
    delete m_addPrinterWizard;
    m_addPrinterWizard = nullptr;
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
    if(m_printerListWidget->selectedItem() != nullptr)
    {
        ui->editPrinterButton->setEnabled(false);
        ui->removePrinterButton->setEnabled(false);
        PrinterDefinition definition = m_printerListWidget->selectedItem()->printerDefinition();
        PrinterPool::removePrinter(definition);
    }
}


void SettingsPage::on_editPrinterButton_clicked()
{
    if(!m_editPrinterDialog)
    {
        m_editPrinterDialog = new EditPrinterDialog();
        connect(m_addPrinterWizard, SIGNAL(finished(int)), this, SLOT(on_addPrinterWizardFinished(int)));
        connect(m_addPrinterWizard, SIGNAL(rejected()), this, SLOT(on_addPrinterWizardCancelled()));
    }

    Printer *printer = PrinterPool::getPrinterById(m_printerListWidget->selectedItem()->printerDefinition().id);

    m_editPrinterDialog->setPrinter(printer);
    m_editPrinterDialog->show();
}


void SettingsPage::on_printersButton_toggled(bool checked)
{
    if(checked)
        ui->tabWidget->setCurrentIndex(0);
}


void SettingsPage::on_themeButton_toggled(bool checked)
{
    if(checked)
        ui->tabWidget->setCurrentIndex(1);
}


void SettingsPage::on_systemButton_toggled(bool checked)
{
    if(checked)
        ui->tabWidget->setCurrentIndex(2);
}

