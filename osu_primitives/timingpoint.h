#ifndef TIMINGPOINT_H
#define TIMINGPOINT_H

#include "primitives/bounded/boundedint.h"
#include "primitives/bounded/boundeddouble.h"
#include "primitives/sampleset.h"

class TimingPoint
{
public:

    virtual ~TimingPoint(){
    }

    double offset() const;
    void setOffset(const double &offset);

    double code() const;
    void setCode(const double &code);

    int metronome() const;
    void setMetronome(const int &metronome);

    SampleSet sample() const;
    void setSample(const SampleSet &sample);

    int sampleSetIndex() const;
    void setSampleSetIndex(const int &sampleSetIndex);

    int volume() const;
    void setVolume(const int &volume);

    bool getIsKiai() const;
    void setIsKiai(const bool &isKiai);

    virtual void debugInfo() const = 0;
    virtual QString toString() const = 0;

    static std::shared_ptr<TimingPoint> fromString(QString string);

    virtual double toValue(const double &code) const = 0;
    virtual double toCode(const double &value) const = 0;

protected:

    BoundedDouble m_offset         = BoundedDouble(0, 0);
    BoundedDouble m_code           = BoundedDouble(-100);
    BoundedInt    m_metronome      = BoundedInt(4, 1, 99);
    SampleSet     m_sample         = SampleSet::AUTO;
    BoundedInt    m_sampleSetIndex = BoundedInt(0, 0, 99);
    BoundedInt    m_volume         = BoundedInt(10, 0, 100);
    bool          m_isKiai         = false;
};

class SliderVelocity final : public TimingPoint
{
public:
    SliderVelocity() {}
    SliderVelocity(const double &offset) {
        m_offset = offset;
    }
    SliderVelocity(const double &offset,
                   const double &value) {
        m_offset = offset;
        m_code = toCode(value);
    }
    SliderVelocity(const double &offset,
                   const double &value,
                   const int &metronome,
                   const SampleSet &sample,
                   const int &sampleSetIndex,
                   const int &volume,
                   const bool &isKiai) {
        m_offset         = offset;
        m_code           = toCode(value);
        m_metronome      = metronome;
        m_sample         = sample;
        m_sampleSetIndex = sampleSetIndex;
        m_volume         = volume;
        m_isKiai         = isKiai;
    }

    void debugInfo() const override;
    QString toString() const override;
    double toValue(const double &code) const override {
        return -100 / code;
    }
    double toCode(const double &value) const override {
        return -100 / value;
    }
};

class BPM final : public TimingPoint
{
public:
    BPM() {}
    BPM(const double &offset) {
        m_offset = offset;
    }
    BPM(const double &offset,
        const double &value) {
        m_offset = offset;
        m_code = toCode(value);
    }
    BPM(const double &offset,
        const double &value,
        const int &metronome,
        const SampleSet &sample,
        const int &sampleSetIndex,
        const int &volume,
        const bool &isKiai) {
        m_offset         = offset;
        m_code           = toCode(value);
        m_metronome      = metronome;
        m_sample         = sample;
        m_sampleSetIndex = sampleSetIndex;
        m_volume         = volume;
        m_isKiai         = isKiai;
    }

    void debugInfo() const override;
    QString toString() const override;
    double toValue(const double &code) const override {
        return 60000 / code;
    }
    double toCode(const double &value) const override {
        return 60000 / value;
    }
};

#endif // TIMINGPOINT_H
