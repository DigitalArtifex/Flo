#ifndef PRINTERTERMINALWIDGET_H
#define PRINTERTERMINALWIDGET_H

#include <QObject>
#include <QWidget>
#include <QMap>
#include <QPair>

#include "../../../ui/list/qanimatedlistwidget.h"
#include <QKlipper/qklipper.h>

#include "printerterminalitem.h"

class PrinterTerminalWidget : public QAnimatedListWidget
{
    Q_OBJECT
public:
    PrinterTerminalWidget(QWidget *parent = nullptr);

    void addMessage(QKlipperMessage *message);
    void addErrorMessage(QString title, QString message);

protected:
    virtual void showEvent(QShowEvent *event);

protected:
    QMap<qint64, PrinterTerminalItem*> m_itemMap;
};

#endif // PRINTERTERMINALWIDGET_H
