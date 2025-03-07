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
    QFont font;
    font.fromString(Settings::get("ui/font-string").toString());
    ui->fontComboBox->setCurrentFont(font);

    ui->openGlCheckbox->setChecked(Settings::get("ui-opengl").toBool());
    ui->pageAnimationDurationSpinBox->setValue(Settings::get("ui/animations-duration", 500).toDouble());
    ui->virtualKeyboardCheckBox->setChecked(Settings::get("ui/virtual-keyboard").toBool());
    ui->kioskModeCheckBox->setChecked(Settings::get("ui/kiosk-mode", false).toBool());

    if(Settings::isAnimationEnabled())
        ui->pageAnimationEnableComboBox->setCurrentIndex(0);
    else
        ui->pageAnimationEnableComboBox->setCurrentIndex(1);

    if(Settings::isAnimationEffectsEnabled())
        ui->pageEffectsEnabledComboBox->setCurrentIndex(0);
    else
        ui->pageEffectsEnabledComboBox->setCurrentIndex(1);

    ui->multimediaComboBox->clear();
    ui->multimediaComboBox->addItem(QString("FFMPEG (Default)"), QString("ffmpeg"));

#if defined(Q_OS_LINUX)
    ui->multimediaComboBox->addItem(QString("GStreamer"), QString("gstreamer"));

    if(Settings::get("ui/media-backend").toString() == QString("gstreamer"))
        ui->multimediaComboBox->setCurrentIndex(1);
#elif defined(Q_OS_WIN)
    ui->multimediaComboBox->addItem(QString("Windows Media"), QString("windowsmediafoundation"));

    ui->multimediaComboBox->addItem(QString("Direct Show"), QString("directshow"));

    if(Settings::get("ui/media-backend").toString() == QString("windowsmediafoundation"))
        ui->multimediaComboBox->setCurrentIndex(1);

    else if(Settings::get("ui/media-backend").toString() == QString("directshow"))
        ui->multimediaComboBox->setCurrentIndex(2);
#endif
}

void SystemSettingsPage::apply()
{
    // if(Settings::get("ui-opengl", false).toBool() != ui->openGlCheckbox->isChecked())
    // {
    //     Settings::set("ui-opengl", ui->openGlCheckbox->isChecked());
    //     m_requiresRestart = true;
    // }

    Settings::setAnimationDuration(ui->pageAnimationDurationSpinBox->value());

    Settings::set("ui/font-string", ui->fontComboBox->currentFont().toString());
    QApplication::setFont(ui->fontComboBox->currentFont());

    if(ui->pageEffectsEnabledComboBox->currentIndex() == 0)
        Settings::setIsAnimationEffectsEnabled(true);
    else
        Settings::setIsAnimationEffectsEnabled(false);

    if(ui->pageAnimationEnableComboBox->currentIndex() == 0)
        Settings::setIsAnimationEnabled(true);
    else
        Settings::setIsAnimationEnabled(false);

    if(Settings::get("ui/virtual-keyboard", false).toBool() != ui->virtualKeyboardCheckBox->isChecked())
    {
        Settings::set("ui/virtual-keyboard", ui->virtualKeyboardCheckBox->isChecked());
        m_requiresRestart = true;
    }

    Settings::set("ui/media-backend",ui->multimediaComboBox->currentData().toString());
    Settings::set("ui/kiosk-mode", ui->kioskModeCheckBox->isChecked());

    Settings::save();
}

bool SystemSettingsPage::requiresRestart()
{
    return m_requiresRestart;
}
