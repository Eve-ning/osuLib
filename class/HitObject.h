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
	// Keys is required to convert xAxis Values to column
	static std::shared_ptr<HitObject> allocate(const std::string &str, int keys);
	double offset() const { return m_offset; }
	virtual double column() const { return m_column; }
	int hitsound() const { return m_hitsound; }
	Osu::SAMPLESET sample() const { return m_sample; }
	Osu::SAMPLESET addition() const { return m_addition; }
	int custom() const { return m_custom; }
	int volume() const { return m_volume; }
	std::string hitsoundFile() const { return m_hitsoundFile; }
	int keys() const { return m_keys; }

	void setOffset(double offset) { m_offset = offset; }
	void setColumn(int column) { m_column = column; }
	void setHitsound(int hitsound) { m_hitsound = hitsound; }
	void setSample(Osu::SAMPLESET sample) { m_sample = sample; }
	void setAddition(Osu::SAMPLESET addition) { m_addition = addition; }
	void setCustom(int custom) { m_custom = custom; }
	void setVolume(int volume) { m_volume = volume; }
	void setHitsoundFile(std::string hitsoundFile) { m_hitsoundFile = hitsoundFile; }
	void setKeys(int keys) { m_keys = keys; }

	// Changes the column of the object via osu! .osu code
	virtual void setCode(double code) {
		m_column = convertToColumn(code, m_keys);
	}

	// Changes the column of the object via osu! .osu code relative to the keys
	// Does not affect the keys value
	virtual void setCode(double code, int keys) {
		m_column = convertToColumn(code, keys);
	}

	// Gets the code as formatted in .osu
	virtual double code() const {
		return convertToCode(m_column, m_keys);
	}

	// Gets the code as formatted in .osu relative to the keys
	// Does not affect the keys value
	virtual double code(int keys) const {
		return convertToCode(m_column, keys);
	}

	// Return osu! formatted string
	virtual std::string str() const;

protected:
	HitObject(double offset,
		int column,
		int keys,
		int hitsound = 0,
		Osu::SAMPLESET sample = Osu::SAMPLESET::AUTO,
		Osu::SAMPLESET addition = Osu::SAMPLESET::AUTO,
		int custom = 0,
		int volume = 0,
		std::string hitsoundFile = "") :
		m_offset(offset), m_column(column), m_keys(keys), m_hitsound(hitsound), m_sample(sample), m_addition(addition), m_custom(custom), m_volume(volume), m_hitsoundFile(hitsoundFile) {}

	// Column returned starts from 1
	static int convertToColumn(const double &code, const int &keys) {
		return round((code / 256.0 * keys - 1.0) / 2.0) + 1;
	}

	// Column input starts from 1
	static double convertToCode(const int &column, const int &keys) {
		return round((column - 0.5) * 512.0 / keys);
	}

	// Specifically for that number
	// x,x,x,1  ,x,x:x:x:x:
	// x,x,x,128,x,x:x:x:x:x:
	virtual int ID() const = 0;

	// This extension is required in str() specifically for Long Note just for Offset End Parameter (E)
	// x,x,x,x,x,x:x:x:x:
	// x,x,x,x,x,E:x:x:x:x:
	virtual double EXTENSION() const = 0;

	double m_offset;
	int m_column;
	int m_hitsound;
	Osu::SAMPLESET m_sample;
	Osu::SAMPLESET m_addition;
	int m_custom;
	int m_volume;
	std::string m_hitsoundFile;
	
	int m_keys;
};

class NormalNote : public HitObject {

public:
	// Creates a NormalNote Object via parameters
	NormalNote(double offset,
		int column,
		int keys,
		int hitsound = 0,
		Osu::SAMPLESET sample = Osu::SAMPLESET::AUTO,
		Osu::SAMPLESET addition = Osu::SAMPLESET::AUTO,
		int custom = 0,
		int volume = 0,
		std::string hitsoundFile = "") : HitObject(offset, column, keys, hitsound, sample, addition, custom, volume, hitsoundFile)
	{

	}

private:
	int ID() const {
		return 1;
	}
	double EXTENSION() const {
		return -1;
	}
};

class LongNote : public HitObject {

public:
	// Creates a LongNote Object via parameters
	LongNote(double offset,
		double offsetEnd,
		int column,
		int keys,
		int hitsound = 0,
		Osu::SAMPLESET sample = Osu::SAMPLESET::AUTO,
		Osu::SAMPLESET addition = Osu::SAMPLESET::AUTO,
		int custom = 0,
		int volume = 0,
		std::string hitsoundFile = "") : HitObject(offset, column, keys, hitsound, sample, addition, custom, volume, hitsoundFile), m_offsetEnd(offsetEnd)
	{

	}

	double offsetEnd() const { return m_offsetEnd; }
	void setOffsetEnd(double offsetEnd) { m_offsetEnd = offsetEnd; }

private:
	double m_offsetEnd;
	int ID() const {
		return 128;
	}
	double EXTENSION() const {
		return m_offsetEnd;
	}
};
