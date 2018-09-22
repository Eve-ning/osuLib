#include "../pch.h"
#include "osuMap.h"
#include "MapSettings.h"
#include "pch.h"
#include <vector>

OsuMap::OsuMap(const std::string & filePath)
{
	std::ifstream ts(filePath);
	std::stringstream ss;
	ss << ts.rdbuf();

	std::vector<std::string> mapSettingsVector;
	std::vector<std::string> mapTPVector;
	std::vector<std::string> mapHOVector;

	segmentFile(ss, mapSettingsVector, "[TimingPoints]");
	segmentFile(ss, mapTPVector, "[HitObjects]");
	segmentFile(ss, mapHOVector, "");

	std::cout << "Loading Map Settings: " << std::endl;
	m_mapSettings = std::make_shared<MapSettings>(MapSettings(mapSettingsVector));
	std::cout << "Complete!" << std::endl;

	std::cout << "Loading Timing Points: ";
	for (const std::string& str : mapTPVector) {
		derive(TimingPoint::allocate(str));
	}
	std::cout << "Complete!" << std::endl;

	std::cout << "Loading Hit Objects: ";
	for (const std::string& str : mapHOVector) {
		derive(HitObject::allocate(str, (int) m_mapSettings->circleSize()));
	}
	std::cout << "Complete!" << std::endl;
}

OsuMap::~OsuMap()
{
}

std::vector<std::string> OsuMap::exportMap() const
{
	std::vector<std::string> output = {};

	std::ifstream ts("MAPTEMPLATE.txt");
	std::stringstream ss;
	ss << ts.rdbuf();

	// we will use the template and replace certain keywords
	
	// Define a small function so I don't have to keep writing output.push_back

	std::string buffer = "";

	// Helps insert the next parameter (based on _____)<5 Underscores>
	auto insertNext = [&](const std::string &str) {
		bool insertable = false;

		while (!insertable && !ss.eof()) { // While it is not insertable AND not the end of the stream, we getline
			std::getline(ss, buffer, '\n');
			if (buffer[0] == '[') { // If it's a tag, we push into the output
				output.push_back(buffer);
			}
			else { // Else we replace _____
				insertable = true;
			}
		}
		if (ss.eof()) {
			throw new std::exception("Exporting replacing function out of index."); // Fail to insert
		}

		boost::replace_first(buffer, "_____", str); // Replace str
		output.push_back(buffer);
	};

	insertNext("14"); // Version Number

	// General
	insertNext(m_mapSettings->audioFileName());
	insertNext(std::to_string(m_mapSettings->audioLeadIn()));
	insertNext(std::to_string(m_mapSettings->previewTime()));
	insertNext(std::to_string(m_mapSettings->countdown()));
	insertNext(Osu::stringFromSample(m_mapSettings->sampleSet()));
	insertNext(std::to_string(m_mapSettings->stackLeniency()));
	insertNext(std::to_string((int)m_mapSettings->mode()));
	insertNext(std::to_string(m_mapSettings->letterboxInBreaks()));
	insertNext(std::to_string(m_mapSettings->specialStyle()));
	insertNext(std::to_string(m_mapSettings->widescreenStoryboard()));

	// Editor
	auto concatBookmarks = [](const std::vector<int> bookmarks) -> std::string {
		std::string output = "";
		for (auto bookmark : bookmarks) {
			output.append(std::to_string(bookmark));
			output.append(",");
		}
		if (!output.empty()) {
			output.pop_back(); // Remove the last comma
		}
		return output;
	};

	insertNext(concatBookmarks(m_mapSettings->bookmarks()));
	insertNext(std::to_string(m_mapSettings->distanceSpacing()));
	insertNext(std::to_string(m_mapSettings->beatDivisor()));
	insertNext(std::to_string(m_mapSettings->gridSize()));
	insertNext(std::to_string(m_mapSettings->timelineZoom()));

	// Metadata
	insertNext(m_mapSettings->title());
	insertNext(m_mapSettings->titleUnicode());
	insertNext(m_mapSettings->artist());
	insertNext(m_mapSettings->artistUnicode());
	insertNext(m_mapSettings->creator());
	insertNext(m_mapSettings->version());
	insertNext(m_mapSettings->source());
	insertNext(boost::join(m_mapSettings->tags(), ",")); // Tags will be joined by ","
	insertNext(std::to_string(m_mapSettings->beatmapID()));
	insertNext(std::to_string(m_mapSettings->beatmapSetID()));

	// Difficulty
	insertNext(std::to_string(m_mapSettings->HPDrainRate()));
	insertNext(std::to_string(m_mapSettings->circleSize()));
	insertNext(std::to_string(m_mapSettings->overallDifficulty()));
	insertNext(std::to_string(m_mapSettings->approachRate()));
	insertNext(std::to_string(m_mapSettings->sliderMultiplier()));
	insertNext(std::to_string(m_mapSettings->sliderTickRate()));
	insertNext(m_mapSettings->background());
	
	// Objects
	output.push_back("[TimingPoints]");
	for (auto TP : m_timingPointList.sptr()) {
		output.push_back(TP->str());
	}

	output.push_back("[HitObjects]");
	for (auto HO : m_hitObjectList.sptr()) {
		output.push_back(HO->str());
	}

	return output;
}

// Takes a stringstream and fills in the vector, breaks on specified tag
// Skips all Tags and Comments
void OsuMap::segmentFile(std::stringstream & ss, std::vector<std::string>& vectorToFill, const std::string & nextTag)
{
	std::string item;

	while (std::getline(ss, item, '\n')) {
		if (item == nextTag) { // If we hit any of the nextTag we break.
			break;
		}

		if (item == "") { // If blank, skip
			continue;
		}
		else if (
			item.front() == '[' || item.back() == ']' || // If tag, we skip
			item.front() == '/') { // If comment, we skip
			continue;
		}
		else
		{
			vectorToFill.push_back(item);
		}
	}
}

// Derive is used to convert shared_ptr to objects
void OsuMap::derive(const std::shared_ptr<TimingPoint> timingPoint)
{
	auto castSV = std::dynamic_pointer_cast<SliderVelocity>(timingPoint);

	if (castSV) {
		m_timingPointList.sliderVelocity.push_back(*castSV);
		return;
	}

	auto castBPM = std::dynamic_pointer_cast<BPM>(timingPoint);

	if (castBPM) {
		m_timingPointList.bpm.push_back(*castBPM);
		return;
	}

	throw new std::exception("Fail to derive TimingPoint.");
}
// Derive is used to convert shared_ptr to objects
void OsuMap::derive(const std::shared_ptr<HitObject> hitObject)
{
	auto castNN = std::dynamic_pointer_cast<NormalNote>(hitObject);

	if (castNN) {
		m_hitObjectList.normalNote.push_back(*castNN);
		return;
	}

	auto castLN = std::dynamic_pointer_cast<LongNote>(hitObject);

	if (castLN) {
		m_hitObjectList.longNote.push_back(*castLN);
		return;
	}

	throw new std::exception("Fail to derive HitObject.");
}

