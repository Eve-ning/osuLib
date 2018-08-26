#include "stdafx.h"
#include "SpriteObject.h"

SpriteObject::SpriteObject(const std::string & filePath, LAYER layer, int x, int y, ORIGIN origin) : 
	m_filePath(filePath), m_layer(layer), m_x(x), m_y(y), m_origin(origin)
{
	// Checks if file provided is valid

	bool ENABLE_VALIDITY_CHECK = false;

	if (ENABLE_VALIDITY_CHECK) {
		std::ifstream f(filePath.c_str());
		if (!f.good()) {
			throw OsuException(OsuException::ID::INVALID_SPRITE_FILE);
		}
	}
}

SpriteObject::~SpriteObject()
{
}
