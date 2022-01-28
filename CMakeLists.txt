cmake_minimum_required(VERSION 3.20.2)
project(GRAPHS_AED)

set(CMAKE_CXX_STANDARD 14)
add_executable(GRAPHS_AED main.cpp src/GraphGN.cpp include/GraphGN.h include/MinHeap.h include/Data.h src/Data.cpp tests/DataTest.cpp src/App.cpp include/App.h tests/AppTest.cpp src/AppStarter.cpp include/AppStarter.h include/Menu.h src/Menu.cpp src/Menu.cpp include/Menu.h include/structs.h src/GraphLines.cpp include/GraphLines.h src/Graph.cpp include/Graph.h)

add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/Tests")

target_link_libraries(GRAPHS_AED gtest gtest_main)

