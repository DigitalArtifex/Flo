#include "printerservicesview.h"

PrinterServicesView::PrinterServicesView(QKlipperInstance *instance, QWidget *parent)
    : QWidget{parent}
{
    m_printer = instance;
    m_layout = new QFlowLayout(this);
    setLayout(m_layout);

    connect(m_printer->system(), SIGNAL(servicesChanged()), this, SLOT(onSystemServiceStatesChanged()));
}

PrinterServicesView::~PrinterServicesView()
{
    if(m_layout)
        m_layout->deleteLater();
}

void PrinterServicesView::onSystemServiceStatesChanged()
{
    QStringList services = m_printer->system()->availableServices();

    for(QString &service : services)
    {
        if(!m_serviceCards.contains(service))
        {
            QKlipperService *serviceState = m_printer->system()->services()[service];

            if(serviceState)
            {
                PrinterServiceWidget *widget = new PrinterServiceWidget(m_printer->system(), serviceState, this);

                m_layout->addWidget(widget);

                m_serviceCards.insert(service, widget);
            }
        }
    }
}
