#include "stdafx.h"
#include "HitObjectList.h"

HitObjectList::HitObjectList()
{
}

HitObjectList::HitObjectList(std::vector<std::string> stringList, const int &keys)
{
	std::vector<std::shared_ptr<HitObject>> input;
	for (auto string : stringList) {
		input.push_back(HitObject::fromString(string, keys));
	}
	setValue(input);
}

HitObjectList::HitObjectList(std::string EHO)
{
	boost::erase_all(EHO, " ");

	using namespace boost::spirit;

	std::string::iterator it = EHO.begin();

	while (*it != '(' && it != EHO.end()) {
		++it;
	}
	++it; // We need to skip the first open bracket

	double offset = 0;
	double column = 0;

	bool parse_flag = true;

	// Breaks down into HitObject
	while (it != EHO.end() && parse_flag)
	{
		parse_flag = qi::parse(it, EHO.end(), qi::int_ >> char('|') >> qi::int_ >> char(','), offset, column);
		std::shared_ptr<HitObject> tempUPtr = std::make_shared<NormalNote>(NormalNote(column, offset));
		m_value.push_back(std::move(tempUPtr));
	}

	if (*it != ')') {
		std::cout << std::endl;
		std::cout << *it << std::endl;
		std::cout << std::endl;
	}
	else {
		std::cout << std::endl;
		std::cout << "OKAY" << std::endl;
		std::cout << std::endl;
	}
}

std::vector<std::shared_ptr<HitObject> > HitObjectList::value() const
{
	return m_value;
}

void HitObjectList::setValue(const std::vector<std::shared_ptr<HitObject> > &value)
{
	m_value = value;
}

//void HitObjectList::sort(bool isAscending)
//{
//    std::sort(m_value.begin(), m_value.end(),
//              [isAscending](std::shared_ptr<HitObject> a,
//                            std::shared_ptr<HitObject> b){
//        if (isAscending) {
//            return a->offset() < b->offset();
//        } else {
//            return a->offset() > b->offset();
//        }
//    });
//}


std::vector<int> HitObjectList::columnList() const {
	std::vector<int> output = {};
	for (const auto &HO : m_value) { output.push_back(HO->column()); }
	return output;
}

//std::vector<double> HitObjectList::offsetList() const {
//    std::vector<double> output = {};
//    for (std::shared_ptr<HitObject> HO : m_value) { output.push_back(HO->offset()); }
//    return output;
//}

std::vector<SampleSet> HitObjectList::hitsoundList() const {
	std::vector<SampleSet> output = {};
	for (const auto &HO : m_value) { output.push_back(HO->hitsound()); }
	return output;
}

std::vector<SampleSet> HitObjectList::sampleList() const {
	std::vector<SampleSet> output = {};
	for (const auto &HO : m_value) { output.push_back(HO->sample()); }
	return output;
}

std::vector<SampleSet> HitObjectList::additionList() const {
	std::vector<SampleSet> output = {};
	for (const auto &HO : m_value) { output.push_back(HO->addition()); }
	return output;
}

std::vector<int> HitObjectList::customList() const {
	std::vector<int> output = {};
	for (const auto &HO : m_value) { output.push_back(HO->custom()); }
	return output;
}

std::vector<int> HitObjectList::volumeList() const {
	std::vector<int> output = {};
	for (const auto &HO : m_value) { output.push_back(HO->volume()); }
	return output;
}

std::vector<std::string> HitObjectList::hitsoundFileList() const {
	std::vector<std::string> output = {};
	for (const auto &HO : m_value) { output.push_back(HO->hitsoundFile()); }
	return output;
}

void HitObjectList::setColumnList(const std::vector<int> &value) {
	if (!sameSize(value)) {
		return;
	}
	for (int i = 0; i < size(); ++i) {
		m_value[i]->setColumn(value[i]);
	}
}
//void HitObjectList::setOffsetList(const std::vector<double> &value) {
//    if (!sameSize(value)) {
//        return;
//    }
//    for (int i = 0; i < size(); ++i) {
//        m_value[i]->setOffset(value[i]);
//    }
//}
void HitObjectList::setHitsoundList(const std::vector<SampleSet> &value) {
	if (!sameSize(value)) {
		return;
	}
	for (int i = 0; i < size(); ++i) {
		m_value[i]->setHitsound(value[i]);
	}
}
void HitObjectList::setSampleList(const std::vector<SampleSet> &value) {
	if (!sameSize(value)) {
		return;
	}
	for (int i = 0; i < size(); ++i) {
		m_value[i]->setSample(value[i]);
	}
}
void HitObjectList::setAdditionList(const std::vector<SampleSet> &value) {
	if (!sameSize(value)) {
		return;
	}
	for (int i = 0; i < size(); ++i) {
		m_value[i]->setAddition(value[i]);
	}
}
void HitObjectList::setCustomList(const std::vector<int> &value) {
	if (!sameSize(value)) {
		return;
	}
	for (int i = 0; i < size(); ++i) {
		m_value[i]->setCustom(value[i]);
	}
}
void HitObjectList::setVolumeList(const std::vector<int> &value) {
	if (!sameSize(value)) {
		return;
	}
	for (int i = 0; i < size(); ++i) {
		m_value[i]->setVolume(value[i]);
	}
}
void HitObjectList::setHitsoundFileList(const std::vector<std::string> &value) {
	if (!sameSize(value)) {
		return;
	}
	for (int i = 0; i < size(); ++i) {
		m_value[i]->setHitsoundFile(value[i]);
	}
}

std::vector<std::string> HitObjectList::toStringList(const int &keys)
{
	std::vector<std::string> output;

	for (auto &HO : m_value) {
		output.push_back(HO->toString(keys));
	}

	return output;
}