#pragma once
#include "HitObject.h"
#include "TimingPoint.h"
#include "MapSettings.h"

typedef std::shared_ptr<HitObject> HitObject_sptr;
typedef std::shared_ptr<TimingPoint> TimingPoint_sptr;

typedef std::vector<std::shared_ptr<HitObject>> HitObjectList_sptr;
typedef std::vector<std::shared_ptr<TimingPoint>> TimingPointList_sptr;

typedef std::shared_ptr<MapSettings> MapSettings_sptr;

struct HitObjectList {
	NormalNoteList normalNote;
	LongNoteList longNote;
};

struct TimingPointList {

	SliderVelocityList sliderVelocity;
	BPMList bpm;
};

class OsuMap
{
public:
	// Loads the map from file path
	OsuMap(const std::string &filePath);
	~OsuMap();

	HitObjectList hitObjectList() const { return m_hitObjectList; }
	TimingPointList timingPointList() const { return m_timingPointList; }
	MapSettings mapSettings() const { return *m_mapSettings; }

private:

	// Takes a stringstream and fills in the vector, breaks on specified tag
	void segmentFile(std::stringstream &ss, std::vector<std::string> &vectorToFill, const std::string &nextTag = "");

	// Converts a vector of string to a vector of specified class
	template <class T>
	std::vector<T> instStringVector(const std::vector<std::string> &vectorToConvert);

	// Derive is used to convert shared_ptr to objects
	void derive(const std::shared_ptr<TimingPoint> timingPoint);
	void derive(const std::shared_ptr<HitObject> hitObject);

	HitObjectList m_hitObjectList;
	TimingPointList m_timingPointList;

	// This is a shared_ptr are there isn't any default for MapSettings()
	MapSettings_sptr m_mapSettings;
};

template<class T>
inline std::vector<T> OsuMap::instStringVector(const std::vector<std::string>& vectorToConvert)
{
	std::vector<T> instVector;

	for (const std::string &str : vectorToConvert) {
		instVector.push_back(T(str)); // Instantiate with string argument and push back into instVector
	}

	return instVector;
}
