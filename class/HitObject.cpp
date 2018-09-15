#include "../pch.h"
#include "pch.h"
#include "HitObject.h"

std::shared_ptr<HitObject> HitObject::allocate(const std::string & str, int keys)
{
	std::vector<std::string> vectorSplit_comma;
	std::vector<std::string> vectorSplit_colon;
	boost::split(vectorSplit_comma, str, boost::is_any_of(",*"));
	boost::split(vectorSplit_colon, vectorSplit_comma.back(), boost::is_any_of(":*"));

	// If 5, means it's NormalNote,
	//    6, means it's LongNote
	if (vectorSplit_colon.size() == 5) {
		return std::make_shared<NormalNote>(
			NormalNote(	
				std::stod(vectorSplit_comma[2]),
				HitObject::convertToColumn(std::stod(vectorSplit_comma[0]), keys),
				keys,
				std::stoi(vectorSplit_comma[4]),
				(Osu::SAMPLESET) std::stoi(vectorSplit_colon[0]),
				(Osu::SAMPLESET) std::stoi(vectorSplit_colon[1]),
				std::stoi(vectorSplit_colon[2]),
				std::stoi(vectorSplit_colon[3]),
				vectorSplit_colon[4]));
	}
	else if (vectorSplit_colon.size() == 6) {
		return std::make_shared<LongNote>(
			LongNote(
				std::stod(vectorSplit_comma[2]),
				std::stod(vectorSplit_colon[0]),
				HitObject::convertToColumn(std::stod(vectorSplit_comma[0]), keys),
				keys,
				std::stoi(vectorSplit_comma[4]),
				(Osu::SAMPLESET) std::stoi(vectorSplit_colon[1]),
				(Osu::SAMPLESET) std::stoi(vectorSplit_colon[2]),
				std::stoi(vectorSplit_colon[3]),
				std::stoi(vectorSplit_colon[4]),
				vectorSplit_colon[5]));
	}
	else {
		throw new std::exception(std::string("HitObject colon count invalid: " + str).c_str());
	}
}

// Return osu! formatted string
inline std::string HitObject::str() const
{
	return
		boost::lexical_cast<std::string>(code()) + ",192," +
		boost::lexical_cast<std::string>(m_offset) + "," +
		boost::lexical_cast<std::string>(ID()) + "," +
		boost::lexical_cast<std::string>(m_hitsound) + "," +

		// If the Extension is Positive (NormalNote will return -1), we add the extension, else we don't
		(EXTENSION() >= 0 ? boost::lexical_cast<std::string>(EXTENSION()) + ":" : "") +

		boost::lexical_cast<std::string>((int) m_sample) + ":" +
		boost::lexical_cast<std::string>((int) m_addition) + ":" +
		boost::lexical_cast<std::string>(m_custom) + ":" +
		boost::lexical_cast<std::string>(m_volume) + ":" +
		m_hitsoundFile;
}
