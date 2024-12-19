#include "printersettingspage.h"
#include "ui_printersettingspage.h"

PrinterSettingsPage::PrinterSettingsPage(QKlipperInstance *instance, QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::PrinterSettingsPage)
{
    ui->setupUi(this);

    m_instance = instance;

    m_configBrowser = new FileBrowser(instance, QString("config"), this, FileBrowser::Widget);
    m_configBrowser->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->filesFrame->layout()->addWidget(m_configBrowser);

    m_updateView = new PrinterUpdateView(m_instance->system(), this);
    ui->updatesFrame->layout()->addWidget(m_updateView);

    m_announcementView = new PrinterAnnouncementView(instance, this);
    ui->announcementsFrame->layout()->addWidget(m_announcementView);

    m_servicesView = new PrinterServicesView(m_instance, this);
    ui->servicesWidget->layout()->addWidget(m_servicesView);

    m_usersView = new PrinterUsersView(m_instance, this);
    ui->usersFrame->layout()->addWidget(m_usersView);

    m_systemView = new PrinterSystemView(m_instance, this);
    ui->statusWidget->layout()->addWidget(m_systemView);

    ui->scrollArea->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "Page"));
    ui->scrollAreaWidgetContents->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "PageContents"));

    style()->polish(this);
}

PrinterSettingsPage::~PrinterSettingsPage()
{
    delete ui;
}

void PrinterSettingsPage::setStyleSheet(const QString &styleSheet)
{
    if(m_announcementView)
        m_announcementView->setStyleSheet(styleSheet);

    if(m_systemView)
        m_systemView->setStyleSheet(styleSheet);

    if(m_usersView)
        m_usersView->setStyleSheet(styleSheet);

    if(m_servicesView)
        m_servicesView->setStyleSheet(styleSheet);

    QFrame::setStyleSheet(styleSheet);
}
