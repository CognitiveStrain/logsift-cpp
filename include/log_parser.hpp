#pragma once
#include <optional>
#include <string>
#include <string_view>

struct LogRecord {
    std::string timestamp;
    std::string level;
    std::string message;
};

std::optional<LogRecord> parse_log_line(std::string_view line);
