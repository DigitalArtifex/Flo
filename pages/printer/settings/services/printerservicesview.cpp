#include "printerservicesview.h"

PrinterServicesView::PrinterServicesView(Printer *printer, QWidget *parent)
    : QWidget{parent}
{
    m_printer = printer;
    m_layout = new QFlowLayout(this);
    setLayout(m_layout);

    connect(m_printer->system(), SIGNAL(updated()), this, SLOT(systemUpdateEvent()));
}

PrinterServicesView::~PrinterServicesView()
{
    if(m_layout)
        delete m_layout;
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
