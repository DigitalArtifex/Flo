#ifndef SETTINGSPAGE_H
#define SETTINGSPAGE_H

#include <QFrame>

namespace Ui {
class SettingsPage;
}

class SettingsPage : public QFrame
{
    Q_OBJECT

public:
    explicit SettingsPage(QWidget *parent = nullptr);
    ~SettingsPage();

private:
    Ui::SettingsPage *ui;
};

#endif // SETTINGSPAGE_H
