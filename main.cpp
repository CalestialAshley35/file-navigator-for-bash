#include <iostream>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <cstdio>
#include <cstring>
#include <dirent.h>
#include <deque>
#include <zip.h>
#include <fcntl.h>
#include <unistd.h>

namespace fs = std::filesystem;

std::deque<std::string> commandHistory;

void listFiles() {
    std::string currentDir = fs::current_path().string();
    for (const auto& entry : fs::directory_iterator(currentDir)) {
        std::cout << entry.path().filename().string() << std::endl;
    }
}

void deleteFile(const std::string& filename) {
    if (fs::exists(filename)) {
        if (fs::remove(filename)) {
            std::cout << "Deleted file: " << filename << std::endl;
        } else {
            std::cerr << "Error deleting file: " << filename << std::endl;
        }
    } else {
        std::cerr << "File does not exist: " << filename << std::endl;
    }
}

void checkFileExtension(const std::string& filename) {
    std::string ext = filename.substr(filename.find_last_of('.') + 1);
    if (ext == "html") std::cout << "HTML Document" << std::endl;
    else if (ext == "c") std::cout << "C Source Code" << std::endl;
    else if (ext == "cpp") std::cout << "C++ Source Code" << std::endl;
    else if (ext == "py") std::cout << "Python Script" << std::endl;
    else if (ext == "java") std::cout << "Java Source Code" << std::endl;
    else if (ext == "js") std::cout << "JavaScript File" << std::endl;
    else if (ext == "rs") std::cout << "Rust Source Code" << std::endl;
    else if (ext == "go") std::cout << "Go Source Code" << std::endl;
    else std::cout << "Unknown file type" << std::endl;
}

void searchFile(const std::string& filename) {
    std::string command = "find . -type f -name '" + filename + "'";
    system(command.c_str());
}

void showFileSize(const std::string& filename) {
    struct stat stat_buf;
    if (stat(filename.c_str(), &stat_buf) == 0) {
        std::cout << "File size: " << stat_buf.st_size << " bytes" << std::endl;
    } else {
        std::cerr << "Error retrieving file size" << std::endl;
    }
}

void viewFileContents(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::cout << line << std::endl;
    }
    file.close();
}

void changePermissions(const std::string& permission, const std::string& filename) {
    mode_t perm = std::stoi(permission, nullptr, 8);
    if (chmod(filename.c_str(), perm) == 0) {
        std::cout << "Changed permissions for " << filename << std::endl;
    } else {
        std::cerr << "Error changing permissions for " << filename << std::endl;
    }
}

void grepWord(const std::string& word, const std::string& filename) {
    std::string command = "grep -H '" + word + "' " + filename;
    system(command.c_str());
}

void createDirectory(const std::string& dirName) {
    try {
        if (fs::create_directory(dirName)) {
            std::cout << "Created directory: " << dirName << std::endl;
        } else {
            std::cerr << "Directory already exists or cannot be created: " << dirName << std::endl;
        }
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Error creating directory: " << e.what() << std::endl;
    }
}

void removeDirectory(const std::string& dirName) {
    try {
        if (fs::remove_all(dirName)) {
            std::cout << "Removed directory: " << dirName << std::endl;
        } else {
            std::cerr << "Directory is not empty, cannot remove" << std::endl;
        }
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Error removing directory: " << e.what() << std::endl;
    }
}

void changeDirectory(const std::string& dirName) {
    if (chdir(dirName.c_str()) == 0) {
        std::cout << "Changed directory to: " << dirName << std::endl;
    } else {
        std::cerr << "Error changing directory to: " << dirName << std::endl;
    }
}

void copyFile(const std::string& source, const std::string& destination) {
    try {
        fs::copy(source, destination);
        std::cout << "File copied from " << source << " to " << destination << std::endl;
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Error copying file: " << e.what() << std::endl;
    }
}

void moveFile(const std::string& source, const std::string& destination) {
    try {
        fs::rename(source, destination);
        std::cout << "File moved from " << source << " to " << destination << std::endl;
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Error moving file: " << e.what() << std::endl;
    }
}

void renameFile(const std::string& oldName, const std::string& newName) {
    try {
        fs::rename(oldName, newName);
        std::cout << "Renamed file from " << oldName << " to " << newName << std::endl;
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Error renaming file: " << e.what() << std::endl;
    }
}

void showHistory() {
    std::cout << "Command history:" << std::endl;
    for (const auto& cmd : commandHistory) {
        std::cout << cmd << std::endl;
    }
}

void searchContentInFiles(const std::string& word) {
    std::string command = "grep -r '" + word + "' .";
    system(command.c_str());
}

void compressFile(const std::string& filename) {
    std::string command = "zip -r " + filename + ".zip " + filename;
    system(command.c_str());
    std::cout << "Compressed file " << filename << " into " << filename + ".zip" << std::endl;
}

void extractFile(const std::string& archive) {
    std::string command = "unzip " + archive;
    system(command.c_str());
    std::cout << "Extracted archive: " << archive << std::endl;
}

void executeCommand(const std::string& command) {
    commandHistory.push_back(command);
    if (commandHistory.size() > 20) {
        commandHistory.pop_front();
    }

    if (command == "help") {
        std::cout << "Available commands:" << std::endl;
        std::cout << "help              - list all available commands" << std::endl;
        std::cout << "files             - list all files in the current directory" << std::endl;
        std::cout << "delete <file>     - delete a file" << std::endl;
        std::cout << "file <file>       - check the file extension" << std::endl;
        std::cout << "search <file>     - search for a file" << std::endl;
        std::cout << "size <file>       - show file size" << std::endl;
        std::cout << "view <file>       - view file contents" << std::endl;
        std::cout << "permission <perm> <file> - change file permissions" << std::endl;
        std::cout << "grep <word> <file> - search for a word in a file using grep" << std::endl;
        std::cout << "mkdir <dir>       - create a new directory" << std::endl;
        std::cout << "rmdir <dir>       - remove an empty directory" << std::endl;
        std::cout << "cd <dir>          - change the current directory" << std::endl;
        std::cout << "copy <source> <destination> - copy a file" << std::endl;
        std::cout << "move <source> <destination> - move a file" << std::endl;
        std::cout << "rename <old> <new> - rename a file" << std::endl;
        std::cout << "history           - show command history" << std::endl;
        std::cout << "searchcontent <word> - search for a word inside files" << std::endl;
        std::cout << "compress <file>   - compress a file into a zip archive" << std::endl;
        std::cout << "extract <archive> - extract a zip archive" << std::endl;
    } else if (command == "files") {
        listFiles();
    } else if (command.substr(0, 6) == "delete") {
        deleteFile(command.substr(7));
    } else if (command.substr(0, 4) == "file") {
        checkFileExtension(command.substr(5));
    } else if (command.substr(0, 6) == "search") {
        searchFile(command.substr(7));
    } else if (command.substr(0, 4) == "size") {
        showFileSize(command.substr(5));
    } else if (command.substr(0, 4) == "view") {
        viewFileContents(command.substr(5));
    } else if (command.substr(0, 9) == "permission") {
        size_t spacePos = command.find(' ', 10);
        std::string perm = command.substr(10, spacePos - 10);
        changePermissions(perm, command.substr(spacePos + 1));
    } else if (command.substr(0, 4) == "grep") {
        size_t spacePos = command.find(' ', 5);
        grepWord(command.substr(5, spacePos - 5), command.substr(spacePos + 1));
    } else if (command.substr(0, 5) == "mkdir") {
        createDirectory(command.substr(6));
    } else if (command.substr(0, 5) == "rmdir") {
        removeDirectory(command.substr(6));
    } else if (command.substr(0, 2) == "cd") {
        changeDirectory(command.substr(3));
    } else if (command.substr(0, 4) == "copy") {
        size_t spacePos = command.find(' ', 5);
        copyFile(command.substr(5, spacePos - 5), command.substr(spacePos + 1));
    } else if (command.substr(0, 4) == "move") {
        size_t spacePos = command.find(' ', 5);
        moveFile(command.substr(5, spacePos - 5), command.substr(spacePos + 1));
    } else if (command.substr(0, 6) == "rename") {
        size_t spacePos = command.find(' ', 7);
        renameFile(command.substr(7, spacePos - 7), command.substr(spacePos + 1));
    } else if (command == "history") {
        showHistory();
    } else if (command.substr(0, 13) == "searchcontent") {
        searchContentInFiles(command.substr(14));
    } else if (command.substr(0, 8) == "compress") {
        compressFile(command.substr(9));
    } else if (command.substr(0, 7) == "extract") {
        extractFile(command.substr(8));
    }
}

int main() {
    std::string command;
    std::cout << "\033[1;32mWelcome to File Navigator for Bash! Type 'help' for a list of all available commands\033[0m" << std::endl;
    while (true) {
        std::cout << "\033[1;32m~" << fs::current_path() << "\033[0m$ ";
        std::getline(std::cin, command);
        executeCommand(command);
    }
    return 0;
}
