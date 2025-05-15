//
// Created by Belinskiy Oleksandr on 15.05.2025.
//

#include "FileManager.h"
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

auto FileManager::pathExists(const std::string& path) -> bool {
    try {
        return fs::exists(fs::path(path));
    } catch (const fs::filesystem_error& e){
        return false;
    }
}

auto FileManager::readLines(const std::string &path) -> std::vector<std::string> {
    auto result = std::vector<std::string>();
    if (pathExists(path)) {
        auto file = std::ifstream(path);
        auto line = std::string();
        while (file >> line) {
            result.push_back(line);
        }
    }
    return result;
}

auto FileManager::writeLines(const std::string &path, const std::vector<std::string> &lines) -> void {
    if (pathExists(path)) {
        auto file = std::ofstream(path);
        for (const auto& line : lines) {
            file << line << std::endl;
        }
    }
}


