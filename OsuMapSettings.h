#pragma once

#include "lib/primitives/bounded/BoundedDouble.h"
#include "lib/primitives/bounded/BoundedInt.h"
#include "lib/primitives/enums/SampleSet.h"
#include <vector>

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/spirit/include/qi_lit.hpp>


enum class GameMode {
	STANDARD,
	TAIKO,
	CATCH,
	MANIA
};


class OsuMapSettings
{
public:
	OsuMapSettings(std::vector<std::string> settings_string) {

		bool flag;

		auto v_iter = settings_string.begin();
		auto end = settings_string.end();

		namespace qi = boost::spirit::qi;
		namespace ascii = boost::spirit::ascii;
		namespace phoenix = boost::phoenix;

		using qi::double_;
		using qi::int_;
		using qi::bool_;
		using qi::phrase_parse;
		using qi::_1;
		using qi::string;	
		using ascii::space;
		using phoenix::ref;

		// We iterate through the vector to find certain "Tags"

		// Find [General] Tag
		if (*v_iter != "[General]" && (v_iter != settings_string.end())) {
			v_iter++;
		}

		auto str_iter_b = v_iter->begin();
		auto str_iter_e = v_iter->end();

		phrase_parse(str_iter_b, str_iter_e, (
			string >> ':' >> string[m_audioFileName += _1] >>
			string >> ':' >> int_[m_audioLeadIn += _1] >>
			string >> ':' >> int_[m_previewTime += _1] >>
			string >> ':' >> int_[m_countdown += _1] >>
			string >> ':' >> string >>
			string >> ':' >> int_[m_stackLeniency += _1] >>
			string >> ':' >> int_[m_gameMode += _1] >>
			string >> ':' >> int_[m_letterbox += _1] >>
			string >> ':' >> int_[m_specialStyle += _1] >>
			string >> ':' >> int_[m_widescreen += _1]
			),space);



	}
	~OsuMapSettings();

private:
	std::string m_audioFileName = "";
	BoundedInt m_audioLeadIn = BoundedInt(0, 0);
	BoundedInt m_previewTime = BoundedInt(0, 0);
	bool m_countdown = false;
	SampleSet m_sampleSet = SampleSet::AUTO;
	BoundedDouble m_stackLeniency = BoundedDouble(0, 0, 1);
	GameMode m_gameMode = GameMode::MANIA;
	bool m_letterbox = false;
	bool m_specialStyle = false;
	bool m_widescreen = false;

	std::string m_title = "";
	std::string m_unicodeTitle = "";
	std::string m_artist = "";
	std::string m_unicodeArtist = "";
	std::string m_creator = "";
	std::string m_source = "";
	std::vector<std::string> m_tags = {};

	BoundedDouble m_HP = BoundedDouble(8, 0, 10);
	BoundedDouble m_CS = BoundedDouble(7, 0, 9);
	BoundedDouble m_OD = BoundedDouble(8, 0, 10);
	BoundedDouble m_AR = BoundedDouble(5, 0, 10);

	// We might not need to read this. Editor Settings
	// std::vector<int> m_bookmarks = {};
	// BoundedInt m_distanceSpacing = BoundedInt(1, 0);
	// BoundedInt m_beatDivisor = BoundedInt(1, 0);
	// BoundedInt m_gridSize = BoundedInt(16, 0);
	// BoundedDouble m_timelineZoom = BoundedDouble(1.9, 0);



};

