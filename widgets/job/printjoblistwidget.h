#ifndef PRINTJOBLISTWIDGET_H
#define PRINTJOBLISTWIDGET_H

#include <QScrollArea>
#include <QGridLayout>

#include "printjoblistitem.h"

namespace Ui {
class PrintJobListWidget;
}

class PrintJobListWidget : public QScrollArea
{
    Q_OBJECT

public:
    explicit PrintJobListWidget(QWidget *parent = nullptr);
    ~PrintJobListWidget();

    void addJob(PrintJob *job);
    void removeJob(PrintJob *job);
    void updateJob(PrintJob *job);

private:
    Ui::PrintJobListWidget *ui;
    QList<PrintJobListItem*> _items;
    QWidget *_centralWidget = nullptr;
};

#endif // PRINTJOBLISTWIDGET_H
