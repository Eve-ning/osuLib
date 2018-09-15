#include "../pch.h"
#include "pch.h"
#include "TimingPoint.h"

std::shared_ptr<TimingPoint> TimingPoint::allocate(const std::string & str)
{
	std::vector<std::string> vectorSplit;
	boost::split(vectorSplit, str, boost::is_any_of(",*"));

	// If "1", means it's BPM,
	//    "0", means it's SliderVelocity
	if (vectorSplit[6] == "0") {
		return std::make_shared<SliderVelocity>(
			SliderVelocity(
				std::stod(vectorSplit[0]),
				SliderVelocity::convert(std::stod(vectorSplit[1])),
				std::stoi(vectorSplit[2]),
				(Osu::SAMPLESET) std::stoi(vectorSplit[3]),
				std::stoi(vectorSplit[4]),
				std::stoi(vectorSplit[5]),
				(bool) std::stoi(vectorSplit[7])));
	}
	else if (vectorSplit[6] == "1") {
		return std::make_shared<BPM>(
			BPM(
				std::stod(vectorSplit[0]),
				BPM::convert(std::stod(vectorSplit[1])),
				std::stoi(vectorSplit[2]),
				(Osu::SAMPLESET) std::stoi(vectorSplit[3]),
				std::stoi(vectorSplit[4]),
				std::stoi(vectorSplit[5]),
				(bool)std::stoi(vectorSplit[7])));
	}
	else {
		throw new std::exception(std::string("TimingPoint allocation value invalid: " + vectorSplit[6]).c_str());
	}
}

// Return osu! formatted string
inline std::string TimingPoint::str() const {
	return
		boost::lexical_cast<std::string>(m_offset) + "," +
		boost::lexical_cast<std::string>(code()) + "," +
		boost::lexical_cast<std::string>(m_metrenome) + "," +
		boost::lexical_cast<std::string>((int)m_sample) + "," +
		boost::lexical_cast<std::string>(m_sampleSetIndex) + "," +
		boost::lexical_cast<std::string>(m_volume) + "," +
		boost::lexical_cast<std::string>(ID()) + "," +
		boost::lexical_cast<std::string>((int)m_kiai);
}

