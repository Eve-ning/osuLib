#include "../pch.h"
#include "pch.h"
#include "MapSettings.h"


// OLD: now we use a map function that uses the value directly instead of index (it's confusing and redundant)
//// Defines what the Parameter List should match EXACTLY, else we throw an exception
//std::vector<std::string> MapSettings::m_parNameList = {
//	"AudioFilename",
//	"AudioLeadIn",
//	"PreviewTime",
//	"Countdown",
//	"SampleSet",
//	"StackLeniency",
//	"Mode",
//	"LetterboxInBreaks",
//	"SpecialStyle",
//	"WidescreenStoryboard",
//	"Bookmarks",
//	"DistanceSpacing",
//	"BeatDivisor",
//	"GridSize",
//	"TimelineZoom",
//	"Title",
//	"TitleUnicode",
//	"Artist",
//	"ArtistUnicode",
//	"Creator",
//	"Version",
//	"Source",
//	"Tags",
//	"BeatmapID",
//	"BeatmapSetID",
//	"HPDrainRate",
//	"CircleSize",
//	"OverallDifficulty",
//	"ApproachRate",
//	"SliderMultiplier",
//	"SliderTickRate",
//	"Background"
//};

MapSettings::MapSettings(const std::vector<std::string> &vec) 
{
	// Splits the vector into a tuple, one holding the parameter name, one holding the parameter value
	auto data = splitValues(vec, ':');

	// Assigns the values according to the parameter names and values.
	assignValues(data);
}

// Splits the vector of strings with a delim,
// returns Parameter Name Vector then Parameter Vector respectively.
MapSettingsData MapSettings::splitValues(const std::vector<std::string>& vec, char delimeter)
{
	std::string parName;
	std::string parValue;

	MapSettingsData data;

	std::vector<std::string> vectorSplit;

	// Throws the strings into a stringstream then parses it towards a string -> char -> string grammar
	for (const std::string &str : vec) {

		boost::split(vectorSplit, str, boost::is_any_of(std::string(1, delimeter) + "*"));

		if (vectorSplit.size() != 2) {
			std::cout << "Skipped : " << str << std::endl;	
			continue;
		}

		// Trim off whitespace
		boost::trim(vectorSplit[0]);
		boost::trim(vectorSplit[1]);
		
		data[vectorSplit[0]] = vectorSplit[1];
	}

	// We assume the background is the last element
	std::string last;
	last = vec.back(); // Get last element
	last = last.substr(last.find("\"") + 1, last.find("\",") - 5); // We Substring between " and ", so we get the background name

	data["Background"] = last; // We manually push background

	return data;
}

// Assigns values as provided, throws an exception if the parameter name is mismatched.
void MapSettings::assignValues(MapSettingsData data)
{
	std::cout << "Setting Beatmap Settings..." << std::endl;

	// If "Bookmarks" tag doesn't exist, we insert it in on index 10
	if (data.find("Bookmarks") == data.end()) {
		data["Bookmarks"] = "";
		std::cout << "Added Bookmark Tag." << std::endl;
	}

	//for (size_t i = 0; (i < parNameList.size()) && (i < m_parNameList.size()); i++) {
	//	if (parNameList[i] != m_parNameList[i]) {
	//		std::string message;

	//		message = "Name Mismatch: " + parNameList[i] + " != " + m_parNameList[i];
	//		std::cout << message << '\n';
	//		throw new std::exception(message.c_str());
	//	}
	//}

	try {
		m_audioFileName  		=	data["AudioFilename"];
		m_audioLeadIn  			=	std::stoi(data["AudioLeadIn"]);
		m_previewTime  			=	std::stoi(data["PreviewTime"]);
		m_countdown  			=	std::stoi(data["Countdown"]);
		m_sampleSet				=   Osu::samplesetFromString(data["SampleSet"]);
		m_stackLeniency  		=	std::stod(data["StackLeniency"]);
		m_mode  				=	(Osu::MODE) std::stoi(data["Mode"]);
		m_letterboxInBreaks  	=	std::stoi(data["LetterboxInBreaks"]);
		m_specialStyle  		=	std::stoi(data["SpecialStyle"]);
		m_widescreenStoryboard 	=	std::stoi(data["WidescreenStoryboard"]);

		if (data["Bookmarks"] == "") { // Means there's no Bookmarks
			m_bookmarks = {};
		}
		else {
			std::vector<std::string> temp_m_bookmarks = {};
			std::string temp = data["Bookmarks"];
			boost::split(temp_m_bookmarks, temp, boost::is_any_of(",*"));
			for (auto bookmark : temp_m_bookmarks) {
				m_bookmarks.push_back(std::stoi(bookmark));
			}
		}

		m_distanceSpacing  		=	std::stoi(data["DistanceSpacing"]);
		m_beatDivisor  			=	std::stoi(data["BeatDivisor"]);
		m_gridSize  			=	std::stoi(data["GridSize"]);
		m_timelineZoom  		=	std::stod(data["TimelineZoom"]);
		m_title  				=	data["Title"];
		m_titleUnicode  		=	data["TitleUnicode"];
		m_artist  				=	data["Artist"];
		m_artistUnicode  		=	data["ArtistUnicode"];
		m_creator  				=	data["Creator"];
		m_version  				=	data["Version"];
		m_source  				=	data["Source"];

		std::string temp_tagsStr = data["Tags"];
		boost::split(m_tags, temp_tagsStr, boost::is_any_of(",*"));

		m_beatmapID  			=	std::stoi(data["BeatmapID"]);
		m_beatmapSetID  		=	std::stoi(data["BeatmapSetID"]);
		m_HPDrainRate  			=	std::stod(data["HPDrainRate"]);
		m_circleSize  			=	std::stod(data["CircleSize"]);
		m_overallDifficulty  	=	std::stod(data["OverallDifficulty"]);
		m_approachRate  		=	std::stod(data["ApproachRate"]);
		m_sliderMultiplier  	=	std::stod(data["SliderMultiplier"]);
		m_sliderTickRate  		=	std::stoi(data["SliderTickRate"]);
		m_background			=   data["Background"];
	}
	catch (...) {
		throw new std::exception("Tag Mismatch in MapSettings.");
	}

	
}

// Joins Int to return a readable std::string
std::string MapSettings::joinIntVector(const std::vector<int>& vect, std::string delim)
{
	std::string output = "";
	for (const int &part : vect) {
		output.append(boost::lexical_cast<std::string>(part));
		output.append(delim);
	}

	for (size_t count = 0; count < delim.size(); count++) {
		output.pop_back();
	}

	return output;
}

// Prints out all values as std::cout
void MapSettings::debugSettings()
{
	std::cout
		<< std::endl << "AudioFilename: "			<< m_audioFileName
		<< std::endl << "AudioLeadIn: "				<< m_audioLeadIn
		<< std::endl << "PreviewTime: "				<< m_previewTime
		<< std::endl << "Countdown: "				<< m_countdown
		<< std::endl << "SampleSet: "				<< Osu::stringFromSample(m_sampleSet)
		<< std::endl << "StackLeniency: "			<< m_stackLeniency
		<< std::endl << "Mode: "					<< Osu::stringFromMode(m_mode)
		<< std::endl << "LetterboxInBreaks: "		<< m_letterboxInBreaks
		<< std::endl << "SpecialStyle: "			<< m_specialStyle
		<< std::endl << "WidescreenStoryboard: "	<< m_widescreenStoryboard
		<< std::endl << "Bookmarks: "				<< (m_bookmarks.empty() ?  "" : joinIntVector(m_bookmarks))
		<< std::endl << "DistanceSpacing: "			<< m_distanceSpacing
		<< std::endl << "BeatDivisor: "				<< m_beatDivisor
		<< std::endl << "GridSize: "				<< m_gridSize
		<< std::endl << "TimelineZoom: "			<< m_timelineZoom
		<< std::endl << "Title: "					<< m_title
		<< std::endl << "TitleUnicode: "			<< m_titleUnicode
		<< std::endl << "Artist: "					<< m_artist
		<< std::endl << "ArtistUnicode: "			<< m_artistUnicode
		<< std::endl << "Creator: "					<< m_creator
		<< std::endl << "Version: "					<< m_version
		<< std::endl << "Source: "					<< m_source
		<< std::endl << "Tags: "					<< boost::algorithm::join(m_tags, ",")
		<< std::endl << "BeatmapID: "				<< m_beatmapID
		<< std::endl << "BeatmapSetID: "			<< m_beatmapSetID
		<< std::endl << "HPDrainRate: "				<< m_HPDrainRate
		<< std::endl << "CircleSize: "				<< m_circleSize
		<< std::endl << "OverallDifficulty: "		<< m_overallDifficulty
		<< std::endl << "ApproachRate: "			<< m_approachRate
		<< std::endl << "SliderMultiplier: "		<< m_sliderMultiplier
		<< std::endl << "SliderTickRate: "			<< m_sliderTickRate
		<< std::endl << "Background: "				<< m_background
		<< std::endl;
}
