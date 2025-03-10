/*
* LineGraphWidget
*
* Provides a widget for a QML Line Graph as a replacement for QtCharts
*
* Copyright (C) 2024-2025 DigitalArtifex
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef LINEGRAPHWIDGET_H
#define LINEGRAPHWIDGET_H

#include <QObject>
#include <QFrame>
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

class LineGraphWidget : public QFrame
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
