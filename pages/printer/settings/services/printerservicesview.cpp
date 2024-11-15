#include "printerservicesview.h"

PrinterServicesView::PrinterServicesView(QKlipperInstance *instance, QWidget *parent)
    : QWidget{parent}
{
    m_printer = instance;
    m_layout = new QFlowLayout(this);
    setLayout(m_layout);

    connect(m_printer->system(), SIGNAL(serviceStatesChanged()), this, SLOT(onSystemServiceStatesChanged()));
}

PrinterServicesView::~PrinterServicesView()
{
    if(m_layout)
        m_layout->deleteLater();
}

void PrinterServicesView::onSystemServiceStatesChanged()
{
    QStringList services = m_printer->system()->availableServices();

    foreach(QString service, services)
    {
        if(!m_serviceCards.contains(service))
        {
            QKlipperServiceState serviceState = m_printer->system()->serviceStates()[service];
            PrinterServiceWidget *widget = new PrinterServiceWidget(m_printer->system(), serviceState, this);

            m_layout->addWidget(widget);

            m_serviceCards.insert(service, widget);
        }
        else
        {
            m_serviceCards[service]->setServiceState(m_printer->system()->serviceStates()[service]);
        }
    }
}
