#pragma once
class MapSettings
{
public:
	// Load Settings by Vector
	MapSettings(const std::vector<std::string> &vec);
	~MapSettings();

private:

	// Splits the vector of strings with a delim,
	// returns Parameter Name Vector then Parameter Vector respectively.
	std::tuple<std::vector<std::string>, std::vector<std::string>>
		splitValues(const std::vector<std::string> &vec, char delimeter = ':');
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
	std::vector<std::string> m_tags;
	int m_beatmapID;
	int m_beatmapSetID;
	double m_HPDrainRate;
	double m_circleSize;
	double m_overallDifficulty;
	double m_approachRate;
	double m_sliderMultiplier;
	int m_sliderTickRate;

	static std::vector<std::string> m_parNameList;
};

