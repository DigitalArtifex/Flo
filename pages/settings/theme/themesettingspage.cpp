#include "themesettingspage.h"
#include "ui_themesettingspage.h"

ThemeSettingsPage::ThemeSettingsPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ThemeSettingsPage)
{
    ui->setupUi(this);

    reset();
}

ThemeSettingsPage::~ThemeSettingsPage()
{
    delete ui;
}

void ThemeSettingsPage::reset()
{
    ui->codeBlockLineEdit->setText(Settings::get("color_CodeBlock").toString());
    ui->codeBuiltInLineEdit->setText(Settings::get("color_CodeBuiltIn").toString());
    ui->codeCommentLineEdit->setText(Settings::get("color_CodeComment").toString());
    ui->codeKeywordLineEdit->setText(Settings::get("color_CodeKeyWord").toString());
    ui->codeOtherLineEdit->setText(Settings::get("color_CodeOther").toString());
    ui->codeStringLineEdit->setText(Settings::get("color_CodeString").toString());
    ui->codeTypeLineEdit->setText(Settings::get("color_CodeType").toString());
    ui->codeNumberLineEdit->setText(Settings::get("color_CodeNumLiteral").toString());
}
