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
#include <QGraphicsEffect>

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

    QSize iconSize() const;

    QMargins textMargins() const;

    Qt::Alignment textAlignment() const;

    Qt::Alignment iconAlignment() const;

    QGraphicsEffect *textEffect() const;

    QGraphicsEffect *iconEffect() const;

public slots:
    void setIcon(const QIcon &icon);
    void setStyleSheet(const QString &styleSheet);

    void setIconSize(const QSize &iconSize);

    void setTextMargins(const QMargins &textMargins);

    void setTextAlignment(const Qt::Alignment &textAlignment);

    void setIconAlignment(const Qt::Alignment &iconAlignment);

    void setTextEffect(QGraphicsEffect *textEffect);

    void setIconEffect(QGraphicsEffect *iconEffect);

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

    void textAlignmentChanged();

    void iconAlignmentChanged();

    void textEffectChanged();

    void iconEffectChanged();

private:
    bool m_pressed = false;
    bool m_checked = false;
    bool m_checkable = false;
    bool m_exclusive = false;

    QGraphicsEffect *m_textEffect = nullptr;
    QGraphicsEffect *m_iconEffect = nullptr;

    Qt::Alignment m_iconAlignment = Qt::AlignLeft | Qt::AlignVCenter;
    Qt::Alignment m_textAlignment = Qt::AlignCenter;

    QString m_text;

    QHBoxLayout *m_layout = nullptr;
    QLabel *m_textLabel = nullptr;

    QIcon m_icon;
    QSize m_iconSize = QSize(24,24);

    QMargins m_textMargins = QMargins(0, 0, 0, 0);

    Q_PROPERTY(QSize iconSize READ iconSize WRITE setIconSize NOTIFY iconSizeChanged FINAL)
    Q_PROPERTY(QMargins textMargins READ textMargins WRITE setTextMargins NOTIFY textMarginsChanged FINAL)
    Q_PROPERTY(Qt::Alignment textAlignment READ textAlignment WRITE setTextAlignment NOTIFY textAlignmentChanged FINAL)
    Q_PROPERTY(Qt::Alignment iconAlignment READ iconAlignment WRITE setIconAlignment NOTIFY iconAlignmentChanged FINAL)
    Q_PROPERTY(QGraphicsEffect *textEffect READ textEffect WRITE setTextEffect NOTIFY textEffectChanged FINAL)
    Q_PROPERTY(QGraphicsEffect *iconEffect READ iconEffect WRITE setIconEffect NOTIFY iconEffectChanged FINAL)
};

#endif // QICONBUTTON_H
