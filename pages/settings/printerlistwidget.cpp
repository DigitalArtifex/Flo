#include "printerlistwidget.h"
#include "ui_printerlistwidget.h"
#include "../../system/printerpool.h"

PrinterListWidget::PrinterListWidget(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::PrinterListWidget)
{
    ui->setupUi(this);
    ui->scrollAreaWidgetContents->setLayout(new QVBoxLayout());
    _spacer = new QSpacerItem(10,10,QSizePolicy::Fixed,QSizePolicy::Expanding);
    _items.clear();

    connect(PrinterPool::instance(), SIGNAL(printerAdded(Printer*)), this, SLOT(on_printerPool_printerAdded(Printer*)));
    connect(PrinterPool::instance(), SIGNAL(printerRemoved(Printer*)), this, SLOT(on_printerPool_printerRemoved(Printer*)));
}

PrinterListWidget::~PrinterListWidget()
{
    delete ui;
}

void PrinterListWidget::addItem(PrinterDefinition definition)
{
    bool found = false;

    foreach(PrinterListItem *item, _items)
    {
        if(item->printerDefinition().id == definition.id)
        {
            found = true;
            break;
        }
    }

    if(!found)
    {
        PrinterListItem *item = new PrinterListItem();
        item->setPrinterDefinition(definition);
        item->setMinimumHeight(50);

        connect(item, SIGNAL(clicked(PrinterListItem*)), this, SLOT(on_itemClicked(PrinterListItem*)));

        ui->scrollAreaWidgetContents->layout()->removeItem(_spacer);
        ui->scrollAreaWidgetContents->layout()->addWidget(item);
        ui->scrollAreaWidgetContents->layout()->addItem(_spacer);
        _items.append(item);
    }
}

PrinterListItem *PrinterListWidget::selectedItem()
{
    return _selectedItem;
}

void PrinterListWidget::on_itemClicked(PrinterListItem *item)
{
    _selectedItem = item;

    for(int i = 0; i < _items.count(); i++)
    {
        _items[i]->setSelected(false);
    }

    item->setSelected(true);

    emit(itemSelected(_selectedItem));
}

void PrinterListWidget::on_printerPool_printerRemoved(Printer *printer)
{
    for(int i = 0; i < _items.count(); i++)
    {
        if(printer->id() == _items[i]->printerDefinition().id)
        {
            PrinterListItem *item = _items[i];
            ui->scrollAreaWidgetContents->layout()->removeWidget(_items[i]);
            _items.removeAt(i);

            delete item;
        }
    }
}

void PrinterListWidget::on_printerPool_printerAdded(Printer *printer)
{

}

void PrinterListWidget::on_printerPool_printerUpdated(Printer *printer)
{

}

void PrinterListWidget::mousePressEvent(QMouseEvent *event)
{
    for(int i = 0; i < _items.count(); i++)
        _items[i]->setSelected(false);

    _selectedItem = nullptr;
    emit(itemSelected(_selectedItem));
}

void PrinterListWidget::mouseReleaseEvent(QMouseEvent *event)
{
}
