#include "printerlistwidget.h"
#include "ui_printerlistwidget.h"
#include <system/qklipperinstancepool.h>

PrinterListWidget::PrinterListWidget(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::PrinterListWidget)
{
    ui->setupUi(this);
    ui->scrollAreaWidgetContents->setLayout(new QVBoxLayout());
    m_spacer = new QSpacerItem(10,10,QSizePolicy::Fixed,QSizePolicy::Expanding);
    m_items.clear();

    connect(QKlipperInstancePool::pool(), SIGNAL(instanceAdded(QKlipperInstance*)), this, SLOT(onInstanceAdded(QKlipperInstance*)));
    connect(QKlipperInstancePool::pool(), SIGNAL(instanceRemoved(QKlipperInstance*)), this, SLOT(onInstanceRemoved(QKlipperInstance*)));
}

PrinterListWidget::~PrinterListWidget()
{
    delete ui;
}

void PrinterListWidget::addItem(QKlipperInstance *definition)
{
    //Check the list for the item
    bool found = false;

    foreach(PrinterListItem *item, m_items)
    {
        if(item->instance() == definition)
            found = true;
    }

    //Create the item if it doesn't exist
    if(!found)
    {
        PrinterListItem *item = new PrinterListItem();
        item->setInstance(definition);
        item->setMinimumHeight(50);

        connect(item, SIGNAL(clicked(PrinterListItem*)), this, SLOT(on_itemClicked(PrinterListItem*)));

        //remove the bottom spacer and replace it after adding the new item
        ui->scrollAreaWidgetContents->layout()->removeItem(m_spacer);
        ui->scrollAreaWidgetContents->layout()->addWidget(item);
        ui->scrollAreaWidgetContents->layout()->addItem(m_spacer);
        m_items.append(item);
    }
}

void PrinterListWidget::removeItem(QKlipperInstance *instance)
{
    //Check the list for the item
    foreach(PrinterListItem *item, m_items)
    {
        if(item->instance() == instance)
        {
            //remove the item from the list
            m_items.removeAll(item);

            //delete the item
            item->deleteLater();
        }
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

void PrinterListWidget::onInstanceRemoved(QKlipperInstance *instance)
{
    removeItem(instance);
}

void PrinterListWidget::onInstanceAdded(QKlipperInstance *instance)
{
    addItem(instance);
}

void PrinterListWidget::mousePressEvent(QMouseEvent *event)
{
    for(int i = 0; i < m_items.count(); i++)
        m_items[i]->setSelected(false);

    m_selectedItem = nullptr;
    emit(itemSelected(m_selectedItem));

    QFrame::mousePressEvent(event);
}
