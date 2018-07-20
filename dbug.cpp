#include "dbug.h"

bool Dbug::debug_boundedInt() {
    BoundedInt a(1, 0, 10);
    BoundedInt b(2, 0, 10);

    // H: 11, R: 10
    a += 10; compareDebug(10, a); //  Max Bound

    // H: 6, R: 6
    a -= 5; compareDebug(6, a); // Value Check

    // H: -4, R: 0
    a -= 10; compareDebug(0, a); // Min Bound

    // H: 4, R: 4
    a += b * 4; compareDebug(4, a); // Check with another Bounded

    return true;
}

bool Dbug::debug_boundedDouble() {
    BoundedDouble a(1.0, 0.0, 10.0);
    BoundedDouble b(2.0, 0.0, 10.0);

    // H: 11, R: 10
    a += 10; compareDebug(10, a); //  Max Bound

    // H: 6.5, R: 6.5
    a -= 5.5; compareDebug(5.5, a); // Value Check

    // H: -4.5, R: 0
    a -= 10; compareDebug(0, a); // Min Bound

    // H: 3.5, R: 3.5
    a += b * 4; compareDebug(3.5, a); // Check with another Bounded

    return true;
}

bool Dbug::debug_hitObject()
{
    int keys = 4;

    DEBUGLABEL("Check loading of Normal Note String");
    QString HOStr = "448,192,18609,1,4,0:0:0:0:";

    std::shared_ptr<HitObject> loadFromString = HitObject::fromString(HOStr, keys);
    compareDebug(HOStr, loadFromString->toString(keys));

    DEBUGLABEL("Check loading via args");
    NormalNote NN = NormalNote(4, 100,
                               SampleSet::AUTO,
                               SampleSet::DRUM,
                               SampleSet::NORMAL,
                               1,
                               70,
                               "hitsound.wav");

    HOStr = "448,192,100,1,0,3:1:1:70:hitsound.wav";
    compareDebug(HOStr,NN.toString(keys));

    DEBUGLABEL("Check loading of Long Note String");
    HOStr = "64,192,20725,128,0,21734:0:0:0:0:";

    loadFromString = HitObject::fromString(HOStr, keys);
    compareDebug(HOStr, loadFromString->toString(keys));

    DEBUGLABEL("Check loading via args");
    LongNote LN = LongNote(4, 100,
                           SampleSet::AUTO,
                           SampleSet::DRUM,
                           SampleSet::NORMAL,
                           1,
                           70,
                           "hitsound.wav", 200);

    HOStr = "448,192,100,128,0,200:3:1:1:70:hitsound.wav";
    compareDebug(HOStr,LN.toString(keys));

    return true;
}

bool Dbug::debug_timingPoint()
{
    DEBUGLABEL("Check loading of SV");
    QString TPStr = "18610,-100,4,1,0,41,0,0";

    std::shared_ptr<TimingPoint> loadFromString = TimingPoint::fromString(TPStr);
    compareDebug(TPStr, loadFromString->toString());

    DEBUGLABEL("Check loading via args");
    SliderVelocity SV = SliderVelocity(100, 2.0, 4,
                                       SampleSet::NORMAL,
                                       2, 50, true);

    TPStr = "100,-50,4,1,2,50,0,1";
    compareDebug(TPStr,SV.toString());

    DEBUGLABEL("Check loading of BPM");
    TPStr = "18610,769.230769230769,4,1,0,41,1,0";

    loadFromString = TimingPoint::fromString(TPStr);
    compareDebug(TPStr, loadFromString->toString());

    DEBUGLABEL("Check loading via args");
    BPM BPM_ = BPM(100, 150, 4,
                   SampleSet::NORMAL,
                   2, 50, true);

    TPStr = "100,400,4,1,2,50,1,1";
    compareDebug(TPStr,BPM_.toString());

    return true;
}

bool Dbug::debug_hitObjectList()
{
    int keys = 4;

    DEBUGLABEL("Check loading from QStringList");
    QStringList HOListStr({"64,192,11528,1,0,0:0:0:0:",
                           "448,192,11528,1,0,0:0:0:0:",
                           "192,192,11700,1,0,0:0:0:0:",
                           "448,192,11873,1,0,0:0:0:0:",
                           "192,192,12045,1,0,0:0:0:0:"});

    HitObjectList loadFromString = HitObjectList(HOListStr, keys);
    compareDebug(HOListStr, loadFromString.toStringList(keys));


    return true;
}

bool Dbug::debug_timingPointList()
{
    DEBUGLABEL("Check loading from QStringList");
    QStringList TPListStr({"494,344.827586206897,4,1,1,5,1,0",
                           "55666,-100,4,1,1,5,0,1",
                           "77045,-100,4,1,1,5,0,0",
                           "121873,-100,4,1,1,5,0,1",
                           "143942,-100,4,1,1,5,0,0",
                           "188080,-100,4,1,1,5,0,1"});

    TimingPointList loadFromString = TimingPointList(TPListStr);
    compareDebug(TPListStr, loadFromString.toStringList());

    DEBUGLABEL("Check toBPM");
    TimingPointList BPM_Split = loadFromString.toBPM();
    compareDebug("494,344.827586206897,4,1,1,5,1,0", BPM_Split.toStringList()[0]);

    DEBUGLABEL("Check toSV");
    TimingPointList SV_Split = loadFromString.toSliderVelocity();
    compareDebug("55666,-100,4,1,1,5,0,1", SV_Split.toStringList()[0]);

    return true;
}

bool Dbug::debug_countInRange()
{
    DEBUGLABEL("HitObjectList Count");
    std::shared_ptr<HitObjectList> eg_HOList = std::make_shared<HitObjectList>(getEgHO());

    compareDebug(2301, OsuAlgorithm::countInRange<HitObject>(eg_HOList, 108639, 290322, true));

    /*int countInRange(const std::shared_ptr<OsuObjectList<T>> &value,
                 const double &lowerBound,
                 const double &upperBound,
                 const bool &inclusive = true);
                 */

    DEBUGLABEL("TimingPointList Count");
    TimingPointList eg_TPList = getEgTP();

    compareDebug(1001, OsuAlgorithm::countInRange<TimingPoint>(std::make_shared<TimingPointList>(eg_TPList), 74047, 327771));

    return true;
}

bool Dbug::debug_adjustToAverage()
{
    TimingPointList test = TimingPointList({"23945,-200,4,1,1,45,0,0",
                                            "23996,-166.666666666667,4,1,1,45,0,0",
                                            "24050,-142.857142857143,4,1,1,45,0,0",
                                            "24098,-125,4,1,1,45,0,0",
                                            "24149,-111.111111111111,4,1,1,45,0,0",
                                            "24200,-100,4,1,1,45,0,0",
                                            "24251,-90.9090909090909,4,1,1,45,0,0"});

    qDebug() << "BEFORE: " << test.average();
    OsuAlgorithm::adjustToAverage(test, 1, 0.6);
    compareDebug(0.6, test.average());

    qDebug() << "BEFORE: " << test.average();
    OsuAlgorithm::adjustToAverage(test, 4, 1.0);
    compareDebug(1.0, test.average());

    qDebug() << "BEFORE: " << test.average();
    OsuAlgorithm::adjustToAverage(test, 5, 1.8);
    compareDebug(1.8, test.average());

    return true;
}

bool Dbug::compareDebug(const double &expected, const double &given)
{
    qDebug() << (expected == given) << "\t| Expected: " << expected << " \t| Given: " << given;
    return expected == given;
}

bool Dbug::compareDebug(const QString &expected, const QString &given)
{
    qDebug() << (expected == given) << endl <<
                "Expected:" << expected << endl <<
                "Given:\t " << given << endl;
    return expected == given;
}

bool Dbug::compareDebug(const QStringList &expected, const QStringList &given)
{
    for (int i = 0; i < expected.length(); ++i) {
        qDebug() << (expected[i] == given[i]) << endl <<
                    "Expected:" << expected[i] << endl <<
                    "Given:\t " << given[i] << endl;
    }
    return expected == given;
}

TimingPointList Dbug::getEgTP() {
    QString proPath = "D:\\qtdoc\\osulib";
    TimingPointList eg_TPList;
    QString eg_TPFileName = "eg_timingPointList.txt";

    QFile eg_TPFile(proPath + "\\" + eg_TPFileName);
    if (!eg_TPFile.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug() << "Fail to open : " << (proPath + "\\" + eg_TPFileName);
    }

    while (!eg_TPFile.atEnd()){
        eg_TPList.append(TimingPoint::fromString(eg_TPFile.readLine()));
    };

    eg_TPFile.close();
    return eg_TPList;
}
HitObjectList Dbug::getEgHO() {
    QString proPath = "D:\\qtdoc\\osulib";
    HitObjectList eg_HOList;
    QString eg_HOFileName = "eg_hitObjectList.txt";

    QFile eg_HOFile(proPath + "\\" + eg_HOFileName);
    if (!eg_HOFile.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug() << "Fail to open : " << (proPath + "\\" + eg_HOFileName);
    }

    while (!eg_HOFile.atEnd()){
        eg_HOList.append(HitObject::fromString(eg_HOFile.readLine(), 7));
    };

    eg_HOFile.close();
    return eg_HOList;
}
