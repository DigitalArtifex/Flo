/*
* Flo :: ExtruderMaterialsDialog
*
* Provides a dialog for material retraction/extrusion info
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

#ifndef EXTRUDERMATERIALSDIALOG_H
#define EXTRUDERMATERIALSDIALOG_H

#include <QObject>
#include <QQmlEngine>
#include <QWidget>
#include <QGridLayout>
#include <QGroupBox>
#include <QDoubleSpinBox>

#include <common/dialog/dialog.h>
#include <ui/QIconButton/qiconbutton.h>

class ExtruderMaterialsDialog : public Dialog
{
        Q_OBJECT
        QML_ELEMENT
    public:
        enum MaterialDirection
        {
            None,
            MaterialExtrude,
            MaterialRetract
        };

        explicit ExtruderMaterialsDialog(QWidget *parent = nullptr);

        MaterialDirection materialDirection() const;

        qreal distance() const;

        qreal speed() const;

    public slots:
        void setMaterialDirection(MaterialDirection materialDirection);

        void setDistance(qreal distance);

        void setSpeed(qreal speed);

    signals:

        void materialDirectionChanged();

        void distanceChanged();

        void speedChanged();

    protected:
        virtual void changeEvent(QEvent *event) override;

    private slots:
        void setupUi();
        void setupIcons();

    private:
        QGridLayout *m_centralLayout = nullptr;

        QWidget *m_footerWidget = nullptr;
        QIconButton *m_extrudeButton = nullptr;
        QIconButton *m_cancelButton = nullptr;

        QGroupBox *m_distanceGroupBox = nullptr;
        QDoubleSpinBox *m_distanceSpinBox = nullptr;
        QLabel *m_distanceUnitLabel = nullptr;

        QGroupBox *m_speedGroupBox = nullptr;
        QDoubleSpinBox *m_speedSpinBox = nullptr;
        QLabel *m_speedUnitLabel = nullptr;

        MaterialDirection m_materialDirection = None;

        qreal m_distance = 0;
        qreal m_speed = 0;

        Q_PROPERTY(MaterialDirection materialDirection READ materialDirection WRITE setMaterialDirection NOTIFY materialDirectionChanged FINAL)
        Q_PROPERTY(qreal distance READ distance WRITE setDistance NOTIFY distanceChanged FINAL)
        Q_PROPERTY(qreal speed READ speed WRITE setSpeed NOTIFY speedChanged FINAL)
};

#endif // EXTRUDERMATERIALSDIALOG_H
