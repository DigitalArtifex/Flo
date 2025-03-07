#include "printersystemview.h"

PrinterSystemView::PrinterSystemView(QKlipperInstance *printer, QWidget *parent)
    : QWidget{parent}
{
    m_instance = printer;

    setupUi();
}

PrinterSystemView::~PrinterSystemView()
{
    if(m_layout)
        m_layout->deleteLater();
}

void PrinterSystemView::setStyleSheet(const QString &styleSheet)
{
    if(m_systemWidget)
        m_systemWidget->setStyleSheet(styleSheet);

    if(m_driveWidget)
        m_driveWidget->setStyleSheet(styleSheet);

    if(m_networkWidget)
        m_networkWidget->setStyleSheet(styleSheet);
}

void PrinterSystemView::setupUi()
{
    m_centralWidget = new QWidget(this);
    m_layout = new QHBoxLayout(m_centralWidget);
    m_layout->setContentsMargins(9,9,9,9);

    m_systemWidget = new PrinterSystemWidget(m_instance, this);
    m_systemWidget->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
    m_layout->addWidget(m_systemWidget);

    m_networkWidget = new PrinterNetworkWidget(m_instance->system(), this);
    m_networkWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::MinimumExpanding);
    m_layout->addWidget(m_networkWidget);

    m_driveWidget = new PrinterDriveWidget(m_instance->printer(), this);
    m_driveWidget->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
    m_layout->addWidget(m_driveWidget);

    //m_layout->addItem(new QSpacerItem(0, 0, QSizePolicy::Preferred, QSizePolicy::Ignored));

    setLayout(m_layout);
}
