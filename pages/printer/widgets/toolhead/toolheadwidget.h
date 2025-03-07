/*
* Flo :: ToolheadWidget
*
* Provides a widget to control various aspects of the toolhead
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

#ifndef TOOLHEADWIDGET_H
#define TOOLHEADWIDGET_H

#include <QFrame>
#include <QLineEdit>
#include "control/toolheadcontrolframe.h"
#include "dialogs/InputShaper/inputshaperwizard.h"
#include "dialogs/ZOffsetWizard/zoffsetwizard.h"

namespace Ui {
class ToolheadWidget;
}

class ToolheadWidget : public QFrame
{
    Q_OBJECT

public:
    explicit ToolheadWidget(QKlipperInstance *instance, QWidget *parent = nullptr);
    ~ToolheadWidget();

protected:
    void setIcons();
    virtual void changeEvent(QEvent *event) override;

private slots:
    void onToolheadPositionChanged();
    void onToolHeadDestinationChanged();
    void onToolHeadIsHomedChanged();

    void onZOffsetWizardFinished(int returnCode);
    void onInputShaperWizardFinished(int returnCode);

    void on_posIncrementSelect_currentTextChanged(const QString &arg1);
    void on_xDestinationSpinBox_valueChanged(double arg1);
    void on_yDestinationSpinBox_valueChanged(double arg1);
    void on_zDestinationSpinBox_valueChanged(double arg1);
    void on_positionResetButton_clicked();
    void on_positionApplyButton_clicked();

    void on_zOffsetWizardButton_clicked();

    void on_inputShaperButton_clicked();

signals:
    void dialogRequested(QDialog *);
    void wizardRequested(QWizard *);

private:
    InputShaperWizard *m_inputShaperWizard = nullptr;
    ZOffsetWizard *m_zOffsetWizard = nullptr;

    bool xPosEditing = false;
    bool yPosEditing = false;
    bool zPosEditing = false;

    QRegularExpression m_number_expression = QRegularExpression("\\d+");
    QKlipperPrinter *m_printer = nullptr;
    QKlipperInstance *m_instance = nullptr;

    Ui::ToolheadWidget *ui;

    ToolHeadControlFrame *m_toolheadControlFrame = nullptr;
};

#endif // TOOLHEADWIDGET_H
