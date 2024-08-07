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
    m_printerListWidget = new PrinterListWidget(this);
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

    QPixmap pixmap = Settings::getThemeIcon("add-icon").pixmap(28,28);
    m_addPrinterButton = new QIconButton(this);
    m_addPrinterButton->setFixedSize(250,50);
    m_addPrinterButton->setText("New Printer");
    m_addPrinterButton->setPixmap(pixmap);
    m_addPrinterButton->setEnabled(true);
    ui->buttonLayout->addWidget(m_addPrinterButton);

    connect(m_addPrinterButton, SIGNAL(clicked()), this, SLOT(addPrinterButtonClickEvent()));

    pixmap = Settings::getThemeIcon("edit-icon").pixmap(28,28);
    m_editPrinterButton = new QIconButton(this);
    m_editPrinterButton->setFixedSize(250,50);
    m_editPrinterButton->setText("Edit Printer");
    m_editPrinterButton->setPixmap(pixmap);
    m_editPrinterButton->setEnabled(false);
    ui->buttonLayout->addWidget(m_editPrinterButton);

    connect(m_editPrinterButton, SIGNAL(clicked()), this, SLOT(editPrinterButtonClickEvent()));

    pixmap = Settings::getThemeIcon("minus-icon").pixmap(28,28);
    m_removePrinterButton = new QIconButton(this);
    m_removePrinterButton->setFixedSize(250,50);
    m_removePrinterButton->setText("Remove Printer");
    m_removePrinterButton->setPixmap(pixmap);
    m_removePrinterButton->setEnabled(false);
    ui->buttonLayout->addWidget(m_removePrinterButton);

    connect(m_removePrinterButton, SIGNAL(clicked()), this, SLOT(removePrinterButtonClickEvent()));

    pixmap = Settings::getThemeIcon("printer-icon").pixmap(28,28);
    m_printersActionButton = new QIconButton(this);
    m_printersActionButton->setFixedSize(250,50);
    m_printersActionButton->setText("Printers");
    m_printersActionButton->setPixmap(pixmap);
    m_printersActionButton->setEnabled(true);
    m_printersActionButton->setCheckable(true);
    m_printersActionButton->setExclusive(true);
    m_printersActionButton->setChecked(true);
    ui->actionBar->layout()->addWidget(m_printersActionButton);

    connect(m_printersActionButton, SIGNAL(clicked()), this, SLOT(printersActionButtonClickEvent()));

    pixmap = Settings::getThemeIcon("theme-icon").pixmap(28,28);
    m_themeActionButton = new QIconButton(this);
    m_themeActionButton->setFixedSize(250,50);
    m_themeActionButton->setText("Themes");
    m_themeActionButton->setPixmap(pixmap);

    m_themeActionButton->setEnabled(true);
    m_themeActionButton->setCheckable(true);
    m_themeActionButton->setExclusive(true);

    ui->actionBar->layout()->addWidget(m_themeActionButton);

    connect(m_themeActionButton, SIGNAL(clicked()), this, SLOT(themeActionButtonClickEvent()));

    ui->actionBar->layout()->addItem(new QSpacerItem(0,0,QSizePolicy::Expanding, QSizePolicy::Fixed));

    pixmap = Settings::getThemeIcon("settings-icon").pixmap(28,28);
    m_systemActionButton = new QIconButton(this);
    m_systemActionButton->setFixedSize(250,50);
    m_systemActionButton->setText("System");
    m_systemActionButton->setPixmap(pixmap);

    m_systemActionButton->setEnabled(true);
    m_systemActionButton->setCheckable(true);
    m_systemActionButton->setExclusive(true);

    ui->actionBar->layout()->addWidget(m_systemActionButton);

    connect(m_systemActionButton, SIGNAL(clicked()), this, SLOT(systemActionButtonClickEvent()));

    connect(m_printerListWidget, SIGNAL(itemSelected(PrinterListItem*)), this, SLOT(printerListWidgetItemSelectedEvent(PrinterListItem*)));

    setProperty("class", "Page");
    ui->actionBar->setProperty("class", "PageActionBar");

    setStyleSheet(Settings::currentTheme());
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

void SettingsPage::printerListWidgetItemSelectedEvent(PrinterListItem *item)
{
    if(item != nullptr)
    {
        m_editPrinterButton->setEnabled(true);
        m_removePrinterButton->setEnabled(true);
    }
    else
    {
        m_editPrinterButton->setEnabled(false);
        m_removePrinterButton->setEnabled(false);
    }
}

void SettingsPage::editPrinterButtonClickEvent()
{
    if(!m_editPrinterDialog)
    {
        m_editPrinterDialog = new EditPrinterDialog(this);
        connect(m_editPrinterDialog, SIGNAL(finished(int)), this, SLOT(on_addPrinterWizardFinished(int)));
    }

    Printer *printer = PrinterPool::getPrinterById(m_printerListWidget->selectedItem()->printerDefinition().id);

    m_editPrinterDialog->setPrinter(printer);
    m_editPrinterDialog->exec();

    delete m_editPrinterDialog;
    m_editPrinterDialog = nullptr;
}

void SettingsPage::addPrinterButtonClickEvent()
{
    if(m_addPrinterWizard == nullptr)
    {
        m_addPrinterWizard = new AddPrinterWizard(this);
        connect(m_addPrinterWizard, SIGNAL(finished(int)), this, SLOT(on_addPrinterWizardFinished(int)));
    }

    int result = m_addPrinterWizard->exec();

    if(result == QDialog::Accepted)
    {
        PrinterDefinition definition = m_addPrinterWizard->definition();
        PrinterPool::addPrinter(definition);
        updatePrinterList();

        emit(printerAdded(definition));
    }

    delete m_addPrinterWizard;
    m_addPrinterWizard = nullptr;
}

void SettingsPage::removePrinterButtonClickEvent()
{
    if(m_printerListWidget->selectedItem() != nullptr)
    {
        m_editPrinterButton->setEnabled(false);
        m_removePrinterButton->setEnabled(false);
        PrinterDefinition definition = m_printerListWidget->selectedItem()->printerDefinition();
        PrinterPool::removePrinter(definition);
        updatePrinterList();
    }
}

void SettingsPage::printersActionButtonClickEvent()
{
    m_themeActionButton->setChecked(false);
    m_systemActionButton->setChecked(false);
    ui->tabWidget->setCurrentIndex(0);
}

void SettingsPage::themeActionButtonClickEvent()
{
    m_printersActionButton->setChecked(false);
    m_systemActionButton->setChecked(false);
    ui->tabWidget->setCurrentIndex(1);
}

void SettingsPage::systemActionButtonClickEvent()
{
    m_printersActionButton->setChecked(false);
    m_themeActionButton->setChecked(false);
    ui->tabWidget->setCurrentIndex(2);
}

