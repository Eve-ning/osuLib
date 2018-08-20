#pragma once
#include "hitobject.h"
#include "../OsuObjectList.h"

class HitObjectList final : public OsuObjectList<HitObject>
{
public:
	HitObjectList();
	HitObjectList(std::string EHO);

	// Load from StringList
	HitObjectList(std::vector<std::string> stringList, const int &keys);
	HitObjectList(std::vector<std::shared_ptr<HitObject>> value) : OsuObjectList<HitObject>(value) {}
	HitObjectList(const HitObjectList& value) : OsuObjectList<HitObject>(value.m_value) {}
	HitObjectList(std::shared_ptr<OsuObjectList<HitObject>> value) : OsuObjectList<HitObject>(value->value()) {}
	HitObjectList& operator =(const HitObjectList &value) {
		m_value = std::move(value.m_value);
		return *this;
	}
	HitObjectList& operator =(HitObjectList &&value) & {
		m_value = std::move(value.m_value);
		return *this;
	}

	~HitObjectList() {}

	std::shared_ptr<HitObjectList> clone() const { return std::static_pointer_cast<HitObjectList>(doClone()); }

	bool operator ==(const HitObjectList &HOList) { return m_value == HOList.m_value; }
	bool operator !=(const HitObjectList &HOList) { return m_value != HOList.m_value; }

	//void operator +=(std::shared_ptr<HitObject> HO) { append(HO); }
	//HitObjectList operator +(std::shared_ptr<HitObject> HO) { append(HO); return *this; }

	using OsuObjectList<HitObject>::append;
	void append(std::shared_ptr<HitObjectList> HOList) { append(*HOList); }
	void operator +=(HitObjectList HOList) { append(HOList); }

	void append(HitObjectList &HOList) { for (auto HO : HOList) { m_value.push_back(HO); } }

	std::vector<std::shared_ptr<HitObject>> value() const;
	void setValue(const std::vector<std::shared_ptr<HitObject>> &value);

	std::vector<int> columnList() const;
	std::vector<SampleSet> hitsoundList() const;
	std::vector<SampleSet> sampleList() const;
	std::vector<SampleSet> additionList() const;
	std::vector<int> customList() const;
	std::vector<int> volumeList() const;
	std::vector<std::string> hitsoundFileList() const;

	void setColumnList(const std::vector<int>       &value);
	void setHitsoundList(const std::vector<SampleSet> &value);
	void setSampleList(const std::vector<SampleSet> &value);
	void setAdditionList(const std::vector<SampleSet> &value);
	void setCustomList(const std::vector<int>       &value);
	void setVolumeList(const std::vector<int>       &value);
	void setHitsoundFileList(const std::vector<std::string>   &value);

	std::vector<std::string> toStringList(const int &keys);

protected:

private:
	std::shared_ptr<OsuObjectList<HitObject>> doClone() const override {
		std::vector<std::shared_ptr<HitObject>> output;
		std::for_each(m_value.begin(), m_value.end(), [&](const std::shared_ptr<HitObject> &value) {
			output.push_back(value->clone());
		});
		return std::make_shared<HitObjectList>(m_value);
	}

};