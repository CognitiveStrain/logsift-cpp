#include "log_parser.hpp"

std::optional<LogRecord> parse_log_line(std::string_view line) {
    const auto first = line.find(' ');
    if (first == std::string_view::npos) return std::nullopt;
    const auto second = line.find(' ', first + 1);
    if (second == std::string_view::npos) return std::nullopt;

    LogRecord record{
        std::string(line.substr(0, first)),
        std::string(line.substr(first + 1, second - first - 1)),
        std::string(line.substr(second + 1))
    };

    if (record.timestamp.empty() || record.level.empty() || record.message.empty()) {
        return std::nullopt;
    }
    return record;
}
