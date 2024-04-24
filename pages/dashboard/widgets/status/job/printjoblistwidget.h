#ifndef PRINTJOBLISTWIDGET_H
#define PRINTJOBLISTWIDGET_H

#include <QScrollArea>
#include <QGridLayout>
#include <QSpacerItem>
#include <QWidget>

#include "printjoblistitem.h"

#include "../../../../../ui/list/qanimatedlistwidget.h"

class PrintJobListWidget : public QAnimatedListWidget
{
    Q_OBJECT

public:
    explicit PrintJobListWidget(QWidget *parent = nullptr);
    ~PrintJobListWidget();

    virtual void setStyleSheet(QString styleSheet);

    void addJob(PrintJob *job);
    void removeJob(PrintJob *job);
    void updateJob(PrintJob *job);

private:
};

#endif // PRINTJOBLISTWIDGET_H
