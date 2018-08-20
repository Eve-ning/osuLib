#pragma once
#include "timingpoint.h"
#include "osuobjectlist.h"

class TimingPointList final : public OsuObjectList<TimingPoint>
{
public:
	// Load from String
	TimingPointList(std::vector<std::string> stringList);
	TimingPointList(std::vector<std::shared_ptr<TimingPoint>> value) : OsuObjectList<TimingPoint>(value) {}
	TimingPointList(const TimingPointList& value) : OsuObjectList<TimingPoint>(value.m_value) {}
	TimingPointList& operator =(const TimingPointList &value) {
		m_value = std::move(value.m_value);
		return *this;
	}
	TimingPointList& operator =(TimingPointList &&value) & {
		m_value = std::move(value.m_value);
		return *this;
	}
	TimingPointList();

	std::shared_ptr<TimingPointList> clone() const { return std::static_pointer_cast<TimingPointList>(doClone()); }

	~TimingPointList() {}

	using OsuObjectList<TimingPoint>::append;
	void append(std::shared_ptr<TimingPointList> TPList) { append(*TPList); }
	void append(TimingPointList &TPList) { for (auto TP : TPList) { m_value.push_back(TP); } }

	void operator +=(std::shared_ptr<TimingPoint> &TP) { append(TP); }
	void operator +=(TimingPointList TPList) { append(TPList); }

	std::vector<std::shared_ptr<TimingPoint>> value() const;
	void setValue(const std::vector<std::shared_ptr<TimingPoint>> &value);
	double distance() const;
	double average() const;

	using OsuObjectList::length;
	double length(int index) const;

	std::vector<double> valueList() const;
	std::vector<double> codeList() const;
	std::vector<int> metronomeList() const;
	std::vector<SampleSet> sampleList() const;
	std::vector<int> sampleSetIndexList() const;
	std::vector<int> volumeList() const;
	std::vector<bool> isKiaiList() const;

	void setValueList(const std::vector<double>    &value);
	void setCodeList(const std::vector<double>    &value);
	void setMetronomeList(const std::vector<int>       &value);
	void setSampleList(const std::vector<SampleSet> &value);
	void setSampleSetIndexList(const std::vector<int>       &value);
	void setVolumeList(const std::vector<int>       &value);
	void setIsKiaiList(const std::vector<bool>      &value);

	std::vector<std::string> toStringList();

	TimingPointList toSliderVelocity() const;
	TimingPointList toBPM() const;

	TimingPointList normalize(const double &referenceBPM) const;

	// Takes one other TimingPointList and "superimposes" together (cross mutliply)
	void superimpose(const TimingPointList &factor,
		double(*fptr)(double, double));


protected:

private:
	std::shared_ptr<OsuObjectList> doClone() const override {
		std::vector<std::shared_ptr<TimingPoint>> output;

		std::for_each(m_value.begin(), m_value.end(), [&](const std::shared_ptr<TimingPoint> &value) {
			output.push_back(value->clone());
		});

		return std::make_shared<TimingPointList>(output);
	}

};
