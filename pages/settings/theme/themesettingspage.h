#ifndef THEMESETTINGSPAGE_H
#define THEMESETTINGSPAGE_H

#include <QWidget>
#include "../../../system/settings.h"

namespace Ui {
class ThemeSettingsPage;
}

class ThemeSettingsPage : public QWidget
{
    Q_OBJECT

public:
    explicit ThemeSettingsPage(QWidget *parent = nullptr);
    ~ThemeSettingsPage();

    void reset();

private:
    Ui::ThemeSettingsPage *ui;
};

#endif // THEMESETTINGSPAGE_H
