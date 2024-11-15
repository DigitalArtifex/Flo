#ifndef PRINTERLISTITEM_H
#define PRINTERLISTITEM_H

#include <QFrame>
#include <QListWidgetItem>
#include <QTimer>
#include <QMouseEvent>
#include <QKlipper/qklipper.h>

namespace Ui {
class PrinterListItem;
}

class PrinterListItem : public QFrame, public QListWidgetItem
{
    Q_OBJECT

public:
    explicit PrinterListItem(QWidget *parent = nullptr);
    ~PrinterListItem();

    void setInstance(QKlipperInstance *instance);
    void setUiClasses();
    void setSelected(bool selected);
    bool selected();

    QKlipperInstance *instance();

protected:
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);

signals:
    void clicked(PrinterListItem *item);
    void longPressed(PrinterListItem *item);

private slots:
    virtual void clickTimeout();

    void onInstanceNameChanged();
    void onAddressChanged();
    void onPortChanged();
    void onInstanceThumbnailChanged();


private:
    Ui::PrinterListItem *ui;
    QKlipperInstance *m_definition = nullptr;
    bool m_pressed = false;
    bool m_longPress = false;
    bool m_rightClick = false;
    QTimer *m_clickTimer = NULL;
};

#endif // PRINTERLISTITEM_H
