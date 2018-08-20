#include "stdafx.h"
#include "HitObject.h"



inline int HitObject::toColumn(const int & xAxis, const int & keys) {
	return round((xAxis / 256.0 * keys - 1.0) / 2.0) + 1;
}

inline int HitObject::toXAxis(const int & column, const int & keys) {
	return round((column - 0.5) * 512.0 / keys);
}

int HitObject::column() const
{
	return m_column;
}

void HitObject::setColumn(const int &column)
{
	m_column = column;
}

SampleSet HitObject::hitsound() const
{
	return m_hitsound;
}

void HitObject::setHitsound(const SampleSet &hitsound)
{
	m_hitsound = hitsound;
}

SampleSet HitObject::sample() const
{
	return m_sample;
}

void HitObject::setSample(const SampleSet &sample)
{
	m_sample = sample;
}

SampleSet HitObject::addition() const
{
	return m_addition;
}

void HitObject::setAddition(const SampleSet &addition)
{
	m_addition = addition;
}

int HitObject::custom() const
{
	return m_custom;
}

void HitObject::setCustom(const int &custom)
{
	m_custom = custom;
}

int HitObject::volume() const
{
	return m_volume;
}

void HitObject::setVolume(const int &volume)
{
	m_volume = volume;
}

std::string HitObject::hitsoundFile() const
{
	return m_hitsoundFile;
}

void HitObject::setHitsoundFile(const std::string &hitsoundFile)
{
	m_hitsoundFile = hitsoundFile;
}

std::shared_ptr<HitObject> HitObject::fromString(std::string string,
	const int &keys) {

	boost::erase_all(string, " ");

	using namespace boost::spirit;


	int		xAxis;
	int		yAxis;
	double	offset;
	int		noteType;
	int		hitsound;
	int		sample;
	int		addition;
	int		custom;
	int		volume;
	std::string hitsoundFile;

	double offsetEnd;

	bool isLongNote = std::count(string.begin(), string.end(), ':') == 5;

	auto it = string.begin();

	bool parse_flag = true;

	// Breaks down the HitObject Format Pt.1
	parse_flag = qi::parse(it, string.end(),
		qi::int_ >> char(',') >>		// xAxis
		qi::int_ >> char(',') >>		// yAxis
		qi::double_ >> char(',') >>		// offset
		qi::int_ >> char(',') >>		// noteType
		qi::int_ >> char(',')			// hitsound
		, xAxis, yAxis, offset, noteType, hitsound);
	
	// If it's a Long Note, there should be an additional parameter here
	if (isLongNote) {
		parse_flag &= qi::parse(it, string.end(),
			qi::double_ >> char(':'),
			offsetEnd);
	}

	// Breaks down the HitObject Format Pt.2
	parse_flag &= qi::parse(it, string.end(),
		qi::int_ >> char(':') >>		// sample
		qi::int_ >> char(':') >>		// addition
		qi::int_ >> char(':') >>		// custom
		qi::int_ >> char(':') >>		// volume
		*qi::char_,						// hitsoundFile
		sample, addition, custom, volume, hitsoundFile);

	if (!parse_flag) {
		throw OsuException(OsuException::ID::PARSE_FAIL);
	}

	// Create Objects according to Criteria
	if (isLongNote) {
		return std::make_shared<LongNote>(
			LongNote(toColumn(xAxis, keys),
				offset,
				static_cast<SampleSet>(hitsound),
				static_cast<SampleSet>(sample),
				static_cast<SampleSet>(addition),
				custom,
				volume,
				hitsoundFile,
				offsetEnd));
	}
	else {
		return std::make_shared<NormalNote>(
			NormalNote(toColumn(xAxis, keys),
				offset,
				static_cast<SampleSet>(hitsound),
				static_cast<SampleSet>(sample),
				static_cast<SampleSet>(addition),
				custom,
				volume,
				hitsoundFile));
	}
}

void LongNote::debugInfo() const
{
	std::cout << "[ Long Note Info ]" << std::endl
		      << "m_column       : " << m_column << std::endl
		      << "m_offset       : " << m_offset << std::endl
		      << "m_hitsound     : " << static_cast<int>(m_hitsound) << std::endl
		      << "m_sample       : " << static_cast<int>(m_sample) << std::endl
		      << "m_addition     : " << static_cast<int>(m_addition) << std::endl
		      << "m_custom       : " << m_custom << std::endl
		      << "m_volume       : " << m_volume << std::endl
		      << "m_hitsoundFile : " << m_hitsoundFile << std::endl
		      << "m_offsetEnd    : " << m_offsetEnd;
}

std::string LongNote::toString(const int &keys) const {

	// 64,192,20725,128,0,21734:0:0:0:0:

	using namespace boost;

	std::string output = "";

	output += lexical_cast<std::string>(toXAxis(m_column, keys))
		+ "," + "192"
		+ "," + lexical_cast<std::string>(m_offset)
		+ "," + "128"
		+ "," + lexical_cast<std::string>(static_cast<int>(m_hitsound))
		+ "," + lexical_cast<std::string>(m_offsetEnd)
		+ ":" + lexical_cast<std::string>(static_cast<int>(m_sample))
		+ ":" + lexical_cast<std::string>(static_cast<int>(m_addition))
		+ ":" + lexical_cast<std::string>(m_custom)
		+ ":" + lexical_cast<std::string>(m_volume)
		+ ":" + m_hitsoundFile;

	return output;
}

double LongNote::offsetEnd() const
{
	return m_offsetEnd;
}

void LongNote::setOffsetEnd(const double &offsetEnd)
{
	m_offsetEnd = offsetEnd;
}

void NormalNote::debugInfo() const
{
	std::cout << "[ Normal Note Info ]" << std::endl
		      << "m_column       : " << m_column << std::endl
		      << "m_offset       : " << m_offset << std::endl
		      << "m_hitsound     : " << static_cast<int>(m_hitsound) << std::endl
		      << "m_sample       : " << static_cast<int>(m_sample) << std::endl
		      << "m_addition     : " << static_cast<int>(m_addition) << std::endl
		      << "m_custom       : " << m_custom << std::endl
		      << "m_volume       : " << m_volume << std::endl
		      << "m_hitsoundFile : " << m_hitsoundFile;
}

std::string NormalNote::toString(const int &keys) const {

	// 448,192,18609,1,4,0:0:0:0:

	using namespace boost;

	std::string output = "";

	output += lexical_cast<std::string>(toXAxis(m_column, keys))
		+ "," + "192"
		+ "," + lexical_cast<std::string>(m_offset)
		+ "," + "1"
		+ "," + lexical_cast<std::string>(static_cast<int>(m_hitsound))
		+ "," + lexical_cast<std::string>(static_cast<int>(m_sample))
		+ ":" + lexical_cast<std::string>(static_cast<int>(m_addition))
		+ ":" + lexical_cast<std::string>(m_custom)
		+ ":" + lexical_cast<std::string>(m_volume)
		+ ":" + m_hitsoundFile;

	return output;
}