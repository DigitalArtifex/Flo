#include "settingspage.h"
#include "flo/qklipperinstancepool.h"
#include "ui_settingspage.h"
#include "flo/settings.h"
#include "printerlistitem.h"

SettingsPage::SettingsPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingsPage)
{
    ui->setupUi(this);
    m_printerListWidget = new PrinterListWidget(ui->printerTab);
    ui->printerListLayout->addWidget(m_printerListWidget);
    updatePrinterList();

    m_themeSettingsPage = new ThemeSettingsPage(ui->themeTab);

    ui->tabWidget->setTabVisible(0, false);
    ui->tabWidget->setTabVisible(1, false);
    ui->tabWidget->setTabVisible(2, false);
    ui->tabWidget->setCurrentIndex(0);

    ui->themeTab->setLayout(new QVBoxLayout());
    ui->themeTab->layout()->setContentsMargins(0,0,0,0);
    ui->themeTab->layout()->setSpacing(0);
    ui->themeTab->layout()->addWidget(m_themeSettingsPage);

    m_systemSettingsPage = new SystemSettingsPage(ui->systemTab);

    ui->systemTab->setLayout(new QVBoxLayout());
    ui->systemTab->layout()->setContentsMargins(0,0,0,0);
    ui->systemTab->layout()->setSpacing(0);
    ui->systemTab->layout()->addWidget(m_systemSettingsPage);

    m_addPrinterButton = new QIconButton(this);
    m_addPrinterButton->setFixedHeight(50);
    m_addPrinterButton->setText("New Printer");
    m_addPrinterButton->setEnabled(true);
    // ui->buttonLayout->addWidget(m_addPrinterButton);

    connect(m_addPrinterButton, SIGNAL(clicked()), this, SLOT(onAddPrinterButtonClicked()));

    m_editPrinterButton = new QIconButton(this);
    m_editPrinterButton->setFixedHeight(50);
    m_editPrinterButton->setText("Edit");
    m_editPrinterButton->setEnabled(false);
    // ui->buttonLayout->addWidget(m_editPrinterButton);

    connect(m_editPrinterButton, SIGNAL(clicked()), this, SLOT(onEditPrinterButtonClicked()));

    m_removePrinterButton = new QIconButton(this);
    m_removePrinterButton->setFixedSize(250, 50);
    m_removePrinterButton->setText("Remove");
    m_removePrinterButton->setEnabled(false);
    // ui->buttonLayout->addWidget(m_removePrinterButton);

    connect(m_removePrinterButton, SIGNAL(clicked()), this, SLOT(onRemovePrinterButtonClicked()));

    m_printersActionButton = new QIconButton(this);
    m_printersActionButton->setFixedSize(250,50);
    m_printersActionButton->setText("Printers");
    m_printersActionButton->setEnabled(true);
    m_printersActionButton->setCheckable(true);
    m_printersActionButton->setExclusive(true);
    m_printersActionButton->setChecked(true);
    ui->actionBar->layout()->addWidget(m_printersActionButton);

    connect(m_printersActionButton, SIGNAL(clicked()), this, SLOT(printersActionButtonClickEvent()));

    m_themeActionButton = new QIconButton(this);
    m_themeActionButton->setFixedSize(250,50);
    m_themeActionButton->setText("Themes");

    m_themeActionButton->setEnabled(true);
    m_themeActionButton->setCheckable(true);
    m_themeActionButton->setExclusive(true);

    ui->actionBar->layout()->addWidget(m_themeActionButton);

    connect(m_themeActionButton, SIGNAL(clicked()), this, SLOT(themeActionButtonClickEvent()));

    ui->actionBar->layout()->addItem(new QSpacerItem(0,0,QSizePolicy::Expanding, QSizePolicy::Fixed));

    m_systemActionButton = new QIconButton(this);
    m_systemActionButton->setFixedSize(250,50);
    m_systemActionButton->setText("System");

    m_systemActionButton->setEnabled(true);
    m_systemActionButton->setCheckable(true);
    m_systemActionButton->setExclusive(true);

    ui->actionBar->layout()->addWidget(m_systemActionButton);

    connect(m_systemActionButton, SIGNAL(clicked()), this, SLOT(systemActionButtonClickEvent()));

    connect(m_printerListWidget, SIGNAL(itemSelected(PrinterListItem*)), this, SLOT(printerListWidgetItemSelectedEvent(PrinterListItem*)));

    setProperty("class", "Page");
    ui->actionBar->setProperty("class", "PageActionBar");

    //Setup footer buttons
    QGridLayout *layout = (QGridLayout*)ui->footerFrame->layout();
    layout->setContentsMargins(QMargins(9,9,9,0));

    m_resetButton = new QIconButton(ui->footerFrame);
    m_resetButton->setFixedSize(250, 50);
    m_resetButton->setText("Reset");
    layout->addWidget(m_resetButton,0,0);

    // m_footerSpacer = new QSpacerItem(0,0,QSizePolicy::Expanding, QSizePolicy::Ignored);
    // layout->addItem(m_footerSpacer,0,1);

    m_acceptButton = new QIconButton(ui->footerFrame);
    m_acceptButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    m_acceptButton->setFixedHeight(50);
    m_acceptButton->setText("Accept");
    layout->addWidget(m_acceptButton,0,3);

    m_cancelButton = new QIconButton(ui->footerFrame);
    m_cancelButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    m_cancelButton->setFixedHeight(50);
    m_cancelButton->setText("Cancel");
    layout->addWidget(m_cancelButton,0,2);

    connect(m_resetButton, SIGNAL(clicked()), this, SLOT(onResetButtonClicked()));
    connect(m_cancelButton, SIGNAL(clicked()), this, SLOT(onCancelButtonClicked()));
    connect(m_acceptButton, SIGNAL(clicked()), this, SLOT(onApplyButtonClicked()));

    ui->pageContents->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "Page"));
    ui->tabWidget->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "Page"));
    ui->printerTab->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "Page"));
    ui->systemTab->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "Page"));
    ui->themeTab->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "Page"));
    ui->footerFrame->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "Subwidget"));

    setStyleSheet(Settings::currentTheme());

    m_viewer = new QQuickView();
    m_viewerWidget = QWidget::createWindowContainer(m_viewer, this);
    m_viewerWidget->setFixedSize(0,0);
    layout->addWidget(m_viewerWidget);
    m_viewer->show();
    showPrinterButtons();

    connect(this, SIGNAL(dialogRequested(QDialog*)), this, SLOT(onDialogRequested(QDialog*)));
}

SettingsPage::~SettingsPage()
{
    delete ui;
}

void SettingsPage::updatePrinterList()
{
    QKlipperInstanceList printers = QKlipperInstancePool::pool()->klipperInstances();

    foreach(QKlipperInstance *printer, printers)
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

void SettingsPage::onEditPrinterButtonClicked()
{
    if(!m_editPrinterDialog)
        m_editPrinterDialog = new EditPrinterDialog(this);

    QKlipperInstance *printer = m_printerListWidget->selectedItem()->instance();

    m_editPrinterDialog->setPrinter(printer);
    emit dialogRequested(m_editPrinterDialog);
    connect(m_editPrinterDialog, SIGNAL(finished(int)), this, SLOT(onEditPrinterDialogFinished(int)));
}

void SettingsPage::onEditPrinterDialogFinished(int returnCode)
{
    if(returnCode == QDialog::Accepted)
    {
        m_editPrinterDialog->printer()->printer()->setupPowerProfile();
        Settings::save();
    }

    delete m_editPrinterDialog;
    m_editPrinterDialog = nullptr;
}

void SettingsPage::onAddPrinterButtonClicked()
{
    if(!m_editPrinterDialog)
        m_editPrinterDialog = new EditPrinterDialog(this);

    QKlipperInstance *printer = new QKlipperInstance;

    m_editPrinterDialog->setPrinter(printer, true);
    emit dialogRequested(m_editPrinterDialog);
    connect(m_editPrinterDialog, SIGNAL(finished(int)), this, SLOT(onAddPrinterDialogFinished(int)));
}

void SettingsPage::onAddPrinterDialogFinished(int returnCode)
{
    if(returnCode == QDialog::Accepted)
    {
        QKlipperInstancePool::pool()->addInstance(m_editPrinterDialog->printer());
        Settings::save();
    }
    else
    {
        QKlipperInstance *instance = m_editPrinterDialog->printer();
        delete instance;
    }

    delete m_editPrinterDialog;
    m_editPrinterDialog = nullptr;
}

void SettingsPage::onRemovePrinterButtonClicked()
{
    if(m_printerListWidget->selectedItem())
    {
        m_editPrinterButton->setEnabled(false);
        m_removePrinterButton->setEnabled(false);
        QKlipperInstance *instance = m_printerListWidget->selectedItem()->instance();
        Settings::removeInstance(instance);
        QKlipperInstancePool::removeInstance(instance);
        Settings::save();
        updatePrinterList();
    }
}

void SettingsPage::printersActionButtonClickEvent()
{
    m_themeActionButton->setChecked(false);
    m_systemActionButton->setChecked(false);
    ui->tabWidget->setCurrentIndex(0);
    showPrinterButtons();
}

void SettingsPage::themeActionButtonClickEvent()
{
    m_printersActionButton->setChecked(false);
    m_systemActionButton->setChecked(false);
    ui->tabWidget->setCurrentIndex(1);
    showSettingsButtons();
}

void SettingsPage::systemActionButtonClickEvent()
{
    m_printersActionButton->setChecked(false);
    m_themeActionButton->setChecked(false);
    ui->tabWidget->setCurrentIndex(2);
    showSettingsButtons();
}

void SettingsPage::onResetButtonClicked()
{
    reset();
}

void SettingsPage::onCancelButtonClicked()
{
    reset();
}

void SettingsPage::onApplyButtonClicked()
{
    apply();
    Settings::save();
}

void SettingsPage::setupIcons()
{
    m_addPrinterButton->setIcon(Settings::getThemeIcon("printer-add"));
    m_editPrinterButton->setIcon(Settings::getThemeIcon("printer-edit"));
    m_removePrinterButton->setIcon(Settings::getThemeIcon("printer-remove"));
    m_printersActionButton->setIcon(Settings::getThemeIcon("printer"));
    m_systemActionButton->setIcon(Settings::getThemeIcon("settings"));
    m_cancelButton->setIcon(Settings::getThemeIcon("cancel"));
    m_acceptButton->setIcon(Settings::getThemeIcon("accept"));
    m_resetButton->setIcon(Settings::getThemeIcon("refresh"));
    m_themeActionButton->setIcon(Settings::getThemeIcon("theme"));
}

void SettingsPage::showPrinterButtons()
{
    QGridLayout *layout = (QGridLayout*)ui->footerFrame->layout();

    if(!layout)
        return;

    layout->removeWidget(m_cancelButton);
    layout->removeWidget(m_resetButton);
    layout->removeWidget(m_acceptButton);

    m_cancelButton->setVisible(false);
    m_resetButton->setVisible(false);
    m_acceptButton->setVisible(false);

    layout->addWidget(m_removePrinterButton, 0, 0);
    layout->addWidget(m_editPrinterButton, 0, 1);
    layout->addWidget(m_addPrinterButton, 0, 2);

    m_removePrinterButton->setVisible(true);
    m_editPrinterButton->setVisible(true);
    m_addPrinterButton->setVisible(true);
}

void SettingsPage::showSettingsButtons()
{
    QGridLayout *layout = (QGridLayout*)ui->footerFrame->layout();

    if(!layout)
        return;

    layout->removeWidget(m_removePrinterButton);
    layout->removeWidget(m_editPrinterButton);
    layout->removeWidget(m_addPrinterButton);

    m_removePrinterButton->setVisible(false);
    m_addPrinterButton->setVisible(false);
    m_editPrinterButton->setVisible(false);

    layout->addWidget(m_resetButton, 0, 0);
    layout->addWidget(m_cancelButton, 0, 1);
    layout->addWidget(m_acceptButton, 0, 2);

    m_resetButton->setVisible(true);
    m_cancelButton->setVisible(true);
    m_acceptButton->setVisible(true);
}

void SettingsPage::onDialogRequested(QDialog *dialog)
{
    m_requestedDialog = dialog;

    m_dialogSheet = new Sheet(m_requestedDialog, this);
    m_dialogSheet->setWidth(width() / 2);
    m_dialogSheet->showSheet(this);
    connect(dialog, SIGNAL(finished(int)), this, SLOT(onDialogFinished(int)));
}

void SettingsPage::onDialogFinished(int returnCode)
{
    Q_UNUSED(returnCode)

    m_dialogSheet->hideSheet(Settings::get("ui/animations_enabled").toBool());
    disconnect(m_requestedDialog, SIGNAL(finished(int)), this, SLOT(onDialogFinished(int)));
    m_requestedDialog = nullptr;
}

void SettingsPage::onWizardRequested(QWizard *wizard)
{
    // m_requestedWizardReturnIndex = ui->stackWidget->currentIndex();
    // m_requestedWizard = wizard;
    // connect(m_requestedWizard, SIGNAL(finished(int)), this, SLOT(onWizardFinished(int)));

    // ui->stackWidget->addWidget(wizard);
    // ui->stackWidget->slideInWgt(wizard);
}

void SettingsPage::onWizardFinished(int returnCode)
{
    Q_UNUSED(returnCode);

    // ui->stackWidget->removeWidget(m_requestedWizard);
    // ui->stackWidget->slideInIdx(m_requestedWizardReturnIndex);
    // m_requestedWizardReturnIndex = 0;

    // disconnect(m_requestedWizard, SIGNAL(finished(int)), this, SLOT(onWizardFinished(int)));
    // m_requestedWizard = nullptr;
}

void SettingsPage::changeEvent(QEvent *event)
{
    if(event->type() == QEvent::StyleChange)
        setupIcons();
}

void SettingsPage::reset()
{
    if(m_systemSettingsPage)
        m_systemSettingsPage->reset();

    if(m_themeSettingsPage)
        m_themeSettingsPage->reset();
}

void SettingsPage::apply()
{
    if(m_systemSettingsPage)
        m_systemSettingsPage->apply();

    if(m_themeSettingsPage)
        m_themeSettingsPage->apply();

    if(requiresRestart())
    {
        QMessageBox msgBox;
        msgBox.setText("Restart Required");
        msgBox.setInformativeText("Changes made to the settings require the application to restart.");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();

        QCoreApplication::exit(APPLICATION_RESTART_CODE);
    }
}

bool SettingsPage::requiresRestart()
{
    return (m_systemSettingsPage->requiresRestart());
}
