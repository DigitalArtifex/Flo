#ifndef MENUBUTTON_H
#define MENUBUTTON_H

#include <QFrame>
#include <QPixmap>
#include <QIcon>
#include <QStyle>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QPainter>

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

    void setIcon(QIcon icon);
    void setText(QString text);
    void setChecked(bool checked);

    QString getText();
    int getId();

    QSize iconSize() const;

public slots:
    void setIconSize(const QSize &iconSize);

signals:
    void clicked(MenuButton *button);


    void iconSizeChanged();

protected:
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void paintEvent(QPaintEvent *event);
    virtual void changeEvent(QEvent *event);

private:
    QIcon m_icon;
    Ui::MenuButton *ui;
    bool m_checked = false;
    bool m_pressed = false;
    QSize m_iconSize = QSize(50,50);
    Q_PROPERTY(QSize iconSize READ iconSize WRITE setIconSize NOTIFY iconSizeChanged FINAL)
};

#endif // MENUBUTTON_H
