# LogSift C++

A fast command-line tool for parsing, filtering, aggregating, and inspecting large log files.

## Why this project

LogSift demonstrates practical modern C++ engineering:

- streaming file processing
- explicit performance and memory tradeoffs
- robust parsing and malformed-input handling
- composable filters and aggregations
- automated tests and benchmarks
- portable command-line packaging

## Planned stack

- C++20
- CMake
- Catch2 or GoogleTest
- CLI11
- GitHub Actions

## Initial capabilities

1. Stream logs without loading the entire file into memory.
2. Filter by severity, timestamp range, source, and text pattern.
3. Aggregate counts and latency statistics.
4. Support structured JSON logs and a configurable plain-text format.
5. Export results as terminal output, JSON, or CSV.
6. Report malformed records without crashing the whole run.

## Quality bar

The project should include reproducible benchmarks, documented complexity, representative fixtures, and tests for malformed and boundary-case input.

## Status

CLI architecture and implementation are in progress.
