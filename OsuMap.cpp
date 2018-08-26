#include "stdafx.h"
#include "OsuMap.h"

OsuMap::OsuMap(std::string fileName)
{
	std::ofstream fileStream;
	fileStream.open(fileName);

	if (!fileStream.is_open()) {
		throw OsuException(OsuException::ID::INVALID_MAP_FILE);
	}
}

OsuMap::OsuMap(HitObjectList hitObjectList, TimingPointList timingPointList) : m_hitObjectList(hitObjectList), m_timingPointList(timingPointList)
{
}

OsuMap::~OsuMap()
{
}
