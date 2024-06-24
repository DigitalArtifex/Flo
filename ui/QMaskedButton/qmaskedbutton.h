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
#include <QPropertyAnimation>

#include "../qwidgetanimation.h"

class QMaskedButton : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(qreal opacity READ widgetOpacity WRITE setOpacity)
    Q_PROPERTY(qreal hover_opacity READ hoverOpacity WRITE setHoverOpacity)
    Q_PROPERTY(qreal click_opacity READ clickOpacity WRITE setClickOpacity)
public:
    explicit QMaskedButton(QWidget *parent = nullptr);
    ~QMaskedButton();

    void setPixmap(const QPixmap &pixmap);
    void setHoverPixmap(const QPixmap &pixmap);
    void setClickPixmap(const QPixmap &pixmap);

    qreal widgetOpacity() const;
    void setOpacity(qreal opacity);

    qreal hoverOpacity() const;
    void setHoverOpacity(qreal hover_opacity);

    qreal clickOpacity() const;
    void setClickOpacity(qreal click_opacity);

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
    bool m_pressed = false;
    bool m_longPressed = false;
    bool m_hover = false;

    QTimer *m_clickTimer = nullptr;

    QPixmap m_pixmap;
    QPixmap m_hoverPixmap;
    QPixmap m_clickPixmap;

    QBitmap m_mask;
    QBitmap m_hoverMask;
    QBitmap m_clickMask;

    qreal m_hover_opacity = 0.0;
    qreal m_click_opacity = 0.0;
    qreal m_opacity = 1.0;

    QPropertyAnimation *m_hover_animation = nullptr;
    QPropertyAnimation *m_click_animation = nullptr;
};

#endif // QMASKEDBUTTON_H
