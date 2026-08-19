#include "log_parser.hpp"

#include <algorithm>
#include <atomic>
#include <fstream>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>
#include <unordered_map>
#include <vector>

struct Stats {
    std::unordered_map<std::string, std::size_t> by_level;
    std::size_t invalid = 0;
};

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "usage: logsift <log-file> [threads]\n";
        return 2;
    }

    std::ifstream in(argv[1]);
    if (!in) {
        std::cerr << "cannot open file: " << argv[1] << "\n";
        return 1;
    }

    std::vector<std::string> lines;
    for (std::string line; std::getline(in, line);) lines.push_back(std::move(line));

    unsigned requested = argc >= 3 ? static_cast<unsigned>(std::stoul(argv[2])) : std::thread::hardware_concurrency();
    const unsigned workers = std::max(1u, requested);

    std::atomic<std::size_t> next{0};
    std::mutex stats_mutex;
    Stats total;

    auto worker = [&] {
        Stats local;
        while (true) {
            const auto i = next.fetch_add(1);
            if (i >= lines.size()) break;
            if (auto rec = parse_log_line(lines[i])) {
                ++local.by_level[rec->level];
            } else {
                ++local.invalid;
            }
        }
        std::lock_guard<std::mutex> lock(stats_mutex);
        total.invalid += local.invalid;
        for (const auto& [level, count] : local.by_level) total.by_level[level] += count;
    };

    std::vector<std::thread> pool;
    pool.reserve(workers);
    for (unsigned i = 0; i < workers; ++i) pool.emplace_back(worker);
    for (auto& t : pool) t.join();

    std::vector<std::pair<std::string, std::size_t>> sorted(total.by_level.begin(), total.by_level.end());
    std::sort(sorted.begin(), sorted.end());

    std::cout << "lines=" << lines.size() << "\n";
    for (const auto& [level, count] : sorted) std::cout << level << '=' << count << "\n";
    std::cout << "INVALID=" << total.invalid << "\n";
    return 0;
}
