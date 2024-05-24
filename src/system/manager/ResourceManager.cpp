#include "ResourceManager.h"

#include "../../system/manager/Directory.h"
#include "../../graphic/shader/ShaderProgram.h"
#include "../console/Console.h"
#include <algorithm>
#include <fstream>
#include <filesystem>

ResourceManager::DirectoryMap		ResourceManager::directories;
ResourceManager::ShaderProgramMap	ResourceManager::shader_programs;

void ResourceManager::Init(int argc, char** argv)
{
	std::string path = getLaunchDirectory(argv[0]);

	ResourceManager::Directory::load("RES", path + "\\res", true);
	ResourceManager::Directory::load("Shader", "RES", "shader", true);
}

void ResourceManager::Terminate()
{
	directories.clear();
	shader_programs.clear();
}

std::string ResourceManager::getLaunchDirectory(const std::string& path)
{
	size_t found = path.find_last_of("/\\");
	return path.substr(0, found);
}

::Directory& ResourceManager::Directory::load(const std::string& name, const std::string& parent_name, const std::string& path, bool is_create)
{
	auto it = directories.find(name);
	if (it == directories.end()) {
		std::shared_ptr<::Directory> directory = nullptr;

		if (!parent_name.empty()) {
			it = directories.find(parent_name);
			if (it != directories.end()) {
				directory = std::make_shared<::Directory>(it->second->get(), path);
			}
		}
		else {
			Console::Warn("Directory not found:", parent_name.c_str());
			directory = std::make_shared<::Directory>(path, "");
		}

		if (directory) {
			ResourceManager::directories.emplace(name, directory);

			std::string path = directory->get();
			if (is_create && !std::filesystem::exists(path)) {
				std::filesystem::create_directory(path);
				Console::Info("Creating a new directory.", path.c_str());
			}
			return *directory;
		}
		else {
			Console::Error("Directory not found:", parent_name.c_str());
			throw std::runtime_error("Directory not found");
		}
	}
	else {
		Console::Warn("The directory already exists:", name.c_str());
		return *(it->second);
	}
}

::Directory& ResourceManager::Directory::load(const std::string& name, const std::string& path, bool is_create)
{
	auto it = directories.find(name);
	if (it == directories.end()) {
		std::shared_ptr<::Directory> directory = std::make_shared<::Directory>(path, "");
		ResourceManager::directories.emplace(name, directory);

		std::string path = directory->get();
		if (is_create && !std::filesystem::exists(path)) {
			std::filesystem::create_directory(path);
			Console::Info("Creating a new directory.", path.c_str());
		}
		return *directory;
	}
	else {
		Console::Warn("The directory already exists:", name.c_str());
		return *(it->second);
	}
}

void ResourceManager::Directory::unload(const std::string& name)
{
	directories.erase(name);
}

::Directory& ResourceManager::Directory::get(const std::string& name)
{
	auto it = directories.find(name);
	if (it != directories.end()) {
		return *(it->second);
	}
	else {
		Console::Error("Directory not found:", name.c_str());
		throw std::runtime_error("Directory not found");
	}
}

::ShaderProgram& ResourceManager::ShaderProgram::load(const std::string& name, const std::string& path_vert, const std::string& path_frag)
{
	auto it = shader_programs.find(name);
	if (it == shader_programs.end()) {
		std::string file_vert = ResourceManager::Directory::get("Shader").get(path_vert);
		std::string file_frag = ResourceManager::Directory::get("Shader").get(path_frag);

		std::shared_ptr<::ShaderProgram> shader_program = std::make_shared<::ShaderProgram>(file_vert, file_frag);
		ResourceManager::shader_programs.emplace(name, shader_program);

		return *shader_program;
	}
	else {
		Console::Warn("Shader program already exists:", name.c_str());
		return *(it->second);
	}
}

void ResourceManager::ShaderProgram::unload(const std::string& name)
{
	shader_programs.erase(name);
}

::ShaderProgram& ResourceManager::ShaderProgram::get(const std::string& name)
{
	auto it = shader_programs.find(name);
	if (it != shader_programs.end()) {
		return *(it->second);
	}
	else {
		Console::Error("Shader program  not found:", name.c_str());
		throw std::runtime_error("Shader program not found");
	}
}