#pragma once
#include <string>
#include <vector>

class FileReader
{
private:
	FileReader() = delete;
	‾FileReader() = delete;
public:
	static std::vector<std::string> ReadLines(std::string& filePath);
	static std::vector<std::string> Split(std::string& inputLineString, char delimiter);
};

