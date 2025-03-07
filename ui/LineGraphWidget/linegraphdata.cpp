#include "linegraphdata.h"

LineGraphData::LineGraphData(QObject *parent)
    : QObject{parent}
{
}

LineGraphData::~LineGraphData()
{
}

QLineSeries *LineGraphData::series(const QString &name) const
{
    if(m_data.contains(name))
        return m_data.value(name);

    return nullptr;
}

void LineGraphData::append(QLineSeries *series)
{
    if(m_data.contains(series->name()))
    {
        QLineSeries *temp = m_data.take(series->name());

        if(temp && temp != series)
        {
            emit seriesRemoved(temp);
            delete temp;
        }
    }

    series->setParent(this);
    m_data.insert(series->name(), series);
    seriesAdded(series);

    normalizeDataAxis();
}

void LineGraphData::append(QString name, QPointF point)
{
    if(!m_data.contains(name))
    {
        QLineSeries *temp = new QLineSeries(this);
        temp->setName(name);

        m_data.insert(name, temp);
        seriesAdded(temp);
    }

    if(point.x() >= m_dateMaximum.toMSecsSinceEpoch())
        setDateMaximum(QDateTime::fromMSecsSinceEpoch(point.x()));
    else if(point.x() < m_dateMinimum.toMSecsSinceEpoch())
        setDateMinimum(QDateTime::fromMSecsSinceEpoch(point.x()));

    m_data[name]->append(point);
    emit dataChanged();

    normalizeDataAxis();
}

void LineGraphData::clear(QString name)
{
    if(m_data.contains(name))
    {
        m_data[name]->clear();
        emit dataChanged();
    }
}

QString LineGraphData::gridMainColor() const
{
    return m_gridMainColor;
}

void LineGraphData::setGridMainColor(const QString &gridMainColor)
{
    if (m_gridMainColor == gridMainColor)
        return;

    m_gridMainColor = gridMainColor;
    emit gridMainColorChanged();
}

QString LineGraphData::gridSubColor() const
{
    return m_gridSubColor;
}

void LineGraphData::setGridSubColor(const QString &gridSubColor)
{
    if (m_gridSubColor == gridSubColor)
        return;
    m_gridSubColor = gridSubColor;
    emit gridSubColorChanged();
}

QString LineGraphData::axisYMainColor() const
{
    return m_axisYMainColor;
}

void LineGraphData::setAxisYMainColor(const QString &axisYMainColor)
{
    if (m_axisYMainColor == axisYMainColor)
        return;
    m_axisYMainColor = axisYMainColor;
    emit axisYMainColorChanged();
}

QString LineGraphData::axisYSubColor() const
{
    return m_axisYSubColor;
}

void LineGraphData::setAxisYSubColor(const QString &axisYSubColor)
{
    if (m_axisYSubColor == axisYSubColor)
        return;

    m_axisYSubColor = axisYSubColor;
    emit axisYSubColorChanged();
}

QString LineGraphData::axisXMainColor() const
{
    return m_axisXMainColor;
}

void LineGraphData::setAxisXMainColor(const QString &axisXMainColor)
{
    if (m_axisXMainColor == axisXMainColor)
        return;

    m_axisXMainColor = axisXMainColor;
    emit axisXMainColorChanged();
}

QString LineGraphData::axisXSubColor() const
{
    return m_axisXSubColor;
}

void LineGraphData::setAxisXSubColor(const QString &axisXSubColor)
{
    if (m_axisXSubColor == axisXSubColor)
        return;

    m_axisXSubColor = axisXSubColor;
    emit axisXSubColorChanged();
}

qreal LineGraphData::valueMaximum() const
{
    return m_valueMaximum;
}

void LineGraphData::setValueMaximum(qreal valueMaximum)
{
    if (qFuzzyCompare(m_valueMaximum, valueMaximum))
        return;
    m_valueMaximum = valueMaximum;
    emit valueMaximumChanged();
}

qreal LineGraphData::valueMinimum() const
{
    return m_valueMinimum;
}

void LineGraphData::setValueMinimum(qreal valueMinimum)
{
    if (qFuzzyCompare(m_valueMinimum, valueMinimum))
        return;

    m_valueMinimum = valueMinimum;
    emit valueMinimumChanged();
}

QDateTime LineGraphData::dateMinimum() const
{
    return m_dateMinimum;
}

void LineGraphData::setDateMinimum(const QDateTime &dateMinimum)
{
    if (m_dateMinimum == dateMinimum)
        return;
    m_dateMinimum = dateMinimum;
    emit dateMinimumChanged();
}

QDateTime LineGraphData::dateMaximum() const
{
    return m_dateMaximum;
}

void LineGraphData::setDateMaximum(const QDateTime &dateMaximum)
{
    if (m_dateMaximum == dateMaximum)
        return;
    m_dateMaximum = dateMaximum;
    emit dateMaximumChanged();
}

void LineGraphData::normalizeDataAxis()
{
    qreal highest = .1;
    qreal lowest = 0;

    qreal rangeMin = m_dateMinimum.toMSecsSinceEpoch();
    qreal rangeMax = m_dateMaximum.toMSecsSinceEpoch();

    for(QLineSeries *series : m_data)
    {
        for(const QPointF &point : series->points())
        {
            if(point.x() >= rangeMin && point.x() <= rangeMax)
            {
                if( point.y() > highest)
                    highest = point.y();

                else if(point.y() <= lowest)
                    lowest = point.y();
            }
        }
    }

    setValueMaximum(highest + (highest * .2));
    setValueMinimum(lowest + (lowest * .2));
}

QString LineGraphData::valueLabelFormat() const
{
    return m_valueLabelFormat;
}

void LineGraphData::setValueLabelFormat(const QString &valueLabelFormat)
{
    if (m_valueLabelFormat == valueLabelFormat)
        return;

    m_valueLabelFormat = valueLabelFormat;
    emit valueLabelFormatChanged();
}

QString LineGraphData::dateLabelFormat() const
{
    return m_dateLabelFormat;
}

void LineGraphData::setDateLabelFormat(const QString &dateLabelFormat)
{
    if (m_dateLabelFormat == dateLabelFormat)
        return;

    m_dateLabelFormat = dateLabelFormat;
    emit dateLabelFormatChanged();
}
