#ifndef POPUP_H
#define POPUP_H

#include <QFrame>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include <QMap>
#include <QPoint>

#include "../types/klipperfile.h"

namespace Ui {
class Popup;
}

class Popup : public QFrame
{
    Q_OBJECT

public:
    explicit Popup(QString title, QWidget *parent = nullptr);
    ~Popup();

    void setFileMode(KlipperFile file);
    void setInputMode(QString acceptText = "Accept", QString cancelText = "Cancel");

    void showPopup();
    void hidePopup();

    virtual void repaint();

signals:
    void accepted(QVariant data);
    void canceled(QVariant data);
    void deleteFile(QVariant file);

private slots:
    void on_cancelButton_clicked();

    void on_acceptButton_clicked();

    void on_deleteButton_clicked();

    void on_animationOutFinished();

    void on_closeButton_clicked();

    void on_acceptButton_2_clicked();

    void on_cancelButton_2_clicked();

    void on_lineEdit_textChanged(const QString &arg1);

private:
    void setupUiClasses();
    Ui::Popup *ui;
    QVariant data;
    QGraphicsOpacityEffect *overlayOpacityEffect;
    QGraphicsOpacityEffect *popupOpacityEffect;

    QPropertyAnimation *overlayOpacityAnimation;
    QPropertyAnimation *popupOpacityAnimation;
    QPropertyAnimation *popupInAnimation;
    QPropertyAnimation *popupOutAnimation;
};

#endif // POPUP_H
