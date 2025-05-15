#pragma once
#include <string>
#include <vector>


class FileManager {
public:
    static auto readLines(const std::string& path) ->  std::vector<std::string>;
    static auto writeLines(const std::string& path, const std::vector<std::string> &lines) ->  void;
    static auto pathExists(const std::string& path) -> bool;
};