#ifndef PRINTJOBOVERVIEWWIDGET_H
#define PRINTJOBOVERVIEWWIDGET_H

#include <QScrollArea>
#include <QGridLayout>
#include <QSpacerItem>
#include <QWidget>

#include <QKlipper/qklipper.h>

#include "printjoboverviewitem.h"

#include "ui/list/qanimatedlistwidget.h"

class PrintJobOverviewWidget : public QAnimatedListWidget
{
    Q_OBJECT

public:
    explicit PrintJobOverviewWidget(QWidget *parent = nullptr);
    ~PrintJobOverviewWidget();

    virtual void setStyleSheet(QString styleSheet);

    void addJob(QKlipperPrintJob *job);
    void removeJob(QKlipperPrintJob *job);

protected slots:
    void onPrintJobAdded(QKlipperInstance *instance, QKlipperPrintJob *job);
    void onPrintJobRemoved(QKlipperInstance *instance, QKlipperPrintJob *job);
    void itemRemoveRequestEvent(PrintJobOverviewItem *item);

private:
};

#endif // PRINTJOBOVERVIEWWIDGET_H
