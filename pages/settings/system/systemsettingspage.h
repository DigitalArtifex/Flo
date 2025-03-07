/*
* Flo :: SystemSettingsPage
*
* Provides a configuration page for current system settings
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

#ifndef SYSTEMSETTINGSPAGE_H
#define SYSTEMSETTINGSPAGE_H

#include <QFrame>

namespace Ui {
class SystemSettingsPage;
}

class SystemSettingsPage : public QFrame
{
        Q_OBJECT

    public:
        explicit SystemSettingsPage(QWidget *parent = nullptr);
        ~SystemSettingsPage();

        void reset();
        void apply();
        bool requiresRestart();

    private:
        Ui::SystemSettingsPage *ui;

        bool m_requiresRestart = false;
};

#endif // SYSTEMSETTINGSPAGE_H
