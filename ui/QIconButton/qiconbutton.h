#ifndef QICONBUTTON_H
#define QICONBUTTON_H

#include <QObject>
#include <QWidget>
#include <QMouseEvent>
#include <QStyle>
#include <QHBoxLayout>
#include <QLabel>
#include <QPixmap>
#include <QPainter>
#include <QIcon>

class QIconButton : public QFrame
{
    Q_OBJECT

public:
    explicit QIconButton(QWidget *parent = nullptr);
    ~QIconButton();

    bool isCheckable() const;
    void setCheckable(bool checkable);

    QString text() const;
    void setText(const QString &text);


    bool isChecked() const;
    void setChecked(bool checked);

    bool exclusive() const;
    void setExclusive(bool exclusive);

    QIcon icon() const;

public slots:
    void setIcon(const QIcon &icon);
    void setStyleSheet(const QString &styleSheet);

protected:
    void setupUi();

    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void paintEvent(QPaintEvent *event);

    virtual void changeEvent(QEvent *event);


signals:
    void clicked();
    void toggled(bool checked);

private:
    bool m_pressed = false;
    bool m_checked = false;
    bool m_checkable = false;
    bool m_exclusive = false;

    QString m_text;

    QHBoxLayout *m_layout = nullptr;
    QLabel *m_textLabel = nullptr;

    QIcon m_icon;
};

#endif // QICONBUTTON_H
