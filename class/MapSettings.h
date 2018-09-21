#pragma once
#include "../constant/Constants.h"

class MapSettings : std::enable_shared_from_this<MapSettings>
{
public:
	// Load Settings by Vector
	MapSettings(const std::vector<std::string> &vec);

	// Prints out all values as std::cout
	void debugSettings();

	// Get Functions
	std::string audioFileName() const		{ return m_audioFileName	   ; }
	int audioLeadIn() const					{ return m_audioLeadIn		   ; }
	int previewTime() const					{ return m_previewTime		   ; }
	bool countdown() const					{ return m_countdown		   ; }
	Osu::SAMPLESET sampleSet() const		{ return m_sampleSet		   ; }
	double stackLeniency() const			{ return m_stackLeniency	   ; }
	Osu::MODE mode() const					{ return m_mode				   ; }
	bool letterboxInBreaks() const			{ return m_letterboxInBreaks   ; }
	bool specialStyle() const				{ return m_specialStyle		   ; }
	bool widescreenStoryboard() const		{ return m_widescreenStoryboard; }
	std::vector<int> bookmarks() const		{ return m_bookmarks		   ; }
	int distanceSpacing() const				{ return m_distanceSpacing	   ; }
	int beatDivisor() const					{ return m_beatDivisor		   ; }
	int gridSize() const					{ return m_gridSize			   ; }
	double timelineZoom() const				{ return m_timelineZoom		   ; }
	std::string title() const				{ return m_title			   ; }
	std::string titleUnicode() const		{ return m_titleUnicode		   ; }
	std::string artist() const				{ return m_artist			   ; }
	std::string artistUnicode() const		{ return m_artistUnicode	   ; }
	std::string creator() const				{ return m_creator			   ; }
	std::string version() const				{ return m_version			   ; }
	std::string source() const				{ return m_source			   ; }
	std::vector<std::string> tags() const	{ return m_tags				   ; }
	int beatmapID() const					{ return m_beatmapID		   ; }
	int beatmapSetID() const				{ return m_beatmapSetID		   ; }
	double HPDrainRate() const				{ return m_HPDrainRate		   ; }
	double circleSize() const				{ return m_circleSize		   ; }
	double overallDifficulty() const		{ return m_overallDifficulty   ; }
	double approachRate() const				{ return m_approachRate		   ; }
	double sliderMultiplier() const			{ return m_sliderMultiplier	   ; }
	int sliderTickRate() const				{ return m_sliderTickRate	   ; }
	std::string background() const			{ return m_background		   ; }

	// Set Functions
	void setAudioFileName		(const std::string audioFileName 		){ m_audioFileName		  = audioFileName		; } 
	void setAudioLeadIn			(const int audioLeadIn 					){ m_audioLeadIn		  =	audioLeadIn		  	; }
	void setPreviewTime			(const int previewTime 					){ m_previewTime		  =	previewTime		  	; }
	void setCountdown			(const bool countdown 					){ m_countdown			  =	countdown			; } 
	void setSampleSet			(const Osu::SAMPLESET sampleSet 		){ m_sampleSet			  =	sampleSet			; } 
	void setStackLeniency		(const double stackLeniency 			){ m_stackLeniency		  =	stackLeniency		; } 
	void setMode				(const Osu::MODE mode 					){ m_mode				  =	mode				; } 
	void setLetterboxInBreaks	(const bool letterboxInBreaks 			){ m_letterboxInBreaks	  =	letterboxInBreaks	; } 
	void setSpecialStyle		(const bool specialStyle 				){ m_specialStyle		  =	specialStyle		; } 
	void setWidescreenStoryboard(const bool widescreenStoryboard 		){ m_widescreenStoryboard =	widescreenStoryboard; }
	void setBookmarks			(const std::vector<int> bookmarks 		){ m_bookmarks			  =	bookmarks			; } 
	void setDistanceSpacing		(const int distanceSpacing 				){ m_distanceSpacing	  =	distanceSpacing	  	; }
	void setBeatDivisor			(const int beatDivisor 					){ m_beatDivisor		  =	beatDivisor		  	; }
	void setGridSize			(const int gridSize 					){ m_gridSize			  =	gridSize			; } 
	void setTimelineZoom		(const double timelineZoom 				){ m_timelineZoom		  =	timelineZoom		; } 
	void setTitle				(const std::string title 				){ m_title				  =	title				; } 
	void setTitleUnicode		(const std::string titleUnicode 		){ m_titleUnicode		  =	titleUnicode		; } 
	void setArtist				(const std::string artist 				){ m_artist				  =	artist				; } 
	void setArtistUnicode		(const std::string artistUnicode 		){ m_artistUnicode		  =	artistUnicode		; } 
	void setCreator				(const std::string creator 				){ m_creator			  =	creator			  	; }
	void setVersion				(const std::string version 				){ m_version			  =	version			  	; }
	void setSource				(const std::string source 				){ m_source				  =	source				; } 
	void setTags				(const std::vector<std::string> tags 	){ m_tags				  =	tags				; } 
	void setBeatmapID			(const int beatmapID 					){ m_beatmapID			  =	beatmapID			; } 
	void setBeatmapSetID		(const int beatmapSetID 				){ m_beatmapSetID		  =	beatmapSetID		; } 
	void setHPDrainRate			(const double HPDrainRate 				){ m_HPDrainRate		  =	HPDrainRate		  	; }
	void setCircleSize			(const double circleSize 				){ m_circleSize			  =	circleSize			; } 
	void setOverallDifficulty	(const double overallDifficulty 		){ m_overallDifficulty	  =	overallDifficulty	; } 
	void setApproachRate		(const double approachRate 				){ m_approachRate		  =	approachRate		; } 
	void setSliderMultiplier	(const double sliderMultiplier 			){ m_sliderMultiplier	  =	sliderMultiplier	; } 
	void setSliderTickRate		(const int sliderTickRate 				){ m_sliderTickRate		  =	sliderTickRate		; } 
	void setBackground			(const std::string background 			){ m_background			  =	background			; } 

private:

	// Splits the vector of strings with a delim,
	// returns Parameter Name Vector then Parameter Vector respectively.
	std::tuple<std::vector<std::string>, std::vector<std::string>>
		splitValues(const std::vector<std::string> &vec, char delimeter = ':');

	// Assigns values as provided, throws an exception if the parameter name is mismatched.
	void assignValues(std::vector<std::string> parNameList,
					  std::vector<std::string> parValueList);

	// Joins Int to return a readable std::string
	std::string joinIntVector(const std::vector<int> &vect, std::string delim = ", ");

	// Parameters
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
// m_bookmarks
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