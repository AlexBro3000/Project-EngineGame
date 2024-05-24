#include "Directory.h"

#include <algorithm>
#include <filesystem>

Directory::Directory()
{
	path_to_directory = std::string();
}

Directory::Directory(const std::string& path, const std::string& directory)
{
	if (!directory.empty()) {
		path_to_directory = path + ((directory[0] == '/' || directory[0] == '\\') ? directory : "\\" + directory);
	}
	else {
		path_to_directory = path;
	}
	std::replace(path_to_directory.begin(), path_to_directory.end(), '/', '\\');
}

Directory::~Directory()
{ }

std::string Directory::get(const std::string& file) const
{
	std::string path = path_to_directory + "\\" + file;
	std::replace(path.begin(), path.end(), '/', '\\');
	return path;
}

std::string Directory::get() const
{
	return path_to_directory;
}

bool Directory::empty() const
{
	if (!path_to_directory.empty()) {
		std::string path = get();
		return std::filesystem::is_empty(path);
	}
	else {
		return true;
	}
}
// // Проходим по всем файлам в директории
//  for (const auto& entry : fs::directory_iterator(directoryPath)) {
//      std::cout << entry.path().filename() << std::endl; // Выводим названия файлов
//  }