#include "printerlistwidget.h"
#include "ui_printerlistwidget.h"
#include "../../system/printerpool.h"

PrinterListWidget::PrinterListWidget(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::PrinterListWidget)
{
    ui->setupUi(this);
    ui->scrollAreaWidgetContents->setLayout(new QVBoxLayout());
    m_spacer = new QSpacerItem(10,10,QSizePolicy::Fixed,QSizePolicy::Expanding);
    m_items.clear();

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

    foreach(PrinterListItem *item, m_items)
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

        ui->scrollAreaWidgetContents->layout()->removeItem(m_spacer);
        ui->scrollAreaWidgetContents->layout()->addWidget(item);
        ui->scrollAreaWidgetContents->layout()->addItem(m_spacer);
        m_items.append(item);
    }
}

PrinterListItem *PrinterListWidget::selectedItem()
{
    return m_selectedItem;
}

void PrinterListWidget::on_itemClicked(PrinterListItem *item)
{
    m_selectedItem = item;

    for(int i = 0; i < m_items.count(); i++)
    {
        m_items[i]->setSelected(false);
    }

    item->setSelected(true);

    emit(itemSelected(m_selectedItem));
}

void PrinterListWidget::on_printerPool_printerRemoved(Printer *printer)
{
    for(int i = 0; i < m_items.count(); i++)
    {
        if(printer->id() == m_items[i]->printerDefinition().id)
        {
            PrinterListItem *item = m_items[i];
            ui->scrollAreaWidgetContents->layout()->removeWidget(m_items[i]);
            m_items.removeAt(i);

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
    for(int i = 0; i < m_items.count(); i++)
        m_items[i]->setSelected(false);

    m_selectedItem = nullptr;
    emit(itemSelected(m_selectedItem));
}

void PrinterListWidget::mouseReleaseEvent(QMouseEvent *event)
{
}
