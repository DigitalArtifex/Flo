#ifndef PROBEDMESHITEMFRAME_H
#define PROBEDMESHITEMFRAME_H

#include <QFrame>
#include <QStyle>

namespace Ui {
class ProbedMeshItemFrame;
}

class ProbedMeshItemFrame : public QFrame
{
    Q_OBJECT

public:
    explicit ProbedMeshItemFrame(QWidget *parent = nullptr);
    ~ProbedMeshItemFrame();

    qreal value() const;

    void setValue(qreal value);

private:
    Ui::ProbedMeshItemFrame *ui;

    qreal m_value = 0.0000;
    qreal m_thresholdLow = -0.025;
    qreal m_thresholdHigh = 0.025;
};

#endif // PROBEDMESHITEMFRAME_H
