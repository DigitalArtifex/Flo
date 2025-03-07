#ifndef LINEGRAPHDATA_H
#define LINEGRAPHDATA_H

#include <QObject>
#include <QMap>
#include <QQmlEngine>
#include <QtGraphs>
#include <QtGraphs/QLineSeries>
#include <QtGraphs/QValueAxis>

class LineGraphData : public QObject
{
    Q_OBJECT
    QML_ELEMENT
public:
    explicit LineGraphData(QObject *parent = nullptr);
    ~LineGraphData();

    QLineSeries * series(const QString &name) const;

    QString gridMainColor() const;

    QString gridSubColor() const;

    QString axisYMainColor() const;

    QString axisYSubColor() const;

    QString axisXMainColor() const;

    QString axisXSubColor() const;

    qreal valueMaximum() const;

    qreal valueMinimum() const;

    QDateTime dateMinimum() const;

    QDateTime dateMaximum() const;

    QString valueLabelFormat() const;

    QString dateLabelFormat() const;

public slots:
    void append(QLineSeries *series);
    void append(QString name, QPointF point);
    void clear(QString name);

    void setGridMainColor(const QString &gridMainColor);

    void setGridSubColor(const QString &gridSubColor);

    void setAxisYMainColor(const QString &axisYMainColor);

    void setAxisYSubColor(const QString &axisYSubColor);

    void setAxisXMainColor(const QString &axisXMainColor);

    void setAxisXSubColor(const QString &axisXSubColor);

    void setValueMaximum(qreal valueMaximum);

    void setValueMinimum(qreal valueMinimum);

    void setDateMinimum(const QDateTime &dateMinimum);

    void setDateMaximum(const QDateTime &dateMaximum);

    void normalizeDataAxis();

    void setValueLabelFormat(const QString &valueLabelFormat);

    void setDateLabelFormat(const QString &dateLabelFormat);

signals:
    void dataChanged();
    void seriesAdded(QLineSeries*);
    void seriesRemoved(QLineSeries*);

    void gridMainColorChanged();

    void gridSubColorChanged();

    void axisYMainColorChanged();

    void axisYSubColorChanged();

    void axisXMainColorChanged();

    void axisXSubColorChanged();

    void valueMaximumChanged();

    void valueMinimumChanged();

    void dateMinimumChanged();

    void dateMaximumChanged();

    void valueLabelFormatChanged();

    void dateLabelFormatChanged();

private:
    QMap<QString, QLineSeries*> m_data;
    QDateTime m_dateMinimum;
    QDateTime m_dateMaximum;

    qreal m_valueMaximum = 10;
    qreal m_valueMinimum = 0;

    QString m_gridMainColor;
    QString m_gridSubColor;
    QString m_axisYMainColor;
    QString m_axisYSubColor;
    QString m_axisXMainColor;
    QString m_axisXSubColor;
    QString m_valueLabelFormat;
    QString m_dateLabelFormat;

    Q_PROPERTY(QString gridMainColor READ gridMainColor WRITE setGridMainColor NOTIFY gridMainColorChanged FINAL)
    Q_PROPERTY(QString gridSubColor READ gridSubColor WRITE setGridSubColor NOTIFY gridSubColorChanged FINAL)
    Q_PROPERTY(QString axisYMainColor READ axisYMainColor WRITE setAxisYMainColor NOTIFY axisYMainColorChanged FINAL)
    Q_PROPERTY(QString axisYSubColor READ axisYSubColor WRITE setAxisYSubColor NOTIFY axisYSubColorChanged FINAL)
    Q_PROPERTY(QString axisXMainColor READ axisXMainColor WRITE setAxisXMainColor NOTIFY axisXMainColorChanged FINAL)
    Q_PROPERTY(QString axisXSubColor READ axisXSubColor WRITE setAxisXSubColor NOTIFY axisXSubColorChanged FINAL)

    Q_PROPERTY(qreal valueMaximum READ valueMaximum WRITE setValueMaximum NOTIFY valueMaximumChanged FINAL)
    Q_PROPERTY(qreal valueMinimum READ valueMinimum WRITE setValueMinimum NOTIFY valueMinimumChanged FINAL)
    Q_PROPERTY(QDateTime dateMinimum READ dateMinimum WRITE setDateMinimum NOTIFY dateMinimumChanged FINAL)
    Q_PROPERTY(QDateTime dateMaximum READ dateMaximum WRITE setDateMaximum NOTIFY dateMaximumChanged FINAL)
    Q_PROPERTY(QString valueLabelFormat READ valueLabelFormat WRITE setValueLabelFormat NOTIFY valueLabelFormatChanged FINAL)
    Q_PROPERTY(QString dateLabelFormat READ dateLabelFormat WRITE setDateLabelFormat NOTIFY dateLabelFormatChanged FINAL)
};

#endif // LINEGRAPHDATA_H
