#pragma once
#include <iostream>
#include <fstream>
#include "../../OsuException.h"

class SpriteObject
{
	enum class LAYER {
		Foreground,
		Background,
		Fail,
		Pass
	};

	enum class ORIGIN {
		TopLeft,
		TopCentre,
		TopRight,
		CentreLeft,
		Centre,
		CentreRight,
		BottomLeft,
		BottomCentre,
		BottomRight
	};
public:
	SpriteObject(const std::string &filePath, LAYER layer = LAYER::Foreground, int x = 320, int y = 240, ORIGIN origin = ORIGIN::TopLeft);
	~SpriteObject();

private:
	int x = 320;
	int y = 240;
	LAYER layer = LAYER::Foreground;
	std::string filePath = "";
	ORIGIN origin = ORIGIN::TopLeft;
};

