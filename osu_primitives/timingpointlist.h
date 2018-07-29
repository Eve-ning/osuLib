#ifndef TIMINGPOINTLIST_H
#define TIMINGPOINTLIST_H
#include "timingpoint.h"
#include "osuobjectlist.h"

class TimingPointList
{
public:    
    // Load from String
    TimingPointList(QStringList stringList);

    TimingPointList();

    ~TimingPointList(){}

    void append(std::shared_ptr<TimingPointList> TPList) { append(*TPList); }
    void append(std::shared_ptr<TimingPoint> TP) { m_value.append(TP); }
    void append(TimingPointList TPList) { m_value.append(TPList.value()); }

    std::shared_ptr<TimingPoint> operator [](int i) const { return at(i); }
    std::shared_ptr<TimingPoint> at(int i) const {
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

    QList<std::shared_ptr<TimingPoint>> value() const;
    void setValue(const QList<std::shared_ptr<TimingPoint>> &value);

    void sort(bool isAscending = true);
    double length() const {
        return max() - min();
    }

    int size() const {
        return m_value.size();
    }
    double min() const {
        auto offset_list = offsetList();
        return *std::min_element(offset_list.begin(), offset_list.end());
    }
    double max() const {
        auto offset_list = offsetList();
        return *std::max_element(offset_list.begin(), offset_list.end());
    }

    auto begin() const {
        return m_value.begin();
    }
    auto end() const {
        return m_value.end();
    }

    double distance() const;
    double average() const;
    double length(int index) const;

    QList<double> offsetList() const;
    QList<double> valueList() const;
    QList<double> codeList() const;
    QList<int> metronomeList() const;
    QList<SampleSet> sampleList() const;
    QList<int> sampleSetIndexList() const;
    QList<int> volumeList() const;
    QList<bool> isKiaiList() const;

    void setOffsetList         (const QList<double>    &value);
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
    QList<std::shared_ptr<TimingPoint>> m_value = {};

};

#endif // TIMINGPOINTLIST_H
