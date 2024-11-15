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
