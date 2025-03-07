#ifndef QANIMATEDTOOLBOXBUTTON_H
#define QANIMATEDTOOLBOXBUTTON_H

#include <QPushButton>
#include <QObject>
#include <QWidget>

#include "ui/QIconButton/qiconbutton.h"

class QAnimatedToolBoxButton : public QIconButton
{
    Q_OBJECT
public:
    QAnimatedToolBoxButton(QWidget *parent = nullptr);
    QAnimatedToolBoxButton(QString text, QWidget *parent = nullptr);
    QAnimatedToolBoxButton(QIcon icon, QString text, QWidget *parent = nullptr);

signals:
    void clicked(QAnimatedToolBoxButton*);

protected slots:
    void onClicked();
};

Q_DECLARE_METATYPE(QAnimatedToolBoxButton)

#endif // QANIMATEDTOOLBOXBUTTON_H
