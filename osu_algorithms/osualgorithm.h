#ifndef OSUALGORITHM_H
#define OSUALGORITHM_H

#include "osu_primitives/hitobjectList.h"
#include "osu_primitives/timingpointlist.h"

namespace OsuAlgorithm
{

// Count the number of HitObjects in the offset range
//int countInRange(const HitObjectList &value,
//                 const double &lowerBound,
//                 const double &upperBound,
//                 const bool &inclusive = true);
// Count the number of TimingPoints in the offset range
template<class T>
int countInRange(const std::shared_ptr<OsuObjectList<T>> &value,
                 const double &lowerBound,
                 const double &upperBound,
                 const bool &inclusive = true) {
    int counter = 0;

    // We call the if outside of the for loop so that it doesn't keep checking the bool
    if (inclusive){
        for (const auto &obj : *value) {

            // We check if it's NOT inside the bounds since it's more plausible, we then INVERT it
            if (!(obj->offset() < lowerBound || obj->offset() > upperBound)) {
                counter += 1;
            }
        }
    } else {
        for (const auto &obj : *value) {
            if (!(obj->offset() <= lowerBound || obj->offset() >= upperBound)) {
                counter += 1;
            }
        }
    }

    return counter;
}

// Adjusts the whole TimingPointList so that it reaches the specified average SV
void adjustToAverage(TimingPointList &value,
                     const int &index,
                     const double &newAverage);

enum class SCALE_OPTIONS {
    MIN_OFFSET,
    MAX_OFFSET
};

// Scales ObjectList
template<class T>
void scale(OsuObjectList<T> &value,
           const double &scaleFactor,
           const double &scaleReference) {
    auto v_offsetList = value.offsetList();
    std::for_each(v_offsetList.begin(), v_offsetList.end(),
                  [&](double &offset) {
        offset -= scaleReference; // Zero the value according to reference
        offset *= scaleFactor; // Scale it
        offset += scaleReference;
    });
}

template<class T>
void scale(OsuObjectList<T> &value,
           const double &scaleFactor,
           const SCALE_OPTIONS &scaleOption){
    auto v_offsetList = value.offsetList();
    switch (scaleOption) {
    case SCALE_OPTIONS::MIN_OFFSET:
        scale(value, scaleFactor, *std::min_element(v_offsetList.begin(), v_offsetList.end()));
        return;
    case SCALE_OPTIONS::MAX_OFFSET:
        scale(value, scaleFactor, *std::max_element(v_offsetList.begin(), v_offsetList.end()));
        return;
    default:
        qDebug() << "Unexpected Error.";
        break;
    }
}

// Moves List by an ms value
template<class T>
void moveBy(OsuObjectList<T> &value, const
            double &moveFactor){
    auto v_offsetList = value.offsetList();
    std::for_each(v_offsetList.begin(), v_offsetList.end(),
                  [&](double &offset) { offset += moveFactor; });
}


// Moves List by an ms value
//void moveTo(TimingPointList &value,
//            const double &moveFactor);
//void moveTo(HitObjectList &value,
//            const double &moveFactor);

}

#endif // OSUALGORITHM_H
