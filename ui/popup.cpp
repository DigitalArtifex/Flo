#include "popup.h"
#include "ui_popup.h"

#include "../system/settings.h"

Popup::Popup(QString title, QWidget *parent) :
    QFrame(parent),
    ui(new Ui::Popup)
{
    ui->setupUi(this);
    this->setupUiClasses();
    ui->popupTitle->setText(title);
    popupOpacityEffect = new QGraphicsOpacityEffect(this);
    overlayOpacityEffect = new QGraphicsOpacityEffect(this);

    this->overlayOpacityAnimation = new QPropertyAnimation(this->overlayOpacityEffect, "opacity", this);
    this->overlayOpacityAnimation->setDuration(200);

    this->popupOpacityAnimation = new QPropertyAnimation(this->popupOpacityEffect, "opacity", this);
    this->popupOpacityAnimation->setDuration(200);

    this->popupInAnimation = new QPropertyAnimation(ui->popupFrame, "pos", this);
    this->popupInAnimation->setDuration(250);

    this->popupOutAnimation = new QPropertyAnimation(ui->popupFrame, "pos", this);
    this->popupOutAnimation->setDuration(250);
}

Popup::~Popup()
{
    delete ui;
}

void Popup::setFileMode(KlipperFile file)
{
    ui->lineEdit->setHidden(true);
    ui->acceptButton_2->setHidden(true);
    ui->cancelButton_2->setHidden(true);
    this->data = QVariant::fromValue(file);
    ui->fileName->setText(file.fileLocation);
    ui->informationList->addAction(QString("Size: ") + QString::number(file.fileSize));
    ui->acceptButton->setText(QString("Print"));
}

void Popup::setInputMode(QString acceptText, QString cancelText)
{
    ui->thumbnail->setHidden(true);
    ui->fileName->setHidden(true);
    ui->acceptButton->setHidden(true);
    ui->deleteButton->setHidden(true);
    ui->informationList->setHidden(true);
    ui->cancelButton->setHidden(true);
    ui->acceptButton->setText(acceptText);
    ui->cancelButton->setText(cancelText);
}

void Popup::showPopup()
{
    ui->closeButton->setIcon(Settings::getThemeIcon("close-icon"));
    this->setHidden(false);
    this->style()->polish(this);
    this->setWindowFlag(Qt::CoverWindow);
    this->showMaximized();
}

void Popup::hidePopup()
{
    this->close();
}

void Popup::repaint()
{
    this->style()->polish(this);
    QFrame::repaint();
}

void Popup::setupUiClasses()
{
    this->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "PopupOverlay"));
    ui->popupFrame->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "Popup"));
    ui->popupTitleFrame->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "PopupTitleBar"));
    ui->popupTitle->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "PopupTitle"));
    ui->informationList->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "PopupInformationList"));
    ui->acceptButton->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "PopupAcceptButton" << "PopupButton"));
    ui->acceptButton_2->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "PopupAcceptButton" << "PopupButton"));
    ui->cancelButton->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "PopupCancelButton" << "PopupButton"));
    ui->deleteButton->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "PopupDeleteButton" << "PopupButton"));
    ui->closeButton->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "PopupCloseButton"));
    ui->cancelButton_2->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "PopupDeleteButton" << "PopupButton"));
    this->style()->polish(this);
}

void Popup::on_cancelButton_clicked()
{
    hidePopup();
    emit(canceled(this->data));
}


void Popup::on_acceptButton_clicked()
{
    hidePopup();
    emit(accepted(this->data));
}


void Popup::on_deleteButton_clicked()
{
    hidePopup();
    emit(deleteFile(this->data));
}

void Popup::on_animationOutFinished()
{
    this->overlayOpacityAnimation->setStartValue(0.9);
    this->overlayOpacityAnimation->setEndValue(0);
    this->close();
}


void Popup::on_closeButton_clicked()
{
    on_cancelButton_clicked();
}


void Popup::on_acceptButton_2_clicked()
{
    on_acceptButton_clicked();
}


void Popup::on_cancelButton_2_clicked()
{
    on_cancelButton_clicked();
}


void Popup::on_lineEdit_textChanged(const QString &arg1)
{
    this->data = arg1;
}

