#ifndef PRINTINGPAGE_H
#define PRINTINGPAGE_H

#include <QObject>
#include <QQmlEngine>
#include <QWidget>

#include <ui/qanimatedwidget.h>

class PrintingPage : public QAnimatedWidget
{
        Q_OBJECT
        QML_ELEMENT
    public:
        explicit PrintingPage(QWidget *parent = nullptr);

    signals:
};

#endif // PRINTINGPAGE_H
