#ifndef BEDMESHWIDGET_H
#define BEDMESHWIDGET_H

#include <QObject>
#include <QWidget>
#include <QGridLayout>
#include <Q3DScene>
#include <QtGui/qguiapplication.h>
// #include <QtQml/qqmlengine.h>
// #include <QtQuick/qquickview.h>
#include <QtQuick/QtQuickDepends>
#include <QQmlContext>
#include <Qt3DQuickDepends>
#include <QtQuick3DDepends>
#include <QQuick3D>
#include <QQuickView>
#include <QQmlEngine>
//#include <QQmlApplicationEngine>
#include <QtGraphs/QAbstractAxis>
#include <QtGraphs/QAreaSeries>

#include <QKlipper/qklipper.h>
#include "bedmeshdata.h"

class BedMeshWidget : public QWidget
{
        Q_OBJECT
    public:
        explicit BedMeshWidget(QKlipperPrintBed *bed, QWidget *parent = 0);
        virtual void setStyleSheet(QString styleSheet);

    protected:
        void setupUi();
        void setupViewer();

    private:
        QGridLayout *m_layout = nullptr;
        QWidget *m_viewerWidget = nullptr;
        QQuickView *m_viewer = nullptr;
        QKlipperPrintBed *m_printBed = nullptr;
        BedMeshData *m_data = nullptr;
};

#endif // BEDMESHWIDGET_H
