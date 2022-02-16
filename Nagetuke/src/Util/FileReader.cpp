#include "FileReader.h"
#include <fstream>
#include <sstream>

/// <summary>
/// 文字列ファイルを改行位置で分割して、文字列vectorで返す
/// </summary>
/// <returns>vector</returns>
std::vector<std::string> FileReader::ReadLines(std::string& filePath)
{
	std::ifstream ifs(filePath);
	std::string line;
	std::vector<std::string> lines;
	while (getline(ifs, line)) {
		lines.push_back(line);
	}
	return lines;
}

/// <summary>
/// 1行の文字列を区切り文字列で分割して、文字列vectorで返す
/// </summary>
/// <param name="inputLineString">1行の文字列</param>
/// <param name="delimiter">区切り文字</param>
/// <returns>vector</returns>
std::vector<std::string> FileReader::Split(std::string& inputLineString, char delimiter)
{
	std::istringstream stream(inputLineString);//指定文字列を入力元とする
	std::string splitted;
	std::vector<std::string> result;
	while (getline(stream, splitted, delimiter)) {
		result.push_back(splitted);
	}
	return result;
}
