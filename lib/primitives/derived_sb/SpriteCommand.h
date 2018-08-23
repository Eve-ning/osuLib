#pragma once
#include "../OsuObject.h"
class SpriteCommand : public OsuObject
{
public:

	//enum class CMDID {
	//	Fade,
	//	Move,
	//	Move_X,
	//	Move_Y,
	//	Scale,
	//	Scale_X,
	//	Scale_Y,
	//	Rotate,
	//	Color
	//};
	enum class EASING {
		Linear				,	// 0 - Linear: no easing
		Easing_Out			,	// 1 - Easing Out : the changes happen fast at first, but then slow down toward the end
		Easing_In			,	// 2 - Easing In : the changes happen slowly at first, but then speed up toward the end
		Quad_In				,	// 3 - Quad In
		Quad_Out			,	// 4 - Quad Out
		Quad_InOut			,	// 5 - Quad In / Out
		Cubic_In			,	// 6 - Cubic In
		Cubic_Out			,	// 7 - Cubic Out
		Cubic_InOut			,	// 8 - Cubic In / Out
		Quart_In			,	// 9 - Quart In
		Quart_Out			,	// 10 - Quart Out
		Quart_InOut			,	// 11 - Quart In / Out
		Quint_In			,	// 12 - Quint In
		Quint_Out			,	// 13 - Quint Out
		Quint_InOut			,	// 14 - Quint In / Out
		Sine_In				,	// 15 - Sine In
		Sine_Out			,	// 16 - Sine Out
		Sine_InOut			,	// 17 - Sine In / Out
		Expo_In				,	// 18 - Expo In
		Expo_Out			,	// 19 - Expo Out
		Expo_InOut			,	// 20 - Expo In / Out
		Circ_In				,	// 21 - Circ In
		Circ_Out			,	// 22 - Circ Out
		Circ_InOut			,	// 23 - Circ In / Out
		Elastic_In			,	// 24 - Elastic In
		Elastic_Out			,	// 25 - Elastic Out
		Elastic_HalfOut		,	// 26 - ElasticHalf Out
		Elastic_QuarterOut	,	// 27 - ElasticQuarter Out
		Elastic_InOut		,	// 28 - Elastic In / Out
		Back_In				,	// 29 - Back In
		Back_Out			,	// 30 - Back Out
		Back_InOut			,	// 31 - Back In / Out
		Bounce_In			,	// 32 - Bounce In
		Bounce_Out			,	// 33 - Bounce Out
		Bounce_InOut			// 34 - Bounce In / Out
	};

	SpriteCommand(EASING easing) : easing(easing) {}
	
	// Transforms class into working .osb command string
	virtual std::string toString() const {

		std::stringstream ss;
		std::string output = "";
		ss << "_" << CMDID() << "," <<
			(int)easing << "," <<
			m_startTime << "," <<
			m_endTime;
		
		for (double par : parameters()){
			ss << "," << par;
		}

		return ss.str();
	}

	double startTime() const { return m_startTime.value(); }
	double endTime() const { return m_endTime.value(); }

	void setStartTime(double value) { m_startTime.setValue(value); }
	void setEndTime(double value) { m_endTime.setValue(value); }

protected:

	virtual std::vector<double> parameters() const = 0;
	virtual char CMDID() const = 0;

	EASING easing = EASING::Linear;
	BoundedInt m_startTime = BoundedInt(0, 0);
	BoundedInt m_endTime = BoundedInt(0, 0);

};

namespace SCommand {
	// Impl of Fade Command
	class Fade : public SpriteCommand {
	public:

		Fade(double startF, double endF, EASING easing = EASING::Linear) :
			SpriteCommand(easing), m_startF(startF), m_endF(endF) {}

		double startF() const { return m_startF; }
		double endF() const { return m_endF; }

	private:
		std::vector<double> parameters() const {
			return std::vector<double>({ (double)m_startF.value(),
										 (double)m_endF.value() });
		}
		char CMDID() const { return 'F'; }

		BoundedInt m_startF = BoundedInt(1);
		BoundedInt m_endF = BoundedInt(1);
	};

	// Impl of Move Command (Single Axis Movement unavailable by design)
	class Move : public SpriteCommand {
	public:

		Move(double startX, double startY, double endX, double endY, EASING easing = EASING::Linear) :
			SpriteCommand(easing), m_startX(startX), m_startY(startY), m_endX(endX), m_endY(endY) {}

		double startX() const { return m_startX; }
		double startY() const { return m_startY; }
		double endX() const { return m_endX; }
		double endY() const { return m_endY; }

	private:
		std::vector<double> parameters() const {
			return std::vector<double>({ (double)m_startX.value(),
										 (double)m_startY.value(),
										 (double)m_endX.value(),
										 (double)m_endY.value() });
		}
		char CMDID() const { return 'M'; }

		BoundedInt m_startX = BoundedInt(320);
		BoundedInt m_startY = BoundedInt(240);
		BoundedInt m_endX = BoundedInt(320);
		BoundedInt m_endY = BoundedInt(240);
	};

	// Impl of Scale Command (Vector Integrated)
	class Scale : public SpriteCommand {
	public:

		// Constructor mimics Vector Scaling
		Scale(double startSX, double startSY, double endSX, double endSY, EASING easing = EASING::Linear) :
			SpriteCommand(easing), m_startSX(startSX), m_startSY(startSY), m_endSX(endSX), m_endSY(endSY) {}

		// Constructor mimics Normal Scaling (Fixed ratio)
		Scale(double startS, double endS, EASING easing = EASING::Linear) :
			SpriteCommand(easing), m_startSX(startS), m_startSY(startS), m_endSX(endS), m_endSY(endS) {}

		double startSX() const { return m_startSX; }
		double startSY() const { return m_startSY; }
		double endSX() const { return m_endSX; }
		double endSY() const { return m_endSY; }

	private:
		std::vector<double> parameters() const {
			return std::vector<double>({ (double)m_startSX.value(),
										 (double)m_startSY.value(),
										 (double)m_endSX.value(),
										 (double)m_endSY.value() });
		}
		char CMDID() const { return 'V'; }

		BoundedInt m_startSX = BoundedInt(1);
		BoundedInt m_startSY = BoundedInt(1);
		BoundedInt m_endSX = BoundedInt(1);
		BoundedInt m_endSY = BoundedInt(1);
	};

	// Impl of Rotate Command
	class Rotate : public SpriteCommand {
	public:

		Rotate(double startR, double endR, EASING easing = EASING::Linear) :
			SpriteCommand(easing), m_startR(startR), m_endR(endR) {}

		double startR() const { return m_startR; }
		double endR() const { return m_endR; }

	private:
		std::vector<double> parameters() const {
			return std::vector<double>({ (double)m_startR.value(),
										 (double)m_endR.value() });
		}
		char CMDID() const { return 'R'; }

		BoundedInt m_startR = BoundedInt(0);
		BoundedInt m_endR = BoundedInt(0);
	};

	// Impl of Color Command
	class Color : public SpriteCommand {
	public:

		// Constructor for full RGB Sequence
		Color(double startCR, double startCG, double startCB, double endCR, double endCG, double endCB, EASING easing = EASING::Linear) :
			SpriteCommand(easing), m_startCR(startCR), m_startCG(startCG), m_startCB(startCB), m_endCR(endCR), m_endCG(endCG), m_endCB(endCB) {}

		// Constructor for linear RGB Sequence
		Color(double startC, double endC, EASING easing = EASING::Linear) :
			SpriteCommand(easing), m_startCR(startC), m_startCG(startC), m_startCB(startC), m_endCR(endC), m_endCG(endC), m_endCB(endC) {}

		double startCR() const { return m_startCR; }
		double startCG() const { return m_startCG; }
		double startCB() const { return m_startCB; }
		double endCR() const { return m_endCR; }
		double endCG() const { return m_endCG; }
		double endCB() const { return m_endCB; }

	private:
		std::vector<double> parameters() const {
			return std::vector<double>({ (double)m_startCR.value(),
										 (double)m_startCG.value(),
										 (double)m_startCB.value(),
										 (double)m_endCR.value(),
										 (double)m_endCG.value(),
										 (double)m_endCB.value(), });
		}
		char CMDID() const { return 'C'; }

		BoundedInt m_startCR = BoundedInt(128, 0, 255);
		BoundedInt m_startCG = BoundedInt(128, 0, 255);
		BoundedInt m_startCB = BoundedInt(128, 0, 255);
		BoundedInt m_endCR = BoundedInt(128, 0, 255);
		BoundedInt m_endCG = BoundedInt(128, 0, 255);
		BoundedInt m_endCB = BoundedInt(128, 0, 255);
	};

	}