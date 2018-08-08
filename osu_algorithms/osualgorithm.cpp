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


TimingPointList OsuAlgorithm::supImp(TimingPointList base, const TimingPointList &factor, double (*fptr)(double, double)) {

    QList<double> base_vList = base.valueList();
    QList<double> fact_vList = factor.valueList();

    fact_vList.append(std::numeric_limits<double>::max());

    for (int b = 0, f = 0; (b < base_vList.length() && f < fact_vList.length() - 1);) {
        if (base_vList[b] < fact_vList[f]) { // f must always be behind b to factor correctly
            b ++;
            continue;
        }
        if (base_vList[b] > fact_vList[f + 1]) { // Index will never throw exceptions due to conditions
            f ++;
            continue;
        }
        base_vList[b] = fptr(base_vList[b], fact_vList[f]);


        b ++; // If factoring successful, we move b forward
    }

    base.setValueList(base_vList);
    return base;
}
