#ifndef QWEBCAMWIDGET_H
#define QWEBCAMWIDGET_H

#include "qdatetime.h"
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

class QWebcamWidget : public QFrame
{
    Q_OBJECT
public:
    QWebcamWidget(QString source, QWidget *parent = nullptr);
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

protected:
    virtual void resizeEvent(QResizeEvent *event);
    virtual void hideEvent(QHideEvent *event);
    virtual void showEvent(QShowEvent *event);

protected slots:
    void on_playbackRateChanged(qreal rate);
    void videoFrameChangeEvent(QVideoFrame frame);

private:
    QGridLayout *m_layout = nullptr;
    QMediaPlayer *m_player = nullptr;

    QLabel *m_nameLabel = nullptr;
    QLabel *m_infoLabel = nullptr;

    bool m_showInfo = false;

    QLabel *m_videoLabel = nullptr;

    QString m_source;
    QString m_info;

    QVideoSink *m_webcamSink = nullptr;

    QWidget *m_overlayWidget = nullptr;
    QLabel *m_overlayIconLabel = nullptr;
    QLabel *m_overlayTextLabel = nullptr;

    qreal m_lastFrameTime = 0;
    qint16 m_frameRate = 2;
};

#endif // QWEBCAMWIDGET_H
