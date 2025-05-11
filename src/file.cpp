#include <filesystem>
#include <stdexcept>
namespace fs = std::filesystem;

class file{
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
    file(){
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


};
