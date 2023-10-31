#pragma once

#include <string>
#include <filesystem>

namespace Utils {
	[[nodiscard]] std::string getFileContent(const std::filesystem::path& path);
}