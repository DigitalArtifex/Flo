#ifndef LOCATIONINDICATOR_H
#define LOCATIONINDICATOR_H

#include <QWidget>
#include <QFrame>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>

#include "locationindicatorprivate.h"

class LocationIndicator : public QFrame
{
    Q_OBJECT
public:
    explicit LocationIndicator(QWidget *parent = nullptr);

    qreal x() const;

    qreal y() const;

    qreal xMaximum() const;

    qreal yMaximum() const;

    QColor crosshairColor() const;

    QColor pointColor() const;

public slots:
    void setX(qreal x);

    void setY(qreal y);

    void setXMaximum(qreal xMaximum);

    void setYMaximum(qreal yMaximum);

    void setCrosshairColor(const QColor &crosshairColor);

    void setPointColor(const QColor &pointColor);

protected:
    virtual void paintEvent(QPaintEvent *event) override;

signals:

    void xChanged();

    void yChanged();

    void xMaximumChanged();

    void yMaximumChanged();

    void crosshairColorChanged();

    void pointColorChanged();

private:
    LocationIndicatorPrivate *m_private = nullptr;
    QPropertyAnimation *m_xAnimation = nullptr;
    QPropertyAnimation *m_yAnimation = nullptr;
    QParallelAnimationGroup *m_animationGroup = nullptr;

    qreal m_x = 0;
    qreal m_y = 0;

    qreal m_xMaximum = 100;
    qreal m_yMaximum = 100;

    QColor m_crosshairColor;
    QColor m_pointColor;

    Q_PROPERTY(qreal x READ x WRITE setX NOTIFY xChanged FINAL)
    Q_PROPERTY(qreal y READ y WRITE setY NOTIFY yChanged FINAL)
    Q_PROPERTY(qreal xMaximum READ xMaximum WRITE setXMaximum NOTIFY xMaximumChanged FINAL)
    Q_PROPERTY(qreal yMaximum READ yMaximum WRITE setYMaximum NOTIFY yMaximumChanged FINAL)
    Q_PROPERTY(QColor crosshairColor READ crosshairColor WRITE setCrosshairColor NOTIFY crosshairColorChanged DESIGNABLE true)
    Q_PROPERTY(QColor pointColor READ pointColor WRITE setPointColor NOTIFY pointColorChanged DESIGNABLE true)
};

#endif // LOCATIONINDICATOR_H
