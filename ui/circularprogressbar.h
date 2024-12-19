#ifndef CIRCULARPROGRESSBAR_H
#define CIRCULARPROGRESSBAR_H

#include<QObject>
#include <QWidget>
#include <QPainter>
#include <QPainterPath>
#include <QFont>
#include <QFontDatabase>
#include <QIcon>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>


class CircularProgressBar : public QWidget {
    Q_OBJECT

public:
    enum Mode
    {
        Percent,
        Temperature,
        Value
    };

    CircularProgressBar(QWidget * parent = 0, Mode mode = Percent) : QWidget(parent)
    {
        m_mode = mode;
        //setMinimumSize(100, 100);
        m_progress = 0.0;

        m_progressAnimation = new QPropertyAnimation(this, "progress");
        m_progressAnimation->setDuration(500);

        m_displayedValueAnimation = new QPropertyAnimation(this, "displayedValue");
        m_displayedValueAnimation->setDuration(500);

        m_animationGroup = new QParallelAnimationGroup(this);
        m_animationGroup->addAnimation(m_progressAnimation);
        m_animationGroup->addAnimation(m_displayedValueAnimation);
    }

    ~CircularProgressBar()
    {
        if(m_progressAnimation)
            delete m_progressAnimation;
    }

    QColor backgroundColor() const;

    QColor foregroundColor() const;

    qreal fontSize() const;

    QSize iconSize() const;

    QIcon icon() const;

    qreal minimum() const;

    qreal maximum() const;

    qreal value() const;

public slots:
    void setBackgroundColor(const QColor &backgroundColor);

    void setForegroundColor(const QColor &foregroundColor);

    void setFontSize(qreal fontSize);

    void setIconSize(const QSize &iconSize);

    void setIcon(const QIcon &icon);

    void setMinimum(qreal minimum);

    void setMaximum(qreal maximum);

    void setValue(qreal value);

protected slots:

    void setProgress(qreal progress);

    void setDisplayedValue(qreal displayedValue);

signals:
    void backgroundColorChanged();

    void foregroundColorChanged();

    void fontSizeChanged();

    void iconSizeChanged();

    void iconChanged();

    void progressChanged();

    void minimumChanged();

    void maximumChanged();

    void valueChanged();

    void displayedValueChanged();

protected:
    qreal progress() const;
    qreal displayedValue() const;

    virtual void paintEvent(QPaintEvent *event) override;
    virtual void resizeEvent(QResizeEvent *event) override;

private:
    qreal m_progress = 0.0; // progress 0.0 to 1.0
    qreal m_minimum = 0;
    qreal m_maximum = 100;
    qreal m_value = 0;
    qreal m_displayedValue = 0; //for animating value text display

    QPropertyAnimation *m_progressAnimation = nullptr;
    QPropertyAnimation *m_displayedValueAnimation = nullptr;
    QParallelAnimationGroup *m_animationGroup = nullptr;
    Mode m_mode = Percent;
    QString m_fontFamily;
    qreal m_fontSize = 12;

    int m_pathWidth = 8;
    int m_pathRadius = 0;
    int m_paddingX = 0;
    int m_paddingY = 0;

    bool m_animationsEnabled = true;

    QColor m_backgroundColor = QColor("#30b7e0");
    QColor m_foregroundColor = QColor("#737373");

    QSize m_iconSize = QSize(24,24);
    QIcon m_icon;
    Qt::Alignment m_iconAlignment = Qt::AlignHCenter | Qt::AlignBottom;

    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor NOTIFY backgroundColorChanged FINAL)
    Q_PROPERTY(QColor foregroundColor READ foregroundColor WRITE setForegroundColor NOTIFY foregroundColorChanged FINAL)
    Q_PROPERTY(qreal fontSize READ fontSize WRITE setFontSize NOTIFY fontSizeChanged FINAL)
    Q_PROPERTY(QSize iconSize READ iconSize WRITE setIconSize NOTIFY iconSizeChanged FINAL)
    Q_PROPERTY(QIcon icon READ icon WRITE setIcon NOTIFY iconChanged FINAL)
    Q_PROPERTY(qreal progress READ progress WRITE setProgress NOTIFY progressChanged FINAL)
    Q_PROPERTY(qreal minimum READ minimum WRITE setMinimum NOTIFY minimumChanged FINAL)
    Q_PROPERTY(qreal maximum READ maximum WRITE setMaximum NOTIFY maximumChanged FINAL)
    Q_PROPERTY(qreal value READ value WRITE setValue NOTIFY valueChanged FINAL)
    Q_PROPERTY(qreal displayedValue READ displayedValue WRITE setDisplayedValue NOTIFY displayedValueChanged FINAL)
};

#endif // CIRCULARPROGRESSBAR_H
