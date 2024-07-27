#include "printerservicesview.h"

PrinterServicesView::PrinterServicesView(Printer *printer, QWidget *parent)
    : QWidget{parent}
{
    m_printer = printer;

    setupUi();

    connect(m_printer->system(), SIGNAL(updated()), this, SLOT(systemUpdateEvent()));
}

PrinterServicesView::~PrinterServicesView()
{
    if(m_layout)
        delete m_layout;
}

void PrinterServicesView::setupUi()
{
    m_centralWidget = new QWidget(this);
    m_layout = new QHBoxLayout(this);
    m_layout->setContentsMargins(9,9,9,9);

    m_systemWidget = new PrinterSystemWidget(m_printer, this);
    m_systemWidget->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    m_systemWidget->setFixedWidth(540);
    m_layout->addWidget(m_systemWidget);

    m_networkWidget = new PrinterNetworkWidget(m_printer->system(), this);
    m_networkWidget->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    m_layout->addWidget(m_networkWidget);

    //m_driveWidget = new PrinterDriveWidget(m_printer->system(), this);
    //m_driveWidget->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    //m_layout->addWidget(m_driveWidget);

    m_layout->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Ignored));

    setLayout(m_layout);
}

void PrinterServicesView::systemUpdateEvent()
{
    QStringList services = m_printer->system()->availableServices();

    foreach(QString service, services)
    {
        if(!m_serviceCards.contains(service))
        {
            System::ServiceState serviceState = m_printer->system()->serviceStates()[service];
            PrinterServiceWidget *widget = new PrinterServiceWidget(m_printer->system(), serviceState, this);

            m_layout->addWidget(widget);

            m_serviceCards.insert(service, widget);
        }
    }
}
