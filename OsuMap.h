#pragma once

#include "lib/primitives/derived_chart/HitObjectList.h"
#include "lib/primitives/derived_chart/TimingPointList.h"
#include "lib/primitives/derived_sb/SpriteObject.h"

class OsuMap
{
public:
	OsuMap(std::string fileName);
	OsuMap(HitObjectList hitObjectList, TimingPointList timingPointList);
	~OsuMap();

private:
	HitObjectList m_hitObjectList = {};
	TimingPointList m_timingPointlist = {};
	std::vector<SpriteObject> m_spriteObjectList = {};
};

