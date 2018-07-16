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

    virtual double value() const = 0;
    virtual void setValue(const double &value) = 0;
    virtual double code() const = 0;
    virtual void setCode(const double &code) = 0;

    int metronome() const;
    void setMetronome(const int &metronome);

    SampleSet sample() const;
    void setSample(const SampleSet &sample);

    int sampleSetIndex() const;
    void setSampleSetIndex(const int &sampleSetIndex);

    int volume() const;
    void setVolume(const int &volume);

    bool isKiai() const;
    void setIsKiai(const bool &isKiai);

    virtual void debugInfo() const = 0;
    virtual QString toString() const = 0;

    static std::shared_ptr<TimingPoint> fromString(QString string);

protected:

    BoundedDouble m_offset         = BoundedDouble(0, 0);
//    BoundedDouble m_value; //Uninitialized
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
        m_value = value;
        m_offset = offset;
    }
    SliderVelocity(const double &offset,
                   const double &value,
                   const int &metronome,
                   const SampleSet &sample,
                   const int &sampleSetIndex,
                   const int &volume,
                   const bool &isKiai) {
        m_value = BoundedDouble(1.0, 0.1, 10.0);
        m_value          = value;
        m_offset         = offset;
        m_metronome      = metronome;
        m_sample         = sample;
        m_sampleSetIndex = sampleSetIndex;
        m_volume         = volume;
        m_isKiai         = isKiai;
    }

    void debugInfo() const override;
    QString toString() const override;

    static double maxBound() { return m_max; }
    static double minBound() { return m_min; }

    double value() const override {
        return m_value;
    }
    void setValue(const double &value) override {
        m_value = value;
    }
    double code() const override {
        return -100 / m_value;
    }
    void setCode(const double& value) override {
        m_value = -100 / value;
    }

    static double toValue(const double &code) {
        return -100 / code;
    }
    static double toCode(const double &value) {
        return -100 / value;
    }

private:

    static constexpr double m_max = 10.0;
    static constexpr double m_min = 0.1;
};

class BPM final : public TimingPoint
{
public:
    BPM(){}
    BPM(const double &offset) {
        m_offset = offset;
    }
    BPM(const double &offset,
        const double &value) {
        m_offset = offset;
        m_value = value;
    }
    BPM(const double &offset,
        const double &value,
        const int &metronome,
        const SampleSet &sample,
        const int &sampleSetIndex,
        const int &volume,
        const bool &isKiai) {
        m_value          = value;
        m_offset         = offset;
        m_metronome      = metronome;
        m_sample         = sample;
        m_sampleSetIndex = sampleSetIndex;
        m_volume         = volume;
        m_isKiai         = isKiai;{}
    }

    void debugInfo() const override;
    QString toString() const override;

    static double maxBound() { return m_max; }
    static double minBound() { return m_min; }

    double value() const override {
        return m_value;
    }
    void setValue(const double &value) override {
        m_value = value;
    }
    double code() const override {
        return 60000 / m_value;
    }
    void setCode(const double& value) override {
        m_value = 60000 / value;
    }

    static double toValue(const double &code) {
        return 60000 / code;
    }
    static double toCode(const double &value) {
        return 60000 / value;
    }

private:

    BoundedDouble m_value = BoundedDouble(100, 0.00000001, std::numeric_limits<double>::max());

    static constexpr double m_max = std::numeric_limits<double>::max();
    static constexpr double m_min = 0.00000001;
};

#endif // TIMINGPOINT_H
