#include "../pch.h"
#include "osuMap.h"
#include "pch.h"

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
	m_mapSettings = std::make_shared<MapSettings>(mapSettingsVector);
	std::cout << "Complete!" << std::endl;

	std::cout << "Loading Timing Points: ";
	for (const std::string& str : mapTPVector) {
		derive(TimingPoint::allocate(str));
	}
	std::cout << "Complete!" << std::endl;

	std::cout << "Loading Hit Objects: ";
	for (const std::string& str : mapHOVector) {
		derive(HitObject::allocate(str, 7));
	}
	std::cout << "Complete!" << std::endl;
}

OsuMap::~OsuMap()
{
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
