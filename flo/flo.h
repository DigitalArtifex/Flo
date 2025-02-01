#ifndef FLO_H
#define FLO_H

#include <QObject>
#include <QUuid>
#include <QtConcurrent/QtConcurrent>

#include "qklipperinstancepool.h"

#include "settings.h"

//generate operators for c++11
#ifndef Q_DECLARE_ENUM_FLAGS
#define Q_DECLARE_ENUM_FLAGS(TYPE)                                                          \
                                                                                            \
inline constexpr TYPE operator|(TYPE a, TYPE b)                                             \
{                                                                                           \
    return static_cast<TYPE>(static_cast<unsigned int>(a) | static_cast<unsigned int>(b));     \
}                                                                                           \
                                                                                            \
inline constexpr TYPE operator&(TYPE a, TYPE b)                                             \
{                                                                                           \
    return static_cast<TYPE>(static_cast<unsigned int>(a) & static_cast<unsigned int>(b));     \
}                                                                                           \
                                                                                            \
inline constexpr TYPE operator^(TYPE a, TYPE b)                                             \
{                                                                                           \
    return static_cast<TYPE>(static_cast<unsigned int>(a) ^ static_cast<unsigned int>(b));     \
}                                                                                           \
                                                                                            \
inline constexpr TYPE operator~(TYPE a)                                                     \
{                                                                                           \
    return static_cast<TYPE>(~static_cast<unsigned int>(a));                                \
}                                                                                           \
inline constexpr TYPE operator|=(TYPE &a, TYPE b)                                           \
{                                                                                           \
    return a = static_cast<TYPE>(static_cast<unsigned int>(a) | static_cast<unsigned int>(b)); \
}                                                                                           \
                                                                                            \
inline constexpr TYPE operator&=(TYPE &a, TYPE b)                                           \
{                                                                                           \
    return a = static_cast<TYPE>(static_cast<unsigned int>(a) & static_cast<unsigned int>(b)); \
}                                                                                           \
                                                                                            \
inline constexpr TYPE operator^=(TYPE &a, TYPE b)                                           \
{                                                                                           \
    return a = static_cast<TYPE>(static_cast<unsigned int>(a) ^ static_cast<unsigned int>(b)); \
}
#endif

class Flo : public QObject
{
    Q_OBJECT
    explicit Flo(QObject *parent = nullptr);
public:

    static QString generatId();
    static Flo *instance();
    void start();

    static QKlipperInstancePool *printerPool();
    static Settings *settings();

signals:
    void loading();
    void loadingProgress(QString message, qreal progress);
    void loadingFinished();

private:
    void on_loading();
    void on_loadingProgress(QString message, qreal progress);
    void on_loadingFinished();

private:
    static QKlipperInstancePool *m_printerPool;
    static Settings *m_settings;

    static Flo *m_instance;
};

#endif // FLO_H
