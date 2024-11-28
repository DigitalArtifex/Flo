#ifndef ADJUSTMENTSCREWEMPTYFRAME_H
#define ADJUSTMENTSCREWEMPTYFRAME_H

#include <QFrame>
#include <QPixmap>
#include <QLabel>
#include <QMovie>
#include <QSpacerItem>
#include <QHBoxLayout>
#include "ui/QIconButton/qiconbutton.h"

#include <QStyle>

#include <QKlipper/qklipper.h>

class AdjustmentScrewEmptyFrame : public QFrame
{
    Q_OBJECT

public:
    explicit AdjustmentScrewEmptyFrame(QKlipperPrintBed *bed, QWidget *parent = nullptr);
    ~AdjustmentScrewEmptyFrame();

public slots:
    void setStyleSheet(const QString &styleSheet);
    virtual void setCalibrationEnabled(bool enabled);

signals:
    void calibrating();

private slots:
    void on_calibrateButton_clicked();
    void onToolheadHoming();
    void onToolheadHomingFinished();

    void on_homeButton_clicked();

private:

    QSpacerItem *m_rightSpacer = nullptr;
    QSpacerItem *m_topSpacer = nullptr;
    QSpacerItem *m_leftSpacer = nullptr;
    QSpacerItem *m_bottomSpacer = nullptr;

    QKlipperPrintBed *m_printerBed = nullptr;

    QLabel *m_iconLabel = nullptr;
    QLabel *m_textLabel = nullptr;
    QIconButton *m_homeButton = nullptr;
    QIconButton *m_calibrateButton = nullptr;
    QHBoxLayout *m_layout = nullptr;
};

#endif // ADJUSTMENTSCREWEMPTYFRAME_H
