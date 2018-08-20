#include "stdafx.h"
#include "timingpoint.h"

int TimingPoint::metronome() const
{
	return m_metronome;
}

void TimingPoint::setMetronome(const int &metronome)
{
	m_metronome = metronome;
}

SampleSet TimingPoint::sample() const
{
	return m_sample;
}

void TimingPoint::setSample(const SampleSet &sample)
{
	m_sample = sample;
}

int TimingPoint::sampleSetIndex() const
{
	return m_sampleSetIndex;
}

void TimingPoint::setSampleSetIndex(const int &sampleSetIndex)
{
	m_sampleSetIndex = sampleSetIndex;
}

int TimingPoint::volume() const
{
	return m_volume;
}

void TimingPoint::setVolume(const int &volume)
{
	m_volume = volume;
}

bool TimingPoint::isKiai() const
{
	return m_isKiai;
}

void TimingPoint::setIsKiai(const bool &isKiai)
{
	m_isKiai = isKiai;
}

std::shared_ptr<TimingPoint> TimingPoint::fromString(std::string string)
{
	//QTextStream ts(&string);

	//char delim;

	using namespace boost::spirit;

	boost::erase_all(string, " ");

	auto it = string.begin();

	double  offset;
	double  code;
	int		metronome;
	int		sample;
	int		sampleSetIndex;
	int		volume;
	int		isBPM;
	int		isKiai;

	// Breaks down into TimingPoint parameters
	qi::parse(it, string.end(),
		qi::double_ >> char(',') >>
		qi::double_ >> char(',') >>
		qi::int_ >> char(',') >>
		qi::int_ >> char(',') >>
		qi::int_ >> char(',') >>
		qi::int_ >> char(',') >>
		qi::int_ >> char(',') >>
		qi::int_,
		offset, code, metronome, sample, sampleSetIndex, volume, isBPM, isKiai);

	// With respect to the isBPM value, we assign different values
	if (isBPM) {
		return std::make_shared<BPM>(
			BPM(offset,
				BPM::toValue(code),
				metronome,
				static_cast<SampleSet>(sample),
				sampleSetIndex,
				volume,
				isKiai));
	}
	else {
		return std::make_shared<SliderVelocity>(
			SliderVelocity(offset,
				SliderVelocity::toValue(code),
				metronome,
				static_cast<SampleSet>(sample),
				sampleSetIndex,
				volume,
				isKiai));
	}
}



void SliderVelocity::debugInfo() const
{
	using namespace std;

	std::cout << "[ Slider Velocity Info ]" << endl
		<< "m_offset        : " << m_offset << endl
		<< "m_value         : " << m_value << endl
		<< "m_metronome     : " << m_metronome << endl
		<< "m_sample        : " << static_cast<int>(m_sample) << endl
		<< "m_sampleSetIndex: " << m_sampleSetIndex << endl
		<< "m_volume        : " << m_volume << endl
		<< "isKiai          : " << m_isKiai;
}

std::string SliderVelocity::toString() const
{
	// 18610,-200,4,1,0,41,0,0

	using namespace boost;

	std::string output = "";

	output +=   lexical_cast<std::string>(m_offset)
		+ "," + lexical_cast<std::string>(code())
		+ "," + lexical_cast<std::string>(m_metronome)
		+ "," + lexical_cast<std::string>(static_cast<int>(m_sample))
		+ "," + lexical_cast<std::string>(m_sampleSetIndex)
		+ "," + lexical_cast<std::string>(m_volume)
		+ "," + "0"				 
		+ "," + lexical_cast<std::string>(m_isKiai);

	return output;
}

void BPM::debugInfo() const
{
	using namespace std;

	std::cout << "[ BPM Info ]" << endl
		<< "m_offset        : " << m_offset << endl
		<< "m_value(temp)   : " << m_value << endl
		<< "m_metronome     : " << m_metronome << endl
		<< "m_sample        : " << static_cast<int>(m_sample) << endl
		<< "m_sampleSetIndex: " << m_sampleSetIndex << endl
		<< "m_volume        : " << m_volume << endl
		<< "isKiai          : " << m_isKiai;
}

std::string BPM::toString() const
{
	// 18610,769.230769230769,4,1,0,41,1,0

	using namespace boost;

	std::string output = "";

	output +=   lexical_cast<std::string>(m_offset)
		+ "," + lexical_cast<std::string>(code())
		+ "," + lexical_cast<std::string>(m_metronome)
		+ "," + lexical_cast<std::string>(static_cast<int>(m_sample))
		+ "," + lexical_cast<std::string>(m_sampleSetIndex)
		+ "," + lexical_cast<std::string>(m_volume)
		+ "," + "1"
		+ "," + lexical_cast<std::string>(m_isKiai);

	return output;
}

