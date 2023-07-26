// find_light_files.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <filesystem>
#include <string>
#include <fstream>
#include <optional>
#include "cmd_line.hpp"
namespace fs = std::filesystem;
namespace {
    std::optional<std::uint64_t> get_file_line_count_when_fewer(const fs::path& p, std::uint64_t lines_threshold)
    {
        if (lines_threshold == 0) return {};
        std::ifstream file(p);
        char c;
        std::uint64_t i = 0;
        // count LF until line count is equal to lines_threshold
        while (i < lines_threshold && file.get(c)) if (c == '\n') ++i;
        if (i == lines_threshold) return {};
        return i;
    }
}
int main(int argc, char** argv)
{
    const auto options = parse_options(argc, argv);
    const fs::path target_path = options.path;
    for (auto&& entry : fs::recursive_directory_iterator(target_path, fs::directory_options::skip_permission_denied)) {
        if (!entry.is_regular_file() || entry.path().extension() != options.ext) continue;
        const auto line_count = get_file_line_count_when_fewer(entry.path(), options.lines_threshold);
        if (!line_count) continue;
        std::cout << *line_count << '\t' << fs::relative(entry.path(), target_path) << std::endl;
    }
}
