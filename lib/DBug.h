#pragma once
#ifndef DBUG_H
#define DBUG_H

#define DEBUGTITLE(title) std::cout << "[ -- " << title << " TEST -- ]" << std::endl
#define DEBUGPASS(title) std::cout << "[ -- " << title << " TEST PASS -- ]" << std::endl
#define DEBUGLABEL(title) std::cout << "[ ## " << title << " ## ]" << std::endl
#define DEBUGSEP std::cout << std::endl << "- - - - - - - -" << std::endl

#include "primitives/derived_chart/TimingPointList.h"
#include "primitives/derived_chart/HitObjectList.h"
#include "OsuAlgorithm.h"
#include <fstream>

class Dbug
{
public:

	static void primitive_debug() {
		DEBUGTITLE("Debug");

		DEBUGTITLE("BoundedInt");
		if (debug_boundedInt()) { DEBUGPASS("BoundedInt"); }
		DEBUGSEP;

		DEBUGTITLE("BoundedDouble");
		if (debug_boundedDouble()) { DEBUGPASS("BoundedDouble"); }
		DEBUGSEP;

		DEBUGTITLE("HitObject");
		if (debug_hitObject()) { DEBUGPASS("HitObject"); }
		DEBUGSEP;

		DEBUGTITLE("TimingPoint");
		if (debug_timingPoint()) { DEBUGPASS("TimingPoint"); }
		DEBUGSEP;

		DEBUGTITLE("HitObjectList");
		if (debug_hitObjectList()) { DEBUGPASS("HitObjectList"); }
		DEBUGSEP;

		DEBUGTITLE("TimingPointList");
		if (debug_timingPointList()) { DEBUGPASS("TimingPointList"); }
		DEBUGSEP;

		DEBUGPASS("Debug");
	}
	static void algorithm_debug() {
		DEBUGTITLE("Debug");

		DEBUGTITLE("countInRange");
		if (debug_countInRange()) { DEBUGPASS("countInRange"); }
		DEBUGSEP;

		DEBUGTITLE("adjustToAverage");
		if (debug_adjustToAverage()) { DEBUGPASS("adjustToAverage"); }
		DEBUGSEP;

		DEBUGTITLE("scale");
		if (debug_scale()) { DEBUGPASS("scale"); }
		DEBUGSEP;

		DEBUGTITLE("moveBy");
		if (debug_moveBy()) { DEBUGPASS("moveBy"); }
		DEBUGSEP;

		DEBUGTITLE("moveTo");
		if (debug_moveTo()) { DEBUGPASS("moveTo"); }
		DEBUGSEP;

		DEBUGTITLE("normalize");
		if (debug_normalize()) { DEBUGPASS("normalize"); }
		DEBUGSEP;

		DEBUGTITLE("stutter");
		if (debug_stutter()) { DEBUGPASS("stutter"); }
		DEBUGSEP;

		DEBUGTITLE("copyTo");
		if (debug_copyTo()) { DEBUGPASS("copyTo"); }
		DEBUGSEP;

		DEBUGTITLE("supImp");
		if (debug_supImp()) { DEBUGPASS("supImp"); }
		DEBUGSEP;

		DEBUGPASS("Debug");
	}

private:

	static bool debug_boundedInt();
	static bool debug_boundedDouble();
	static bool debug_hitObject();
	static bool debug_timingPoint();
	static bool debug_hitObjectList();
	static bool debug_timingPointList();

	static bool debug_countInRange();
	static bool debug_adjustToAverage();
	static bool debug_scale();
	static bool debug_moveBy();
	static bool debug_moveTo();
	static bool debug_normalize();
	static bool debug_stutter();
	static bool debug_copyTo();
	static bool debug_supImp();

	static bool compareDebug(const double &expected,
		const double &given);
	static bool compareDebug(const std::string &expected,
		const std::string &given);
	template <class T>
	static bool compareDebug(const std::vector<T> &expected,
		const std::vector<T> &given) {
		//std::cout << (expected == given) << std::endl <<
		//	"Expected:" << expected << std::endl <<
		//	"Given:\t " << given << std::endl;
		//return expected == given;

		for (int i = 0; i < expected.size(); i++) {
			std::cout << (expected[i] == given[i]) << std::endl <<
				"Expected:" << expected[i] << std::endl <<
				"Given:\t " << given[i] << std::endl;
		}
		return expected == given;
	}
	static void printStringList(const std::vector<std::string> &expected) {

		for (int i = 0; i < expected.size(); i++) {
			std::cout << expected[i] << std::endl;
		}

	}
	static bool compareDebug(const std::vector<std::string> &expected,
		const std::vector<std::string> &given);

	static TimingPointList getEgTP();
	static HitObjectList getEgHO();

private:

};

#endif // DBUG_H
