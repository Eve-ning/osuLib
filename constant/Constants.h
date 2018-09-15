#pragma once

class Osu {
public:

	enum class MODE
	{
		STANDARD,
		TAIKO,
		CATCH,
		MANIA
	};
    enum class SAMPLESET {
		AUTO,
		SOFT,
		NORMAL,
		DRUM
	};

	// These are all bitwise (base 2)
	enum class HITSOUNDS {
		WHISTLE = 2,
		FINISH = 4,
		CLAP = 8
	};
	
	// Converts String (case insensitive) to SAMPLESET
	static SAMPLESET samplesetFromString(std::string str) {
		std::transform(str.begin(), str.end(), str.begin(), ::toupper);
		
		if (str == "AUTO" || str == "NONE") {
			return SAMPLESET::AUTO;
		}
		else if (str == "SOFT")
		{
			return SAMPLESET::SOFT;
		}
		else if (str == "NORMAL")
		{
			return SAMPLESET::NORMAL;
		}
		else if (str == "DRUM")
		{
			return SAMPLESET::DRUM;
		}
		else
		{
			throw new std::exception(std::string("Failed to convert String to SAMPLESET: " + str).c_str());
		}
	}

	// Converts SAMPLESET to String (Uppercase)
	static std::string stringFromSample(SAMPLESET sample) {

		switch (sample)
		{
		case SAMPLESET::AUTO:
			return "AUTO";
		case SAMPLESET::SOFT:
			return "SOFT";
		case SAMPLESET::NORMAL:
			return "NORMAL";
		case SAMPLESET::DRUM:
			return "DRUM";
		default:
			throw new std::exception(std::string("Failed to convert SAMPLESET to String").c_str());
			break;
		}

	}

	// Converts String (case insensitive) to MODE
	static MODE modeFromString(std::string str) {
		std::transform(str.begin(), str.end(), str.begin(), ::toupper);

		if (str == "STANDARD") {
			return MODE::STANDARD;
		}
		else if (str == "TAIKO")
		{
			return MODE::TAIKO;
		}
		else if (str == "CATCH")
		{
			return MODE::CATCH;
		}
		else if (str == "MANIA")
		{
			return MODE::MANIA;
		}
		else
		{
			throw new std::exception(std::string("Failed to convert String to MODE: " + str).c_str());
		}
	}

	// Converts MODE to String (Uppercase)
	static std::string stringFromMode(MODE sample) {

		switch (sample)
		{
		case MODE::STANDARD:
			return "STANDARD";
		case MODE::TAIKO:
			return "TAIKO";
		case MODE::CATCH:
			return "CATCH";
		case MODE::MANIA:
			return "MANIA";
		default:
			throw new std::exception(std::string("Failed to convert MODE to String").c_str());
			break;
		}

	}

};