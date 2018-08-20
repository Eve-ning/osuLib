#include "stdafx.h"
#include "SpriteObject.h"

SpriteObject::SpriteObject(const std::string & filePath, LAYER layer, int x, int y, ORIGIN origin) : 
	layer(layer), x(x), y(y), origin(origin)
{
	std::ifstream f(filePath.c_str());
	if (f.good()) {
		throw 1;
	}
}

SpriteObject::~SpriteObject()
{
}
