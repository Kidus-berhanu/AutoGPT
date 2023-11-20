#include <iostream>
#include <string>
#include <filesystem>
#include <vector>

namespace fs = std::filesystem;

class FileExplorer {
    fs::path currentPath;

public:
    FileExplorer() : currentPath(fs::current_path()) {}

    void listFiles() const {
        std::cout << "Listing files in: " << currentPath << std::endl;
        for (const auto& entry : fs::directory_iterator(currentPath)) {
            std::cout << (entry.is_directory() ? "[DIR] " : "[FILE] ") << entry.path().filename() << std::endl;
        }
    }

    void changeDirectory(const std::string& dirName) {
        fs::path newPath = currentPath / dirName;
        if (fs::exists(newPath) && fs::is_directory(newPath)) {
            currentPath = newPath;
            std::cout << "Changed directory to: " << currentPath << std::endl;
        } else {
            std::cout << "Directory not found: " << newPath << std::endl;
        }
    }

    void goUp() {
        if (currentPath.has_parent_path()) {
            currentPath = currentPath.parent_path();
            std::cout << "Moved up to: " << currentPath << std::endl;
        } else {
            std::cout << "Already at the root directory." << std::endl;
        }
    }
};

int main() {
    FileExplorer explorer;
    std::string command;

    while (true) {
        std::cout << "Enter command (list, cd <dir>, up, quit): ";
        std::getline(std::cin, command);

        if (command == "list") {
            explorer.listFiles();
        } else if (command.substr(0, 3) == "cd ") {
            explorer.changeDirectory(command.substr(3));
        } else if (command == "up") {
            explorer.goUp();
        } else if (command == "quit") {
            break;
        } else {
            std::cout << "Unknown command." << std::endl;
        }
    }

    return 0;
}
