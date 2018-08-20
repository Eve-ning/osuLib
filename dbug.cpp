#include "stdafx.h"
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
	std::string HOStr = "448,192,18609,1,4,0:0:0:0:";

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
	compareDebug(HOStr, NN.toString(keys));

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
	compareDebug(HOStr, LN.toString(keys));

	return true;
}

bool Dbug::debug_timingPoint()
{
	DEBUGLABEL("Check loading of SV");
	std::string TPStr = "18610,-100,4,1,0,41,0,0";

	std::shared_ptr<TimingPoint> loadFromString = TimingPoint::fromString(TPStr);
	compareDebug(TPStr, loadFromString->toString());

	DEBUGLABEL("Check loading via args");
	SliderVelocity SV = SliderVelocity(100, 2.0, 4,
		SampleSet::NORMAL,
		2, 50, true);

	TPStr = "100,-50,4,1,2,50,0,1";
	compareDebug(TPStr, SV.toString());

	DEBUGLABEL("Check loading of BPM");
	TPStr = "18610,769.230769230769,4,1,0,41,1,0";

	loadFromString = TimingPoint::fromString(TPStr);
	compareDebug(TPStr, loadFromString->toString());

	DEBUGLABEL("Check loading via args");
	BPM BPM_ = BPM(100, 150, 4,
		SampleSet::NORMAL,
		2, 50, true);

	TPStr = "100,400,4,1,2,50,1,1";
	compareDebug(TPStr, BPM_.toString());

	return true;
}

bool Dbug::debug_hitObjectList()
{
	int keys = 4;

	DEBUGLABEL("Check loading from std::vector<std::string>");
	std::vector<std::string> HOListStr({ "64,192,11528,1,0,0:0:0:0:",
		"448,192,11528,1,0,0:0:0:0:",
		"192,192,11700,1,0,0:0:0:0:",
		"448,192,11873,1,0,0:0:0:0:",
		"192,192,12045,1,0,0:0:0:0:" });

	HitObjectList loadFromString = HitObjectList(HOListStr, keys);
	compareDebug(HOListStr, loadFromString.toStringList(keys));


	return true;
}

bool Dbug::debug_timingPointList()
{
	DEBUGLABEL("Check loading from std::vector<std::string>");
	std::vector<std::string> TPListStr({ "494,344.827586206897,4,1,1,5,1,0",
		"55666,-100,4,1,1,5,0,1",
		"77045,-100,4,1,1,5,0,0",
		"121873,-100,4,1,1,5,0,1",
		"143942,-100,4,1,1,5,0,0",
		"188080,-100,4,1,1,5,0,1" });

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
	HitObjectList eg_HOList = getEgHO();

	compareDebug(2301, OsuAlgorithm::countInRange(eg_HOList, 108639, 290322, true));

	/*int countInRange(const std::shared_ptr<OsuObjectList<T>> &value,
	const double &lowerBound,
	const double &upperBound,
	const bool &inclusive = true);
	*/

	DEBUGLABEL("TimingPointList Count");
	TimingPointList eg_TPList = getEgTP();

	compareDebug(1001, OsuAlgorithm::countInRange(eg_TPList, 74047, 327771));

	return true;
}

bool Dbug::debug_adjustToAverage()
{
	TimingPointList TPList = TimingPointList({ "23945,-200,4,1,1,45,0,0",
		"23996,-166.666666666667,4,1,1,45,0,0",
		"24050,-142.857142857143,4,1,1,45,0,0",
		"24098,-125,4,1,1,45,0,0",
		"24149,-111.111111111111,4,1,1,45,0,0",
		"24200,-100,4,1,1,45,0,0",
		"24251,-90.9090909090909,4,1,1,45,0,0" });

	std::cout << "BEFORE: " << TPList.average() << std::endl;
	TPList = OsuAlgorithm::adjustToAverage<SliderVelocity>(TPList, 1, 0.6);
	compareDebug(0.6, TPList.average());

	std::cout << "BEFORE: " << TPList.average() << std::endl;
	TPList = OsuAlgorithm::adjustToAverage<SliderVelocity>(TPList, 4, 1.0);
	compareDebug(1.0, TPList.average());

	std::cout << "BEFORE: " << TPList.average() << std::endl;
	TPList = OsuAlgorithm::adjustToAverage<SliderVelocity>(TPList, 5, 1.8);
	compareDebug(1.8, TPList.average());

	return true;
}

bool Dbug::debug_scale()
{
	TimingPointList eg_TPList = TimingPointList({ "0,-200,4,1,1,45,0,0",
		"100,-166.666666666667,4,1,1,45,0,0",
		"200,-142.857142857143,4,1,1,45,0,0" });
	TimingPointList comp_TPList = TimingPointList({ "0,-200,4,1,1,45,0,0",
		"200,-166.666666666667,4,1,1,45,0,0",
		"400,-142.857142857143,4,1,1,45,0,0" });

	eg_TPList = OsuAlgorithm::scale(eg_TPList, 2, 0);

	DEBUGLABEL("Scale");
	compareDebug(comp_TPList.toStringList(), eg_TPList.toStringList());

	return true;
}

bool Dbug::debug_moveBy()
{
	TimingPointList eg_TPList = TimingPointList({ "0,-200,4,1,1,45,0,0",
		"100,-166.666666666667,4,1,1,45,0,0",
		"200,-142.857142857143,4,1,1,45,0,0" });
	TimingPointList comp_TPList = TimingPointList({ "100,-200,4,1,1,45,0,0",
		"200,-166.666666666667,4,1,1,45,0,0",
		"300,-142.857142857143,4,1,1,45,0,0" });

	eg_TPList = OsuAlgorithm::moveBy(eg_TPList, 100);

	DEBUGLABEL("Move By");
	compareDebug(comp_TPList.toStringList(), eg_TPList.toStringList());

	return true;
}

bool Dbug::debug_moveTo()
{
	TimingPointList eg_TPList = TimingPointList({ "0,-200,4,1,1,45,0,0",
		"100,-166.666666666667,4,1,1,45,0,0",
		"200,-142.857142857143,4,1,1,45,0,0" });
	TimingPointList comp_TPList = TimingPointList({ "200,-200,4,1,1,45,0,0",
		"300,-166.666666666667,4,1,1,45,0,0",
		"400,-142.857142857143,4,1,1,45,0,0" });

	eg_TPList = OsuAlgorithm::moveTo(eg_TPList, 200, true);

	DEBUGLABEL("Move To (Anchor Start)");
	compareDebug(comp_TPList.toStringList(), eg_TPList.toStringList());

	comp_TPList = TimingPointList({ "300,-200,4,1,1,45,0,0",
		"400,-166.666666666667,4,1,1,45,0,0",
		"500,-142.857142857143,4,1,1,45,0,0" });

	eg_TPList = OsuAlgorithm::moveTo(eg_TPList, 500, false);

	DEBUGLABEL("Move To (Anchor End)");
	compareDebug(comp_TPList.toStringList(), eg_TPList.toStringList());

	return true;
}

bool Dbug::debug_normalize()
{
	TimingPointList eg_TPList = TimingPointList({ "0,600,4,1,1,45,1,0",     // BPM: 100
		"100,150,4,1,1,45,1,0",   // BPM: 400
		"200,300,4,1,1,45,1,0" }); // BPM: 200

	TimingPointList test = eg_TPList.normalize(200);

	DEBUGLABEL("Normalize");
	compareDebug(std::vector<double>({ 2.0, 0.5, 1.0 }), test.valueList());

	return true;
}

bool Dbug::debug_stutter()
{
	//    TimingPointList eg_TPList = TimingPointList({"0,-200,4,1,1,45,0,0",
	//                                                 "100,-166,4,1,1,45,0,0"});

	//    TimingPointList test = OsuAlgorithm::stutterSV(eg_TPList, 0.5, 1.0, 1.0);

	HitObjectList eg_HOList = HitObjectList("00:00:000 (0|1,100|1,400|1) - ");
	TimingPointList test = OsuAlgorithm::stutter<BPM>(eg_HOList, 0.5, 1.0, 1.0, BPM::minBound(), 100000);

	DEBUGLABEL("StutterSV");
	printStringList(test.toStringList());

	return true;
}

bool Dbug::debug_copyTo()
{
	TimingPointList TPList = TimingPointList(std::vector<std::string>({ "0,-200,4,1,1,45,0,0",
																		"100,-166,4,1,1,45,0,0" }));

	HitObjectList HOList = HitObjectList("00:01:000 (1000|1,2000|1) - ");
	//	HitObjectList HOList = HitObjectList(std::vector<std::string>({ "192,192,197406,1,0,0:0:0:0:",
	// "448,192,197504,1,0,0:0:0:0:"
	// }), 4);

	TPList = OsuAlgorithm::copyTo(TPList, HOList, true);

	printStringList(TPList.toStringList());

	return true;
}

bool Dbug::debug_supImp()
{
	TimingPointList factTP = TimingPointList({ "0,-200,4,1,1,45,0,0" });

	TimingPointList baseTP = TimingPointList(std::vector<std::string>({ "100,-200,4,1,1,45,0,0",
																		"200,-50,4,1,1,45,0,0" }));

	baseTP.superimpose(factTP, [](double base, double fact) -> double {
		return base + fact;
	});

	printStringList(baseTP.toStringList());

	return true;
}

// -------------------- HELPER FUNCTIONS --------------------

bool Dbug::compareDebug(const double &expected, const double &given)
{
	std::cout << (expected == given) << "\t| Expected: " << expected << " \t| Given: " << given << std::endl;
	return expected == given;
}

bool Dbug::compareDebug(const std::string &expected, const std::string &given)
{
	std::cout << (expected == given) << std::endl <<
		"Expected:" << expected << std::endl <<
		"Given:\t " << given << std::endl;
	return expected == given;
}

bool Dbug::compareDebug(const std::vector<std::string> &expected, const std::vector<std::string> &given)
{
	for (int i = 0; i < expected.size(); ++i) {
		std::cout << (expected[i] == given[i]) << std::endl <<
			"Expected:" << expected[i] << std::endl <<
			"Given:\t " << given[i] << std::endl;
	}
	return expected == given;
}

TimingPointList Dbug::getEgTP() {
	std::string proPath = "D:\\qtdoc\\osulib";
	TimingPointList eg_TPList;
	std::string eg_TPFileName = "eg_timingPointList.txt";

	using namespace std;

	ifstream eg_TPFile;
	eg_TPFile.open(proPath + "\\" + eg_TPFileName);

	if (!eg_TPFile.is_open()) {
		std::cout << "Fail to open : " << (proPath + "\\" + eg_TPFileName);
	}

	std::string line;

	while (getline(eg_TPFile, line))
	{
		eg_TPList.append(TimingPoint::fromString(line));
	}

	eg_TPFile.close();
	return eg_TPList;
}
HitObjectList Dbug::getEgHO() {
	std::string proPath = "D:\\qtdoc\\osulib";
	HitObjectList eg_HOList;
	std::string eg_HOFileName = "eg_hitObjectList.txt";

	using namespace std;

	ifstream eg_HOFile;
	eg_HOFile.open(proPath + "\\" + eg_HOFileName);

	if (!eg_HOFile.is_open()) {
		std::cout << "Fail to open : " << (proPath + "\\" + eg_HOFileName);
	}

	std::string line;
	int keys = 4;

	while (getline(eg_HOFile, line))
	{
		eg_HOList.append(HitObject::fromString(line,keys));
	}

	eg_HOFile.close();
	return eg_HOList;
}

