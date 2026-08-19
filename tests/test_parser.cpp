#include "log_parser.hpp"
#include <cassert>
#include <iostream>

int main() {
    auto ok = parse_log_line("2026-08-19T10:15:00Z ERROR disk full");
    assert(ok.has_value());
    assert(ok->level == "ERROR");
    assert(ok->message == "disk full");

    assert(!parse_log_line("malformed").has_value());
    std::cout << "parser tests passed\n";
}
