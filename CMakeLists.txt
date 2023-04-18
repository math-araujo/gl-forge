cmake_minimum_required(VERSION 3.25)
include(cmake/fetchvcpkg.cmake)
project(gl-forge LANGUAGES CXX)

find_package(glad CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_path(STB_INCLUDE_DIRS "stb_c_lexer.h")

add_subdirectory(src)

# Initial executable as a test
add_executable(main src/main.cpp)
target_compile_features(main PRIVATE cxx_std_20)
target_link_libraries(main PRIVATE gl-forge)