#ifndef MENUBUTTON_H
#define MENUBUTTON_H

#include <QFrame>
#include <QPixmap>
#include <QIcon>
#include <QStyle>
#include <QMouseEvent>

namespace Ui {
class MenuButton;
}

class MenuButton : public QFrame
{
    Q_OBJECT
    QString icon;
    QString text;
    int id;
    bool pressed = false;

public:
    explicit MenuButton(int id, QWidget *parent = nullptr);
    ~MenuButton();

    void setIcon(QString icon);
    void setText(QString text);
    void setChecked(bool checked);

    QString getText();
    int getId();

signals:
    void clicked(MenuButton *button);


private slots:
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void paintEvent(QPaintEvent *event);

private:
    Ui::MenuButton *ui;
    bool m_checked = false;

};

#endif // MENUBUTTON_H
