#ifndef QMASKEDBUTTON_H
#define QMASKEDBUTTON_H

#include <QObject>
#include <QWidget>
#include <QTimer>
#include <QStyle>
#include <QLabel>
#include <QMouseEvent>
#include <QPushButton>
#include <QImage>
#include <QPainter>

class QMaskedButton : public QWidget
{
    Q_OBJECT
public:
    explicit QMaskedButton(QWidget *parent = nullptr);
    ~QMaskedButton();

    void setPixmap(const QPixmap &pixmap);
    void setHoverPixmap(const QPixmap &pixmap);
    void setClickPixmap(const QPixmap &pixmap);

protected:
    virtual void enterEvent(QEnterEvent *event);
    virtual void leaveEvent(QEvent *event);
    virtual void mouseDoubleClickEvent(QMouseEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void paintEvent(QPaintEvent *event);

protected slots:
    void on_clickTimer_timeout();

signals:
    void clicked(QMaskedButton *button);
    void longPressed(QMaskedButton *button);
    void doubleClicked(QMaskedButton *button);

private:
    bool _pressed = false;
    bool _longPressed = false;
    bool _hover = false;

    QTimer *_clickTimer = nullptr;

    QPixmap _pixmap;
    QPixmap _hoverPixmap;
    QPixmap _clickPixmap;

    QBitmap _mask;
    QBitmap _hoverMask;
    QBitmap _clickMask;
};

#endif // QMASKEDBUTTON_H
