#ifndef PROBEDMESHFRAME_H
#define PROBEDMESHFRAME_H

#include <QFrame>
#include <QGridLayout>
#include <QLabel>
#include <QMovie>

#include <QKlipper/qklipper.h>
#include "ui/qwidgetanimation.h"
#include "ui/common/cardwidget/cardwidget.h"

#include "empty/probedmeshemptyframe.h"
#include "item/probedmeshitemframe.h"

class ProbedMeshFrame : public CardWidget
{
    Q_OBJECT
public:
    explicit ProbedMeshFrame(QKlipperPrintBed *bed, QWidget *parent = nullptr);
    ~ProbedMeshFrame();

public slots:
    virtual void changeEvent(QEvent *event) override;

protected:
    void setupIcons();

protected slots:

    void onBedMeshCalibratingFinished();

    void clearLayout();

private:
    QWidget *m_centralWidget = nullptr;
    QGridLayout *m_centralLayout = nullptr;

    ProbedMeshEmptyFrame *m_emptyFrame = nullptr;

    QKlipperPrintBed *m_printerBed;

    bool m_calibrating = false;
};

#endif // PROBEDMESHFRAME_H
