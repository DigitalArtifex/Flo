#ifndef QICONBUTTON_H
#define QICONBUTTON_H

#include <QObject>
#include <QWidget>
#include <QMouseEvent>
#include <QStyle>
#include <QHBoxLayout>
#include <QLabel>
#include <QPixmap>

class QIconButton : public QFrame
{
    Q_OBJECT

public:
    explicit QIconButton(QWidget *parent = nullptr);
    ~QIconButton();

    bool isCheckable() const;
    void setCheckable(bool newCheckable);

    QPixmap pixmap() const;
    void setPixmap(const QPixmap &newPixmap);

    QString text() const;
    void setText(const QString &newText);

    virtual void setStyleSheet(QString &styleSheet);

    bool isChecked() const;
    void setChecked(bool newChecked);

    bool exclusive() const;
    void setExclusive(bool newExclusive);

protected:
    void setupUi();

protected slots:
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);

signals:
    void clicked();
    void toggled(bool checked);

private:
    bool m_pressed = false;
    bool m_checked = false;
    bool m_checkable = false;
    bool m_exclusive = false;

    QPixmap m_pixmap;
    QString m_text;

    QHBoxLayout *m_layout = nullptr;
    QLabel *m_iconLabel = nullptr;
    QLabel *m_textLabel = nullptr;
};

#endif // QICONBUTTON_H
