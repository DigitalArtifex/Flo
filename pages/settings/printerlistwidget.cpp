#include "printerlistwidget.h"
#include "ui_printerlistwidget.h"

PrinterListWidget::PrinterListWidget(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::PrinterListWidget)
{
    ui->setupUi(this);
    ui->scrollAreaWidgetContents->setLayout(new QVBoxLayout());
    _spacer = new QSpacerItem(10,10,QSizePolicy::Fixed,QSizePolicy::Expanding);
    _items.clear();
}

PrinterListWidget::~PrinterListWidget()
{
    delete ui;
}

void PrinterListWidget::addItem(PrinterListItem *item)
{
    ui->scrollAreaWidgetContents->layout()->removeItem(_spacer);
    ui->scrollAreaWidgetContents->layout()->addWidget(item);
    ui->scrollAreaWidgetContents->layout()->addItem(_spacer);
    _items.append(item);
}

void PrinterListWidget::on_itemClicked(PrinterListItem *item)
{
    _selectedItem = item;

    for(int i = 0; i < _items.count(); i++)
    {
        if(item != _selectedItem)
            _items[i]->setSelected(false);
    }
}

void PrinterListWidget::mousePressEvent(QMouseEvent *event)
{
    for(int i = 0; i < _items.count(); i++)
        _items[i]->setSelected(false);

    _selectedItem = nullptr;
}

void PrinterListWidget::mouseReleaseEvent(QMouseEvent *event)
{
}
