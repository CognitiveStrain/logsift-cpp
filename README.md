# LogSift C++

A C++20 multithreaded command-line log analyzer built to demonstrate systems-oriented programming, concurrency, parsing, CMake, tests, and cross-platform CI.

## Features

- Parses timestamp / severity / message records
- Counts log levels concurrently using a worker pool pattern
- Separates malformed input instead of crashing
- Deterministic summary output
- CMake build
- Unit-style parser tests
- GitHub Actions on Linux and Windows

## Build

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
ctest --test-dir build -C Release --output-on-failure
```

## Run

```bash
./build/logsift examples/sample.log
```

Expected summary:

```text
lines=5
ERROR=1
INFO=2
WARN=1
INVALID=1
```

## Engineering extensions

- Stream very large files instead of loading them entirely into memory
- Add time-range and regex filtering
- Aggregate repeated error signatures
- Add JSON/CSV output
- Benchmark single-thread vs multi-thread throughput
- Add bounded producer/consumer queues
