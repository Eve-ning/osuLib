#ifndef HITOBJECTLIST_H
#define HITOBJECTLIST_H
#include "hitobject.h"
#include "osuobjectlist.h"

class HitObjectList final : public OsuObjectList<HitObject>
{
public:
    HitObjectList();

    // Load from StringList
    HitObjectList(QStringList stringList, const int &keys);
    HitObjectList(QList<std::shared_ptr<HitObject>> value) : OsuObjectList<HitObject>(value){}
    HitObjectList(const HitObjectList& value) : OsuObjectList<HitObject>(value.m_value){}
    HitObjectList(std::shared_ptr<OsuObjectList<HitObject>> value) : OsuObjectList<HitObject>(value->value()) {}
    HitObjectList& operator =(const HitObjectList &value){
        m_value = std::move(value.m_value);
        return *this;
    }
    HitObjectList& operator =(HitObjectList &&value) &{
        m_value = std::move(value.m_value);
        return *this;
    }

    ~HitObjectList(){}

    std::shared_ptr<HitObjectList> clone() const { return std::static_pointer_cast<HitObjectList>(doClone()); }

    // Convert Editor HitObject to HitObjectList
    static HitObjectList readEHO(const QString &value);

    bool operator ==(const HitObjectList &HOList) { return m_value == HOList.m_value; }
    bool operator !=(const HitObjectList &HOList) { return m_value != HOList.m_value; }

    void operator +=(std::shared_ptr<HitObject> HO) { append(HO);}
    HitObjectList operator +(std::shared_ptr<HitObject> HO) { append(HO); return *this;}

    void operator +=(HitObjectList HOList) { append(HOList);}
    HitObjectList operator +(HitObjectList HOList) { append(HOList); return *this;}

    void append(std::shared_ptr<HitObject> HO) { m_value.append(HO); }
    void append(HitObjectList HOList) { m_value.append(HOList.value()); }

    QList<std::shared_ptr<HitObject>> value() const;
    void setValue(const QList<std::shared_ptr<HitObject>> &value);

    QList<int> columnList() const;
    QList<SampleSet> hitsoundList() const;
    QList<SampleSet> sampleList() const;
    QList<SampleSet> additionList() const;
    QList<int> customList() const;
    QList<int> volumeList() const;
    QList<QString> hitsoundFileList() const;

    void setColumnList       (const QList<int>       &value);
    void setHitsoundList     (const QList<SampleSet> &value);
    void setSampleList       (const QList<SampleSet> &value);
    void setAdditionList     (const QList<SampleSet> &value);
    void setCustomList       (const QList<int>       &value);
    void setVolumeList       (const QList<int>       &value);
    void setHitsoundFileList (const QList<QString>   &value);

    QStringList toStringList(const int &keys);

protected:

private:
    std::shared_ptr<OsuObjectList<HitObject>> doClone() const override {
        QList<std::shared_ptr<HitObject>> output;
        std::for_each(m_value.begin(), m_value.end(), [&](const std::shared_ptr<HitObject> &value){
            output.append(value->clone());
        });
        return std::make_shared<HitObjectList>(m_value);
    }

};

#endif // HITOBJECTLIST_H
