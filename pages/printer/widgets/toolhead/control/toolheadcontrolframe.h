#ifndef TOOLHEADCONTROLFRAME_H
#define TOOLHEADCONTROLFRAME_H

#include <QFrame>
#include <QObject>
#include <QWidget>

#include <QBitmap>

#include "../../../../../ui/QMaskedButton/qmaskedbutton.h"

class ToolHeadControlFrame : public QFrame
{
    Q_OBJECT
public:
    ToolHeadControlFrame(QWidget *parent);

protected:
    virtual void resizeEvent(QResizeEvent *event);

protected slots:
    void xUpClickEvent();
    void xDownClickEvent();
    void yUpClickEvent();
    void yDownClickEvent();
    void zUpClickEvent();
    void zDownClickEvent();
    void homeClickEvent();

private:

    QMaskedButton *_xUpWidget = nullptr;
    QMaskedButton *_xDownWidget = nullptr;
    QMaskedButton *_yUpWidget = nullptr;
    QMaskedButton *_yDownWidget = nullptr;
    QMaskedButton *_zUpWidget = nullptr;
    QMaskedButton *_zDownWidget = nullptr;
    QMaskedButton *_homeWidget = nullptr;
};

#endif // TOOLHEADCONTROLFRAME_H
