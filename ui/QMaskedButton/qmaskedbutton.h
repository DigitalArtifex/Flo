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
#include <QBitmap>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>

//#include "dalib_global.h"

class QMaskedButton : public QWidget
{
        Q_OBJECT
    public:
        explicit QMaskedButton(QWidget *parent = nullptr);
        ~QMaskedButton();

        QPixmap pixmap() const
        {
            return m_pixmap;
        }

        QPixmap hoverPixmap() const
        {
            return m_hoverPixmap;
        }

        QPixmap clickPixmap() const
        {
            return m_clickPixmap;
        }

    public slots:

        void setPixmap(const QPixmap &pixmap);

        void setHoverPixmap(const QPixmap &hoverPixmap);

        void setClickPixmap(const QPixmap &clickPixmap);

    protected:
        virtual void enterEvent(QEnterEvent *event);
        virtual void leaveEvent(QEvent *event);
        virtual void mouseDoubleClickEvent(QMouseEvent *event);
        virtual void mousePressEvent(QMouseEvent *event);
        virtual void mouseReleaseEvent(QMouseEvent *event);
        virtual void paintEvent(QPaintEvent *event);

        qreal hoverOpacity() const
        {
            return m_hoverOpacity;
        }

        qreal clickOpacity() const
        {
            return m_clickOpacity;
        }

        qreal opacity() const
        {
            return m_opacity;
        }

    protected slots:
        void onClickTimerTimeout();

        void setHoverOpacity(qreal hoverOpacity);
        void setClickOpacity(qreal clickOpacity);
        void setOpacity(qreal opacity);

    signals:
        void clicked(QMaskedButton *button);
        void longClicked(QMaskedButton *button);
        void doubleClicked(QMaskedButton *button);

        void clicked();
        void longClicked();
        void doubleClicked();

        void pixmapChanged();
        void hoverPixmapChanged();
        void clickPixmapChanged();

    private:
        bool m_pressed = false;
        bool m_longPressed = false;
        bool m_hover = false;
        bool m_updating = false;

        QTimer *m_clickTimer = nullptr;

        QPixmap m_pixmap;
        QPixmap m_hoverPixmap;
        QPixmap m_clickPixmap;

        QBitmap m_mask;
        QBitmap m_hoverMask;
        QBitmap m_clickMask;

        qreal m_hoverOpacity = 0.0;
        qreal m_clickOpacity = 0.0;
        qreal m_opacity = 1.0;

        QPropertyAnimation *m_hoverAnimation = nullptr;
        QPropertyAnimation *m_clickAnimation = nullptr;
        QPropertyAnimation *m_pixmapAnimation = nullptr;
        QParallelAnimationGroup *m_animationGroup = nullptr;

        Q_PROPERTY(QPixmap pixmap READ pixmap WRITE setPixmap NOTIFY pixmapChanged FINAL)
        Q_PROPERTY(QPixmap hoverPixmap READ hoverPixmap WRITE setHoverPixmap NOTIFY hoverPixmapChanged FINAL)
        Q_PROPERTY(QPixmap clickPixmap READ clickPixmap WRITE setClickPixmap NOTIFY clickPixmapChanged FINAL)
        Q_PROPERTY(qreal hoverOpacity READ hoverOpacity WRITE setHoverOpacity)
        Q_PROPERTY(qreal clickOpacity READ clickOpacity WRITE setClickOpacity)
        Q_PROPERTY(qreal opacity READ opacity WRITE setOpacity)
};

#endif // QMASKEDBUTTON_H
