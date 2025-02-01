#include "systemsettingspage.h"
#include "flo/settings.h"
#include "ui_systemsettingspage.h"

SystemSettingsPage::SystemSettingsPage(QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::SystemSettingsPage)
{
    ui->setupUi(this);

    reset();
    setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "Page"));
    ui->scrollAreaWidgetContents->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "Page"));
}

SystemSettingsPage::~SystemSettingsPage()
{
    delete ui;
}

void SystemSettingsPage::reset()
{
    //ui->openGlCheckbox->setChecked(Settings::get("ui-opengl").toBool());
    ui->pageAnimationDurationSpinBox->setValue(Settings::get("ui/animations-duration", 500).toDouble());

    if(Settings::isAnimationEnabled())
        ui->pageAnimationEnableComboBox->setCurrentIndex(0);
    else
        ui->pageAnimationEnableComboBox->setCurrentIndex(1);

    if(Settings::isAnimationEffectsEnabled())
        ui->pageEffectsEnabledComboBox->setCurrentIndex(0);
    else
        ui->pageEffectsEnabledComboBox->setCurrentIndex(1);
}

void SystemSettingsPage::apply()
{
    // if(Settings::get("ui-opengl", false).toBool() != ui->openGlCheckbox->isChecked())
    // {
    //     Settings::set("ui-opengl", ui->openGlCheckbox->isChecked());
    //     m_requiresRestart = true;
    // }

    Settings::setAnimationDuration(ui->pageAnimationDurationSpinBox->value());

    if(ui->pageEffectsEnabledComboBox->currentIndex() == 0)
        Settings::setIsAnimationEffectsEnabled(true);
    else
        Settings::setIsAnimationEffectsEnabled(false);

    if(ui->pageAnimationEnableComboBox->currentIndex() == 0)
        Settings::setIsAnimationEnabled(true);
    else
        Settings::setIsAnimationEnabled(false);

    if(Settings::get("ui/virtual-keyboard", false).toBool() != ui->virtualKeyboardCheckBox->isChecked())
        Settings::set("ui/virtual-keyboard", ui->virtualKeyboardCheckBox->isChecked());

    Settings::save();
}

bool SystemSettingsPage::requiresRestart()
{
    return m_requiresRestart;
}
