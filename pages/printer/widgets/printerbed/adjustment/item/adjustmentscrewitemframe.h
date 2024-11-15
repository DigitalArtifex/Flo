#ifndef ADJUSTMENTSCREWITEMFRAME_H
#define ADJUSTMENTSCREWITEMFRAME_H

#include <QFrame>
#include <QPixmap>

#include <QKlipper/qklipper.h>

namespace Ui {
class AdjustmentScrewItemFrame;
}

class AdjustmentScrewItemFrame : public QFrame
{
    Q_OBJECT

public:
    explicit AdjustmentScrewItemFrame(QWidget *parent = nullptr);
    ~AdjustmentScrewItemFrame();

    QKlipperAdjustmentScrew *adjustmentScrew() const;
    void setAdjustmentScrew(QKlipperAdjustmentScrew *adjustmentScrew);

public slots:
    void setupIcons();
    void setStyleSheet(const QString &styleSheet);

protected slots:
    void onAdjustmentScrewAmountChanged();

private:
    Ui::AdjustmentScrewItemFrame *ui;

    QKlipperAdjustmentScrew *m_adjustmentScrew = nullptr;
};

#endif // ADJUSTMENTSCREWITEMFRAME_H
