cmake_minimum_required(VERSION 3.10)

# Project name
project(RegexSearchEngine)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add include directory
include_directories(include)

# Add source files
file(GLOB SOURCES "src/*.cpp")

# Add executable target
add_executable(${PROJECT_NAME} ${SOURCES})

# Set output directory for executable
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE    _CURRENT_SOURCE_DIR}/bin
)