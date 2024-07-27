#include "dashboardpage.h"
#include "ui_dashboardpage.h"
#include "../../system/settings.h"
#include "../../system/printerpool.h"

DashboardPage::DashboardPage(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::DashboardPage)
{
    ui->setupUi(this);

    m_layout = new QFlowLayout(ui->scrollAreaWidgetContents);
    ui->scrollAreaWidgetContents->setLayout(m_layout);

    m_systemWidget = new SystemWidget();
    ui->scrollAreaWidgetContents->layout()->addWidget(m_systemWidget);

    m_statusWidget = new StatusWidget(this);
    ui->scrollAreaWidgetContents->layout()->addWidget(m_statusWidget);

    setUiClasses();
    loadPrinters();

    connect(PrinterPool::instance(), SIGNAL(printerAdded(Printer*)), this, SLOT(on_printerPool_printerAdded(Printer*)));
    connect(PrinterPool::instance(), SIGNAL(printerRemoved(Printer*)), this, SLOT(on_printerPool_printerRemoved(Printer*)));

    setStyleSheet(Settings::currentTheme());
}

DashboardPage::~DashboardPage()
{
    delete ui;

    if(m_systemWidget)
        delete m_systemWidget;

    if(m_statusWidget)
        delete m_statusWidget;

    for(int i = 0; i < m_printerWidgets.count(); i++)
        delete m_printerWidgets[i];

    if(m_layout)
        delete m_layout;
}

void DashboardPage::loadPrinters()
{
    PrinterDefinitionList printers = Settings::printers();

    foreach(PrinterDefinition definition, printers)
    {
        bool found = false;
        foreach(PrinterWidget *widget, m_printerWidgets)
        {
            if(widget->printer()->id() == definition.id)
            {
                found = true;
                break;
            }
        }
        if(!found)
        {
            PrinterWidget *widget = new PrinterWidget();
            Printer *printer = PrinterPool::getPrinterById(definition.id);

            if(printer == nullptr)
                printer = new Printer(definition);

            widget->setPrinter(printer);
            m_printerWidgets.append(widget);
            ui->scrollAreaWidgetContents->layout()->addWidget(widget);

            if(definition.defaultPrinter)
            {
                m_selectedWidget = widget;
                m_systemWidget->setPrinter(printer);
            }
        }
    }

    if(m_selectedWidget == nullptr && !m_printerWidgets.isEmpty())
    {
        m_selectedWidget = m_printerWidgets[0];
        m_systemWidget->setPrinter(m_selectedWidget->printer());
    }
}

void DashboardPage::setUiClasses()
{
    ui->scrollArea->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "Page" ));
    ui->scrollAreaWidgetContents->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "Page" ));
}

void DashboardPage::updateStyleSheet(QString styleSheet)
{
    this->setStyleSheet(styleSheet);
}

void DashboardPage::setStyleSheet(QString styleSheet)
{
    QFrame::setStyleSheet(styleSheet);

    if(m_systemWidget)
        m_systemWidget->setStyleSheet(styleSheet);

    if(m_statusWidget)
        m_statusWidget->setStyleSheet(styleSheet);

    for(int i = 0; i < m_printerWidgets.count(); i++)
        m_printerWidgets[i]->setStyleSheet(styleSheet);
}

void DashboardPage::resizeEvent(QResizeEvent *event)
{
    QFrame::resizeEvent(event);

    qint32 padding = m_layout->horizontalSpacing() * 2;
    padding += m_layout->contentsMargins().left();
    padding += m_layout->contentsMargins().right();
    qint32 statusWidth = ((width() - padding) - m_systemWidget->width()) - 20;
    qint32 statusHeight = m_systemWidget->height();

    if(m_statusWidget)
        m_statusWidget->setFixedSize(QSize(statusWidth, statusHeight));
}

void DashboardPage::on_printerPool_printerRemoved(Printer *printer)
{
    for(int i = 0; i < m_printerWidgets.count(); i++)
    {
        if(printer->id() == m_printerWidgets[i]->printer()->id())
        {
            PrinterWidget *widget = m_printerWidgets[i];
            ui->scrollAreaWidgetContents->layout()->removeWidget(m_printerWidgets[i]);
            m_printerWidgets.removeAt(i);
            delete widget;
        }
    }
}

void DashboardPage::on_printerPool_printerAdded(Printer *printer)
{
    PrinterWidget *widget = new PrinterWidget();
    widget->setPrinter(printer);
    m_printerWidgets.append(widget);
    ui->scrollAreaWidgetContents->layout()->addWidget(widget);
}
