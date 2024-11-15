#ifndef PRINTJOBLISTWIDGET_H
#define PRINTJOBLISTWIDGET_H

#include <QScrollArea>
#include <QGridLayout>
#include <QSpacerItem>
#include <QWidget>

#include <QKlipper/qklipper.h>

#include "printjoblistitem.h"

#include "../../../../../ui/list/qanimatedlistwidget.h"

class PrintJobListWidget : public QAnimatedListWidget
{
    Q_OBJECT

public:
    explicit PrintJobListWidget(QWidget *parent = nullptr);
    ~PrintJobListWidget();

    virtual void setStyleSheet(QString styleSheet);

    void addJob(QKlipperPrintJob *job);
    void removeJob(QKlipperPrintJob *job);

protected slots:
    void onPrintJobAdded(QKlipperInstance *instance, QKlipperPrintJob *job);
    void onPrintJobRemoved(QKlipperInstance *instance, QKlipperPrintJob *job);
    void itemRemoveRequestEvent(PrintJobListItem *item);

private:
};

#endif // PRINTJOBLISTWIDGET_H
