cmake_minimum_required(VERSION 3.25)
include(cmake/fetchvcpkg.cmake)
project(gl-forge LANGUAGES CXX)

find_package(glad CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_path(STB_INCLUDE_DIRS "stb_c_lexer.h")

set(gl_forge_files 
    src/application.hpp src/application.cpp
    src/window.hpp src/window.cpp
    src/camera.hpp src/camera.cpp
    src/shader.hpp src/shader.cpp
    src/shader_program.hpp src/shader_program.cpp
    src/vertex_array.hpp src/vertex_array.cpp
    src/vertex_buffer.hpp src/vertex_buffer.cpp
    src/index_buffer.hpp src/index_buffer.cpp
    src/texture.hpp src/texture.cpp
    src/texture_sampler.hpp src/texture_sampler.cpp)
add_library(gl-forge STATIC ${gl_forge_files})
target_include_directories(gl-forge PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

target_link_libraries(gl-forge PRIVATE glad::glad glfw glm::glm imgui::imgui)
target_compile_features(gl-forge PRIVATE cxx_std_20)
set_target_properties(gl-forge PROPERTIES CXX_EXTENSIONS OFF)
target_include_directories(gl-forge PUBLIC ${STB_INCLUDE_DIRS})
target_include_directories(gl-forge PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

if (MSVC)
    target_compile_options(gl-forge PRIVATE /W4 /WX)
else()
    target_compile_options(gl-forge PRIVATE -Wall -Wextra -Wpedantic)
endif()

# Initial executable as a test
add_executable(main src/main.cpp)
target_compile_features(main PRIVATE cxx_std_20)
target_link_libraries(main PRIVATE gl-forge)