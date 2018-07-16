#include "osu_primitives/timingpoint.h"

int TimingPoint::metronome() const
{
    return m_metronome;
}

void TimingPoint::setMetronome(const int &metronome)
{
    m_metronome = metronome;
}

SampleSet TimingPoint::sample() const
{
    return m_sample;
}

void TimingPoint::setSample(const SampleSet &sample)
{
    m_sample = sample;
}

int TimingPoint::sampleSetIndex() const
{
    return m_sampleSetIndex;
}

void TimingPoint::setSampleSetIndex(const int &sampleSetIndex)
{
    m_sampleSetIndex = sampleSetIndex;
}

int TimingPoint::volume() const
{
    return m_volume;
}

void TimingPoint::setVolume(const int &volume)
{
    m_volume = volume;
}

bool TimingPoint::isKiai() const
{
    return m_isKiai;
}

void TimingPoint::setIsKiai(const bool &isKiai)
{
    m_isKiai = isKiai;
}

std::shared_ptr<TimingPoint> TimingPoint::fromString(QString string)
{
    QTextStream ts(&string);

    char delim;

    double offset;
    double code;
    int metronome;
    int sample;
    int sampleSetIndex;
    int volume;
    int isBPM;
    int isKiai;

    ts >> offset >> delim
       >> code >> delim
       >> metronome >> delim
       >> sample >> delim
       >> sampleSetIndex >> delim
       >> volume >> delim
       >> isBPM >> delim
       >> isKiai;

    if (isBPM) {
        return std::make_shared<BPM>(
                BPM(offset,
                    BPM::toValue(code),
                    metronome,
                    static_cast<SampleSet>(sample),
                    sampleSetIndex,
                    volume,
                    isKiai));
    } else {
        return std::make_shared<SliderVelocity>(
                SliderVelocity(offset,
                               SliderVelocity::toValue(code),
                               metronome,
                               static_cast<SampleSet>(sample),
                               sampleSetIndex,
                               volume,
                               isKiai));
    }
}



void SliderVelocity::debugInfo() const
{
    qDebug() << "[ Slider Velocity Info ]" << endl
             << "m_offset        : " << m_offset         << endl
             << "m_value         : " << m_value           << endl
             << "m_metronome     : " << m_metronome      << endl
             << "m_sample        : " << static_cast<int>(m_sample) << endl
             << "m_sampleSetIndex: " << m_sampleSetIndex << endl
             << "m_volume        : " << m_volume         << endl
             << "isKiai          : " << m_isKiai;
}

QString SliderVelocity::toString() const
{
    // 18610,-200,4,1,0,41,0,0

    QString output = "";

    output += QString::number(m_offset)
            + "," + QString::number(code(), 'g', 15)
            + "," + QString::number(m_metronome)
            + "," + QString::number(static_cast<int>(m_sample))
            + "," + QString::number(m_sampleSetIndex)
            + "," + QString::number(m_volume)
            + "," + "0"
            + "," + QString::number(m_isKiai);

    return output;
}

void BPM::debugInfo() const
{
    qDebug() << "[ BPM Info ]" << endl
             << "m_offset        : " << m_offset         << endl
             << "m_value(temp)   : " << m_value          << endl
             << "m_metronome     : " << m_metronome      << endl
             << "m_sample        : " << static_cast<int>(m_sample) << endl
             << "m_sampleSetIndex: " << m_sampleSetIndex << endl
             << "m_volume        : " << m_volume         << endl
             << "isKiai          : " << m_isKiai;
}

QString BPM::toString() const
{
    // 18610,769.230769230769,4,1,0,41,1,0

    QString output = "";

    output += QString::number(m_offset)
            + "," + QString::number(code(), 'g', 15)
            + "," + QString::number(m_metronome)
            + "," + QString::number(static_cast<int>(m_sample))
            + "," + QString::number(m_sampleSetIndex)
            + "," + QString::number(m_volume)
            + "," + "1"
            + "," + QString::number(m_isKiai);

    return output;
}

