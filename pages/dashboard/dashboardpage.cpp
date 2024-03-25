#include "dashboardpage.h"
#include "ui_dashboardpage.h"
#include "../../system/settings.h"
#include "../../system/printerpool.h"

DashboardPage::DashboardPage(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::DashboardPage)
{
    ui->setupUi(this);

    _layout = new QFlowLayout(ui->scrollAreaWidgetContents);
    ui->scrollAreaWidgetContents->setLayout(_layout);

    _systemWidget = new SystemWidget();
    ui->scrollAreaWidgetContents->layout()->addWidget(_systemWidget);

    _printJobWidget = new PrintJobWidget();
    ui->scrollAreaWidgetContents->layout()->addWidget(_printJobWidget);

    setUiClasses();
    loadPrinters();

    connect(PrinterPool::instance(), SIGNAL(printerAdded(Printer*)), this, SLOT(on_printerPool_printerAdded(Printer*)));
    connect(PrinterPool::instance(), SIGNAL(printerRemoved(Printer*)), this, SLOT(on_printerPool_printerRemoved(Printer*)));
}

DashboardPage::~DashboardPage()
{
    delete ui;
}

void DashboardPage::loadPrinters()
{
    PrinterDefinitionList printers = Settings::printers();

    foreach(PrinterDefinition definition, printers)
    {
        bool found = false;
        foreach(PrinterWidget *widget, _printerWidgets)
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
            _printerWidgets.append(widget);
            ui->scrollAreaWidgetContents->layout()->addWidget(widget);

            connect(printer, SIGNAL(systemUpdate(Printer*)), this, SLOT(on_printer_systemUpdate(Printer*)));
        }
    }

    if(_selectedWidget == nullptr && !_printerWidgets.isEmpty())
    {
        _selectedWidget = _printerWidgets[0];
        _systemWidget->setPrinter(_selectedWidget->printer());
    }
}

void DashboardPage::setUiClasses()
{
    this->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "Page" ));
    ui->actionBarFrame->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "PageActionBar" ));
    ui->scrollAreaWidgetContents->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "PageContainer" ));
}

void DashboardPage::updateStyleSheet(QString styleSheet)
{
    this->setStyleSheet(styleSheet);
}

void DashboardPage::setStyleSheet(QString styleSheet)
{
    QFrame::setStyleSheet(styleSheet);
    _systemWidget->setStyleSheet(styleSheet);
    _printJobWidget->setStyleSheet(styleSheet);

    for(int i = 0; i < _printerWidgets.count(); i++)
        _printerWidgets[i]->setStyleSheet(styleSheet);
}

void DashboardPage::on_console_response(Printer *printer, KlipperResponse response)
{

}

void DashboardPage::on_printer_update(Printer *printer)
{

}

void DashboardPage::on_printer_systemUpdate(Printer *printer)
{

}

void DashboardPage::on_printerPool_printerRemoved(Printer *printer)
{
    for(int i = 0; i < _printerWidgets.count(); i++)
    {
        if(printer->id() == _printerWidgets[i]->printer()->id())
        {
            PrinterWidget *widget = _printerWidgets[i];
            ui->scrollAreaWidgetContents->layout()->removeWidget(_printerWidgets[i]);
            _printerWidgets.removeAt(i);
            delete widget;
        }
    }
}

void DashboardPage::on_printerPool_printerAdded(Printer *printer)
{
    loadPrinters();
}

void DashboardPage::on_printerPool_printerUpdated(Printer *printer)
{
    for(int i = 0; i < _printerWidgets.count(); i++)
    {
        if(printer->id() == _printerWidgets[i]->printer()->id())
        {
            _printerWidgets[i]->setPrinter(printer);
        }
    }
}
