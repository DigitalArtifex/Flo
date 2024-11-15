#ifndef QWEBCAMWIDGET_H
#define QWEBCAMWIDGET_H

#include <QDateTime>
#include <QtConcurrent/QtConcurrent>
#include <QFrame>
#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QStyle>

#include <QGraphicsView>
#include <QGraphicsVideoItem>
#include <QMediaPlayer>
#include <QGridLayout>
#include <QVideoWidget>
#include <QVideoSink>
#include <QVideoFrame>

#include <QScrollBar>

#include <QResizeEvent>
#include "qwebcamsource.h"

class QWebcamWidget : public QWidget
{
    Q_OBJECT
public:
    QWebcamWidget(QString source, QWidget *parent = nullptr, int timeout = 5000);
    ~QWebcamWidget();

    void setSource(QString &source);
    void setTitle(QString &title);
    void showInfo();
    void hideInfo();

    void play();
    void pause();
    void stop();

    QString source() const;

    QString info() const;
    void setInfo(const QString &info);

    QPixmap lastFrame() const;

    QWebcamSource::State state() const;

public slots:
    void setupIcons();
    void setStyleSheet(const QString &styleSheet);

signals:
    void stateChanged();
    void frameChanged();

protected:
    void setupUi();

protected slots:
    void on_playbackRateChanged(qreal rate);
    void videoFrameChangeEvent(QVideoFrame frame);
    void webcamSourceStateChanged();

    virtual void resizeEvent(QResizeEvent *event);
    virtual void hideEvent(QHideEvent *event);
    virtual void showEvent(QShowEvent *event);
    virtual void paintEvent(QPaintEvent *event);

private:
    QThread *m_webcamThread;
    QWebcamSource *m_webcamSource = nullptr;

    QGridLayout *m_layout = nullptr;

    QLabel *m_nameLabel = nullptr;
    QLabel *m_infoLabel = nullptr;

    QPixmap m_lastFrame;

    bool m_showInfo = false;

    QLabel *m_videoLabel = nullptr;
    QString m_info;

    QWidget *m_overlayWidget = nullptr;
    QLabel *m_overlayIconLabel = nullptr;
    QLabel *m_overlayTextLabel = nullptr;
    QSpacerItem *m_overlayTopSpacer = nullptr;
    QSpacerItem *m_overlayBottomSpacer = nullptr;
    QGridLayout *m_overlayLayout = nullptr;
};

#endif // QWEBCAMWIDGET_H
