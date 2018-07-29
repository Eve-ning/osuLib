#include "osualgorithm.h"



TimingPointList OsuAlgorithm::normalize(const TimingPointList &value,
                                        const double &referenceBPM){
    TimingPointList c_value = value;
    c_value = c_value.toBPM();

    if (c_value.size() == 0) {
        qDebug() << "Normalize called with no BPM.";
        return TimingPointList();
    }

    TimingPointList normalizeList = {};

    std::for_each(c_value.begin(), c_value.end(), [&](auto &TP){
        std::shared_ptr<TimingPoint> test =
                std::make_shared<SliderVelocity>(SliderVelocity(TP->offset(), referenceBPM / TP->value()));
        normalizeList.append(test);
    });

    return normalizeList;
}

HitObjectList OsuAlgorithm::readEHO(const QString &value)
{
    QString rValue = value;
    QTextStream ts(&rValue);

    char delim;

    // Find the open bracket
    while (delim != '(' && !ts.atEnd()) {
        ts >> delim;
    }

    double offset = 0;
    double column = 0;

    HitObjectList HOList = {};

    while (!ts.atEnd()) {
        ts >> offset >> delim >> column >> delim;
        HOList.append(std::make_shared<NormalNote>(NormalNote(column, offset)));
        if (delim == ')') {
            break;
        }
    }

    return HOList;
}

