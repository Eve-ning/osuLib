#ifndef HITOBJECT_H
#define HITOBJECT_H

#include "bounded/boundedint.h"
#include "bounded/boundeddouble.h"

class HitObject
{
public:

    virtual ~HitObject() {
    }

    enum SampleSet {
        AUTO,
        NORMAL,
        SOFT,
        DRUM
    };

    int column() const;
    void setColumn(const int &column);

    double offset() const;
    void setOffset(const double &offset);

    SampleSet hitsound() const;
    void setHitsound(const SampleSet &hitsound);

    SampleSet sample() const;
    void setSample(const SampleSet &sample);

    SampleSet addition() const;
    void setAddition(const SampleSet &addition);

    int custom() const;
    void setCustom(const int &custom);

    int volume() const;
    void setVolume(const int &volume);

    QString hitsoundFile() const;
    void setHitsoundFile(const QString &hitsoundFile);

    virtual void debugInfo() const = 0;
    virtual QString toString() const = 0;

    static std::shared_ptr<HitObject> fromString(QString string,
                                                 const int &keys);

    static int toColumn(const int &xAxis,
                        const int &keys) {
        return round((xAxis / 256.0 * keys - 1.0) / 2.0) + 1;
    }
    static int toXAxis(const int &column,
                       const int &keys) {
        return round((column - 0.5) * 512.0 / keys);
    }

protected:

    BoundedInt    m_column       = BoundedInt(1, 1, 18);
    BoundedDouble m_offset       = BoundedDouble(0, 0);
    SampleSet     m_hitsound     = SampleSet::AUTO;
    SampleSet     m_sample       = SampleSet::AUTO;
    SampleSet     m_addition     = SampleSet::AUTO;
    BoundedInt    m_custom       = BoundedInt(0, 0, 99);
    BoundedInt    m_volume       = BoundedInt(10, 0, 100);
    QString       m_hitsoundFile = "";

};

struct NormalNote final : public HitObject
{
public:
    NormalNote() {}
    NormalNote(const double &offset) {
        m_offset = offset;
    }
    NormalNote(const int &column,
               const double &offset) {
        m_column = column;
        m_offset = offset;
    }
    NormalNote(const BoundedInt    &column,
               const BoundedDouble &offset,
               const SampleSet     &hitsound,
               const SampleSet     &sample,
               const SampleSet     &addition,
               const BoundedInt    &custom,
               const BoundedInt    &volume,
               const QString       &hitsoundFile) {
        m_column       = column;
        m_offset       = offset;
        m_hitsound     = hitsound;
        m_sample       = sample;
        m_addition     = addition;
        m_custom       = custom;
        m_volume       = volume;
        m_hitsoundFile = hitsoundFile;
    }
    void debugInfo() const override;
    QString toString() const override;
};

struct LongNote final : public HitObject
{
public:
    LongNote() {}
    LongNote(const double &offset,
             const double &offsetEnd) {
        m_offset    = offset;
        m_offsetEnd = offsetEnd;
    }
    LongNote(const int &column,
             const double &offset,
             const double &offsetEnd) {
        m_column    = column;
        m_offset    = offset;
        m_offsetEnd = offsetEnd;
    }
    LongNote(const BoundedInt    &column,
             const BoundedDouble &offset,
             const SampleSet     &hitsound,
             const SampleSet     &sample,
             const SampleSet     &addition,
             const BoundedInt    &custom,
             const BoundedInt    &volume,
             const QString       &hitsoundFile,
             const BoundedDouble &offsetEnd) {
        m_column       = column;
        m_offset       = offset;
        m_hitsound     = hitsound;
        m_sample       = sample;
        m_addition     = addition;
        m_custom       = custom;
        m_volume       = volume;
        m_hitsoundFile = hitsoundFile;
        m_offsetEnd    = offsetEnd;
    }
    void debugInfo() const override;
    QString toString() const override;

    double offsetEnd() const;
    void setOffsetEnd(const double &offsetEnd);

private:

    BoundedDouble m_offsetEnd = BoundedDouble(1, 0);
};

#endif // HITOBJECT_H
