#ifndef CIRCULARPROGRESSBAR_H
#define CIRCULARPROGRESSBAR_H

#include<QObject>
#include <QWidget>
#include <QPainter>
#include <QPainterPath>
#include <QFont>
#include <QFontDatabase>


class CircularProgressBar : public QWidget {
    Q_OBJECT
    qreal progress; // progress 0.0 to 1.0
    qreal min = 0;
    qreal max = 100;
    qreal current = 0;

public:
    enum Mode
    {
        Percent,
        Temperature,
        Value
    };

    CircularProgressBar(QWidget * parent = 0, Mode mode = Percent) : QWidget(parent)
    {
        m_mode = mode;
        setMinimumSize(104, 104);
        setMaximumSize(104, 104);
        progress = 0.285;

        int id = QFontDatabase::addApplicationFont(":/fonts/digital-7(mono).ttf");
        m_fontFamily = QFontDatabase::applicationFontFamilies(id).at(0);
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

private:
    Mode m_mode = Percent;
    QString m_fontFamily;
};

#endif // CIRCULARPROGRESSBAR_H
