#pragma once
#include "../OsuObject.h"

class HitObject : public OsuObject
{
public:

	virtual ~HitObject() {
	}

	virtual std::shared_ptr<HitObject> clone() = 0;

	int column() const;
	void setColumn(const int &column);

	SampleSet hitsound() const;
	void setHitsound(const SampleSet &hitsound);

	SampleSet sample() const;
	void setSample(const SampleSet &sample);

	SampleSet addition() const;
	void setAddition(const SampleSet &addition);

	int custom() const;
	void setCustom(const int &custom);

	int volume() const;
	void setVolume(const int &volume);

	std::string hitsoundFile() const;
	void setHitsoundFile(const std::string &hitsoundFile);

	virtual void debugInfo() const = 0;
	virtual std::string toString(const int &keys) const = 0;

	static std::shared_ptr<HitObject> fromString(std::string string, const int &keys);

	static int toColumn(const int &xAxis, const int &keys);
	static int toXAxis(const int &column, const int &keys);

protected:

	BoundedInt    m_column = BoundedInt(1, 1, 18);
	SampleSet     m_hitsound = SampleSet::AUTO;
	SampleSet     m_sample = SampleSet::AUTO;
	SampleSet     m_addition = SampleSet::AUTO;
	BoundedInt    m_custom = BoundedInt(0, 0, 99);
	BoundedInt    m_volume = BoundedInt(10, 0, 100);
	std::string   m_hitsoundFile = "";

};

struct NormalNote final : public HitObject
{
public:
	NormalNote() {}
	NormalNote(const double &offset) {
		m_offset = offset;
	}
	NormalNote(const int &column,
		const double &offset) {
		m_column = column;
		m_offset = offset;
	}
	NormalNote(const int &column,
		const double &offset,
		const SampleSet &hitsound,
		const SampleSet &sample,
		const SampleSet &addition,
		const int &custom,
		const int &volume,
		const std::string &hitsoundFile) {
		m_column = column;
		m_offset = offset;
		m_hitsound = hitsound;
		m_sample = sample;
		m_addition = addition;
		m_custom = custom;
		m_volume = volume;
		m_hitsoundFile = hitsoundFile;
	}

	std::shared_ptr<HitObject> clone() override {
		return std::make_shared<NormalNote>(*this);
	}

	void debugInfo() const override;
	std::string toString(const int &keys) const override;
};

struct LongNote final : public HitObject
{
public:
	LongNote() {}
	LongNote(const double &offset,
		const double &offsetEnd) {
		m_offset = offset;
		m_offsetEnd = offsetEnd;
	}
	LongNote(const int &column,
		const double &offset,
		const double &offsetEnd) {
		m_column = column;
		m_offset = offset;
		m_offsetEnd = offsetEnd;
	}
	LongNote(const int &column,
		const double &offset,
		const SampleSet &hitsound,
		const SampleSet &sample,
		const SampleSet &addition,
		const int &custom,
		const int &volume,
		const std::string &hitsoundFile,
		const double &offsetEnd) {
		m_column = column;
		m_offset = offset;
		m_hitsound = hitsound;
		m_sample = sample;
		m_addition = addition;
		m_custom = custom;
		m_volume = volume;
		m_hitsoundFile = hitsoundFile;
		m_offsetEnd = offsetEnd;
	}

	std::shared_ptr<HitObject> clone() {
		return std::make_shared<LongNote>(*this);
	}

	void debugInfo() const override;
	std::string toString(const int &keys) const override;

	double offsetEnd() const;
	void setOffsetEnd(const double &offsetEnd);

private:

	BoundedDouble m_offsetEnd = BoundedDouble(1, 0);
};