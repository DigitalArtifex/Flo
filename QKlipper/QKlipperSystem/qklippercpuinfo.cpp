#include "qklippercpuinfo.h"

QKlipperCpuInfo::QKlipperCpuInfo(QObject *parent)
    : QObject{parent}
{

}

QKlipperCpuInfo::QKlipperCpuInfo(const QKlipperCpuInfo &value)
{
    m_bitCount = value.m_bitCount;
    m_cpuCount = value.m_cpuCount;
    m_coreUsage = value.m_coreUsage;
    m_usage = value.m_usage;
    m_description = value.m_description;
    m_hardwareDescription = value.m_hardwareDescription;
    m_memoryUnits = value.m_memoryUnits;
    m_totalMemory = value.m_totalMemory;
    m_model = value.m_model;
    m_processor = value.m_processor;
    m_temp = value.m_temp;
    m_serialNumber = value.m_serialNumber;
}

QKlipperCpuInfo::QKlipperCpuInfo(QKlipperCpuInfo &&value)
{
    m_bitCount = value.m_bitCount;
    m_cpuCount = value.m_cpuCount;
    m_coreUsage = value.m_coreUsage;
    m_usage = value.m_usage;
    m_description = value.m_description;
    m_hardwareDescription = value.m_hardwareDescription;
    m_memoryUnits = value.m_memoryUnits;
    m_totalMemory = value.m_totalMemory;
    m_model = value.m_model;
    m_processor = value.m_processor;
    m_temp = value.m_temp;
    m_serialNumber = value.m_serialNumber;
}

QKlipperCpuInfo &QKlipperCpuInfo::operator=(const QKlipperCpuInfo &value)
{
    m_bitCount = value.m_bitCount;
    m_cpuCount = value.m_cpuCount;
    m_coreUsage = value.m_coreUsage;
    m_usage = value.m_usage;
    m_description = value.m_description;
    m_hardwareDescription = value.m_hardwareDescription;
    m_memoryUnits = value.m_memoryUnits;
    m_totalMemory = value.m_totalMemory;
    m_model = value.m_model;
    m_processor = value.m_processor;
    m_temp = value.m_temp;
    m_serialNumber = value.m_serialNumber;

    return *this;
}

bool QKlipperCpuInfo::operator==(const QKlipperCpuInfo &value)
{
    if(m_bitCount != value.m_bitCount) return false;
    if(m_cpuCount != value.m_cpuCount) return false;
    if(m_coreUsage != value.m_coreUsage) return false;
    if(m_usage != value.m_usage) return false;
    if(m_description != value.m_description) return false;
    if(m_hardwareDescription != value.m_hardwareDescription) return false;
    if(m_memoryUnits != value.m_memoryUnits) return false;
    if(m_totalMemory != value.m_totalMemory) return false;
    if(m_model != value.m_model) return false;
    if(m_processor != value.m_processor) return false;
    if(m_temp != value.m_temp) return false;
    if(m_serialNumber != value.m_serialNumber) return false;

    return true;
}

bool QKlipperCpuInfo::operator==(QKlipperCpuInfo &&value)
{
    if(m_bitCount != value.m_bitCount) return false;
    if(m_cpuCount != value.m_cpuCount) return false;
    if(m_coreUsage != value.m_coreUsage) return false;
    if(m_usage != value.m_usage) return false;
    if(m_description != value.m_description) return false;
    if(m_hardwareDescription != value.m_hardwareDescription) return false;
    if(m_memoryUnits != value.m_memoryUnits) return false;
    if(m_totalMemory != value.m_totalMemory) return false;
    if(m_model != value.m_model) return false;
    if(m_processor != value.m_processor) return false;
    if(m_temp != value.m_temp) return false;
    if(m_serialNumber != value.m_serialNumber) return false;

    return true;
}

bool QKlipperCpuInfo::operator!=(const QKlipperCpuInfo &value)
{
    if(m_bitCount == value.m_bitCount &&
        m_cpuCount == value.m_cpuCount &&
        m_coreUsage == value.m_coreUsage &&
        m_usage == value.m_usage &&
        m_description == value.m_description &&
        m_hardwareDescription == value.m_hardwareDescription &&
        m_memoryUnits == value.m_memoryUnits &&
        m_totalMemory == value.m_totalMemory &&
        m_model == value.m_model &&
        m_processor == value.m_processor &&
        m_temp == value.m_temp &&
        m_serialNumber == value.m_serialNumber)
        return false;

    return true;
}

bool QKlipperCpuInfo::operator!=(QKlipperCpuInfo &&value)
{
    if(m_bitCount == value.m_bitCount &&
        m_cpuCount == value.m_cpuCount &&
        m_coreUsage == value.m_coreUsage &&
        m_usage == value.m_usage &&
        m_description == value.m_description &&
        m_hardwareDescription == value.m_hardwareDescription &&
        m_memoryUnits == value.m_memoryUnits &&
        m_totalMemory == value.m_totalMemory &&
        m_model == value.m_model &&
        m_processor == value.m_processor &&
        m_temp == value.m_temp &&
        m_serialNumber == value.m_serialNumber)
        return false;

    return true;
}

QKlipperCpuInfo &QKlipperCpuInfo::operator=(QKlipperCpuInfo &&value)
{
    m_bitCount = value.m_bitCount;
    m_cpuCount = value.m_cpuCount;
    m_coreUsage = value.m_coreUsage;
    m_usage = value.m_usage;
    m_description = value.m_description;
    m_hardwareDescription = value.m_hardwareDescription;
    m_memoryUnits = value.m_memoryUnits;
    m_totalMemory = value.m_totalMemory;
    m_model = value.m_model;
    m_processor = value.m_processor;
    m_temp = value.m_temp;
    m_serialNumber = value.m_serialNumber;

    return *this;
}

qint32 QKlipperCpuInfo::cpuCount() const
{
    return m_cpuCount;
}

void QKlipperCpuInfo::setCpuCount(qint32 cpuCount)
{
    if (m_cpuCount == cpuCount)
        return;

    m_cpuCount = cpuCount;
    emit cpuCountChanged();
}

void QKlipperCpuInfo::resetCpuCount()
{
    setCpuCount({}); // TODO: Adapt to use your actual default value
}

qint32 QKlipperCpuInfo::bitCount() const
{
    return m_bitCount;
}

void QKlipperCpuInfo::setBitCount(qint32 bitCount)
{
    if (m_bitCount == bitCount)
        return;

    m_bitCount = bitCount;
    emit bitCountChanged();
}

void QKlipperCpuInfo::resetBitCount()
{
    setBitCount({}); // TODO: Adapt to use your actual default value
}

qint64 QKlipperCpuInfo::totalMemory() const
{
    return m_totalMemory;
}

void QKlipperCpuInfo::setTotalMemory(qint64 totalMemory)
{
    if (m_totalMemory == totalMemory)
        return;

    m_totalMemory = totalMemory;
    emit totalMemoryChanged();
}

void QKlipperCpuInfo::resetTotalMemory()
{
    setTotalMemory({}); // TODO: Adapt to use your actual default value
}

qreal QKlipperCpuInfo::temp() const
{
    return m_temp;
}

void QKlipperCpuInfo::setTemp(qreal temp)
{
    if (qFuzzyCompare(m_temp, temp))
        return;

    m_temp = temp;
    emit tempChanged();
}

void QKlipperCpuInfo::resetTemp()
{
    setTemp({}); // TODO: Adapt to use your actual default value
}

qreal QKlipperCpuInfo::usage() const
{
    return m_usage;
}

void QKlipperCpuInfo::setUsage(qreal usage)
{
    if (qFuzzyCompare(m_usage, usage))
        return;

    m_usage = usage;
    emit usageChanged();
}

void QKlipperCpuInfo::resetUsage()
{
    setUsage({}); // TODO: Adapt to use your actual default value
}

QString QKlipperCpuInfo::processor() const
{
    return m_processor;
}

void QKlipperCpuInfo::setProcessor(const QString &processor)
{
    if (m_processor == processor)
        return;

    m_processor = processor;
    emit processorChanged();
}

void QKlipperCpuInfo::resetProcessor()
{
    setProcessor({}); // TODO: Adapt to use your actual default value
}

QString QKlipperCpuInfo::description() const
{
    return m_description;
}

void QKlipperCpuInfo::setDescription(const QString &description)
{
    if (m_description == description)
        return;

    m_description = description;
    emit descriptionChanged();
}

void QKlipperCpuInfo::resetDescription()
{
    setDescription({}); // TODO: Adapt to use your actual default value
}

QString QKlipperCpuInfo::serialNumber() const
{
    return m_serialNumber;
}

void QKlipperCpuInfo::setSerialNumber(const QString &serialNumber)
{
    if (m_serialNumber == serialNumber)
        return;

    m_serialNumber = serialNumber;
    emit serialNumberChanged();
}

void QKlipperCpuInfo::resetSerialNumber()
{
    setSerialNumber({}); // TODO: Adapt to use your actual default value
}

QString QKlipperCpuInfo::hardwareDescription() const
{
    return m_hardwareDescription;
}

void QKlipperCpuInfo::setHardwareDescription(const QString &hardwareDescription)
{
    if (m_hardwareDescription == hardwareDescription)
        return;

    m_hardwareDescription = hardwareDescription;
    emit hardwareDescriptionChanged();
}

void QKlipperCpuInfo::resetHardwareDescription()
{
    setHardwareDescription({}); // TODO: Adapt to use your actual default value
}

QString QKlipperCpuInfo::model() const
{
    return m_model;
}

void QKlipperCpuInfo::setModel(const QString &model)
{
    if (m_model == model)
        return;

    m_model = model;
    emit modelChanged();
}

void QKlipperCpuInfo::resetModel()
{
    setModel({}); // TODO: Adapt to use your actual default value
}

QString QKlipperCpuInfo::memoryUnits() const
{
    return m_memoryUnits;
}

void QKlipperCpuInfo::setMemoryUnits(const QString &memoryUnits)
{
    if (m_memoryUnits == memoryUnits)
        return;

    m_memoryUnits = memoryUnits;
    emit memoryUnitsChanged();
}

void QKlipperCpuInfo::resetMemoryUnits()
{
    setMemoryUnits({}); // TODO: Adapt to use your actual default value
}

QList<qreal> QKlipperCpuInfo::coreUsage() const
{
    return m_coreUsage;
}

void QKlipperCpuInfo::setCoreUsage(const QList<qreal> &coreUsage)
{
    if (m_coreUsage == coreUsage)
        return;

    m_coreUsage = coreUsage;
    emit coreUsageChanged();
}

void QKlipperCpuInfo::resetCoreUsage()
{
    setCoreUsage({}); // TODO: Adapt to use your actual default value
}
