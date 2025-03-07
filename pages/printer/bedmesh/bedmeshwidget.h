#ifndef BEDMESHWIDGET_H
#define BEDMESHWIDGET_H

#include <QObject>
#include <QWidget>
#include <QGridLayout>
#include <Q3DScene>
#include <QtGui/qguiapplication.h>
#include <QtQuick/QtQuickDepends>
#include <QQmlContext>
#include <Qt3DQuickDepends>
#include <QtQuick3DDepends>
#include <QQuick3D>
#include <QQuickView>
#include <QQmlEngine>
#include <QOpenGLWidget>
#include <QtGraphs/QAbstractAxis>
#include <QtGraphs/QAreaSeries>

#include <QKlipper/qklipper.h>
#include <QtDAWidgets/qthrobberwidget.h>
#include <QtQuickWidgets/qquickwidget.h>
#include "bedmeshdata.h"

#include "adjustment/adjustmentscrewframe.h"
#include "common/CardWidget/cardwidget.h"
#include "common/Page/page.h"
#include "health/bedmeshhealthcard.h"
#include "probed/probedmeshframe.h"

class BedMeshWidget : public Page
{
        Q_OBJECT
    public:
        explicit BedMeshWidget(QKlipperPrintBed *bed, QWidget *parent = 0);
        ~BedMeshWidget();
        virtual void setStyleSheet(QString styleSheet);

    protected:
        void setupUi();
        void setupViewer();
        void setupSidebar();
        void setupButtonBox();

    protected slots:
        void onHomeButtonClicked();
        void onCalibrateMeshButtonClicked();
        void onCalibrateScrewsButtonClicked();
        void onToolheadHomedChanged();

    private:
        QGridLayout *m_layout = nullptr;
        QGridLayout *m_centralLayout = nullptr;
        QGridLayout *m_contentLayout = nullptr;
        QGridLayout *m_sidebarLayout = nullptr;
        QWidget *m_centralWidget = nullptr;
        QWidget *m_viewerWidget = nullptr;
        QWidget *m_sideBarWidget = nullptr;
        QQuickView *m_viewer = nullptr;
        QQuickWidget *m_bedMeshWidget = nullptr;
        QKlipperPrintBed *m_printBed = nullptr;
        BedMeshData *m_data = nullptr;

        BedMeshHealthCard *m_healthCard = nullptr;
        ProbedMeshFrame *m_bedMeshFrame = nullptr;
        AdjustmentScrewFrame *m_adjustmentScrewFrame = nullptr;
        CardWidget *m_bedMeshCard = nullptr;

        QHBoxLayout *m_buttonBoxLayout = nullptr;
        QWidget *m_buttonBoxWidget = nullptr;

        QIconButton *m_homeButton = nullptr;
        QIconButton *m_calibrateMeshButton = nullptr;
        QIconButton *m_calibrateScrewsButton = nullptr;
        QIconButton *m_closeButton = nullptr;
};

#endif // BEDMESHWIDGET_H
