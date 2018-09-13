#include "pch.h"
#include "osuMap.h"

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

	MapSettings test = MapSettings(mapSettingsVector);

	test.debugSettings();
	
}

OsuMap::~OsuMap()
{
}

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
