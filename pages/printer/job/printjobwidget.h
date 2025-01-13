#ifndef PRINTJOBOVERVIEWWIDGET_H
#define PRINTJOBOVERVIEWWIDGET_H

#include <QScrollArea>
#include <QGridLayout>
#include <QSpacerItem>
#include <QWidget>

#include <QKlipper/qklipper.h>

#include "printjobitem.h"

#include "ui/list/qanimatedlistwidget.h"

class PrintJobWidget : public QAnimatedListWidget
{
    Q_OBJECT

public:
    explicit PrintJobWidget(QKlipperInstance *instance, QWidget *parent = nullptr);
    ~PrintJobWidget();

public slots:
    void addJob(QKlipperPrintJob *job);
    void removeJob(QKlipperPrintJob *job);

protected:
    void setupIcons();
    virtual void changeEvent(QEvent *event) override;

protected slots:
    void itemRemoveRequestEvent(PrintJobItem *item);

private:
};

#endif // PRINTJOBOVERVIEWWIDGET_H
