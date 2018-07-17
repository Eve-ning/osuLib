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
int countInRange(const std::shared_ptr<OsuObjectList> &value,
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

// Scales ObjectList
void scale(std::shared_ptr<OsuObjectList> &value,
           const double &scaleFactor,
           const double &scaleReference);
void scale(std::shared_ptr<OsuObjectList> &value,
           const double &scaleFactor,
           const SCALE_OPTIONS &scaleOption);

// Moves List by an ms value
void moveBy(std::shared_ptr<OsuObjectList> &value, const
            double &moveFactor);

// Moves List by an ms value
void moveTo(TimingPointList &value,
            const double &moveFactor);
void moveTo(HitObjectList &value,
            const double &moveFactor);

}

#endif // OSUALGORITHM_H
