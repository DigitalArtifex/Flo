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

    _statusWidget = new StatusWidget(this);
    ui->scrollAreaWidgetContents->layout()->addWidget(_statusWidget);

    setUiClasses();
    loadPrinters();

    connect(PrinterPool::instance(), SIGNAL(printerAdded(Printer*)), this, SLOT(on_printerPool_printerAdded(Printer*)));
    connect(PrinterPool::instance(), SIGNAL(printerRemoved(Printer*)), this, SLOT(on_printerPool_printerRemoved(Printer*)));

    setStyleSheet(Settings::currentTheme());
}

DashboardPage::~DashboardPage()
{
    delete ui;

    if(_systemWidget)
        delete _systemWidget;

    if(_statusWidget)
        delete _statusWidget;

    for(int i = 0; i < _printerWidgets.count(); i++)
        delete _printerWidgets[i];

    if(_layout)
        delete _layout;
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

            if(definition.defaultPrinter)
            {
                _selectedWidget = widget;
                _systemWidget->setPrinter(printer);
            }
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

    if(_systemWidget)
        _systemWidget->setStyleSheet(styleSheet);

    if(_statusWidget)
        _statusWidget->setStyleSheet(styleSheet);

    for(int i = 0; i < _printerWidgets.count(); i++)
        _printerWidgets[i]->setStyleSheet(styleSheet);
}

void DashboardPage::resizeEvent(QResizeEvent *event)
{
    QFrame::resizeEvent(event);

    qint32 padding = _layout->horizontalSpacing() * 2;
    padding += _layout->contentsMargins().left();
    padding += _layout->contentsMargins().right();
    qint32 statusWidth = ((width() - padding) - _systemWidget->width()) - 20;
    qint32 statusHeight = _systemWidget->height();

    if(_statusWidget)
        _statusWidget->setFixedSize(QSize(statusWidth, statusHeight));
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
