#include "osualgorithm.h"

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
