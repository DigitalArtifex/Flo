#ifndef QGAUGEWIDGET_H
#define QGAUGEWIDGET_H

#include<QObject>
#include <QWidget>
#include <QPainter>
#include <QPainterPath>
#include <QFont>
#include <QFontDatabase>
#include <QIcon>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QMovie>


class QGaugeWidget : public QWidget {
        Q_OBJECT

    public:
        enum Mode
        {
            Percent,
            Temperature,
            Value
        };

        QGaugeWidget(QWidget * parent = 0, Mode mode = Percent);

        ~QGaugeWidget();

        QColor backgroundColor() const
        {
            return m_backgroundColor;
        }

        QColor textColor() const
        {
            return m_textColor;
        }

        qreal fontSize() const
        {
            return m_fontSize;
        }

        QSize iconSize() const
        {
            return m_iconSize;
        }

        QIcon icon() const
        {
            return m_icon;
        }

        qreal minimum() const
        {
            return m_minimum;
        }

        qreal maximum() const
        {
            return m_maximum;
        }

        qreal value() const
        {
            return m_value;
        }

        int pathWidth() const
        {
            return m_pathWidth;
        }

        bool animatedIconEnabled() const
        {
            return m_animatedIconEnabled;
        }

        QString animatedIcon() const
        {
            return m_animatedIcon;
        }

        bool animationsEnabled() const
        {
            return m_animationsEnabled;
        }

        QColor progressBarColor() const
        {
            return m_progressBarColor;
        }

        QColor progressBarFillColor() const
        {
            return m_progressBarFillColor;
        }

        QPen progressBarPen() const
        {
            return m_progressBarPen;
        }

        QPen progressBarFillPen() const
        {
            return m_progressBarFillPen;
        }

    public slots:
        Q_INVOKABLE void setBackgroundColor(const QColor &backgroundColor);

        Q_INVOKABLE void setFontSize(qreal fontSize);

        Q_INVOKABLE void setIconSize(const QSize &iconSize);

        Q_INVOKABLE void setIcon(const QIcon &icon);

        Q_INVOKABLE void setMinimum(qreal minimum);

        Q_INVOKABLE void setMaximum(qreal maximum);

        Q_INVOKABLE void setValue(qreal value);

        Q_INVOKABLE void setPathWidth(int pathWidth);

        Q_INVOKABLE void setAnimatedIconEnabled(bool animatedIconEnabled);

        Q_INVOKABLE void setAnimatedIcon(const QString &animatedIcon);

        Q_INVOKABLE void setAnimationsEnabled(bool animationsEnabled);

        Q_INVOKABLE void setProgressBarColor(const QColor &progressBarColor);

        Q_INVOKABLE void setProgressBarFillColor(const QColor &progressBarFillColor);

        void setProgressBarPen(const QPen &progressBarPen);

        void setProgressBarFillPen(const QPen &progressBarFillPen);

        void setTextColor(const QColor &textColor);

    protected slots:

        void setProgress(qreal progress);

        void setDisplayedValue(qreal displayedValue);

        void iconMovieFrameChanged(int frame);

    signals:
        void backgroundColorChanged();

        void textColorChanged();

        void fontSizeChanged();

        void iconSizeChanged();

        void iconChanged();

        void progressChanged();

        void minimumChanged();

        void maximumChanged();

        void valueChanged();

        void displayedValueChanged();

        void pathWidthChanged();

        void animatedIconEnabledChanged();

        void animatedIconChanged();

        void animationsEnabledChanged();

        void progressBarColorChanged();

        void progressBarFillColorChanged();

        void progressBarPenChanged();

        void progressBarFillPenChanged();

    protected:
        qreal progress() const
        {
            return m_progress;
        }

        qreal displayedValue() const
        {
            return m_displayedValue;
        }

        virtual void paintEvent(QPaintEvent *event) override;
        virtual void resizeEvent(QResizeEvent *event) override;
        virtual void showEvent(QShowEvent *event) override;
        virtual void hideEvent(QHideEvent *event) override;

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

#ifdef QGAUGEWIDGET_DEFAULT_FONT
        QString m_fontFamily = QGAUGEWIDGET_DEFAULT_FONT;
#else
        QString m_fontFamily;
#endif

        qreal m_fontSize = 12;

        int m_pathWidth = 8;
        int m_pathRadius = 0;
        int m_paddingX = 0;
        int m_paddingY = 0;

        bool m_animationsEnabled = true;

        QString m_animatedIcon;
        bool m_animatedIconEnabled = false;
        QMovie *m_iconMovie = nullptr;

        QColor m_backgroundColor = QColor(0,0,0,0);
        QColor m_textColor = QColor(48,183,224);

        QPen m_progressBarPen;
        QPen m_progressBarFillPen;
        QColor m_progressBarColor = QColor(115,115,115);
        QColor m_progressBarFillColor = QColor(48,183,224);

        QSize m_iconSize = QSize(24,24);
        QIcon m_icon;
        Qt::Alignment m_iconAlignment = Qt::AlignHCenter | Qt::AlignBottom;

        Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor NOTIFY backgroundColorChanged FINAL)
        Q_PROPERTY(qreal fontSize READ fontSize WRITE setFontSize NOTIFY fontSizeChanged FINAL)
        Q_PROPERTY(QSize iconSize READ iconSize WRITE setIconSize NOTIFY iconSizeChanged FINAL)
        Q_PROPERTY(QIcon icon READ icon WRITE setIcon NOTIFY iconChanged FINAL)
        Q_PROPERTY(qreal progress READ progress WRITE setProgress NOTIFY progressChanged FINAL)
        Q_PROPERTY(qreal minimum READ minimum WRITE setMinimum NOTIFY minimumChanged FINAL)
        Q_PROPERTY(qreal maximum READ maximum WRITE setMaximum NOTIFY maximumChanged FINAL)
        Q_PROPERTY(qreal value READ value WRITE setValue NOTIFY valueChanged FINAL)
        Q_PROPERTY(qreal displayedValue READ displayedValue WRITE setDisplayedValue NOTIFY displayedValueChanged FINAL)
        Q_PROPERTY(int pathWidth READ pathWidth WRITE setPathWidth NOTIFY pathWidthChanged FINAL)
        Q_PROPERTY(bool animatedIconEnabled READ animatedIconEnabled WRITE setAnimatedIconEnabled NOTIFY animatedIconEnabledChanged FINAL)
        Q_PROPERTY(QString animatedIcon READ animatedIcon WRITE setAnimatedIcon NOTIFY animatedIconChanged FINAL)
        Q_PROPERTY(bool animationsEnabled READ animationsEnabled WRITE setAnimationsEnabled NOTIFY animationsEnabledChanged FINAL)
        Q_PROPERTY(QColor progressBarColor READ progressBarColor WRITE setProgressBarColor NOTIFY progressBarColorChanged FINAL)
        Q_PROPERTY(QColor progressBarFillColor READ progressBarFillColor WRITE setProgressBarFillColor NOTIFY progressBarFillColorChanged FINAL)
        Q_PROPERTY(QPen progressBarPen READ progressBarPen WRITE setProgressBarPen NOTIFY progressBarPenChanged FINAL)
        Q_PROPERTY(QPen progressBarFillPen READ progressBarFillPen WRITE setProgressBarFillPen NOTIFY progressBarFillPenChanged FINAL)
        Q_PROPERTY(QColor textColor READ textColor WRITE setTextColor NOTIFY textColorChanged FINAL)
};

#endif // QGAUGEWIDGET_H
