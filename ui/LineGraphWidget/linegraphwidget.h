#ifndef LINEGRAPHWIDGET_H
#define LINEGRAPHWIDGET_H

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
#include <QtGraphs/QAbstractAxis>
#include <QtGraphs/QAreaSeries>

#include "linegraphdata.h"

class LineGraphWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LineGraphWidget(QWidget *parent = nullptr);
    ~LineGraphWidget();

    LineGraphData *data() const;

    QString gridMainColor() const;
    QString gridSubColor() const;
    QString axisYMainColor() const;
    QString axisYSubColor() const;
    QString axisXMainColor() const;
    QString axisXSubColor() const;

    qreal valueMinimum() const;
    qreal valueMaximum() const;

    QDateTime dateMaximum() const;
    QDateTime dateMinimum() const;

    QString valueLabelFormat() const;

    QString dateLabelFormat() const;

public slots:
    void setGridMainColor(const QString &gridMainColor);
    void setGridSubColor(const QString &gridSubColor);
    void setAxisYMainColor(const QString &axisYMainColor);
    void setAxisYSubColor(const QString &axisYSubColor);
    void setAxisXMainColor(const QString &axisXMainColor);
    void setAxisXSubColor(const QString &axisXSubColor);
    void setValueMaximum(const qreal &maximum);
    void setValueMinimum(const qreal &minimum);
    void setDateMaximum(const QDateTime &maximum);
    void setDateMinimum(const QDateTime &minimum);

    void setValueLabelFormat(const QString &valueLabelFormat);

    void setDateLabelFormat(const QString &dateLabelFormat);

signals:

private slots:
    void setupViewer();

private:
    QGridLayout *m_centralLayout = nullptr;
    QWidget *m_viewerWidget = nullptr;
    QQuickView *m_viewer = nullptr;

    LineGraphData *m_data;
};

#endif // LINEGRAPHWIDGET_H
