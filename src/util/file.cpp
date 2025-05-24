#include "file.h"
#include <filesystem>
#include <stdexcept>
#include <fstream>
#include <regex>
#include <sstream>
#include <cstdlib>

namespace fs = std::filesystem;

filemanager::filemanager() {
    homeDir = getHome();
}

fs::path filemanager::getHome() {
    const char* home = std::getenv("HOME");
    if (!home) {
        throw std::runtime_error("No HOME directory found");
    }
    return home;
}

bool filemanager::searchRc(std::string filename) {
    for (const auto& entry : fs::directory_iterator(homeDir)) {
        if (entry.path().filename() == filename) {
            return true;
        }
    }
    return false;
}

std::vector<std::pair<std::string, std::string>> filemanager::getAliases(std::string filename) {
    std::vector<std::pair<std::string, std::string>> aliases;
    std::ifstream file(homeDir / filename);
    if (!file)
        throw std::runtime_error("Could not open file: " + filename);

    const std::regex rx(R"(^\s*alias\s+([A-Za-z0-9_\-]+)\s*=\s*(['\"])(.*)\2\s*$)");
    std::string line;
    std::smatch m;

    while (std::getline(file, line)) {
        if (std::regex_match(line, m, rx))
            aliases.emplace_back(m[1].str(), m[3].str());
    }
    return aliases;
}

bool filemanager::appendAlias(std::string filename, const std::string alias, const std::string command) {
    std::ofstream file(homeDir / filename, std::ios::app);
    if (!file)
        return false;

    file << "alias " << alias << "=\"" << command << "\"" << std::endl;
    return true;
}

bool filemanager::updateAlias(std::string filename, const std::string& oldAlias, const std::string& newAlias, const std::string& command) {
    std::ifstream file(homeDir / filename);
    if (!file)
        return false;

    std::stringstream buffer;
    std::string line;
    const std::regex rx("^\\s*alias\\s+" + oldAlias + "\\s*=\\s*(['\"])(.*)\\1\\s*$");
    bool found = false;

    while (std::getline(file, line)) {
        std::smatch m;
        if (std::regex_match(line, m, rx)) {
            buffer << "alias " << newAlias << "=\"" << command << "\"" << std::endl;
            found = true;
        } else {
            buffer << line << std::endl;
        }
    }
    file.close();

    if (!found)
        return false;

    std::ofstream outfile(homeDir / filename, std::ios::trunc);
    if (!outfile)
        return false;

    outfile << buffer.str();
    return true;
}

bool filemanager::removeAlias(std::string filename, const std::string& aliasToRemove) {
    std::ifstream file(homeDir / filename);
    if (!file)
        return false;

    std::stringstream buffer;
    std::string line;
    const std::regex rx("^\\s*alias\\s+" + aliasToRemove + "\\s*=\\s*(['\"])(.*)\\1\\s*$");
    bool found = false;

    while (std::getline(file, line)) {
        std::smatch m;
        if (std::regex_match(line, m, rx)) {
            found = true;
            continue; // skip
        } else {
            buffer << line << std::endl;
        }
    }
    file.close();

    if (!found)
        return false;

    std::ofstream outfile(homeDir / filename, std::ios::trunc);
    if (!outfile)
        return false;

    outfile << buffer.str();
    return true;
}


bool filemanager::writeAliasesToFile(const std::string& directory, const std::vector<std::pair<std::string, std::string>>& aliases) {
    std::ofstream outfile(fs::path(directory) / "exported-aliases");
    if (!outfile)
        return false;

    for (const auto& [alias, command] : aliases) {
        outfile << alias << "=\"" << command <<"\""<< std::endl;
    }

    return true;
}
