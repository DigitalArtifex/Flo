#include "printersystemview.h"

PrinterSystemView::PrinterSystemView(Printer *printer, QWidget *parent)
    : QWidget{parent}
{
    m_printer = printer;

    setupUi();

    connect(m_printer->system(), SIGNAL(updated()), this, SLOT(systemUpdateEvent()));
}

PrinterSystemView::~PrinterSystemView()
{
    if(m_layout)
        delete m_layout;
}

void PrinterSystemView::setupUi()
{
    m_centralWidget = new QWidget(this);
    m_layout = new QHBoxLayout(m_centralWidget);
    m_layout->setContentsMargins(9,9,9,9);

    m_systemWidget = new PrinterSystemWidget(m_printer, this);
    m_systemWidget->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    m_layout->addWidget(m_systemWidget);

    m_networkWidget = new PrinterNetworkWidget(m_printer->system(), this);
    m_networkWidget->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::MinimumExpanding);
    m_layout->addWidget(m_networkWidget);

    m_driveWidget = new PrinterDriveWidget(m_printer->system(), this);
    m_driveWidget->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    m_layout->addWidget(m_driveWidget);

    m_layout->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Ignored));

    setLayout(m_layout);
}
