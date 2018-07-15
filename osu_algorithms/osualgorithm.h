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

// Get the average value for TimingPointList


// Adjusts the whole TimingPointList so that it reaches the specified average SV
void adjustToAverage(TimingPointList &value,
                     const int &index,
                     const double &newAverage);

}

#endif // OSUALGORITHM_H
