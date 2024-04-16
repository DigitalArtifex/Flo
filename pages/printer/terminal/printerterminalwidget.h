#ifndef PRINTERTERMINALWIDGET_H
#define PRINTERTERMINALWIDGET_H

#include <QObject>
#include <QWidget>

#include "../../../widgets/list/qanimatedlistwidget.h"

class PrinterTerminalWidget : public QAnimatedListWidget
{
    Q_OBJECT
public:
    PrinterTerminalWidget(QWidget *parent = nullptr);
};

#endif // PRINTERTERMINALWIDGET_H
