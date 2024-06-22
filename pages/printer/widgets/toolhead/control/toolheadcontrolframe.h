#ifndef TOOLHEADCONTROLFRAME_H
#define TOOLHEADCONTROLFRAME_H

#include <QFrame>
#include <QObject>
#include <QWidget>
#include <QComboBox>

#include <QBitmap>

#include "../../../../../ui/QMaskedButton/qmaskedbutton.h"
#include "../../../../../types/toolhead.h"
#include "../../../../../types/printer.h"

class ToolHeadControlFrame : public QFrame
{
    Q_OBJECT
public:
    ToolHeadControlFrame(Toolhead *toolhead, QWidget *parent);
    ~ToolHeadControlFrame();

    qreal increment() const;
    void setIncrement(qreal increment);

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

    void toolheadUpdateEvent();

private:

    QMaskedButton *m_xUpWidget = nullptr;
    QMaskedButton *m_xDownWidget = nullptr;
    QMaskedButton *m_yUpWidget = nullptr;
    QMaskedButton *m_yDownWidget = nullptr;
    QMaskedButton *m_zUpWidget = nullptr;
    QMaskedButton *m_zDownWidget = nullptr;
    QMaskedButton *m_homeWidget = nullptr;

    Toolhead *m_toolhead = nullptr;

    qreal m_increment = 1.0;
};

#endif // TOOLHEADCONTROLFRAME_H
