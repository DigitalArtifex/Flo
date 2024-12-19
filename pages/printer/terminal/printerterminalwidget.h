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
    void addMessage(QString title, QString message);
    void addErrorMessage(QString title, QString message);
    void addGcodeResponse(QString &message);

protected:

private:
    QMap<qint64, PrinterTerminalItem*> m_itemMap;

    const static inline QRegularExpression s_gcodeErrorResponseCleanup = QRegularExpression("(\\!\\! )|\n");
    const static inline QRegularExpression s_gcodeResponseCleanup = QRegularExpression("(\\/\\/ )|\n");

};

#endif // PRINTERTERMINALWIDGET_H
