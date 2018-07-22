#ifndef TIMINGPOINTLIST_H
#define TIMINGPOINTLIST_H
#include "timingpoint.h"
#include "osuobjectlist.h"

class TimingPointList final : public OsuObjectList<TimingPoint>
{
public:
    TimingPointList(){}

    std::shared_ptr<OsuObjectList> Clone() override { return std::make_shared<TimingPointList>(*this); }

    void append(std::shared_ptr<TimingPointList> TPList) { append(*TPList); }
    void append(std::shared_ptr<TimingPoint> TP) override { m_value.append(TP); }
    void append(TimingPointList TPList) { m_value.append(TPList.value()); }

    // Load from String
    TimingPointList(QStringList stringList);

    ~TimingPointList(){}

    std::shared_ptr<TimingPoint> operator [](int i) const override  { return at(i); }
    std::shared_ptr<TimingPoint> at(int i) const override {
        if (i < size() && i >= 0) {
            return m_value.at(i);
        } else {
            qDebug() << "Index on TimingPointList out of range.";
            return m_value.at(0);
        }
    }

    void operator +=(std::shared_ptr<TimingPoint> TP) { append(TP);}
    TimingPointList operator +(std::shared_ptr<TimingPoint> TP) { append(TP); return *this;}

    void operator +=(TimingPointList TPList) { append(TPList);}
    TimingPointList operator +(TimingPointList TPList) { append(TPList); return *this;}



    QList<std::shared_ptr<TimingPoint>> value() const override;
    void setValue(const QList<std::shared_ptr<TimingPoint>> &value);

    int size() const override  { return m_value.size(); }
    void sort(bool isAscending = true) override ;
    double length() const override {
        return max() - min();
    }

    double min() const override {
        auto offset_list = offsetList();
        return *std::min_element(offset_list.begin(), offset_list.end());
    }
    double max() const override {
        auto offset_list = offsetList();
        return *std::max_element(offset_list.begin(), offset_list.end());
    }

    double distance() const;
    double average() const;
    double length(int index) const;

    QList<double> offsetList() const override ;
    QList<double> valueList() const;
    QList<double> codeList() const;
    QList<int> metronomeList() const;
    QList<SampleSet> sampleList() const;
    QList<int> sampleSetIndexList() const;
    QList<int> volumeList() const;
    QList<bool> isKiaiList() const;

    void setOffsetList         (const QList<double>    &value) override ;
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

    template <typename T>
    bool sameSize(QList<T> compare){
        return this->size() == compare.size();
    }

};

#endif // TIMINGPOINTLIST_H
