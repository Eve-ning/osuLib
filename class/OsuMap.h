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

	// Returns a shared_ptr vector of HitObject
	HitObjectList_sptr sptr() const {
		HitObjectList_sptr output = {};
		for (auto NN : normalNote) {
			output.push_back(std::make_shared<NormalNote>(NN));
		}
		for (auto LN : longNote) {
			output.push_back(std::make_shared<LongNote>(LN));
		}
		return output;
	}

	// Converts sptr list back to original objects
	void derive(HitObjectList_sptr sptr) {

		normalNote.clear();
		longNote.clear();

		for (auto obj_sptr : sptr) {
			auto castNN = std::dynamic_pointer_cast<NormalNote>(obj_sptr);

			if (castNN) {
				normalNote.push_back(*castNN);
				continue;
			}

			auto castLN = std::dynamic_pointer_cast<LongNote>(obj_sptr);

			if (castLN) {
				longNote.push_back(*castLN);
				continue;
			}

			throw new std::exception("Fail to derive HitObject.");
		}
	}
};

struct TimingPointList {
	SliderVelocityList sliderVelocity;
	BPMList bpm;

	// Returns a shared_ptr vector of TimingPoint
	TimingPointList_sptr sptr() const {
		TimingPointList_sptr output = {};
		for (auto SV : sliderVelocity) {
			output.push_back(std::make_shared<SliderVelocity>(SV));
		}
		for (auto BPM_ : bpm) {
			output.push_back(std::make_shared<BPM>(BPM_));
		}
		return output;
	}

	// Converts sptr list back to original objects
	void derive(TimingPointList_sptr sptr) {

		sliderVelocity.clear();
		bpm.clear();

		for (auto obj_sptr : sptr) {
			auto castSV = std::dynamic_pointer_cast<SliderVelocity>(obj_sptr);

			if (castSV) {
				sliderVelocity.push_back(*castSV);
				continue;
			}

			auto castBPM = std::dynamic_pointer_cast<BPM>(obj_sptr);

			if (castBPM) {
				bpm.push_back(*castBPM);
				continue;
			}

			throw new std::exception("Fail to derive TimingPoint.");
		}

		
	}
};

class OsuMap : std::enable_shared_from_this<OsuMap>
{
public:
	// Loads the map from file path
	OsuMap(const std::string &filePath);
	~OsuMap();

	HitObjectList hitObjectList() const { return m_hitObjectList; }
	TimingPointList timingPointList() const { return m_timingPointList; }
	MapSettings mapSettings() const { return *m_mapSettings; }

	void setHitObjectList(HitObjectList list) { m_hitObjectList = list; }
	void setTimingPointList(TimingPointList list) { m_timingPointList = list; }
	void setMapSettings(MapSettings settings) { m_mapSettings = std::make_shared<MapSettings>(settings); }

	std::vector<std::string> exportMap() const;

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
