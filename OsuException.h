#pragma once
#include <iostream>

class OsuException : std::exception
{
public:

	enum class ID {
		INVALID_SPRITE_FILE,
		OOR_ADJUST_TO_AVERAGE,
		MISMATCH_SET_LENGTH,
		PARSE_FAIL
	};

	OsuException(ID id);
};

