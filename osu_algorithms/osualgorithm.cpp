#include "osualgorithm.h"


int OsuAlgorithm::countInRange(const HitObjectList &value, const double &lowerBound, const double &upperBound, const bool &inclusive)
{
    int counter = 0;

    // We call the if outside of the for loop so that it doesn't keep checking the bool
    if (inclusive){
        for (const auto &obj : value) {
            // We check if it's NOT inside the bounds since it's more plausible, we then INVERT it
            if (!(obj->offset() < lowerBound || obj->offset() > upperBound)) {
                counter += 1;
            }
        }
    } else {
        for (const auto &obj : value) {
            if (!(obj->offset() <= lowerBound || obj->offset() >= upperBound)) {
                counter += 1;
            }
        }
    }

    return counter;
}

int OsuAlgorithm::countInRange(const TimingPointList &value, const double &lowerBound, const double &upperBound, const bool &inclusive)
{
    int counter = 0;

    // We call the if outside of the for loop so that it doesn't keep checking the bool
    if (inclusive){
        for (const auto &obj : value) {
            // We check if it's NOT inside the bounds since it's more plausible, we then INVERT it
            if (!(obj->offset() < lowerBound || obj->offset() > upperBound)) {
                counter += 1;
            }
        }
    } else {
        for (const auto &obj : value) {
            if (!(obj->offset() <= lowerBound || obj->offset() >= upperBound)) {
                counter += 1;
            }
        }
    }

    return counter;
}

void OsuAlgorithm::adjustToAverage(TimingPointList &value, const int &index, const double &newAverage)
{
    if (index == value.size() - 1) {
        qDebug() << "adjustToAverage cannot adjust the last TimingPoint.";
        return;
    } else if (index < 0 || index >= value.size()) {
        qDebug() << "adjustToAverage index is invalid";
        return;
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

    if (indexNewValue > SliderVelocity::maxBound() ||
        indexNewValue < SliderVelocity::minBound()) {
        qDebug () << "Adjust out of bounds: " << indexNewValue;
    }

    // Adjust to that value
    value[index]->setValue(indexNewValue);
}
