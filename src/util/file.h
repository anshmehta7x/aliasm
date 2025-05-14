#ifndef ALIASM_UTIL_FILE_H
#define ALIASM_UTIL_FILE_H

#include <filesystem>
#include <stdexcept>
#include <vector>
#include <fstream>
#include <regex>
#include <sstream>
namespace fs = std::filesystem;

class filemanager{
    private:
    fs::path homeDir;

    fs::path getHome(){
        const char* home = std::getenv("HOME");
        if(!home){
            std::runtime_error("No HOME directory found");
        }
        return home;
    }

    public:
    filemanager(){
        homeDir = getHome();
    }

    bool searchRc(std::string filename){
        bool found = false;
        for (const auto& entry : std::filesystem::directory_iterator(homeDir)) {
            if (entry.path().filename() == filename){
                return true;
            }
        }
        return false;
    }

    std::vector<std::pair<std::string, std::string>> getAliases(std::string filename){
        std::vector<std::pair<std::string, std::string>> aliases;
        std::ifstream file(homeDir / filename);
        if (!file)
            throw std::runtime_error("Could not open file: " + filename);

        const std::regex rx(R"(^\s*alias\s+([A-Za-z0-9_\-]+)\s*=\s*['"]([^'"]+)['"]\s*$)");
        std::string line;
        std::smatch m;

        while (std::getline(file, line)) {
            if (std::regex_match(line, m, rx))
                aliases.emplace_back(m[1].str(), m[2].str());
        }
        return aliases;
    }

    bool appendAlias(std::string filename, const std::string alias, const std::string command){
        std::ofstream file(homeDir / filename, std::ios::app);
        if (!file)
            return false;

        file << "alias " << alias << "=\"" << command << "\"" << std::endl;
        return true;
    }

    bool updateAlias(std::string filename, const std::string& oldAlias, const std::string& newAlias, const std::string& command) {
        std::ifstream file(homeDir / filename);
        if (!file)
            return false;

        std::stringstream buffer;
        std::string line;
        const std::regex rx(R"(^\s*alias\s+)" + oldAlias + R"(\s*=\s*['"]([^'"]+)['"]\s*$)");
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
};

#endif
