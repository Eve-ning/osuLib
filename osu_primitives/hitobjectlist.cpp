#include "hitobjectlist.h"

HitObjectList::HitObjectList(QStringList stringList, const int &keys)
{
    QList<std::shared_ptr<HitObject> > input;
    for (auto string : stringList) {
        input.append(HitObject::fromString(string, keys));
    }
    setValue(input);
}

QList<std::shared_ptr<HitObject> > HitObjectList::value() const
{
    return m_value;
}

void HitObjectList::setValue(const QList<std::shared_ptr<HitObject> > &value)
{
    m_value = value;
}

void HitObjectList::sort(bool isAscending)
{
    std::sort(m_value.begin(), m_value.end(),
              [isAscending](std::shared_ptr<HitObject> a,
                            std::shared_ptr<HitObject> b){
        if (isAscending) {
            return a->offset() < b->offset();
        } else {
            return a->offset() > b->offset();
        }
    });
}

QList<int> HitObjectList::columnList() const {
    QList<int> output = {};
    for (std::shared_ptr<HitObject> HO : m_value) { output.append(HO->column()); }
    return output;
}

QList<double> HitObjectList::offsetList() const {
    QList<double> output = {};
    for (std::shared_ptr<HitObject> HO : m_value) { output.append(HO->offset()); }
    return output;
}

QList<SampleSet> HitObjectList::hitsoundList() const {
    QList<SampleSet> output = {};
    for (std::shared_ptr<HitObject> HO : m_value) { output.append(HO->hitsound()); }
    return output;
}

QList<SampleSet> HitObjectList::sampleList() const {
    QList<SampleSet> output = {};
    for (std::shared_ptr<HitObject> HO : m_value) { output.append(HO->sample()); }
    return output;
}

QList<SampleSet> HitObjectList::additionList() const {
    QList<SampleSet> output = {};
    for (std::shared_ptr<HitObject> HO : m_value) { output.append(HO->addition()); }
    return output;
}

QList<int> HitObjectList::customList() const {
    QList<int> output = {};
    for (std::shared_ptr<HitObject> HO : m_value) { output.append(HO->custom()); }
    return output;
}

QList<int> HitObjectList::volumeList() const {
    QList<int> output = {};
    for (std::shared_ptr<HitObject> HO : m_value) { output.append(HO->volume()); }
    return output;
}

QList<QString> HitObjectList::hitsoundFileList() const {
    QList<QString> output = {};
    for (std::shared_ptr<HitObject> HO : m_value) { output.append(HO->hitsoundFile()); }
    return output;
}

void HitObjectList::setColumnList(const QList<int> &value) {
    if (!sameSize(value)) {
        return;
    }
    for (int i; i < size(); ++i) {
        m_value[i]->setColumn(value[i]);
    }
}
void HitObjectList::setOffsetList(const QList<double> &value) {
    if (!sameSize(value)) {
        return;
    }
    for (int i; i < size(); ++i) {
        m_value[i]->setOffset(value[i]);
    }
}
void HitObjectList::setHitsoundList(const QList<SampleSet> &value) {
    if (!sameSize(value)) {
        return;
    }
    for (int i; i < size(); ++i) {
        m_value[i]->setHitsound(value[i]);
    }
}
void HitObjectList::setSampleList(const QList<SampleSet> &value) {
    if (!sameSize(value)) {
        return;
    }
    for (int i; i < size(); ++i) {
        m_value[i]->setSample(value[i]);
    }
}
void HitObjectList::setAdditionList(const QList<SampleSet> &value) {
    if (!sameSize(value)) {
        return;
    }
    for (int i; i < size(); ++i) {
        m_value[i]->setAddition(value[i]);
    }
}
void HitObjectList::setCustomList(const QList<int> &value) {
    if (!sameSize(value)) {
        return;
    }
    for (int i; i < size(); ++i) {
        m_value[i]->setCustom(value[i]);
    }
}
void HitObjectList::setVolumeList(const QList<int> &value) {
    if (!sameSize(value)) {
        return;
    }
    for (int i; i < size(); ++i) {
        m_value[i]->setVolume(value[i]);
    }
}
void HitObjectList::setHitsoundFileList(const QList<QString> &value) {
    if (!sameSize(value)) {
        return;
    }
    for (int i; i < size(); ++i) {
        m_value[i]->setHitsoundFile(value[i]);
    }
}

QStringList HitObjectList::toStringList(const int &keys)
{
    QStringList output;

    for (auto &HO : m_value) {
        output.append(HO->toString(keys));
    }

    return output;
}



