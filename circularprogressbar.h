#ifndef CIRCULARPROGRESSBAR_H
#define CIRCULARPROGRESSBAR_H

#include<QObject>
#include <QWidget>
#include <QPainter>
#include <QPainterPath>


class CircularProgressBar : public QWidget {
    Q_OBJECT
    qreal progress; // progress 0.0 to 1.0
    qreal min = 0;
    qreal max = 100;
    qreal current = 0;

public:
    CircularProgressBar(QWidget * parent = 0) : QWidget(parent)
    {
        setMinimumSize(104, 104);
        setMaximumSize(104, 104);
        progress = 0.285;
    }
    void setMinimum(qreal min);
    void setMaximum(qreal max);
    void setProgress(qreal progress);

    void upd(qreal pp)
    {
        if (progress == pp) return;
        progress = pp;
        update();
    }
    void paintEvent(QPaintEvent *event);
};

#endif // CIRCULARPROGRESSBAR_H
