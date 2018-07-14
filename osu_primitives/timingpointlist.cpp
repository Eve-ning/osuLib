#include "timingpointlist.h"

TimingPointList::TimingPointList(QStringList stringList)
{
    QList<std::shared_ptr<TimingPoint> > input;
    for (auto string : stringList) {
        input.append(TimingPoint::fromString(string));
    }
    setValue(input);
}

QList<std::shared_ptr<TimingPoint> > TimingPointList::value() const
{
    return m_value;
}

void TimingPointList::setValue(const QList<std::shared_ptr<TimingPoint> > &value)
{
    m_value = value;
}

void TimingPointList::sort(bool isAscending)
{
    std::sort(m_value.begin(), m_value.end(),
              [isAscending](std::shared_ptr<TimingPoint> a,
                            std::shared_ptr<TimingPoint> b){
        if (isAscending) {
            return a->offset() < b->offset();
        } else {
            return a->offset() > b->offset();
        }
    });
}

QList<double> TimingPointList::offsetList() const {
    QList<double> output = {};
    for (std::shared_ptr<TimingPoint> TP : m_value) { output.append(TP->offset()); }
    return output;
}

QList<double> TimingPointList::codeList() const {
    QList<double> output = {};
    for (std::shared_ptr<TimingPoint> TP : m_value) { output.append(TP->code()); }
    return output;
}

QList<int> TimingPointList::metronomeList() const {
    QList<int> output = {};
    for (std::shared_ptr<TimingPoint> TP : m_value) { output.append(TP->metronome()); }
    return output;
}

QList<SampleSet> TimingPointList::sampleList() const {
    QList<SampleSet> output = {};
    for (std::shared_ptr<TimingPoint> TP : m_value) { output.append(TP->sample()); }
    return output;
}

QList<int> TimingPointList::sampleSetIndexList() const {
    QList<int> output = {};
    for (std::shared_ptr<TimingPoint> TP : m_value) { output.append(TP->sampleSetIndex()); }
    return output;
}

QList<int> TimingPointList::volumeList() const {
    QList<int> output = {};
    for (std::shared_ptr<TimingPoint> TP : m_value) { output.append(TP->volume()); }
    return output;
}

QList<bool> TimingPointList::isKiaiList() const {
    QList<bool> output = {};
    for (std::shared_ptr<TimingPoint> TP : m_value) { output.append(TP->isKiai()); }
    return output;
}

void TimingPointList::setOffsetList(const QList<double> &value) {
    if (!sameSize(value)) {
        return;
    }
    for (int i; i < size(); ++i) {
        m_value[i]->setOffset(value[i]);
    }
}
void TimingPointList::setCodeList(const QList<double> &value) {
    if (!sameSize(value)) {
        return;
    }
    for (int i; i < size(); ++i) {
        m_value[i]->setCode(value[i]);
    }
}
void TimingPointList::setMetronomeList(const QList<int> &value) {
    if (!sameSize(value)) {
        return;
    }
    for (int i; i < size(); ++i) {
        m_value[i]->setMetronome(value[i]);
    }
}
void TimingPointList::setSampleList(const QList<SampleSet> &value) {
    if (!sameSize(value)) {
        return;
    }
    for (int i; i < size(); ++i) {
        m_value[i]->setSample(value[i]);
    }
}
void TimingPointList::setSampleSetIndexList(const QList<int> &value) {
    if (!sameSize(value)) {
        return;
    }
    for (int i; i < size(); ++i) {
        m_value[i]->setSampleSetIndex(value[i]);
    }
}
void TimingPointList::setVolumeList(const QList<int> &value) {
    if (!sameSize(value)) {
        return;
    }
    for (int i; i < size(); ++i) {
        m_value[i]->setVolume(value[i]);
    }
}
void TimingPointList::setIsKiaiList(const QList<bool> &value) {
    if (!sameSize(value)) {
        return;
    }
    for (int i; i < size(); ++i) {
        m_value[i]->setIsKiai(value[i]);
    }
}

QStringList TimingPointList::toStringList()
{
    QStringList output;

    for (auto &TP : m_value) {
        output.append(TP->toString());
    }

    return output;
}
