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
    enum Flags
    {
        IconHCentered = 1,
        IconVCentered = 2,
        IconCentered = IconHCentered | IconVCentered,
        TextHCentered = 4,
        TextVCentered = 8,
        TextCentered = TextHCentered | TextVCentered
    };

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

    QSize iconSize() const;

    Flags flags() const;

    QMargins textMargins() const;

public slots:
    void setIcon(const QIcon &icon);
    void setStyleSheet(const QString &styleSheet);

    void setIconSize(const QSize &iconSize);

    void setFlags(Flags flags);
    void setFlag(Flags flag, bool on = true);

    void setTextMargins(const QMargins &textMargins);

protected:
    void setupUi();

    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void paintEvent(QPaintEvent *event);

    virtual void changeEvent(QEvent *event);


signals:
    void clicked();
    void toggled(bool checked);

    void iconSizeChanged();

    void flagsChanged();

    void textMarginsChanged();

private:
    bool m_pressed = false;
    bool m_checked = false;
    bool m_checkable = false;
    bool m_exclusive = false;
    Flags m_flags = Flags(IconVCentered | TextCentered);

    QString m_text;

    QHBoxLayout *m_layout = nullptr;
    QLabel *m_textLabel = nullptr;

    QIcon m_icon;
    QSize m_iconSize = QSize(24,24);

    QMargins m_textMargins = QMargins(34, 0, 0, 0);

    Q_PROPERTY(QSize iconSize READ iconSize WRITE setIconSize NOTIFY iconSizeChanged FINAL)
    Q_PROPERTY(Flags flags READ flags WRITE setFlags NOTIFY flagsChanged FINAL)
    Q_PROPERTY(QMargins textMargins READ textMargins WRITE setTextMargins NOTIFY textMarginsChanged FINAL)
};

#endif // QICONBUTTON_H
