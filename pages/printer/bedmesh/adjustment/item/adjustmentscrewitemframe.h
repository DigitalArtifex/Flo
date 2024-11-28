#ifndef ADJUSTMENTSCREWITEMFRAME_H
#define ADJUSTMENTSCREWITEMFRAME_H

#include <QFrame>
#include <QPixmap>
#include <QLabel>
#include <QHBoxLayout>

#include <QKlipper/qklipper.h>

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
    QKlipperAdjustmentScrew *m_adjustmentScrew = nullptr;
    QLabel *m_iconLabel = nullptr;
    QLabel *m_screwNameLabel = nullptr;
    QLabel *m_adjustmentLabel= nullptr;
    QHBoxLayout *m_layout = nullptr;
};

#endif // ADJUSTMENTSCREWITEMFRAME_H
