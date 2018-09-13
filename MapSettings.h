#pragma once
class MapSettings
{
public:
	// Load Settings by Vector
	MapSettings(const std::vector<std::string> &vec);
	~MapSettings();

	// probably have this print out all settings
	void debugSettings();

private:

	// Splits the vector of strings with a delim,
	// returns Parameter Name Vector then Parameter Vector respectively.
	std::tuple<std::vector<std::string>, std::vector<std::string>>
		splitValues(const std::vector<std::string> &vec, char delimeter = ':');

	// Assigns values as provided, throws an exception if the parameter name is mismatched.
	void assignValues(const std::vector<std::string> &parNameList,
					  const std::vector<std::string> &parValueList);

	

	std::string m_audioFileName;
	int m_audioLeadIn;
	int m_previewTime;
	bool m_countdown;
	Osu::SAMPLESET m_sampleSet;
	double m_stackLeniency;
	Osu::MODE m_mode;
	bool m_letterboxInBreaks;
	bool m_specialStyle;
	bool m_widescreenStoryboard;
	std::vector<int> m_bookmarks = {};
	int m_distanceSpacing;
	int m_beatDivisor;
	int m_gridSize;
	double m_timelineZoom;
	std::string m_title;
	std::string m_titleUnicode;
	std::string m_artist;
	std::string m_artistUnicode;
	std::string m_creator;
	std::string m_version;
	std::string m_source;
	std::vector<std::string> m_tags = {};
	int m_beatmapID;
	int m_beatmapSetID;
	double m_HPDrainRate;
	double m_circleSize;
	double m_overallDifficulty;
	double m_approachRate;
	double m_sliderMultiplier;
	int m_sliderTickRate;
	std::string m_background;


	static std::vector<std::string> m_parNameList;
};


// Easier to copy
// m_audioFileName
// m_audioLeadIn
// m_previewTime
// m_countdown
// m_sampleSet
// m_stackLeniency
// m_mode
// m_letterboxInBreaks
// m_specialStyle
// m_widescreenStoryboard
// m_bookmarks={}
// m_distanceSpacing
// m_beatDivisor
// m_gridSize
// m_timelineZoom
// m_title
// m_titleUnicode
// m_artist
// m_artistUnicode
// m_creator
// m_version
// m_source
// m_tags
// m_beatmapID
// m_beatmapSetID
// m_HPDrainRate
// m_circleSize
// m_overallDifficulty
// m_approachRate
// m_sliderMultiplier
// m_sliderTickRate
// m_background