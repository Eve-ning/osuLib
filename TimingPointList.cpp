#include "stdafx.h"
#include "timingpointlist.h"

TimingPointList::TimingPointList(std::vector<std::string> stringList)
{
	std::vector<std::shared_ptr<TimingPoint> > input;
	for (auto string : stringList) {
		input.push_back(TimingPoint::fromString(string));
	}
	setValue(input);
}

TimingPointList::TimingPointList() {}

std::vector<std::shared_ptr<TimingPoint> > TimingPointList::value() const
{
	return m_value;
}

void TimingPointList::setValue(const std::vector<std::shared_ptr<TimingPoint> > &value)
{
	m_value = value;
}

double TimingPointList::distance() const
{
	double output = 0;
	for (int i = 0; i < size() - 1; ++i) {
		output += (length(i) * m_value[i]->value());
	}

	return output;
}

double TimingPointList::average() const
{
	double dist = distance();
	return dist / length();
}

//std::vector<double> TimingPointList::offsetList() const {
//    std::vector<double> output = {};
//    for (std::shared_ptr<TimingPoint> TP : m_value) { output.append(TP->offset()); }
//    return output;
//}

std::vector<double> TimingPointList::valueList() const
{
	std::vector<double> output = {};
	for (const std::shared_ptr<TimingPoint> &TP : m_value) { output.push_back(TP->value()); }
	return output;
}

std::vector<double> TimingPointList::codeList() const {
	std::vector<double> output = {};
	for (const std::shared_ptr<TimingPoint> &TP : m_value) { output.push_back(TP->code()); }
	return output;
}

std::vector<int> TimingPointList::metronomeList() const {
	std::vector<int> output = {};
	for (const std::shared_ptr<TimingPoint> &TP : m_value) { output.push_back(TP->metronome()); }
	return output;
}

std::vector<SampleSet> TimingPointList::sampleList() const {
	std::vector<SampleSet> output = {};
	for (const std::shared_ptr<TimingPoint> &TP : m_value) { output.push_back(TP->sample()); }
	return output;
}

std::vector<int> TimingPointList::sampleSetIndexList() const {
	std::vector<int> output = {};
	for (const std::shared_ptr<TimingPoint> &TP : m_value) { output.push_back(TP->sampleSetIndex()); }
	return output;
}

std::vector<int> TimingPointList::volumeList() const {
	std::vector<int> output = {};
	for (const std::shared_ptr<TimingPoint> &TP : m_value) { output.push_back(TP->volume()); }
	return output;
}

std::vector<bool> TimingPointList::isKiaiList() const {
	std::vector<bool> output = {};
	for (const std::shared_ptr<TimingPoint> &TP : m_value) { output.push_back(TP->isKiai()); }
	return output;
}

void TimingPointList::setValueList(const std::vector<double> &value) {
	if (!sameSize(value)) {
		return;
	}
	for (int i = 0; i < size(); ++i) {
		m_value[i]->setValue(value[i]);
	}
}

//void TimingPointList::setOffsetList(const std::vector<double> &value) {
//    if (!sameSize(value)) {
//        return;
//    }
//    for (int i = 0; i < size(); ++i) {
//        m_value[i]->setOffset(value[i]);
//    }
//}
void TimingPointList::setCodeList(const std::vector<double> &value) {
	if (!sameSize(value)) {
		return;
	}
	for (int i = 0; i < size(); ++i) {
		m_value[i]->setCode(value[i]);
	}
}
void TimingPointList::setMetronomeList(const std::vector<int> &value) {
	if (!sameSize(value)) {
		return;
	}
	for (int i = 0; i < size(); ++i) {
		m_value[i]->setMetronome(value[i]);
	}
}
void TimingPointList::setSampleList(const std::vector<SampleSet> &value) {
	if (!sameSize(value)) {
		return;
	}
	for (int i = 0; i < size(); ++i) {
		m_value[i]->setSample(value[i]);
	}
}
void TimingPointList::setSampleSetIndexList(const std::vector<int> &value) {
	if (!sameSize(value)) {
		return;
	}
	for (int i = 0; i < size(); ++i) {
		m_value[i]->setSampleSetIndex(value[i]);
	}
}
void TimingPointList::setVolumeList(const std::vector<int> &value) {
	if (!sameSize(value)) {
		return;
	}
	for (int i = 0; i < size(); ++i) {
		m_value[i]->setVolume(value[i]);
	}
}
void TimingPointList::setIsKiaiList(const std::vector<bool> &value) {
	if (!sameSize(value)) {
		return;
	}
	for (int i = 0; i < size(); ++i) {
		m_value[i]->setIsKiai(value[i]);
	}
}

std::vector<std::string> TimingPointList::toStringList()
{
	std::vector<std::string> output;

	for (auto &TP : m_value) {
		output.push_back(TP->toString());
	}

	return output;
}

TimingPointList TimingPointList::toSliderVelocity() const
{
	std::vector<std::shared_ptr<TimingPoint>> output = {};

	for (auto &TP : m_value) {
		auto isCasted = std::dynamic_pointer_cast<SliderVelocity>(TP);
		if (isCasted) {
			output.push_back(isCasted);
		}
	}

	return TimingPointList(output);
}

TimingPointList TimingPointList::toBPM() const
{
	std::vector<std::shared_ptr<TimingPoint>> output = {};

	for (auto &TP : m_value) {
		auto isCasted = std::dynamic_pointer_cast<BPM>(TP);
		if (isCasted) {
			output.push_back(std::move(TP));
		}
	}

	return TimingPointList(output);
}

TimingPointList TimingPointList::normalize(const double &referenceBPM) const
{
	TimingPointList c_value = toBPM();

	if (c_value.size() == 0) {
		std::cout << "Normalize called with no BPM.";
		return TimingPointList();
	}

	TimingPointList normalizeList = {};

	for (auto& ea : c_value){
		SliderVelocity temp(ea->offset(), referenceBPM / ea->value());

		std::shared_ptr<TimingPoint> test =
			std::make_shared<SliderVelocity>(temp);
		normalizeList.append(test);
	}

	return normalizeList;
}

void TimingPointList::superimpose(const TimingPointList &factor, double(*fptr)(double, double))
{
	std::vector<double> base_vList = valueList();
	std::vector<double> fact_vList = factor.valueList();

	fact_vList.push_back(std::numeric_limits<double>::max());

	for (int b = 0, f = 0; (b < base_vList.size() && f < fact_vList.size() - 1);) {
		if (base_vList[b] < fact_vList[f]) { // f must always be behind b to factor correctly
			b++;
			continue;
		}
		if (base_vList[b] > fact_vList[f + 1]) { // Index will never throw exceptions due to conditions
			f++;
			continue;
		}
		base_vList[b] = fptr(base_vList[b], fact_vList[f]);


		b++; // If factoring successful, we move b forward
	}

	setValueList(base_vList);
}

double TimingPointList::length(int index) const
{
	if (index >= size() - 1 || index < 0) {
		std::cout << "length() function fail.";
		return 0;
	}

	auto offsetL = offsetList();
	return offsetL[index + 1] - offsetL[index];
}
