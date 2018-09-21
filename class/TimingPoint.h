#pragma once
#include "../constant/Constants.h"

// We will allow TimingPoint creation in 2 ways:
// Via static TimingPoint::allocate(std::string) as osu! generated code -> Outputs s_ptr<TimingPoint>
// Via SliderVelocity/BPM(parameters ...) as actual values

class TimingPoint : std::enable_shared_from_this<TimingPoint>
{
public:
	// Create a TimingPoint by allocate, it will automatically return a shared_ptr<TimingPoint>
	TimingPoint() = delete;

	// Based on the string provided, we can determine if it's BPM or SliderVelocity, then we return a s_ptr
	static std::shared_ptr<TimingPoint> allocate(const std::string &str);

	double offset() const			{ return m_offset; }
	virtual double value() const	{ return m_value; }
	int metrenome() const			{ return m_metrenome; }
	Osu::SAMPLESET sample() const	{ return m_sample; }
	int sampleSetIndex() const		{ return m_sampleSetIndex; }
	bool kiai() const				{ return m_kiai; }

	void setOffset		  (double offset)		 { m_offset			= offset;		  }	
	void setValue	      (double value)         { m_value          = value;		  }
	void setMetrenome	  (int metrenome)		 { m_metrenome		= metrenome;	  }
	void setSample		  (Osu::SAMPLESET sample){ m_sample			= sample;		  }
	void setSampleSetIndex(int sampleSetIndex)	 { m_sampleSetIndex	= sampleSetIndex; }
	void setKiai		  (bool kiai)			 { m_kiai			= kiai;			  }

	// Changes the value of the object via osu! .osu code
	virtual void setCode(double code) {
		m_value = CONVERSION_FACTOR() / code;
	}

	// Gets the code as formatted in .osu
	virtual double code() const {
		return CONVERSION_FACTOR() / m_value;
	}

	// Return osu! formatted string
	virtual std::string str() const;

protected:
	TimingPoint(double offset,
		double value,
		int metrenome = 4,
		Osu::SAMPLESET sample = Osu::SAMPLESET::AUTO,
		int volume = 10,
		int sampleSetIndex = 0,
		bool kiai = 0) :
		m_offset(offset), m_value(value), m_metrenome(metrenome), m_sample(sample), m_volume(volume), m_sampleSetIndex(sampleSetIndex), m_kiai(kiai) {}

	// Gets the conversion factor to convert from code to value vice versa
	virtual double CONVERSION_FACTOR() const = 0;

	// Gets the ID to be used in string formatting
	virtual int ID() const = 0;

	double m_offset;
	double m_value;
	int m_metrenome;
	int m_volume;
	Osu::SAMPLESET m_sample;
	int m_sampleSetIndex;
	bool m_kiai;
};

class SliderVelocity : public TimingPoint {

public:
	// Creates a SliderVelocity Object via parameters
	SliderVelocity(double offset,
		double value,
		int metrenome = 4,
		Osu::SAMPLESET sample = Osu::SAMPLESET::AUTO,
		int volume = 10,
		int sampleSetIndex = 0,
		bool kiai = 0) : TimingPoint(offset, value, metrenome, sample, volume, sampleSetIndex, kiai)
	{

	}

	// Converts value to code, vice versa
	static double convert(double input) {
		return -100 / input;
	}


private:
	// Gets the conversion factor to convert from code to value vice versa
	virtual double CONVERSION_FACTOR() const {
		return -100;
	}

	// Gets the ID to be used in string formatting
	virtual int ID() const {
		return 0;
	}
};

class BPM : public TimingPoint {

public:
	// Creates a BPM Object via parameters
	BPM(double offset,
		double value,
		int metrenome = 4,
		Osu::SAMPLESET sample = Osu::SAMPLESET::AUTO,
		int volume = 10,
		int sampleSetIndex = 0,
		bool kiai = 0) : TimingPoint(offset, value, metrenome, sample, volume, sampleSetIndex, kiai)
	{

	}

	// Converts value to code, vice versa
	static double convert(double input) {
		return 60000 / input;
	}

private:
	// Gets the conversion factor to convert from code to value vice versa
	virtual double CONVERSION_FACTOR() const {
		return 60000;
	}

	// Gets the ID to be used in string formatting
	virtual int ID() const {
		return 1;
	}
};

typedef std::vector<SliderVelocity> SliderVelocityList;
typedef std::vector<BPM> BPMList;
