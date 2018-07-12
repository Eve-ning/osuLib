#include "hitobject.h"

int HitObject::column() const
{
    return m_column;
}

void HitObject::setColumn(const int &column)
{
    m_column = column;
}

double HitObject::offset() const
{
    return m_offset;
}

void HitObject::setOffset(const double &offset)
{
    m_offset = offset;
}

SampleSet HitObject::hitsound() const
{
    return m_hitsound;
}

void HitObject::setHitsound(const SampleSet &hitsound)
{
    m_hitsound = hitsound;
}

SampleSet HitObject::sample() const
{
    return m_sample;
}

void HitObject::setSample(const SampleSet &sample)
{
    m_sample = sample;
}

SampleSet HitObject::addition() const
{
    return m_addition;
}

void HitObject::setAddition(const SampleSet &addition)
{
    m_addition = addition;
}

int HitObject::custom() const
{
    return m_custom;
}

void HitObject::setCustom(const int &custom)
{
    m_custom = custom;
}

int HitObject::volume() const
{
    return m_volume;
}

void HitObject::setVolume(const int &volume)
{
    m_volume = volume;
}

QString HitObject::hitsoundFile() const
{
    return m_hitsoundFile;
}

void HitObject::setHitsoundFile(const QString &hitsoundFile)
{
    m_hitsoundFile = hitsoundFile;
}

std::shared_ptr<HitObject> HitObject::fromString(QString string,
                                                 const int &keys){
    QTextStream ts(&string);

    char delim;

    int xAxis;
    int yAxis;
    double offset;
    int noteType;
    int hitsound;
    int sample;
    int addition;
    int custom;
    int volume;
    QString hitsoundFile;

    double offsetEnd;

    bool isLongNote = std::count(string.begin(), string.end(), ':') == 5;

    // Textstream to temporary variables
    ts >> xAxis >> delim
       >> yAxis >> delim
       >> offset >> delim
       >> noteType >> delim
       >> hitsound >> delim;

    if (isLongNote) {
        ts >> offsetEnd >> delim;
    }

    ts >> sample >> delim
       >> addition >> delim
       >> custom >> delim
       >> volume >> delim
       >> hitsoundFile;

    if (isLongNote) {
        return std::make_shared<LongNote>(
                LongNote(toColumn(xAxis, keys),
                         offset,
                         static_cast<SampleSet>(hitsound),
                         static_cast<SampleSet>(sample),
                         static_cast<SampleSet>(addition),
                         custom,
                         volume,
                         hitsoundFile,
                         offsetEnd));
    } else {
        return std::make_shared<NormalNote>(
                NormalNote(toColumn(xAxis, keys),
                           offset,
                           static_cast<SampleSet>(hitsound),
                           static_cast<SampleSet>(sample),
                           static_cast<SampleSet>(addition),
                           custom,
                           volume,
                           hitsoundFile));
    }


}

void LongNote::debugInfo() const
{
    qDebug() << "[ Long Note Info ]" << endl
             << "m_column       : " << m_column       << endl
             << "m_offset       : " << m_offset       << endl
             << "m_hitsound     : " << QString::number(static_cast<int>(m_hitsound)) << endl
             << "m_sample       : " << QString::number(static_cast<int>(m_sample)) << endl
             << "m_addition     : " << QString::number(static_cast<int>(m_addition)) << endl
             << "m_custom       : " << m_custom       << endl
             << "m_volume       : " << m_volume       << endl
             << "m_hitsoundFile : " << m_hitsoundFile << endl
             << "m_offsetEnd    : " << m_offsetEnd;
}

QString LongNote::toString(const int &keys) const {

    // 64,192,20725,128,0,21734:0:0:0:0:

    QString output = "";

    output += QString::number(toXAxis(m_column, keys))
            + "," + "192"
            + "," + QString::number(m_offset)
            + "," + "128"
            + "," + QString::number(static_cast<int>(m_hitsound))
            + "," + QString::number(m_offsetEnd)
            + ":" + QString::number(static_cast<int>(m_sample))
            + ":" + QString::number(static_cast<int>(m_addition))
            + ":" + QString::number(m_custom)
            + ":" + QString::number(m_volume)
            + ":" + m_hitsoundFile;

    return output;
}

double LongNote::offsetEnd() const
{
    return m_offsetEnd;
}

void LongNote::setOffsetEnd(const double &offsetEnd)
{
    m_offsetEnd = offsetEnd;
}

void NormalNote::debugInfo() const
{
    qDebug() << "[ Normal Note Info ]" << endl
             << "m_column       : " << m_column       << endl
             << "m_offset       : " << m_offset       << endl
             << "m_hitsound     : " << static_cast<int>(m_hitsound) << endl
             << "m_sample       : " << static_cast<int>(m_sample)   << endl
             << "m_addition     : " << static_cast<int>(m_addition) << endl
             << "m_custom       : " << m_custom       << endl
             << "m_volume       : " << m_volume       << endl
             << "m_hitsoundFile : " << m_hitsoundFile;
}

QString NormalNote::toString(const int &keys) const {

    // 448,192,18609,1,4,0:0:0:0:

    QString output = "";

    output += QString::number(toXAxis(m_column, keys))
            + "," + "192"
            + "," + QString::number(m_offset)
            + "," + "1"
            + "," + QString::number(static_cast<int>(m_hitsound))
            + "," + QString::number(static_cast<int>(m_sample))
            + ":" + QString::number(static_cast<int>(m_addition))
            + ":" + QString::number(m_custom)
            + ":" + QString::number(m_volume)
            + ":" + m_hitsoundFile;

    return output;
}
