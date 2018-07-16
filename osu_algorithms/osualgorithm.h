#ifndef OSUALGORITHM_H
#define OSUALGORITHM_H

#include "osu_primitives/hitobjectList.h"
#include "osu_primitives/timingpointlist.h"

namespace OsuAlgorithm
{

// Count the number of HitObjects in the offset range
int countInRange(const HitObjectList &value,
                 const double &lowerBound,
                 const double &upperBound,
                 const bool &inclusive = true);
// Count the number of TimingPoints in the offset range
int countInRange(const TimingPointList &value,
                 const double &lowerBound,
                 const double &upperBound,
                 const bool &inclusive = true);

// Adjusts the whole TimingPointList so that it reaches the specified average SV
void adjustToAverage(TimingPointList &value,
                     const int &index,
                     const double &newAverage);

enum class SCALE_OPTIONS {
    MIN_OFFSET,
    MAX_OFFSET
};
// Scales TimingPointList
void scale(TimingPointList &value,
           const double &scaleFactor,
           const double &scaleReference);
void scale(TimingPointList &value,
           const double &scaleFactor,
           const SCALE_OPTIONS &scaleOption);

// Scales HitObjectList
void scale(HitObjectList &value,
           const double &scaleFactor,
           const double &scaleReference);
void scale(HitObjectList &value,
           const double &scaleFactor,
           const SCALE_OPTIONS &scaleOption);

void move(TimingPointList &value,
          const double &moveFactor,
          const SCALE_OPTIONS &scaleOption);
void move(HitObjectList &value,
          const double &moveFactor,
          const SCALE_OPTIONS &scaleOption);

}

#endif // OSUALGORITHM_H
