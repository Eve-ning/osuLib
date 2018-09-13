#include "pch.h"
#include "MapSettings.h"

// Defines what the Parameter List should match EXACTLY, else we throw an exception
std::vector<std::string> MapSettings::m_parNameList = {
	"AudioFilename",
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
	"SliderTickRate",
	"Background"
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
	std::string parName;
	std::string parValue;

	std::vector<std::string> parNameList;
	std::vector<std::string> parValueList;

	std::vector<std::string> vectorSplit;

	// Throws the strings into a stringstream then parses it towards a string -> char -> string grammar
	for (const std::string &str : vec) {

		boost::split(vectorSplit, str, boost::is_any_of(std::string(1, delimeter) + "*"));

		if (vectorSplit.size() != 2) {
			std::cout << "Skipped : " << str << std::endl;	
			continue;
		}

		// Trim off whitespace
		boost::erase_all(vectorSplit[0], " "); 
		boost::erase_all(vectorSplit[1], " ");
		
		parNameList.push_back(vectorSplit[0]);
		parValueList.push_back(vectorSplit[1]);
	}

	// We assume the background is the last element
	std::string last;
	last = vec.back();
	last = last.substr(last.find("\"") + 1, last.find("\",") - 4); // We Substring between " and ", so we get the background

	parNameList.push_back("Background"); // We manually push background
	parValueList.push_back(last);

	return std::make_tuple(parNameList, parValueList);
}

void MapSettings::assignValues(const std::vector<std::string>& parNameList, const std::vector<std::string>& parValueList)
{
	for (size_t i = 0; (i < parNameList.size()) && (i < m_parNameList.size()); i++) {
		if (parNameList[i] != m_parNameList[i]) {
			std::string message;

			message = "Name Mismatch: " + parNameList[i] + " != " + m_parNameList[i];
			std::cout << message << '\n';
			throw new std::exception(message.c_str());
		}
	}

	m_audioFileName  		=	parValueList[0];
	m_audioLeadIn  			=	std::stoi(parValueList[1]);
	m_previewTime  			=	std::stoi(parValueList[2]);
	m_countdown  			=	std::stoi(parValueList[3]);
	m_sampleSet  			=	Osu::samplesetFromString(parValueList[4]);
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
	m_background			=   parValueList[31];
	
}

void MapSettings::debugSettings()
{
	std::cout
	<< std::endl << m_audioFileName
	<< std::endl << m_audioLeadIn
	<< std::endl << m_previewTime
	<< std::endl << m_countdown
	<< std::endl << Osu::stringFromSample(m_sampleSet)
	<< std::endl << m_stackLeniency
	<< std::endl << Osu::stringFromMode(m_mode)
	<< std::endl << m_letterboxInBreaks
	<< std::endl << m_specialStyle
	<< std::endl << m_widescreenStoryboard
	<< std::endl/* << boost::algorithm::join(m_bookmarks, ",")*/
	<< std::endl << m_distanceSpacing
	<< std::endl << m_beatDivisor
	<< std::endl << m_gridSize
	<< std::endl << m_timelineZoom
	<< std::endl << m_title
	<< std::endl << m_titleUnicode
	<< std::endl << m_artist
	<< std::endl << m_artistUnicode
	<< std::endl << m_creator
	<< std::endl << m_version
	<< std::endl << m_source
	<< std::endl /*<< boost::algorithm::join(m_tags, ",")*/
	<< std::endl << m_beatmapID
	<< std::endl << m_beatmapSetID
	<< std::endl << m_HPDrainRate
	<< std::endl << m_circleSize
	<< std::endl << m_overallDifficulty
	<< std::endl << m_approachRate
	<< std::endl << m_sliderMultiplier
	<< std::endl << m_sliderTickRate
	<< std::endl << m_background
	<< std::endl;
}
