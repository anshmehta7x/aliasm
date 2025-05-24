#ifndef ALIASM_UTIL_FILE_H
#define ALIASM_UTIL_FILE_H

#include <string>
#include <vector>
#include <filesystem>
#include <utility>

class filemanager {
public:
    filemanager();

    bool searchRc(std::string filename);
    std::vector<std::pair<std::string, std::string>> getAliases(std::string filename);
    bool appendAlias(std::string filename, const std::string alias, const std::string command);
    bool updateAlias(std::string filename, const std::string& oldAlias, const std::string& newAlias, const std::string& command);
    bool removeAlias(std::string filename, const std::string& aliasToRemove);
    bool writeAliasesToFile(const std::string& directory, const std::vector<std::pair<std::string, std::string>>& aliases);

private:
    std::filesystem::path homeDir;
    std::filesystem::path getHome();
};

#endif
