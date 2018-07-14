#ifndef HITOBJECTLIST_H
#define HITOBJECTLIST_H
#include "hitobject.h"

class HitObjectList
{
public:
    HitObjectList(){}

    // Load from String
    HitObjectList(QStringList stringList, const int &keys);

    ~HitObjectList(){}

    std::shared_ptr<HitObject> operator [](int i) const { return at(i); }
    std::shared_ptr<HitObject> at(int i) const { return m_value.at(i); }

    void operator +=(std::shared_ptr<HitObject> HO) { append(HO);}
    HitObjectList operator +(std::shared_ptr<HitObject> HO) { append(HO); return *this;}

    void operator +=(HitObjectList HOList) { append(HOList);}
    HitObjectList operator +(HitObjectList HOList) { append(HOList); return *this;}

    void append(std::shared_ptr<HitObject> HO) { m_value.append(HO); }
    void append(HitObjectList HOList) { m_value.append(HOList.value()); }

    QList<std::shared_ptr<HitObject>> value() const;
    void setValue(const QList<std::shared_ptr<HitObject>> &value);

    int size() const { return m_value.size(); }
    void sort(bool isAscending = true);
    double length() const {
        auto offset_list = offsetList();
        return *std::max_element(offset_list.begin(), offset_list.end()) -
               *std::min_element(offset_list.begin(), offset_list.end());
    }

    QList<int> columnList() const;
    QList<double> offsetList() const;
    QList<SampleSet> hitsoundList() const;
    QList<SampleSet> sampleList() const;
    QList<SampleSet> additionList() const;
    QList<int> customList() const;
    QList<int> volumeList() const;
    QList<QString> hitsoundFileList() const;

    void setColumnList       (const QList<int>       &value);
    void setOffsetList       (const QList<double>    &value);
    void setHitsoundList     (const QList<SampleSet> &value);
    void setSampleList       (const QList<SampleSet> &value);
    void setAdditionList     (const QList<SampleSet> &value);
    void setCustomList       (const QList<int>       &value);
    void setVolumeList       (const QList<int>       &value);
    void setHitsoundFileList (const QList<QString>   &value);

    QStringList toStringList(const int &keys);

protected:

    template <typename T>
    bool sameSize(QList<T> compare){
        return this->size() == compare.size();
    }

private:
    QList<std::shared_ptr<HitObject>> m_value = {};
};

#endif // HITOBJECTLIST_H
