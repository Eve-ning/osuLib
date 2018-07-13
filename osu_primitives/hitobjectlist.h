#ifndef HITOBJECTLIST_H
#define HITOBJECTLIST_H
#include "hitobject.h"

class HitObjectList
{
public:
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

    void setColumnList       (const QList<int>       &value) { if (!sameSize(value)) { return; } for (int i; i < size(); ++i) {m_value[i]->setColumn      (value[i]);}}
    void setOffsetList       (const QList<double>    &value) { if (!sameSize(value)) { return; } for (int i; i < size(); ++i) {m_value[i]->setOffset      (value[i]);}}
    void setHitsoundList     (const QList<SampleSet> &value) { if (!sameSize(value)) { return; } for (int i; i < size(); ++i) {m_value[i]->setHitsound    (value[i]);}}
    void setSampleList       (const QList<SampleSet> &value) { if (!sameSize(value)) { return; } for (int i; i < size(); ++i) {m_value[i]->setSample      (value[i]);}}
    void setAdditionList     (const QList<SampleSet> &value) { if (!sameSize(value)) { return; } for (int i; i < size(); ++i) {m_value[i]->setAddition    (value[i]);}}
    void setCustomList       (const QList<int>       &value) { if (!sameSize(value)) { return; } for (int i; i < size(); ++i) {m_value[i]->setCustom      (value[i]);}}
    void setVolumeList       (const QList<int>       &value) { if (!sameSize(value)) { return; } for (int i; i < size(); ++i) {m_value[i]->setVolume      (value[i]);}}
    void setHitsoundFileList (const QList<QString>   &value) { if (!sameSize(value)) { return; } for (int i; i < size(); ++i) {m_value[i]->setHitsoundFile(value[i]);}}


protected:

    template <typename T>
    bool sameSize(QList<T> compare){
        return this->size() == compare.size();
    }

private:
    QList<std::shared_ptr<HitObject>> m_value = {};
};

#endif // HITOBJECTLIST_H
