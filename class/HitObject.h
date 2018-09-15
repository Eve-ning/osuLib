#pragma once

// We will allow HitObject creation in 2 ways:
// Via static HitObject::allocate(std::string) as osu! generated code -> Outputs s_ptr<HitObject>
// Via NormalNote/LongNote(parameters ...) as actual columns

class HitObject
{
public:
	// Create a HitObject by allocate, it will automatically return a shared_ptr<HitObject>
	HitObject() = delete;

	// Based on the string provided, we can determine if it's LongNote or NormalNote, then we return a s_ptrs
	static std::shared_ptr<HitObject> allocate(const std::string &str);
	double offset() const { return m_offset; }
	virtual double column() const { return m_column; }
	Osu::SAMPLESET hitsound() const { return m_hitsound; }
	Osu::SAMPLESET sample() const { return m_sample; }
	Osu::SAMPLESET addition() const { return m_addition; }
	int custom() const { return m_custom; }
	int volume() const { return m_volume; }
	std::string hitsoundFile() const { return m_hitsoundFile; }

	void setOffset(double offset) { m_offset = offset; }
	void setColumn(double column) { m_column = column; }
	void setHitsound(Osu::SAMPLESET hitsound) { m_hitsound = hitsound; }
	void setSample(Osu::SAMPLESET sample) { m_sample = sample; }
	void setAddition(Osu::SAMPLESET addition) { m_addition = addition; }
	void setCustom(int custom) { m_custom = custom; }
	void setVolume(int volume) { m_volume = volume; }
	void setHitsoundFile(std::string hitsoundFile) { m_hitsoundFile = hitsoundFile; }

	// Return osu! formatted string
	virtual std::string str() const;

protected:
	HitObject(double offset,
		double column,
		Osu::SAMPLESET hitsound = Osu::SAMPLESET::AUTO,
		Osu::SAMPLESET sample = Osu::SAMPLESET::AUTO,
		Osu::SAMPLESET addition = Osu::SAMPLESET::AUTO,
		int custom = 0,
		int volume = 0,
		std::string hitsoundFile = "") :
		m_offset(offset), m_column(column), m_hitsound(hitsound), m_sample(sample), m_addition(addition), m_custom(custom), m_volume(volume), m_hitsoundFile(hitsoundFile) {}

	double m_offset;
	double m_column;
	Osu::SAMPLESET m_hitsound;
	Osu::SAMPLESET m_sample;
	Osu::SAMPLESET m_addition;
	int m_custom;
	int m_volume;
	std::string m_hitsoundFile;
};

class NormalNote : public HitObject {

public:
	// Creates a NormalNote Object via parameters
	NormalNote(double offset,
		double column,
		Osu::SAMPLESET hitsound = Osu::SAMPLESET::AUTO,
		Osu::SAMPLESET sample = Osu::SAMPLESET::AUTO,
		Osu::SAMPLESET addition = Osu::SAMPLESET::AUTO,
		int custom = 0,
		int volume = 0,
		std::string hitsoundFile = "") : HitObject(offset, column, hitsound, sample, addition, custom, volume, hitsoundFile)
	{

	}

private:

};

class LongNote : public HitObject {

public:
	// Creates a LongNote Object via parameters
	LongNote(double offset,
		double offsetEnd,
		double column,
		Osu::SAMPLESET hitsound = Osu::SAMPLESET::AUTO,
		Osu::SAMPLESET sample = Osu::SAMPLESET::AUTO,
		Osu::SAMPLESET addition = Osu::SAMPLESET::AUTO,
		int custom = 0,
		int volume = 0,
		std::string hitsoundFile = "") : HitObject(offset, column, hitsound, sample, addition, custom, volume, hitsoundFile), m_offsetEnd(offsetEnd)
	{

	}

private:
	double m_offsetEnd;
};
