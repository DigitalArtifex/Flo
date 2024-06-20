#ifndef QWEBCAMWIDGET_H
#define QWEBCAMWIDGET_H

#include <QFrame>
#include <QObject>
#include <QWidget>
#include <QLabel>

#include <QGraphicsView>
#include <QGraphicsVideoItem>
#include <QMediaPlayer>
#include <QGridLayout>
#include <QVideoWidget>
#include <QVideoSink>
#include <QVideoFrame>

#include <QScrollBar>

#include <QResizeEvent>

class QWebcamWidget : public QWidget
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
    QGridLayout *_layout = nullptr;
    QMediaPlayer *_player = nullptr;

    QLabel *_nameLabel = nullptr;
    QLabel *_infoLabel = nullptr;

    bool _showInfo = false;

    QLabel *_videoLabel = nullptr;

    QString _source;
    QString _info;

    QVideoSink *_webcamSink = nullptr;
};

#endif // QWEBCAMWIDGET_H
