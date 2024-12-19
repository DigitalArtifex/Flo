#include "settingspage.h"
#include "system/qklipperinstancepool.h"
#include "ui_settingspage.h"
#include "../../system/settings.h"
#include "printerlistitem.h"

SettingsPage::SettingsPage(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::SettingsPage)
{
    ui->setupUi(this);
    m_printerListWidget = new PrinterListWidget(ui->printerTab);
    ui->printerListLayout->addWidget(m_printerListWidget);
    updatePrinterList();

    m_themeSettingsPage = new ThemeSettingsPage(ui->themeTab);

    ui->tabWidget->setTabVisible(0, false);
    ui->tabWidget->setTabVisible(1, false);
    ui->tabWidget->setTabVisible(2, false);
    ui->tabWidget->setCurrentIndex(0);

    ui->themeTab->setLayout(new QVBoxLayout());
    ui->themeTab->layout()->setContentsMargins(0,0,0,0);
    ui->themeTab->layout()->setSpacing(0);
    ui->themeTab->layout()->addWidget(m_themeSettingsPage);

    m_systemSettingsPage = new SystemSettingsPage(ui->systemTab);

    ui->systemTab->setLayout(new QVBoxLayout());
    ui->systemTab->layout()->setContentsMargins(0,0,0,0);
    ui->systemTab->layout()->setSpacing(0);
    ui->systemTab->layout()->addWidget(m_systemSettingsPage);

    m_addPrinterButton = new QIconButton(this);
    m_addPrinterButton->setFixedSize(100,100);
    m_addPrinterButton->setIconSize(QSize(50,50));
    m_addPrinterButton->setIconAlignment(Qt::AlignCenter);
    m_addPrinterButton->setEnabled(true);
    ui->buttonLayout->addWidget(m_addPrinterButton);

    connect(m_addPrinterButton, SIGNAL(clicked()), this, SLOT(addPrinterButtonClickEvent()));

    m_editPrinterButton = new QIconButton(this);
    m_editPrinterButton->setFixedSize(100,100);
    m_editPrinterButton->setIconSize(QSize(50,50));
    m_editPrinterButton->setIconAlignment(Qt::AlignCenter);
    m_editPrinterButton->setEnabled(false);
    ui->buttonLayout->addWidget(m_editPrinterButton);

    connect(m_editPrinterButton, SIGNAL(clicked()), this, SLOT(editPrinterButtonClickEvent()));

    m_removePrinterButton = new QIconButton(this);
    m_removePrinterButton->setFixedSize(100,100);
    m_removePrinterButton->setIconSize(QSize(50,50));
    m_removePrinterButton->setIconAlignment(Qt::AlignCenter);
    m_removePrinterButton->setEnabled(false);
    ui->buttonLayout->addWidget(m_removePrinterButton);

    connect(m_removePrinterButton, SIGNAL(clicked()), this, SLOT(removePrinterButtonClickEvent()));

    m_printersActionButton = new QIconButton(this);
    m_printersActionButton->setFixedSize(250,50);
    m_printersActionButton->setText("Printers");
    m_printersActionButton->setEnabled(true);
    m_printersActionButton->setCheckable(true);
    m_printersActionButton->setExclusive(true);
    m_printersActionButton->setChecked(true);
    ui->actionBar->layout()->addWidget(m_printersActionButton);

    connect(m_printersActionButton, SIGNAL(clicked()), this, SLOT(printersActionButtonClickEvent()));

    m_themeActionButton = new QIconButton(this);
    m_themeActionButton->setFixedSize(250,50);
    m_themeActionButton->setText("Themes");

    m_themeActionButton->setEnabled(true);
    m_themeActionButton->setCheckable(true);
    m_themeActionButton->setExclusive(true);

    ui->actionBar->layout()->addWidget(m_themeActionButton);

    connect(m_themeActionButton, SIGNAL(clicked()), this, SLOT(themeActionButtonClickEvent()));

    ui->actionBar->layout()->addItem(new QSpacerItem(0,0,QSizePolicy::Expanding, QSizePolicy::Fixed));

    m_systemActionButton = new QIconButton(this);
    m_systemActionButton->setFixedSize(250,50);
    m_systemActionButton->setText("System");

    m_systemActionButton->setEnabled(true);
    m_systemActionButton->setCheckable(true);
    m_systemActionButton->setExclusive(true);

    ui->actionBar->layout()->addWidget(m_systemActionButton);

    connect(m_systemActionButton, SIGNAL(clicked()), this, SLOT(systemActionButtonClickEvent()));

    connect(m_printerListWidget, SIGNAL(itemSelected(PrinterListItem*)), this, SLOT(printerListWidgetItemSelectedEvent(PrinterListItem*)));

    setProperty("class", "Page");
    ui->actionBar->setProperty("class", "PageActionBar");

    //Setup footer buttons
    QGridLayout *layout = (QGridLayout*)ui->footerFrame->layout();
    layout->setContentsMargins(QMargins(0,0,0,0));

    m_resetButton = new QIconButton(ui->footerFrame);
    m_resetButton->setFixedSize(250, 50);
    m_resetButton->setText("Reset");
    layout->addWidget(m_resetButton,0,0);

    // m_footerSpacer = new QSpacerItem(0,0,QSizePolicy::Expanding, QSizePolicy::Ignored);
    // layout->addItem(m_footerSpacer,0,1);

    m_acceptButton = new QIconButton(ui->footerFrame);
    m_acceptButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    m_acceptButton->setFixedHeight(50);
    m_acceptButton->setText("Accept");
    layout->addWidget(m_acceptButton,0,3);

    m_cancelButton = new QIconButton(ui->footerFrame);
    m_cancelButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    m_cancelButton->setFixedHeight(50);
    m_cancelButton->setText("Cancel");
    layout->addWidget(m_cancelButton,0,2);

    connect(m_resetButton, SIGNAL(clicked()), this, SLOT(onResetButtonClicked()));
    connect(m_cancelButton, SIGNAL(clicked()), this, SLOT(onCancelButtonClicked()));
    connect(m_acceptButton, SIGNAL(clicked()), this, SLOT(onApplyButtonClicked()));

    ui->pageContents->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "Page"));
    ui->tabWidget->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "Page"));
    ui->printerTab->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "Page"));
    ui->systemTab->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "Page"));
    ui->themeTab->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "Page"));
    ui->footerFrame->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "Subwidget"));

    setupAnimations();
    setStyleSheet(Settings::currentTheme());
}

SettingsPage::~SettingsPage()
{
    delete ui;
}

void SettingsPage::updatePrinterList()
{
    QKlipperInstanceList printers = QKlipperInstancePool::pool()->klipperInstances();

    foreach(QKlipperInstance *printer, printers)
    {
        m_printerListWidget->addItem(printer);
    }
}

void SettingsPage::printerListWidgetItemSelectedEvent(PrinterListItem *item)
{
    if(item != nullptr)
    {
        m_editPrinterButton->setEnabled(true);
        m_removePrinterButton->setEnabled(true);
    }
    else
    {
        m_editPrinterButton->setEnabled(false);
        m_removePrinterButton->setEnabled(false);
    }
}

void SettingsPage::editPrinterButtonClickEvent()
{
    if(!m_editPrinterDialog)
        m_editPrinterDialog = new EditPrinterDialog(this);

    QKlipperInstance *printer = m_printerListWidget->selectedItem()->instance();

    m_editPrinterDialog->setPrinter(printer);
    m_editPrinterDialog->exec();

    m_editPrinterDialog->deleteLater();
    m_editPrinterDialog = nullptr;

    Settings::save();
}

void SettingsPage::addPrinterButtonClickEvent()
{
    if(!m_editPrinterDialog)
    {
        m_editPrinterDialog = new EditPrinterDialog(this);
        connect(m_editPrinterDialog, SIGNAL(finished(int)), this, SLOT(on_addPrinterWizardFinished(int)));
    }

    QKlipperInstance *printer = new QKlipperInstance();

    m_editPrinterDialog->setPrinter(printer, true);
    int ret = m_editPrinterDialog->exec();

    switch((QDialog::DialogCode)ret)
    {

    case QDialog::Rejected:
        delete printer;
        break;
    case QDialog::Accepted:
        QKlipperInstancePool::pool()->addInstance(printer);
        Settings::save();
        break;
    }

    m_editPrinterDialog->deleteLater();
    m_editPrinterDialog = nullptr;
}

void SettingsPage::removePrinterButtonClickEvent()
{
    if(m_printerListWidget->selectedItem())
    {
        m_editPrinterButton->setEnabled(false);
        m_removePrinterButton->setEnabled(false);
        QKlipperInstance *instance = m_printerListWidget->selectedItem()->instance();
        Settings::removeInstance(instance);
        QKlipperInstancePool::removeInstance(instance);
        Settings::save();
        updatePrinterList();
    }
}

void SettingsPage::printersActionButtonClickEvent()
{
    m_themeActionButton->setChecked(false);
    m_systemActionButton->setChecked(false);
    ui->tabWidget->setCurrentIndex(0);
    hideFooter();
}

void SettingsPage::themeActionButtonClickEvent()
{
    m_printersActionButton->setChecked(false);
    m_systemActionButton->setChecked(false);
    ui->tabWidget->setCurrentIndex(1);
    showFooter();
}

void SettingsPage::systemActionButtonClickEvent()
{
    m_printersActionButton->setChecked(false);
    m_themeActionButton->setChecked(false);
    ui->tabWidget->setCurrentIndex(2);
    showFooter();
}

void SettingsPage::onResetButtonClicked()
{
    reset();
}

void SettingsPage::onCancelButtonClicked()
{
    reset();
}

void SettingsPage::onApplyButtonClicked()
{
    apply();
    Settings::save();
}

void SettingsPage::hideFooter()
{
    if(!m_isFooterShown)
        return;

    m_isFooterShown = false;

    m_footerInGeometry = ui->footerFrame->geometry();
    m_footerOutGeometry = m_footerInGeometry;
    m_footerOutGeometry.setY(m_footerOutGeometry.y() + m_footerOutGeometry.height());
    m_footerOutGeometry.setHeight(0);

    if(Settings::isAnimationEnabled())
    {
        QRect currentRect = m_footerInGeometry;
        QRect currentPageRect = ui->pageContents->geometry();

        bool isRunning = (m_footerAnimationGroup->state() == QParallelAnimationGroup::Running);

        if(isRunning)
        {
            m_footerAnimationGroup->pause();
            currentRect = ui->footerFrame->geometry();
        }

        m_footerAnimation->setStartValue(currentRect);
        m_footerAnimation->setEndValue(m_footerOutGeometry);
        m_footerAnimation->setDuration(Settings::animationDuration());

        m_pageAnimation->setStartValue(currentPageRect.size());
        currentPageRect.setHeight(currentPageRect.height() + (m_footerInGeometry.height() + ui->mainLayout->layout()->spacing()));

        m_pageAnimation->setEndValue(currentPageRect.size());

        m_pageAnimation->setDuration(Settings::animationDuration());

        if(isRunning)
            m_footerAnimationGroup->resume();
        else
            m_footerAnimationGroup->start();

        ui->pageLayout->removeWidget(ui->footerFrame);
    }
    else
        onFooterAnimationFinished();
}

void SettingsPage::showFooter()
{
    if(m_isFooterShown)
        return;

    m_isFooterShown = true;

    if(Settings::isAnimationEnabled())
    {
        QRect currentRect = m_footerOutGeometry;
        QRect currentPageRect = ui->pageContents->geometry();

        bool isRunning = (m_footerAnimationGroup->state() == QParallelAnimationGroup::Running);

        if(isRunning)
        {
            m_footerAnimationGroup->pause();
            currentRect = ui->footerFrame->geometry();
        }

        m_footerAnimation->setStartValue(currentRect);
        m_footerAnimation->setEndValue(m_footerInGeometry);

        m_footerAnimation->setDuration(Settings::animationDuration());

        qDebug() << currentPageRect;
        m_pageAnimation->setStartValue(currentPageRect.size());
        currentPageRect.setHeight(currentPageRect.height() - (m_footerInGeometry.height() + ui->mainLayout->layout()->spacing()));

        qDebug() << currentPageRect;
        m_pageAnimation->setEndValue(currentPageRect.size());

        m_pageAnimation->setDuration(Settings::animationDuration());

        if(isRunning)
            m_footerAnimationGroup->resume();
        else
            m_footerAnimationGroup->start();

        ui->footerFrame->setVisible(true);
    }
    else
    {
        ui->pageLayout->addWidget(ui->footerFrame, 2, 0, 1, 1);
        ui->footerFrame->setVisible(true);
    }
}

void SettingsPage::setupAnimations()
{
    m_footerAnimation = new QPropertyAnimation(ui->footerFrame, "geometry", this);
    m_footerAnimation->setDuration(Settings::animationDuration());
    m_footerAnimation->setEasingCurve(QEasingCurve::Linear);

    m_pageAnimation = new QPropertyAnimation(ui->pageContents, "size", this);
    m_pageAnimation->setDuration(Settings::animationDuration());
    m_pageAnimation->setEasingCurve(QEasingCurve::Linear);

    m_footerAnimationGroup = new QParallelAnimationGroup(this);
    m_footerAnimationGroup->addAnimation(m_footerAnimation);
    //m_footerAnimationGroup->addAnimation(m_pageAnimation);

    connect(m_footerAnimationGroup, SIGNAL(finished()), this, SLOT(onFooterAnimationFinished()));
}

void SettingsPage::onFooterAnimationFinished()
{
    if(!m_isFooterShown)
    {
        ui->footerFrame->setVisible(false);
        //ui->pageLayout->removeWidget(ui->footerFrame);
    }
    else
        ui->pageLayout->addWidget(ui->footerFrame);
}

void SettingsPage::setupIcons()
{
    m_addPrinterButton->setIcon(Settings::getThemeIcon("printer-add"));
    m_editPrinterButton->setIcon(Settings::getThemeIcon("printer-edit"));
    m_removePrinterButton->setIcon(Settings::getThemeIcon("printer-remove"));
    m_printersActionButton->setIcon(Settings::getThemeIcon("printer"));
    m_systemActionButton->setIcon(Settings::getThemeIcon("settings"));
    m_cancelButton->setIcon(Settings::getThemeIcon("cancel"));
    m_acceptButton->setIcon(Settings::getThemeIcon("accept"));
    m_resetButton->setIcon(Settings::getThemeIcon("refresh"));
    m_themeActionButton->setIcon(Settings::getThemeIcon("theme"));
}

void SettingsPage::reset()
{
    if(m_systemSettingsPage)
        m_systemSettingsPage->reset();

    if(m_themeSettingsPage)
        m_themeSettingsPage->reset();
}

void SettingsPage::apply()
{
    if(m_systemSettingsPage)
        m_systemSettingsPage->apply();

    if(m_themeSettingsPage)
        m_themeSettingsPage->apply();

    if(m_systemSettingsPage->requiresRestart())
    {
        QMessageBox msgBox;
        msgBox.setText("Restart Required");
        msgBox.setInformativeText("Changes made to the settings require the application to restart.");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        int ret = msgBox.exec();

        QCoreApplication::exit(APPLICATION_RESTART_CODE);
    }
}

void SettingsPage::setStyleSheet(const QString &styleSheet)
{
    setupIcons();

    if(m_themeSettingsPage)
        m_themeSettingsPage->setStyleSheet(styleSheet);

    if(m_systemSettingsPage)
        m_systemSettingsPage->setStyleSheet(styleSheet);

    m_addPrinterButton->setStyleSheet(styleSheet);
    m_editPrinterButton->setStyleSheet(styleSheet);
    m_removePrinterButton->setStyleSheet(styleSheet);
    m_printersActionButton->setStyleSheet(styleSheet);
    m_systemActionButton->setStyleSheet(styleSheet);
    m_cancelButton->setStyleSheet(styleSheet);
    m_acceptButton->setStyleSheet(styleSheet);
    m_resetButton->setStyleSheet(styleSheet);
    m_themeActionButton->setStyleSheet(styleSheet);

    QFrame::setStyleSheet(styleSheet);
    style()->polish(this);
}

void SettingsPage::resizeEvent(QResizeEvent *event)
{
    QFrame::resizeEvent(event);

    //set expanded size for animations
    if(ui->footerFrame->isVisible() && (m_footerAnimation->state() == QParallelAnimationGroup::Stopped))
    {
        m_footerInGeometry = ui->footerFrame->geometry();
        m_footerOutGeometry = QRect(m_footerInGeometry.x(),m_footerInGeometry.y(), m_footerInGeometry.width(), 0);
    }
}

void SettingsPage::showEvent(QShowEvent *event)
{
    //set expanded size for animations
    if(ui->footerFrame->isVisible() && (m_footerAnimation->state() == QParallelAnimationGroup::Stopped))
    {
        m_footerInGeometry = ui->footerFrame->geometry();
        m_footerOutGeometry = QRect(m_footerInGeometry.x(), m_footerInGeometry.height(), m_footerInGeometry.width(), 0);
    }

    if(ui->tabWidget->currentIndex() == 0)
    {
        hideFooter();
    }

    QFrame::showEvent(event);
}

