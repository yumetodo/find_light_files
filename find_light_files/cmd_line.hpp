#pragma once
#include <filesystem>
#include <string>
#include <cstdint>
#include <unordered_set>
struct command_options {
    std::string ext;
    std::filesystem::path path;
    std::uint64_t lines_threshold;
    std::unordered_set<std::filesystem::path> exclude_path;
};
command_options parse_options(int argc, char** argv);
