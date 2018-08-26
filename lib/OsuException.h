#pragma once
#include <iostream>
#include <vector>
#include <boost/tuple/tuple.hpp>

class OsuException : std::exception
{
public:

	enum class ID {
		INVALID_SPRITE_FILE,
		INVALID_MAP_FILE,
		OOR_ADJUST_TO_AVERAGE,
		MISMATCH_SET_LENGTH,
		PARSE_FAIL
	};

	char const* what() const override {
		return IDWhat.at((int)id).get<1>().c_str();
	}

	OsuException(ID id) : id(id) {

	}
private:
	std::vector<boost::tuple<ID, std::string>> IDWhat = {
	{ ID::INVALID_SPRITE_FILE, "Sprite File specified does not exist." },
	{ ID::INVALID_MAP_FILE, "Map File specified does not exist." },
	{ ID::OOR_ADJUST_TO_AVERAGE, "Adjust to Average Function failed to adjust to correct value. The value is bounded." },
	{ ID::MISMATCH_SET_LENGTH, "The vector you tried to set to has a different length."},
	{ ID::PARSE_FAIL, "The string passed did not parse correctly."}
	};

	ID id;

};

