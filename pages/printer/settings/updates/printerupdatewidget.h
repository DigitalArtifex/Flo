#ifndef PRINTERUPDATEWIDGET_H
#define PRINTERUPDATEWIDGET_H

#include <QFrame>
#include <QObject>
#include <QWidget>
#include <QToolButton>
#include <QGridLayout>

#include "printerupdateitem.h"

#include "ui/list/qanimatedlistwidget.h"
#include "types/system.h"

class PrinterUpdateWidget : public QAnimatedListWidget
{
    Q_OBJECT
public:
    explicit PrinterUpdateWidget(QWidget *parent);
    ~PrinterUpdateWidget();

    System::UpdateState updateState() const;
    void setUpdateState(const System::UpdateState &newUpdateState);

signals:
    void itemUpdateRequested(PrinterUpdateItem *item);

protected slots:
    void itemUpdateRequestedEvent(PrinterUpdateItem* item);

private:
    System::UpdateState m_updateState;
};

#endif // PRINTERUPDATEWIDGET_H
