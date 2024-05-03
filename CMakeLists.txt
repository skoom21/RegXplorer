cmake_minimum_required(VERSION 3.10)

# Project name
project(RegexSearchEngine)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add include directories
include_directories(include)

# Find FLTK package
find_package(FLTK REQUIRED)
include_directories(${FLTK_INCLUDE_DIRS})

# Add source files for the backend (search engine)
file(GLOB SEARCH_ENGINE_SOURCES "src/*.cpp")

# Add source files for the GUI
file(GLOB GUI_SOURCES "src/gui/*.cpp")

# Add executable target
add_executable(${PROJECT_NAME} ${SEARCH_ENGINE_SOURCES} ${GUI_SOURCES})

# Link FLTK library
target_link_libraries(${PROJECT_NAME} ${FLTK_LIBRARIES})

# Set output directory for executable
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
