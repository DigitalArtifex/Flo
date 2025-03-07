/*
* Flo :: ZOffsetWizard
*
* Provides a means of running a Z-Offset Calibration in an easy to use QWizard
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

#ifndef ZOFFSETWIZARD_H
#define ZOFFSETWIZARD_H

#include <QWizard>
#include <QKlipper/qklipper.h>

namespace Ui {
class ZOffsetWizard;
}

class ZOffsetWizard : public QWizard
{
    Q_OBJECT

public:
    explicit ZOffsetWizard(QKlipperInstance *instance, QWidget *parent = nullptr);
    ~ZOffsetWizard();

    virtual bool validateCurrentPage() override;

private slots:
    void on_ZOffsetWizard_currentIdChanged(int id);
    void showErrorMessage(QString message);
    void goToHome();
    void onHomingStarted();
    void onHomingFinished();
    bool moveToolhead(qreal amount);
    bool acceptOffset();
    bool rejectOffset();
    bool saveOffset();

    void on_up0025Button_clicked();

    void on_up005Button_clicked();

    void on_up010Button_clicked();

    void on_up10Button_clicked();

    void on_down0025Button_clicked();

    void on_down005Button_clicked();

    void on_down010Button_clicked();

    void on_down10Button_clicked();

    void on_up050Button_clicked();

    void on_down050Button_clicked();

    void on_ZOffsetWizard_finished(int result);

private:
    Ui::ZOffsetWizard *ui;

    bool m_homingStarted = false;
    bool m_homingFinished = false;
    bool m_wizardStarted = false;

    QKlipperInstance *m_instance = nullptr;

    qreal m_offsetValue = 0.0;
};

#endif // ZOFFSETWIZARD_H
