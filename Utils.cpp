#include "Utils.h"

#include <fstream>
#include <iostream>

std::string Utils::getFileContent(const std::filesystem::path& path)
{
	std::fstream file(path.string());
	
	if (!file.is_open())
		std::cerr << "File is not open" << std::endl;

	std::string content((std::istreambuf_iterator<char>(file)),
		(std::istreambuf_iterator<char>()));

	file.close();

	return content;
}
