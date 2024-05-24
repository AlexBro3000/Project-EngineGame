#pragma once

#include <string>

class Directory
{
private:
    std::string path_to_directory;

public:
    Directory();
    Directory(const std::string& path, const std::string& directory);
    ~Directory();

    std::string get(const std::string& file) const;
    std::string get() const;

    bool empty() const;

private:

};