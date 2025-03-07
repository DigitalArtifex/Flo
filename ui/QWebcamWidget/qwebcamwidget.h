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
#include <QOpenGLWidget>
#include "qwebcamsource.h"

class QWebcamWidget : public QFrame
{
    Q_OBJECT
public:
    QWebcamWidget(QString source = "", int timeout = 10000, QWidget *parent = nullptr);
    ~QWebcamWidget();

    void setStateIcon(QWebcamSource::State state, QIcon icon);

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

signals:
    void stateChanged();
    void frameChanged();

protected:
    void setupUi();
    void setupIcons();

    virtual void changeEvent(QEvent *event) override;
    virtual void resizeEvent(QResizeEvent *event) override;
    virtual void paintEvent(QPaintEvent *event) override;

protected slots:
    void on_playbackRateChanged(qreal rate);
    void videoFrameChangeEvent(QVideoFrame frame);
    void webcamSourceStateChanged();

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

    quint32 m_timeout = 10000;

    QMap<QWebcamSource::State, QIcon> m_iconMap;
    QSize m_iconSize = QSize(32, 32);
};

#endif // QWEBCAMWIDGET_H
