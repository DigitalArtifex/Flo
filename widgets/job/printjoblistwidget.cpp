#include "printjoblistwidget.h"
#include "ui_printjoblistwidget.h"

PrintJobListWidget::PrintJobListWidget(QWidget *parent) :
    QScrollArea(parent),
    ui(new Ui::PrintJobListWidget)
{
    ui->setupUi(this);
    _centralWidget = new QWidget(this);
    setWidget(_centralWidget);
}

PrintJobListWidget::~PrintJobListWidget()
{
    delete ui;
}

void PrintJobListWidget::addJob(PrintJob *job)
{

}

void PrintJobListWidget::removeJob(PrintJob *job)
{

}

void PrintJobListWidget::updateJob(PrintJob *job)
{

}
