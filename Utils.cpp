#include "Utils.h"

#include <fstream>

std::string Utils::getFileContent(const std::filesystem::path& path)
{
	std::fstream file(path.string());
	
	std::string content((std::istreambuf_iterator<char>(file)),
		(std::istreambuf_iterator<char>()));

	file.close();

	return content;
}
