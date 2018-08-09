#include "timingpointlist.h"

TimingPointList::TimingPointList(QStringList stringList)
{
    QList<std::shared_ptr<TimingPoint> > input;
    for (auto string : stringList) {
        input.append(TimingPoint::fromString(string));
    }
    setValue(input);
}

TimingPointList::TimingPointList(){}

QList<std::shared_ptr<TimingPoint> > TimingPointList::value() const
{
    return m_value;
}

void TimingPointList::setValue(const QList<std::shared_ptr<TimingPoint> > &value)
{
    m_value = value;
}

//void TimingPointList::sort(bool isAscending)
//{
//    std::sort(m_value.begin(), m_value.end(),
//              [isAscending](std::shared_ptr<TimingPoint> a,
//                            std::shared_ptr<TimingPoint> b){
//        if (isAscending) {
//            return a->offset() < b->offset();
//        } else {
//            return a->offset() > b->offset();
//        }
//    });
//}

double TimingPointList::distance() const
{
    double output = 0;
    for (int i = 0; i < size() - 1; ++i){
        output += (length(i) * m_value[i]->value());
    }

    return output;
}

double TimingPointList::average() const
{
    double dist = distance();
    return dist / length();
}

//QList<double> TimingPointList::offsetList() const {
//    QList<double> output = {};
//    for (std::shared_ptr<TimingPoint> TP : m_value) { output.append(TP->offset()); }
//    return output;
//}

QList<double> TimingPointList::valueList() const
{
    QList<double> output = {};
    for (std::shared_ptr<TimingPoint> TP : m_value) { output.append(TP->value()); }
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

void TimingPointList::setValueList(const QList<double> &value) {
    if (!sameSize(value)) {
        return;
    }
    for (int i = 0; i < size(); ++i) {
        m_value[i]->setValue(value[i]);
    }
}

//void TimingPointList::setOffsetList(const QList<double> &value) {
//    if (!sameSize(value)) {
//        return;
//    }
//    for (int i = 0; i < size(); ++i) {
//        m_value[i]->setOffset(value[i]);
//    }
//}
void TimingPointList::setCodeList(const QList<double> &value) {
    if (!sameSize(value)) {
        return;
    }
    for (int i = 0; i < size(); ++i) {
        m_value[i]->setCode(value[i]);
    }
}
void TimingPointList::setMetronomeList(const QList<int> &value) {
    if (!sameSize(value)) {
        return;
    }
    for (int i = 0; i < size(); ++i) {
        m_value[i]->setMetronome(value[i]);
    }
}
void TimingPointList::setSampleList(const QList<SampleSet> &value) {
    if (!sameSize(value)) {
        return;
    }
    for (int i = 0; i < size(); ++i) {
        m_value[i]->setSample(value[i]);
    }
}
void TimingPointList::setSampleSetIndexList(const QList<int> &value) {
    if (!sameSize(value)) {
        return;
    }
    for (int i = 0; i < size(); ++i) {
        m_value[i]->setSampleSetIndex(value[i]);
    }
}
void TimingPointList::setVolumeList(const QList<int> &value) {
    if (!sameSize(value)) {
        return;
    }
    for (int i = 0; i < size(); ++i) {
        m_value[i]->setVolume(value[i]);
    }
}
void TimingPointList::setIsKiaiList(const QList<bool> &value) {
    if (!sameSize(value)) {
        return;
    }
    for (int i = 0; i < size(); ++i) {
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

TimingPointList TimingPointList::toSliderVelocity()
{
    TimingPointList output = {};

    for (const auto &TP: m_value) {
        auto isCasted = std::dynamic_pointer_cast<SliderVelocity>(TP);
        if (isCasted) {
            output.append(TP);
        }
    }
    return output;
}

TimingPointList TimingPointList::toBPM()
{
    TimingPointList output = {};

    for (const auto &TP: m_value) {
        auto isCasted = std::dynamic_pointer_cast<BPM>(TP);
        if (isCasted) {
            output.append(TP);
        }
    }
    return output;
}

TimingPointList TimingPointList::normalize(const double &referenceBPM) const
{
    TimingPointList c_value = *this;
    c_value = c_value.toBPM();

    if (c_value.size() == 0) {
        qDebug() << "Normalize called with no BPM.";
        return TimingPointList();
    }

    TimingPointList normalizeList = {};

    std::for_each(c_value.begin(), c_value.end(), [&](auto &TP){
        std::shared_ptr<TimingPoint> test =
                std::make_shared<SliderVelocity>(SliderVelocity(TP->offset(), referenceBPM / TP->value()));
        normalizeList.append(test);
    });

    return normalizeList;
}

void TimingPointList::superimpose(const TimingPointList &factor, double (*fptr)(double, double))
{
    QList<double> base_vList = valueList();
    QList<double> fact_vList = factor.valueList();

    fact_vList.append(std::numeric_limits<double>::max());

    for (int b = 0, f = 0; (b < base_vList.length() && f < fact_vList.length() - 1);) {
        if (base_vList[b] < fact_vList[f]) { // f must always be behind b to factor correctly
            b ++;
            continue;
        }
        if (base_vList[b] > fact_vList[f + 1]) { // Index will never throw exceptions due to conditions
            f ++;
            continue;
        }
        base_vList[b] = fptr(base_vList[b], fact_vList[f]);


        b ++; // If factoring successful, we move b forward
    }

    setValueList(base_vList);
}

double TimingPointList::length(int index) const
{
    if (index >= size() - 1 || index < 0) {
        qDebug() << "length() function fail.";
        return 0;
    }

    auto offsetL = offsetList();
    return offsetL[index + 1] - offsetL[index];
}
