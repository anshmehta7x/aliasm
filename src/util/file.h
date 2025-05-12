#ifndef ALIASM_UTIL_FILE_H
#define ALIASM_UTIL_FILE_H

#include <filesystem>
#include <stdexcept>
#include <vector>
#include <fstream>
#include <regex>
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

    bool searchRc(std::string filename){ // to find .zshrc or .bashrc
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

};

#endif // ALIASM_UTIL_FILE_H
