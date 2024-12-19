#include "printerupdateview.h"

#include "system/settings.h"

PrinterUpdateView::PrinterUpdateView(QKlipperSystem *system, QWidget *parent)
    : QFrame{parent}
{
    m_system = system;

    setupUi();
}

PrinterUpdateView::~PrinterUpdateView()
{

}

void PrinterUpdateView::setupUi()
{
    m_layout = new QGridLayout();
    m_layout->setContentsMargins(0,0,0,0);
    m_layout->setSpacing(0);

    //Action bar
    m_actionBar = new QWidget();
    m_actionBarLayout = new QGridLayout(m_actionBar);
    m_actionBarLayout->setContentsMargins(4,4,4,4);

    m_titleLabel = new QLabel(m_actionBar);
    m_titleLabel->setText(QString("Updates"));
    m_titleLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    m_actionBarLayout->addWidget(m_titleLabel, 0, 0, 1, 1);

    QSpacerItem *actionSpacer = new QSpacerItem(10,10,QSizePolicy::Expanding,QSizePolicy::Fixed);
    m_actionBarLayout->addItem(actionSpacer, 0, 1, 1, 1);

    m_refreshButton = new QToolButton(m_actionBar);
    m_refreshButton->setFixedSize(32,32);
    m_refreshButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    m_actionBarLayout->addWidget(m_refreshButton, 0, 2, 1, 1);

    m_updateAllButton = new QToolButton(m_actionBar);
    m_updateAllButton->setFixedSize(32,32);
    m_updateAllButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    m_actionBarLayout->addWidget(m_updateAllButton, 0, 3, 1, 1);

    m_actionBar->setLayout(m_actionBarLayout);
    m_layout->addWidget(m_actionBar, 0, 0, 1, 2);

    m_updateWidget = new PrinterUpdateWidget(this);
    m_layout->addWidget(m_updateWidget);

    m_updateAllButton->setIcon(Settings::getThemeIcon(QString("update")));
    m_refreshButton->setIcon(Settings::getThemeIcon(QString("refresh")));

    connect(m_system->updateManager(), SIGNAL(packagesChanged()), this, SLOT(updateStateUpdateEvent()));
    connect(m_system->updateManager(), SIGNAL(systemPackagesChanged()), this, SLOT(updateStateUpdateEvent()));
    // connect(m_printer->console(), SIGNAL(machineUpdatedClient(QString)), this, SLOT(machineUpdateClientEvent(QString)));
    // connect(m_printer->console(), SIGNAL(machineUpdatedFull()), this, SLOT(machineUpdateClientEvent(QString)));
    connect(m_refreshButton, SIGNAL(clicked()), this, SLOT(refreshButtonClickEvent()));
    connect(m_updateAllButton, SIGNAL(clicked()), this, SLOT(updateAllButtonClickEvent()));
    connect(m_updateWidget, SIGNAL(itemUpdateRequested(PrinterUpdateItem*)), this, SLOT(itemUpdateRequestedEvent(PrinterUpdateItem*)));

    setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "Widget"));
    m_actionBar->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "WidgetTitleBar"));

    setLayout(m_layout);
}

void PrinterUpdateView::updateStateUpdateEvent()
{
    m_updateWidget->setUpdateState(m_system->updateManager());
}

void PrinterUpdateView::updateAllButtonClickEvent()
{
    QKlipperInstance *instance = qobject_cast<QKlipperInstance*>(m_system->parent());

    if(instance)
    {
        QKlipperError error;

        m_updateWidget->setEmptyIcon(Settings::getThemeIcon("update"));
        m_updateWidget->setEmptyText("Updating All");
        m_updateWidget->clear();
        instance->console()->machineUpdateFull(&error);

        if(error.type() != QKlipperError::NoError)
            updateStateUpdateEvent();
        else
        {
            //handle error
        }
    }
}

void PrinterUpdateView::refreshButtonClickEvent()
{
    QKlipperInstance *instance = qobject_cast<QKlipperInstance*>(m_system->parent());

    if(instance)
    {
        m_updateWidget->setEmptyIcon(Settings::getThemeIcon("refresh"));
        m_updateWidget->setEmptyText("Refreshing");
        m_updateWidget->clear();
        instance->console()->machineUpdateRefresh();
    }
}

void PrinterUpdateView::itemUpdateRequestedEvent(PrinterUpdateItem *item)
{
    QKlipperInstance *instance = qobject_cast<QKlipperInstance*>(m_system->parent());

    if(instance)
    {
        m_updateWidget->setEmptyIcon(Settings::getThemeIcon("refresh"));
        m_updateWidget->setEmptyText(QString("Updating Client \"%1\"").arg(item->title()));
        m_updateWidget->clear();

        QKlipperError error;

        if(!item->title().isEmpty() && item->title() == QString("klipper"))
            instance->console()->machineUpdateKlipper(&error);
        else if(!item->title().isEmpty() && item->title() == QString("moonraker"))
            instance->console()->machineUpdateMoonraker(&error);
        else if(!item->title().isEmpty())
            instance->console()->machineUpdateClient(item->title(), &error);

        if(error.type() != QKlipperError::NoError)
            updateStateUpdateEvent();
        else
        {
            //handle error
        }
    }
}
