#include "cmd_line.hpp"
#include <string_view>
#include <iostream>
#include <cstdlib>
#include <charconv>
#include <string_view>
constexpr std::uint64_t default_lines_threshold = 12;
constexpr const char* help_text = R"(find_light_files [options]
OPTIONS
--ext [string] target extension
--path [path] search target path
--threshold [integer] line count threshold to list up(only fewer files)
--exclude-path [path] exclude path. you can apply this multiple times.
)";
command_options parse_options(int argc, char** argv)
{
    using namespace std::literals;
    if (argc == 2 && argv[1] == "--help"sv) {
        std::cerr << help_text << std::flush;
        std::quick_exit(0);
    }
    command_options ret{};
    ret.lines_threshold = default_lines_threshold;

    for (int i = 0; i < argc; ++i) {
        if (argv[i] == "--ext"sv && i + 1 < argc) {
            ret.ext = argv[i + 1][0] == '.' ? argv[i + 1] : "."s + argv[i + 1];
            ++i;
        } else if (argv[i] == "--path"sv && i + 1 < argc) {
            ret.path = argv[i + 1];
            ++i;
        } else if (argv[i] == "--threshold"sv && i + 1 < argc) {
            std::string_view sv = argv[i + 1];
            decltype(ret.lines_threshold) lines_threshold = 0;
            if (auto [ptr, ec] = std::from_chars(sv.data(), sv.data() + sv.size(), lines_threshold); ec != std::errc{}) continue;
            ret.lines_threshold = lines_threshold;
            ++i;
        } else if (argv[i] == "--exclude-path"sv && i + 1 < argc) {
            ret.exclude_path.emplace(argv[i + 1]);
        }
    }
    if (ret.ext.empty() || ret.path.empty()) {
        std::cerr << help_text << std::flush;
        std::quick_exit(1);
    }
    return ret;
}