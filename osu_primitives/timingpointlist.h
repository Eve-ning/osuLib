#ifndef TIMINGPOINTLIST_H
#define TIMINGPOINTLIST_H
#include "timingpoint.h"
#include "osuobjectlist.h"

class TimingPointList final : public OsuObjectList<TimingPoint>
{
public:    
    // Load from String
    TimingPointList(QStringList stringList);
    TimingPointList(QList<std::shared_ptr<TimingPoint>> value) : OsuObjectList<TimingPoint>(value){}
    TimingPointList(const TimingPointList& value) : OsuObjectList<TimingPoint>(value.m_value){}
    TimingPointList& operator =(const TimingPointList &value){
        m_value = std::move(value.m_value);
        return *this;
    }
    TimingPointList& operator =(TimingPointList &&value) &{
        m_value = std::move(value.m_value);
        return *this;
    }
    TimingPointList();

    std::shared_ptr<TimingPointList> clone() const { return std::static_pointer_cast<TimingPointList>(doClone()); }

    ~TimingPointList(){}

    void append(std::shared_ptr<TimingPointList> TPList) { append(*TPList); }
    void append(std::shared_ptr<TimingPoint> TP) { m_value.append(TP); }
    void append(TimingPointList TPList) { m_value.append(TPList.value()); }

    void operator +=(std::shared_ptr<TimingPoint> TP) { append(TP);}
    TimingPointList operator +(std::shared_ptr<TimingPoint> TP) { append(TP); return *this;}

    void operator +=(TimingPointList TPList) { append(TPList);}
    TimingPointList operator +(TimingPointList TPList) { append(TPList); return *this;}

    QList<std::shared_ptr<TimingPoint>> value() const;
    void setValue(const QList<std::shared_ptr<TimingPoint>> &value);
    double distance() const;
    double average() const;

    using OsuObjectList::length;
    double length(int index) const;

    QList<double> valueList() const;
    QList<double> codeList() const;
    QList<int> metronomeList() const;
    QList<SampleSet> sampleList() const;
    QList<int> sampleSetIndexList() const;
    QList<int> volumeList() const;
    QList<bool> isKiaiList() const;

    void setValueList          (const QList<double>    &value);
    void setCodeList           (const QList<double>    &value);
    void setMetronomeList      (const QList<int>       &value);
    void setSampleList         (const QList<SampleSet> &value);
    void setSampleSetIndexList (const QList<int>       &value);
    void setVolumeList         (const QList<int>       &value);
    void setIsKiaiList         (const QList<bool>      &value);

    QStringList toStringList();

    TimingPointList toSliderVelocity();
    TimingPointList toBPM();

protected:

private:
    std::shared_ptr<OsuObjectList> doClone() const override {
        QList<std::shared_ptr<TimingPoint>> output;

        std::for_each(m_value.begin(), m_value.end(), [&](const std::shared_ptr<TimingPoint> &value){
            output.append(value->clone());
        });

        return std::make_shared<TimingPointList>(output);
    }

};

#endif // TIMINGPOINTLIST_H
