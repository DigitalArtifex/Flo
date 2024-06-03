#ifndef PRINTERFANWIDGET_H
#define PRINTERFANWIDGET_H

#include <QFrame>
#include <QObject>
#include <QWidget>

class PrinterFanWidget : public QFrame
{
    Q_OBJECT
public:
    PrinterFanWidget(QWidget *parent = nullptr);
};

#endif // PRINTERFANWIDGET_H
