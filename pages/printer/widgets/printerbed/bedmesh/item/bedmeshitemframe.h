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

    qreal m_value = 0.0000;
    qreal m_thresholdLow = -0.02;
    qreal m_thresholdHigh = 0.02;
};

#endif // BEDMESHITEMFRAME_H
