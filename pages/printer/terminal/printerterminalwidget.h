#ifndef PRINTERTERMINALWIDGET_H
#define PRINTERTERMINALWIDGET_H

#include <QObject>
#include <QWidget>
#include <QMap>
#include <QPair>

#include "../../../widgets/list/qanimatedlistwidget.h"
#include "../../../types/klippermessage.h"
#include "../../../types/klipperresponse.h"

#include "printerterminalitem.h"

typedef QPair<KlipperMessage, KlipperResponse> KlipperCommunication;

class PrinterTerminalWidget : public QAnimatedListWidget
{
    Q_OBJECT
public:
    PrinterTerminalWidget(QWidget *parent = nullptr);

    void addMessage(KlipperMessage message);
    void addResponse(KlipperResponse response);

protected:
    QMap<qint64, PrinterTerminalItem*> _itemMap;
};

#endif // PRINTERTERMINALWIDGET_H