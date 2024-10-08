#include "printersettingspage.h"
#include "ui_printersettingspage.h"

PrinterSettingsPage::PrinterSettingsPage(Printer *printer, QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::PrinterSettingsPage)
{
    ui->setupUi(this);

    m_printer = printer;

    m_configBrowser = new FileBrowser(printer, QString("config"), this, FileBrowser::Widget);
    m_configBrowser->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->filesFrame->layout()->addWidget(m_configBrowser);

    m_updateView = new PrinterUpdateView(printer, this);
    ui->updatesFrame->layout()->addWidget(m_updateView);

    m_announcementView = new PrinterAnnouncementView(printer, this);
    ui->announcementsFrame->layout()->addWidget(m_announcementView);

    m_servicesView = new PrinterServicesView(m_printer, this);
    ui->servicesWidget->layout()->addWidget(m_servicesView);

    m_usersView = new PrinterUsersView(m_printer, this);
    ui->usersFrame->layout()->addWidget(m_usersView);

    m_systemView = new PrinterSystemView(m_printer, this);
    ui->statusWidget->layout()->addWidget(m_systemView);

    ui->scrollArea->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "Page"));
    ui->scrollAreaWidgetContents->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "PageContents"));

    style()->polish(this);
}

PrinterSettingsPage::~PrinterSettingsPage()
{
    delete ui;
}
