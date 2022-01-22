cmake_minimum_required(VERSION 3.21)
project(GRAPHS_AED)

set(CMAKE_CXX_STANDARD 14)
add_executable(GRAPHS_AED main.cpp src/Graph.cpp include/Graph.h include/MinHeap.h tests/tests.cpp)

add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/Tests")

target_link_libraries(GRAPHS_AED gtest gtest_main)

