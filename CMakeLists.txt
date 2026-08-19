cmake_minimum_required(VERSION 3.20)
project(logsift VERSION 1.0.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(log_parser src/log_parser.cpp)
target_include_directories(log_parser PUBLIC include)

add_executable(logsift src/main.cpp)
target_link_libraries(logsift PRIVATE log_parser)

add_executable(logsift_tests tests/test_parser.cpp)
target_link_libraries(logsift_tests PRIVATE log_parser)

enable_testing()
add_test(NAME parser COMMAND logsift_tests)
