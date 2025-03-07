/*
* Flo :: PidDialog
*
* Provides a means of grabbing user input for running a PID Tune
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

#ifndef PIDDIALOG_H
#define PIDDIALOG_H

#include <QObject>
#include <QWidget>
#include <QGroupBox>
#include <QDoubleSpinBox>

#include <common/dialog/dialog.h>
#include <ui/QIconButton/qiconbutton.h>

class PidDialog : public Dialog
{
        Q_OBJECT
    public:
        explicit PidDialog(QWidget *parent = nullptr);

        qreal target() const;

    public slots:
        void setTarget(qreal target);

    signals:

        void targetChanged();

    protected:
        virtual void changeEvent(QEvent *event) override;

    private slots:
        void setupUi();
        void setupIcons();

    private:
        QGridLayout *m_centralLayout = nullptr;

        QWidget *m_footerWidget = nullptr;
        QIconButton *m_acceptButton = nullptr;
        QIconButton *m_rejectButton = nullptr;

        QGroupBox *m_targetGroupBox = nullptr;
        QDoubleSpinBox *m_targetSpinBox = nullptr;

        qreal m_target = 0;

        QLabel *m_pidText = nullptr;

        Q_PROPERTY(qreal target READ target WRITE setTarget NOTIFY targetChanged FINAL)
};

#endif // PIDDIALOG_H
