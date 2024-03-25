#include "printjoblistitem.h"
#include "ui_printjoblistitem.h"

PrintJobListItem::PrintJobListItem(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::PrintJobListItem)
{
    ui->setupUi(this);
}

PrintJobListItem::~PrintJobListItem()
{
    delete ui;
}

void PrintJobListItem::setUiClasses()
{
    setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "ListItem" << "JobListItem"));
}

PrintJob *PrintJobListItem::printJob()
{
    return _job;
}

void PrintJobListItem::setStyleSheet(QString styleSheet)
{
    QFrame::setStyleSheet(styleSheet);


}
