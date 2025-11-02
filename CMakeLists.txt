cmake_minimum_required(VERSION 3.20)
project(SmartStudy VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Options
option(BUILD_TESTING "Build tests" ON)

# Find Qt6
find_package(Qt6 REQUIRED COMPONENTS Core Widgets)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Find SQLite3
find_package(SQLite3 REQUIRED)

# Find SQLiteCpp (from vcpkg)
find_package(SQLiteCpp CONFIG REQUIRED)

# Compiler warnings
if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Main executable
file(GLOB_RECURSE SOURCES 
    "src/*.cpp"
    "src/*.h"
)

add_executable(smart-study
    ${SOURCES}
)

target_include_directories(smart-study PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(smart-study PRIVATE
    Qt6::Core
    Qt6::Widgets
    SQLite::SQLite3
    SQLiteCpp
)

# Tests (to be added later)
if(BUILD_TESTING)
    enable_testing()
    message(STATUS "Tests will be added in future commits")
endif()

# Install
install(TARGETS smart-study
    RUNTIME DESTINATION bin
)