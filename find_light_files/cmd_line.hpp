#pragma once
#include <string>
#include <cstdint>
struct command_options {
    std::string ext;
    std::string path;
    std::uint64_t lines_threshold;
};
command_options parse_options(int argc, char** argv);
