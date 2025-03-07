#ifndef PRINTJOBWIDGET_H
#define PRINTJOBWIDGET_H

#include <QScrollArea>
#include <QGridLayout>
#include <QSpacerItem>
#include <QWidget>

#include <QKlipper/qklipper.h>

#include "ui/list/qanimatedlistwidget.h"
#include "printjobitem.h"

class PrintJobWidget : public QAnimatedListWidget
{
    Q_OBJECT

public:
    PrintJobWidget(QKlipperInstance *instance, QWidget *parent = nullptr);
    ~PrintJobWidget();

public slots:
    void addJob(QKlipperPrintJob *job);
    void removeJob(QKlipperPrintJob *job);

protected slots:
    void itemRemoveRequestEvent(PrintJobItem *item);

protected:
    void setupIcons();
    virtual void changeEvent(QEvent *event) override;

private:
};

#endif // PRINTJOBWIDGET_H
