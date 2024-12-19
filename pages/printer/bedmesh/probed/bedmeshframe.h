#ifndef BEDMESHFRAME_H
#define BEDMESHFRAME_H

#include <QFrame>
#include <QGridLayout>
#include <QLabel>
#include <QMovie>

#include <QKlipper/qklipper.h>
#include "ui/qwidgetanimation.h"
#include "ui/common/cardwidget/cardwidget.h"

#include "empty/bedmeshemptyframe.h"
#include "item/bedmeshitemframe.h"

class BedMeshFrame : public CardWidget
{
    Q_OBJECT
public:
    explicit BedMeshFrame(QKlipperPrintBed *bed, QWidget *parent = nullptr);
    ~BedMeshFrame();

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

    BedMeshEmptyFrame *m_emptyFrame = nullptr;

    QKlipperPrintBed *m_printerBed;

    bool m_calibrating = false;
};

#endif // BEDMESHFRAME_H
