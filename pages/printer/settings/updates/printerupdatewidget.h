#ifndef PRINTERUPDATEWIDGET_H
#define PRINTERUPDATEWIDGET_H

#include <QFrame>
#include <QObject>
#include <QWidget>
#include <QToolButton>
#include <QGridLayout>

#include "printerupdateitem.h"

#include "ui/list/qanimatedlistwidget.h"
#include <QKlipper/qklipper.h>

class PrinterUpdateWidget : public QAnimatedListWidget
{
    Q_OBJECT
public:
    explicit PrinterUpdateWidget(QWidget *parent);
    ~PrinterUpdateWidget();

    QKlipperUpdateState *updateState() const;
    void setUpdateState(QKlipperUpdateState *newUpdateState);

signals:
    void itemUpdateRequested(PrinterUpdateItem *item);

protected slots:
    void itemUpdateRequestedEvent(PrinterUpdateItem* item);

private:
    QKlipperUpdateState *m_updateState;
};

#endif // PRINTERUPDATEWIDGET_H
