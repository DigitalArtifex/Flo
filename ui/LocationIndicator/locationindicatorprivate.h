#ifndef LOCATIONINDICATORPRIVATE_H
#define LOCATIONINDICATORPRIVATE_H

#include <QObject>
#include <QPropertyAnimation>

class LocationIndicatorPrivate : public QObject
{
    Q_OBJECT
public:
    explicit LocationIndicatorPrivate(QObject *parent = nullptr);
    ~LocationIndicatorPrivate();

    qreal x() const;

    qreal y() const;

    bool animated() const;

public slots:
    void setX(qreal x);
    void setY(qreal y);

    void setAnimated(bool animated);

protected slots:
    void setXPrivate(qreal x);
    void setYPrivate(qreal y);

signals:
    void xChanged();
    void yChanged();

    void animatedChanged();

private:
    QPropertyAnimation *m_xAnimation = nullptr;
    QPropertyAnimation *m_yAnimation = nullptr;

    bool m_animated = true;

    qreal m_x = 0;
    qreal m_y = 0;

    Q_PROPERTY(qreal x READ x WRITE setXPrivate NOTIFY xChanged FINAL)
    Q_PROPERTY(qreal y READ y WRITE setYPrivate NOTIFY yChanged FINAL)
    Q_PROPERTY(bool animated READ animated WRITE setAnimated NOTIFY animatedChanged FINAL)
};

#endif // LOCATIONINDICATORPRIVATE_H
