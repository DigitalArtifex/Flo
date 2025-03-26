#include "printersettingspage.h"
#include "ui_printersettingspage.h"

PrinterSettingsPage::PrinterSettingsPage(QKlipperInstance *instance, QWidget *parent)
    : Page(parent)
    , ui(new Ui::PrinterSettingsPage)
{
    ui->setupUi(this);

    m_instance = instance;

    m_configBrowser = new FileBrowser(instance, QString("config"), this, FileBrowser::WidgetMode);
    m_configBrowser->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->filesFrame->layout()->addWidget(m_configBrowser);

    connect(m_configBrowser, SIGNAL(dialogRequested(QDialog*)), this, SLOT(onDialogRequested(QDialog*)));
    connect(m_configBrowser, SIGNAL(wizardRequested(QWizard*)), this, SLOT(onWizardRequested(QWizard*)));

    m_updateView = new PrinterUpdateView(m_instance->system(), this);
    ui->updatesFrame->layout()->addWidget(m_updateView);

    m_announcementView = new PrinterAnnouncementView(instance, this);
    ui->announcementsFrame->layout()->addWidget(m_announcementView);

    m_servicesView = new PrinterServicesView(m_instance, this);
    ui->servicesWidget->layout()->addWidget(m_servicesView);

    m_usersView = new PrinterUsersView(m_instance, this);
    ui->usersFrame->layout()->addWidget(m_usersView);

    connect(m_usersView, SIGNAL(dialogRequested(QDialog*)), this, SLOT(onDialogRequested(QDialog*)));
    connect(m_usersView, SIGNAL(wizardRequested(QWizard*)), this, SLOT(onWizardRequested(QWizard*)));

    m_systemView = new PrinterSystemView(m_instance, this);
    ui->statusWidget->layout()->addWidget(m_systemView);

    m_closeButton = new QIconButton(ui->buttonBoxWidget);
    m_closeButton->setIcon(Settings::getThemeIcon(QString("multiply")));
    m_closeButton->setFixedSize(50,50);
    m_closeButton->setTextMargins(QMargins(34,0,0,0));
    m_closeButton->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
    ui->buttonBoxWidget->layout()->addWidget(m_closeButton);

    connect(m_closeButton, SIGNAL(clicked()), this, SLOT(close()));

    ui->buttonBoxWidget->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "PageActionBar"));
    ui->scrollAreaWidgetContents->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "PageContents"));
}

PrinterSettingsPage::~PrinterSettingsPage()
{
    delete ui;
}

void PrinterSettingsPage::onDialogRequested(QDialog *dialog)
{
    emit dialogRequested(dialog);
}

void PrinterSettingsPage::onWizardRequested(QWizard *wizard)
{
    emit wizardRequested(wizard);
}

void PrinterSettingsPage::setIcons()
{
    ui->machinePowerButton->setIcon(Settings::getThemeIcon("power"));
}

void PrinterSettingsPage::changeEvent(QEvent *event)
{
    if(event->type() == QEvent::StyleChange)
        setIcons();
}

void PrinterSettingsPage::on_machinePowerButton_clicked()
{
    m_powerOptionsDialog = new MachinePowerDialog(this);
    emit dialogRequested(m_powerOptionsDialog);
    connect(m_powerOptionsDialog, SIGNAL(finished(int)), this, SLOT(onPowerOptionsDialogFinished(int)));
}

void PrinterSettingsPage::onPowerOptionsDialogFinished(int code)
{
    switch(code)
    {
    case MachinePowerDialog::FirmwareRestart:
        m_instance->console()->restartFirmware();
        break;
    case MachinePowerDialog::KlipperRestart:
        m_instance->console()->restartKlipper();
        break;
    case MachinePowerDialog::Shutdown:
        m_instance->system()->shutdown();
        break;
    case MachinePowerDialog::Restart:
        m_instance->system()->restart();
        break;
    }

    delete m_powerOptionsDialog;
    m_powerOptionsDialog = nullptr;
}
