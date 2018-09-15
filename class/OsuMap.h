#pragma once


class OsuMap
{
public:
	// Loads the map from file path
	OsuMap(const std::string &filePath);
	~OsuMap();

private:

	// Takes a stringstream and fills in the vector, breaks on specified tag
	void segmentFile(std::stringstream &ss, std::vector<std::string> &vectorToFill, const std::string &nextTag = "");

	// Converts a vector of string to a vector of specified class
	template <class T>
	std::vector<T> instStringVector(const std::vector<std::string> &vectorToConvert);
};

template<class T>
inline std::vector<T> OsuMap::instStringVector(const std::vector<std::string>& vectorToConvert)
{
	std::vector<T> instVector;

	for (const std::string &str : vectorToConvert) {
		instVector.push_back(T(str)); // Instantiate with string argument and push back into instVector
	}

	return instVector;
}
