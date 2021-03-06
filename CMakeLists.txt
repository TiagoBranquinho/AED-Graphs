cmake_minimum_required(VERSION 3.20.2)
project(GRAPHS_AED)

set(CMAKE_CXX_STANDARD 14)
add_executable(GRAPHS_AED main.cpp src/GraphGN.cpp include/GraphGN.h include/MinHeap.h include/Data.h src/Data.cpp src/App.cpp include/App.h src/AppStarter.cpp include/AppStarter.h include/Menu.h src/Menu.cpp src/Menu.cpp include/Menu.h include/structs.h src/GraphLines.cpp include/GraphLines.h src/Graph.cpp include/Graph.h)

target_link_libraries(GRAPHS_AED)

# Doxygen Build
find_package(Doxygen)
if(DOXYGEN_FOUND)
    set(BUILD_DOC_DIR "${CMAKE_SOURCE_DIR}/docs/output")
    if(NOT EXISTS "${BUILD_DOC_DIR}")
        file(MAKE_DIRECTORY "${BUILD_DOC_DIR}")
    endif()

    set(DOXYGEN_IN "${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile")
    set(DOXYGEN_OUT "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile")
    configure_file("${DOXYGEN_IN}" "${DOXYGEN_OUT}" @ONLY)

    message("Doxygen build started")
    add_custom_target(Doxygen ALL
            COMMAND "${DOXYGEN_EXECUTABLE}" "${DOXYGEN_OUT}"
            WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
            COMMENT "Generating API documentation with Doxygen"
            VERBATIM)
else(DOXYGEN_FOUND)
    message("Doxygen needs to be installed to generate the documentation.")
endif(DOXYGEN_FOUND)