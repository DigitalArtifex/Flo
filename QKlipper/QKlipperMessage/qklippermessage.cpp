#include "qklippermessage.h"

qint32 QKlipperMessage::s_currentId = 0;

QKlipperMessage::QKlipperMessage(QObject *parent)
    : QObject{parent}
{
    m_id = ++s_currentId;

    m_timestamp = QDateTime::currentDateTime();

    m_responseTimer = new QTimer();
    m_responseTimer->setInterval(3000);
    m_responseTimer->setSingleShot(true);

    connect(m_responseTimer, SIGNAL(timeout()), this, SLOT(on_responseTimerTimeout()));
}

QKlipperMessage::~QKlipperMessage()
{
    if(m_responseTimer)
        m_responseTimer->deleteLater();
}

qint32 QKlipperMessage::id() const
{
    return m_id;
}

void QKlipperMessage::setId(qint32 id)
{
    if (m_id == id)
        return;

    m_id = id;
    emit idChanged();
}

void QKlipperMessage::resetId()
{
    setId(0);
}

QKlipperMessage::Protocol QKlipperMessage::protocol() const
{
    return m_protocol;
}

void QKlipperMessage::setProtocol(Protocol protocol)
{
    if (m_protocol == protocol)
        return;

    m_protocol = protocol;
    emit protocolChanged();
}

void QKlipperMessage::resetProtocol()
{
    setProtocol(HttpProtocol);
}

QMap<QString, QVariant> QKlipperMessage::params() const
{
    return m_params;
}

QVariant QKlipperMessage::param(QString key) const
{
    if(m_params.contains(key))
        return m_params[key];

    return QVariant();
}

void QKlipperMessage::setParams(const QMap<QString, QVariant> &params)
{
    if (m_params == params)
        return;

    m_params = params;
    emit paramsChanged();
}

void QKlipperMessage::setParam(QString key, QVariant value)
{
    if(m_params.contains(key))
        return;

    m_params[key] = value;
    emit paramsChanged();
}

void QKlipperMessage::resetParams()
{
    m_params.clear();
    emit paramsChanged();
}

QString QKlipperMessage::method() const
{
    return m_method;
}

QString QKlipperMessage::toUri(bool parameterEncoded) const
{
    QString method = m_method;
    QString uri;

    //change the few that don't conform to a direct conversion
    if(method.contains("get_"))
        method.remove("get_");
    else if(method.contains("post_"))
        method.remove("post_");
    else if(method.contains("delete_"))
        method.remove("delete_");

    method.replace('.', '/');

    if(parameterEncoded && !m_params.isEmpty())
    {
        QStringList paramKeys = m_params.keys();
        QString params;

        foreach(QString key, paramKeys)
        {
            switch((QMetaType::Type)m_params[key].metaType().id())
            {
            case QMetaType::Bool:
                if(m_params[key].toBool())
                    params += QString("&%1=%2").arg(key).arg("true");
                else
                    params += QString("&%1=%2").arg(key).arg("false");
                break;

            case QMetaType::Int:
            case QMetaType::UInt:
            case QMetaType::LongLong:
            case QMetaType::ULongLong:
            case QMetaType::Long:
            case QMetaType::Short:
            case QMetaType::ULong:
            case QMetaType::UShort:
                params += QString("&%1=%2").arg(key).arg(m_params[key].toInt());
                break;
            case QMetaType::Double:
            case QMetaType::Float:
                params += QString("&%1=%2").arg(key).arg(m_params[key].toDouble());
                break;
            case QMetaType::Char:
            case QMetaType::Char16:
            case QMetaType::Char32:
            case QMetaType::UChar:
            case QMetaType::SChar:
            case QMetaType::QChar:
                break;
            case QMetaType::Nullptr:
            case QMetaType::Void:
            case QMetaType::VoidStar:
                params += QString("&%1").arg(key);
                break;
            case QMetaType::QString:
            case QMetaType::QByteArray:
                params += QString("&%1=%2").arg(key).arg(m_params[key].toString());
                break;
            case QMetaType::QStringList:
                break;
            case QMetaType::QBitArray:
            case QMetaType::QDateTime:
            case QMetaType::QDate:
            case QMetaType::QTime:
            case QMetaType::QUrl:
            case QMetaType::QLocale:
            case QMetaType::QRect:
            case QMetaType::QRectF:
            case QMetaType::QSize:
            case QMetaType::QSizeF:
            case QMetaType::QLine:
            case QMetaType::QLineF:
            case QMetaType::QPoint:
            case QMetaType::QPointF:
            case QMetaType::QEasingCurve:
            case QMetaType::QUuid:
            case QMetaType::QVariant:
            case QMetaType::QRegularExpression:
            case QMetaType::QJsonValue:
            case QMetaType::QJsonObject:
            case QMetaType::QJsonArray:
            case QMetaType::QJsonDocument:
            case QMetaType::QCborValue:
            case QMetaType::QCborArray:
            case QMetaType::QCborMap:
            case QMetaType::Float16:
            case QMetaType::QModelIndex:
            case QMetaType::QPersistentModelIndex:
            case QMetaType::QObjectStar:
            case QMetaType::QVariantMap:
            case QMetaType::QVariantList:
            case QMetaType::QVariantHash:
            case QMetaType::QVariantPair:
            case QMetaType::QByteArrayList:
            case QMetaType::QFont:
            case QMetaType::QPixmap:
            case QMetaType::QBrush:
            case QMetaType::QColor:
            case QMetaType::QPalette:
            case QMetaType::QIcon:
            case QMetaType::QImage:
            case QMetaType::QPolygon:
            case QMetaType::QRegion:
            case QMetaType::QBitmap:
            case QMetaType::QCursor:
            case QMetaType::QKeySequence:
            case QMetaType::QPen:
            case QMetaType::QTextLength:
            case QMetaType::QTextFormat:
            case QMetaType::QTransform:
            case QMetaType::QMatrix4x4:
            case QMetaType::QVector2D:
            case QMetaType::QVector3D:
            case QMetaType::QVector4D:
            case QMetaType::QQuaternion:
            case QMetaType::QPolygonF:
            case QMetaType::QColorSpace:
            case QMetaType::QSizePolicy:
            case QMetaType::UnknownType:
            case QMetaType::User:
            case QMetaType::QCborSimpleType:
                params += QString("&%1").arg(key);
                break;
            }
        }

        if(params.startsWith('&'))
            params.removeAt(0);

        uri = QString("/%1?%2").arg(method).arg(QUrl::toPercentEncoding(params, QByteArray("&=")));
    }
    else
        uri = QString("/%1").arg(method);

    return uri;
}

QByteArray QKlipperMessage::toRpc() const
{
    QJsonDocument document;
    QJsonObject rootObject;
    QJsonObject paramsObject;

    if(m_params.count() > 0)
    {
        QStringList paramKeys = m_params.keys();

        foreach(QString param, paramKeys)
        {
            switch((QMetaType::Type)m_params[param].metaType().id())
            {
            case QMetaType::Bool:
                paramsObject[param] = m_params[param].toBool();
                break;

            case QMetaType::Int:
            case QMetaType::UInt:
            case QMetaType::LongLong:
            case QMetaType::ULongLong:
            case QMetaType::Long:
            case QMetaType::Short:
            case QMetaType::ULong:
            case QMetaType::UShort:
                paramsObject[param] = m_params[param].toInt();
                break;
            case QMetaType::Double:
                paramsObject[param] = m_params[param].toDouble();
                break;
            case QMetaType::Float:
                paramsObject[param] = m_params[param].toFloat();
                break;
            case QMetaType::Char:
            case QMetaType::Char16:
            case QMetaType::Char32:
            case QMetaType::UChar:
            case QMetaType::SChar:
            case QMetaType::QChar:
                paramsObject[param] = m_params[param].toString();
                break;
            case QMetaType::QString:
            case QMetaType::QByteArray:
                paramsObject[param] = m_params[param].toString();
                break;
            case QMetaType::QStringList:
                break;

                //treat 'unknowns' as nullptr
            case QMetaType::Nullptr:
            case QMetaType::Void:
            case QMetaType::VoidStar:
            case QMetaType::QBitArray:
            case QMetaType::QDateTime:
            case QMetaType::QDate:
            case QMetaType::QTime:
            case QMetaType::QUrl:
            case QMetaType::QLocale:
            case QMetaType::QRect:
            case QMetaType::QRectF:
            case QMetaType::QSize:
            case QMetaType::QSizeF:
            case QMetaType::QLine:
            case QMetaType::QLineF:
            case QMetaType::QPoint:
            case QMetaType::QPointF:
            case QMetaType::QEasingCurve:
            case QMetaType::QUuid:
            case QMetaType::QVariant:
            case QMetaType::QRegularExpression:
            case QMetaType::QJsonDocument:
            case QMetaType::QCborValue:
            case QMetaType::QCborArray:
            case QMetaType::QCborMap:
            case QMetaType::Float16:
            case QMetaType::QModelIndex:
            case QMetaType::QPersistentModelIndex:
            case QMetaType::QObjectStar:
            case QMetaType::QVariantMap:
            case QMetaType::QVariantList:
            case QMetaType::QVariantHash:
            case QMetaType::QVariantPair:
            case QMetaType::QByteArrayList:
            case QMetaType::QFont:
            case QMetaType::QPixmap:
            case QMetaType::QBrush:
            case QMetaType::QColor:
            case QMetaType::QPalette:
            case QMetaType::QIcon:
            case QMetaType::QImage:
            case QMetaType::QPolygon:
            case QMetaType::QRegion:
            case QMetaType::QBitmap:
            case QMetaType::QCursor:
            case QMetaType::QKeySequence:
            case QMetaType::QPen:
            case QMetaType::QTextLength:
            case QMetaType::QTextFormat:
            case QMetaType::QTransform:
            case QMetaType::QMatrix4x4:
            case QMetaType::QVector2D:
            case QMetaType::QVector3D:
            case QMetaType::QVector4D:
            case QMetaType::QQuaternion:
            case QMetaType::QPolygonF:
            case QMetaType::QColorSpace:
            case QMetaType::QSizePolicy:
            case QMetaType::UnknownType:
            case QMetaType::User:
            case QMetaType::QCborSimpleType:
                paramsObject[param];
                break;
            case QMetaType::QJsonValue:
                paramsObject[param] = m_params[param].toJsonValue();
                break;
            case QMetaType::QJsonObject:
                paramsObject[param] = m_params[param].toJsonObject();
                break;
            case QMetaType::QJsonArray:
                paramsObject[param] = m_params[param].toJsonArray();
                break;
            }
        }

        rootObject["params"] = paramsObject;
    }

    rootObject["method"] = m_method;
    rootObject["id"] = m_id;
    rootObject["jsonrpc"] = QString("2.0");

    document.setObject(rootObject);

    QByteArray data = document.toJson(QJsonDocument::Indented) + QKLIPPER_RPC_EOF;

    return data;
}

void QKlipperMessage::setMethod(const QString &method)
{
    if (m_method == method)
        return;

    m_method = method;
    emit methodChanged();
}

void QKlipperMessage::resetMethod()
{
    setMethod(QString());
}

QKlipperMessage::State QKlipperMessage::state() const
{
    return m_state;
}

void QKlipperMessage::setState(State state)
{
    if (m_state == state)
        return;

    m_state = state;
    emit stateChanged();
}

void QKlipperMessage::resetState()
{
    setState(None);
}

QJsonValue QKlipperMessage::response() const
{
    return m_response;
}

void QKlipperMessage::setResponse(const QJsonValue &response)
{
    if(m_responseTimer->isActive())
        m_responseTimer->stop();

    m_response = response;

    emit responseChanged();
}

void QKlipperMessage::setResponse(const QByteArray &response)
{
    if(m_responseTimer->isActive())
        m_responseTimer->stop();

    setResponseTimestamp(QDateTime::currentDateTime());

    QJsonParseError parseError;
    QJsonDocument document = QJsonDocument::fromJson(response, &parseError);

    if(parseError.error != QJsonParseError::NoError)
    {
        setState(Error);

        return;
    }

    setResponse(document.object());
}

void QKlipperMessage::resetResponse()
{
    setResponse(QJsonObject());
}

void QKlipperMessage::startTimer()
{
    if(m_responseTimer->isActive())
        m_responseTimer->stop();

    m_responseTimer->start();
}

void QKlipperMessage::on_responseTimerTimeout()
{
    qDebug() << "Response Timeout" << m_method;

    emit responseTimeout();
}

QKlipperError QKlipperMessage::error() const
{
    return m_error;
}

void QKlipperMessage::setError(const QKlipperError &error)
{
    if (m_error == error)
        return;

    m_error = error;
    emit errorChanged();
}

QDateTime QKlipperMessage::responseTimestamp() const
{
    return m_responseTimestamp;
}

void QKlipperMessage::setResponseTimestamp(const QDateTime &responseTimestamp)
{
    if (m_responseTimestamp == responseTimestamp)
        return;

    m_responseTimestamp = responseTimestamp;
    emit responseTimestampChanged();
}

QDateTime QKlipperMessage::timestamp() const
{
    return m_timestamp;
}

void QKlipperMessage::setTimestamp(const QDateTime &timestamp)
{
    if (m_timestamp == timestamp)
        return;

    m_timestamp = timestamp;
    emit timestampChanged();
}

QKlipperMessage::Origin QKlipperMessage::origin() const
{
    return m_origin;
}

void QKlipperMessage::setOrigin(Origin origin)
{
    if (m_origin == origin)
        return;

    m_origin = origin;
    emit originChanged();
}

void QKlipperMessage::resetOrigin()
{
    setOrigin(System);
}
