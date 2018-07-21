#ifndef HITOBJECTLIST_H
#define HITOBJECTLIST_H
#include "hitobject.h"
#include "osuobjectlist.h"

class HitObjectList final : public OsuObjectList<HitObject>
{
public:
    HitObjectList(){}

    // Load from StringList
    HitObjectList(QStringList stringList, const int &keys);

    ~HitObjectList(){}

    std::shared_ptr<HitObject> operator [](int i) const { return at(i); }
    std::shared_ptr<HitObject> at(int i) const {
        if (i < size() && i >= 0) {
            return m_value.at(i);
        } else {
            qDebug() << "Index on HitObjectList out of range.";
            return m_value.at(0);
        }
    }

    void operator +=(std::shared_ptr<HitObject> HO) { append(HO);}
    HitObjectList operator +(std::shared_ptr<HitObject> HO) { append(HO); return *this;}

    void operator +=(HitObjectList HOList) { append(HOList);}
    HitObjectList operator +(HitObjectList HOList) { append(HOList); return *this;}

    void append(std::shared_ptr<HitObject> HO) { m_value.append(HO); }
    void append(HitObjectList HOList) { m_value.append(HOList.value()); }

    QList<std::shared_ptr<HitObject>> value() const;
    void setValue(const QList<std::shared_ptr<HitObject>> &value);

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

    int size() const { return m_value.size(); }
    void sort(bool isAscending = true);
    double length() const {
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

protected:

    template <typename T>
    bool sameSize(QList<T> compare){
        return this->size() == compare.size();
    }

};

#endif // HITOBJECTLIST_H
