#ifndef OSUALGORITHM_H
#define OSUALGORITHM_H

#include "osu_primitives/hitobjectList.h"
#include "osu_primitives/timingpointlist.h"

namespace OsuAlgorithm
{

// Count the number of OsuObjects in the offset range
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
template<class AdjustType>
TimingPointList adjustToAverage(const TimingPointList &value,
                                const int &index,
                                const double &newAverage)
{
    if (index == value.size() - 1) {
        qDebug() << "adjustToAverage cannot adjust the last TimingPoint.";
        return TimingPointList();
    } else if (index < 0 || index >= value.size()) {
        qDebug() << "adjustToAverage index is invalid";
        return TimingPointList();
    }

    TimingPointList c_value = value;

    // Distance: Offset * Value
    double curDistance = c_value.distance();
    double newDistance = newAverage * c_value.length();
    double netDistance = newDistance - curDistance;

    // We get the parameters of the index that wants to be adjusted
    double indexCurValue = c_value[index]->value();
    double indexCurLength = c_value.length(index);

    // Note that Net is the DIFFERENCE, New is the value we want to adjust to
    double indexNetValue = netDistance / indexCurLength;
    double indexNewValue = indexCurValue + indexNetValue;

    if (indexNewValue > AdjustType::maxBound() ||
        indexNewValue < AdjustType::minBound()) {
        qDebug () << "Adjust out of bounds: " << indexNewValue;
    }

    // Adjust to that value
    c_value[index]->setValue(indexNewValue);

    return c_value;
}

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
    std::for_each(v_offsetList.begin(),
                  v_offsetList.end(),
                  [&](double &offset) {
        offset -= scaleReference; // Zero the value according to reference
        offset *= scaleFactor; // Scale it
        offset += scaleReference;
    });
    value.setOffsetList(v_offsetList);
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
void moveBy(OsuObjectList<T> &value,
            const double &moveFactor){
    auto v_offsetList = value.offsetList();
    std::for_each(v_offsetList.begin(), v_offsetList.end(),
                  [&](double &offset) { offset += moveFactor; });
    value.setOffsetList(v_offsetList);
}

// Moves List by an ms value
template<class T>
void moveTo(OsuObjectList<T> &value,
            const double &moveReference,
            bool anchorOnStart = true){
    // Anchor on start means that the whole pattern will START ON specified moveReference value
    // Anchor on end (!start) means it'll END ON specified moveReference value
    double moveFactor = 0;

    if (anchorOnStart) {
        moveFactor = moveReference - value.min();
    } else {
        moveFactor = moveReference - value.max();
    }

    moveBy(value, moveFactor);
}

// Generate Normalize SVs
TimingPointList normalize(const TimingPointList &value, const double &referenceBPM);

// Get Unique Offset List
template<class T>
QList<double> unqOffsetList(const OsuObjectList<T> &value) {
    QList<double> v_offsetList = value.offsetList();
    QList<double> unq_offsetList = {};

    std::for_each(v_offsetList.begin(), v_offsetList.end(), [&](double &offset) {
        if (unq_offsetList.indexOf(offset) < 0) {
            unq_offsetList.append(offset);
        }
    });

    return unq_offsetList;
}

// Convert Editor HitObject to HitObjectList
HitObjectList readEHO(const QString &value);

// Generate Stutter SVs in between offsets in OsuObjectList
template<class ReturnType = SliderVelocity, class T>
TimingPointList stutter(const OsuObjectList<T> &value,
                        double initialValue,
                        double strength, // Strength indicates the offset of secValue (Secondary Value)
                        double averageValue,
                        double customValueMin = ReturnType::minBound(),
                        double customValueMax = ReturnType::maxBound()) {
    if (strength < 0 || strength > 1.0) {
        qDebug() << "stutterSV only allows strength values between 0 - 1.0";
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
    QList<double> v_offsetList = unqOffsetList(value);
    double length = 0;

    // Note that we only access every index except the last
    for (int i = 0; i < v_offsetList.size() - 1; ++ i) {
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
