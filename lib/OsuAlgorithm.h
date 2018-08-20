#pragma once
#ifndef OSUALGORITHM_H
#define OSUALGORITHM_H

#include "primitives/derived_chart/TimingPointList.h"
#include "primitives/derived_chart/HitObjectList.h"

namespace OsuAlgorithm
{

	// Count the number of OsuObjects in the offset range
	template<class OsuObjList>
	int countInRange(const OsuObjList &value,
		const double &lowerBound,
		const double &upperBound,
		const bool &inclusive = true) {
		int counter = 0;

		// We call the if outside of the for loop so that it doesn't keep checking the bool
		if (inclusive) {
			for (const auto &obj : value) {
				// We check if it's NOT inside the bounds since it's more plausible, we then INVERT it
				if (!(obj->offset() < lowerBound || obj->offset() > upperBound)) {
					counter += 1;
				}
			}
		}
		else {
			for (const auto &obj : value) {
				if (!(obj->offset() <= lowerBound || obj->offset() >= upperBound)) {
					counter += 1;
				}
			}
		}

		return counter;
	}

	// References countInRange and gets density
	template<class OsuObjList>
	double densityInRange(const OsuObjList &value,
		const double &lowerBound,
		const double &upperBound,
		const bool &inclusive = true) {
		return (countInRange(value, lowerBound, upperBound, inclusive) / (upperBound - lowerBound));
	}

	// Adjusts the whole TimingPointList so that it reaches the specified average SV
	template<class AdjustType>
	TimingPointList adjustToAverage(TimingPointList value,
		const int &index,
		const double &newAverage)
	{
		if (index == value.size() - 1) {
			std::cout << "adjustToAverage cannot adjust the last TimingPoint.";
			return TimingPointList();
		}
		else if (index < 0 || index >= value.size()) {
			std::cout << "adjustToAverage index is invalid";
			return TimingPointList();
		}

		// Distance: Offset * Value
		double curDistance = value.distance();
		double newDistance = newAverage * value.length();
		double netDistance = newDistance - curDistance;

		// We get the parameters of the index that wants to be adjusted
		double indexCurValue = value[index]->value();
		double indexCurLength = value.length(index);

		// Note that Net is the DIFFERENCE, New is the value we want to adjust to
		double indexNetValue = netDistance / indexCurLength;
		double indexNewValue = indexCurValue + indexNetValue;

		if (indexNewValue > AdjustType::maxBound() ||
			indexNewValue < AdjustType::minBound()) {
			std::cout << "Adjust out of bounds: " << indexNewValue << std::endl;
		}

		// Adjust to that value
		value[index]->setValue(indexNewValue);

		return value;
	}

	enum class SCALE_OPTIONS {
		MIN_OFFSET,
		MAX_OFFSET
	};

	// Scales ObjectList
	template<class OsuObjList>
	OsuObjList scale(OsuObjList value,
		const double &scaleFactor,
		const double &scaleReference) {

		auto v_offsetList = value.offsetList();
		std::for_each(v_offsetList.begin(),
			v_offsetList.end(),
			[&](double &offset) {
			offset -= scaleReference; // Zero the value according to reference
			offset *= scaleFactor; // Scale it
			offset += scaleReference;
		});
		value.setOffsetList(v_offsetList);
		return value;
	}

	template<class OsuObjList>
	OsuObjList scale(const OsuObjList &value,
		const double &scaleFactor,
		const SCALE_OPTIONS &scaleOption) {
		auto v_offsetList = value.offsetList();
		switch (scaleOption) {
		case SCALE_OPTIONS::MIN_OFFSET:
			return scale(value, scaleFactor, *std::min_element(v_offsetList.begin(), v_offsetList.end()));
		case SCALE_OPTIONS::MAX_OFFSET:
			return scale(value, scaleFactor, *std::max_element(v_offsetList.begin(), v_offsetList.end()));
		default:
			std::cout << "Unexpected Error.";
			return OsuObjList();
			break;
		}
	}

	// Moves List by an ms value
	template<class OsuObjList>
	OsuObjList moveBy(const OsuObjList &value,
		const double &moveFactor) {
		OsuObjList output = value;

		std::vector<double> v_offsetList = value.offsetList();
		std::for_each(v_offsetList.begin(), v_offsetList.end(),
			[&](double &offset) { offset += moveFactor; });
		output.setOffsetList(v_offsetList);

		return output;
	}

	// Moves List by an ms value
	template<class OsuObjList>
	OsuObjList moveTo(const OsuObjList &value,
		const double &moveReference,
		bool anchorOnStart = true) {
		// Anchor on start means that the whole pattern will START ON specified moveReference value
		// Anchor on end (!start) means it'll END ON specified moveReference value
		double moveFactor = 0;

		if (anchorOnStart) {
			moveFactor = moveReference - value.min();
		}
		else {
			moveFactor = moveReference - value.max();
		}

		return moveBy(value, moveFactor);
	}

	// Copy Objects from ObjList to other ObjList's offset
	template<class OsuObjList_From, class OsuObjList_To>
	OsuObjList_From copyTo(const OsuObjList_From &from,
		const OsuObjList_To &to,
		bool anchorOnStart = true) {

		OsuObjList_From output = {};

		std::vector<double> to_offsetList = {};
		to_offsetList = to.offsetList();

		for (int i = 0; i < to_offsetList.size(); i ++) {
			output.append(moveTo(from, to_offsetList[i], anchorOnStart).clone());
		}

		return output;
	}

	// Generate Stutter SVs in between offsets in OsuObjectList
	template<class ReturnType = SliderVelocity, class OsuObjList>
	TimingPointList stutter(const OsuObjList &value,
		double initialValue,
		double strength, // Strength indicates the offset of secValue (Secondary Value)
		double averageValue,
		double customValueMin = ReturnType::minBound(),
		double customValueMax = ReturnType::maxBound()) {
		if (strength < 0 || strength > 1.0) {
			std::cout << "stutterSV only allows strength values between 0 - 1.0";
			return TimingPointList();
		}

		const double MIN_VBOUND = customValueMin;
		const double MAX_VBOUND = customValueMax;

		// Clamp values
		initialValue = (initialValue < MIN_VBOUND) ? MIN_VBOUND : (initialValue > MAX_VBOUND) ? MAX_VBOUND : initialValue;
		averageValue = (averageValue < MIN_VBOUND) ? MIN_VBOUND : (averageValue > MAX_VBOUND) ? MAX_VBOUND : averageValue;

		/* DETAILS
		* START     INIT SV         SEC SV      END
		*     <|[////////////]|[//////////////]|>
		*  INIT OFFSET    SEC OFFSET       END OFFSET
		*
		* START       1                2        END
		*     <|[////////////]|[//////////////]|>
		*      1              2                3
		*
		* MINIMUM SV2 OFFSET CASE
		* START                2                END
		*     <|[/////////////////////////////]|>
		*      2                               3
		* OK : SV 2 = SV 3
		*
		* INCORRECT MAXIMUM SV2 OFFSET CASE
		* START                1                END
		*     <|[/////////////////////////////]|>
		*      1                               3
		* FAIL : SV 1 != SV 3
		*
		* CORRECTED MAXIMUM SV2 OFFSET CASE
		* START             1               2   END
		*     <|[///////////////////////]|[///]|>
		*      1                         2     3
		* OK : SV 1 + (SV 2 * MIN OR MAX) = SV 3
		*/

		ReturnType initTP = ReturnType(0, initialValue);
		ReturnType secTP = ReturnType();
		ReturnType endTP = ReturnType(1.0, averageValue);

		const double min_secOffset = 0.0; // Minimum will always be 0, see DETAILS
		double max_secOffset = 0.0;

		// We have a ternary to see which boundary would incite the maximum offset allowable
		max_secOffset = 1 - ((initialValue - averageValue) /
			(initialValue - (initialValue < averageValue ? MAX_VBOUND : MIN_VBOUND)));

		// Now we have the min and max offset of Secondary SV, we reference strength to find the offset
		secTP.setOffset((max_secOffset - min_secOffset) * strength);

		// Append into a TPList
		TimingPointList stutterRefList = {};
		stutterRefList.append(std::make_shared<ReturnType>(initTP));
		stutterRefList.append(std::make_shared<ReturnType>(secTP));
		stutterRefList.append(std::make_shared<ReturnType>(endTP));

		// Automatically find the appropriate value with adjustToAverage
		stutterRefList = adjustToAverage<ReturnType>(stutterRefList, 1, averageValue);

		// Create the output
		TimingPointList stutterList = {};
		std::vector<double> v_offsetList = value.unqOffsetList();
		double length = 0;

		// Note that we only access every index except the last
		for (int i = 0; i < v_offsetList.size() - 1; ++i) {
			// Length between the pair of offsets to use as reference
			length = v_offsetList[i + 1] - v_offsetList[i];

			// Init SV
			stutterList.append(std::make_shared<ReturnType>(ReturnType(v_offsetList[i],
				stutterRefList[0]->value())));

			// Secondary SV
			stutterList.append(std::make_shared<ReturnType>(ReturnType(v_offsetList[i] +
				length * stutterRefList[1]->offset(),
				stutterRefList[1]->value())));
		}

		stutterList.append(std::make_shared<ReturnType>(ReturnType(v_offsetList[v_offsetList.size() - 1],
			stutterRefList[2]->value())));

		return stutterList;
	}




}

#endif // OSUALGORITHM_H

