#ifndef BEDMESHITEMFRAME_H
#define BEDMESHITEMFRAME_H

#include <QFrame>
#include <QStyle>

namespace Ui {
class BedMeshItemFrame;
}

class BedMeshItemFrame : public QFrame
{
    Q_OBJECT

public:
    explicit BedMeshItemFrame(QWidget *parent = nullptr);
    ~BedMeshItemFrame();

    qreal value() const;

    void setValue(qreal value);

private:
    Ui::BedMeshItemFrame *ui;

    qreal _value = 0.0000;
    qreal _thresholdLow = -0.02;
    qreal _thresholdHigh = 0.02;
};

#endif // BEDMESHITEMFRAME_H
