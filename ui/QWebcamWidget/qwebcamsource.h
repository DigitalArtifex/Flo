#ifndef QWEBCAMSOURCE_H
#define QWEBCAMSOURCE_H

#include <QObject>
#include <QVideoSink>
#include <QVideoFrame>
#include <QMediaPlayer>
#include <QtMultimedia>
#include <QThread>
#include <QImage>
#include <QTimer>

class QWebcamSource : public QObject
{
        Q_OBJECT
    public:

        enum State
        {
            None,
            NoConnection,
            Connecting,
            Connected,
            Paused,
            InvalidFrame
        };

        explicit QWebcamSource(int timeout = 5000, QObject *parent = nullptr);
        ~QWebcamSource();

        void play();
        void pause();
        void stop();

        QUrl source() const;
        State state() const;
        QVideoFrame frame() const;

    public slots:
        void setSource(const QUrl &source);

    signals:
        void sourceChanged();
        void frameChanged(QVideoFrame);
        void stateChanged();

    protected slots:
        void videoFrameChangeEvent(QVideoFrame frame);
        void onSignalTimeout();
        void createSink();

        void stopSignalTimer();
        void startSignalTimer();
        void resetSignalTimer();

        void setState(State state);
        void setFrame(const QVideoFrame &frame);

    private:
        State        m_state = None;
        QTimer      *m_signalTimer = nullptr;
        QMediaPlayer *m_player = nullptr;
        QUrl m_source;
        QVideoFrame m_frame;
        QVideoSink *m_webcamSink = nullptr;

        Q_PROPERTY(QUrl source READ source WRITE setSource NOTIFY sourceChanged FINAL)
        Q_PROPERTY(State state READ state WRITE setState NOTIFY stateChanged FINAL)
        Q_PROPERTY(QVideoFrame frame READ frame WRITE setFrame NOTIFY frameChanged FINAL)
};

#endif // QWEBCAMSOURCE_H
