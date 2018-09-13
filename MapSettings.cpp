#include "pch.h"
#include "MapSettings.h"

std::vector<std::string> MapSettings::m_parNameList = {
	"AudioLeadIn",
	"PreviewTime",
	"Countdown",
	"SampleSet",
	"StackLeniency",
	"Mode",
	"LetterboxInBreaks",
	"SpecialStyle",
	"WidescreenStoryboard",
	"Bookmarks",
	"DistanceSpacing",
	"BeatDivisor",
	"GridSize",
	"TimelineZoom",
	"Title",
	"TitleUnicode",
	"Artist",
	"ArtistUnicode",
	"Creator",
	"Version",
	"Source",
	"Tags",
	"BeatmapID",
	"BeatmapSetID",
	"HPDrainRate",
	"CircleSize",
	"OverallDifficulty",
	"ApproachRate",
	"SliderMultiplier",
	"SliderTickRate"
};

MapSettings::MapSettings(const std::vector<std::string> &vec)
{
	auto split = splitValues(vec, ':');
	assignValues(std::get<0>(split), std::get<1>(split));

}

MapSettings::~MapSettings()
{
}

std::tuple<std::vector<std::string>, std::vector<std::string>> MapSettings::splitValues(const std::vector<std::string>& vec, char delimeter)
{
	std::stringstream vecStr;

	std::string parName;
	std::string parValue;
	char delim;

	std::vector<std::string> parNameList;
	std::vector<std::string> parValueList;

	// Throws the strings into a stringstream then parses it towards a string -> char -> string grammar
	for (const std::string &str : vec) {
		vecStr << str;
		vecStr >> parName >> delim >> parValue;

		if (delim != delimeter) {
			std::cout << "Skipped : " << str << std::endl;	
		}

		parNameList.push_back(parName);
		parValueList.push_back(parValue);

		vecStr.str(std::string()); // Make sure to clear the stream
	}

	// We assume the background is the last element
	std::string last;
	last = vec.back();
	last = last.substr(last.find("\""), last.find("\"," - 1)); // We Substring between " and ", so we get the background

	parNameList.push_back("Background"); // We manually push background
	parValueList.push_back(last);
	// 

	return std::make_tuple(parNameList, parValueList);
}

void MapSettings::assignValues(const std::vector<std::string>& parNameList, const std::vector<std::string>& parValueList)
{
	if (m_parNameList != parNameList) {
		std::cout << "Name mismatch" << std::endl;
		return;
	}
	m_audioFileName  		=	parValueList[0];
	m_audioLeadIn  			=	std::stoi(parValueList[1]);
	m_previewTime  			=	std::stoi(parValueList[2]);
	m_countdown  			=	std::stoi(parValueList[3]);
	m_sampleSet  			=	(Osu::SAMPLESET) std::stoi(parValueList[4]);
	m_stackLeniency  		=	std::stod(parValueList[5]);
	m_mode  				=	(Osu::MODE) std::stoi(parValueList[6]);
	m_letterboxInBreaks  	=	std::stoi(parValueList[7]);
	m_specialStyle  		=	std::stoi(parValueList[8]);
	m_widescreenStoryboard 	=	std::stoi(parValueList[9]);

	std::vector<std::string> temp_m_bookmarks = {};
	boost::split(temp_m_bookmarks, parValueList[10], boost::is_any_of(",*"));
	for (auto bookmark : temp_m_bookmarks) {
		m_bookmarks.push_back(std::stoi(bookmark));
	}

	m_distanceSpacing  		=	std::stoi(parValueList[11]);
	m_beatDivisor  			=	std::stoi(parValueList[12]);
	m_gridSize  			=	std::stoi(parValueList[13]);
	m_timelineZoom  		=	std::stod(parValueList[14]);
	m_title  				=	parValueList[15];
	m_titleUnicode  		=	parValueList[16];
	m_artist  				=	parValueList[17];
	m_artistUnicode  		=	parValueList[18];
	m_creator  				=	parValueList[19];
	m_version  				=	parValueList[20];
	m_source  				=	parValueList[21];
	boost::split(m_tags, parValueList[22], boost::is_any_of(",*"));
	m_beatmapID  			=	std::stoi(parValueList[23]);
	m_beatmapSetID  		=	std::stoi(parValueList[24]);
	m_HPDrainRate  			=	std::stod(parValueList[25]);
	m_circleSize  			=	std::stod(parValueList[26]);
	m_overallDifficulty  	=	std::stod(parValueList[27]);
	m_approachRate  		=	std::stod(parValueList[28]);
	m_sliderMultiplier  	=	std::stod(parValueList[29]);
	m_sliderTickRate  		=	std::stoi(parValueList[30]);
}
