cmake_minimum_required(VERSION 3.25)
include(cmake/fetchvcpkg.cmake)
project(glforge LANGUAGES CXX)

find_package(glad CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_path(STB_INCLUDE_DIRS "stb_c_lexer.h")

set(gl_forge_files 
    include/glforge/application.hpp src/application.cpp
    include/glforge/window.hpp src/window.cpp
    include/glforge/camera.hpp src/camera.cpp
    include/glforge/shader.hpp src/shader.cpp
    include/glforge/shader_program.hpp src/shader_program.cpp
    include/glforge/vertex_array.hpp src/vertex_array.cpp
    include/glforge/vertex_buffer.hpp src/vertex_buffer.cpp
    include/glforge/index_buffer.hpp src/index_buffer.cpp
    include/glforge/texture.hpp src/texture.cpp
    include/glforge/texture_sampler.hpp src/texture_sampler.cpp)
add_library(glforge STATIC ${gl_forge_files})
target_include_directories(glforge PUBLIC include)

target_link_libraries(glforge PRIVATE glad::glad glfw glm::glm imgui::imgui)
target_compile_features(glforge PRIVATE cxx_std_20)
set_target_properties(glforge PROPERTIES CXX_EXTENSIONS OFF)
target_include_directories(glforge PUBLIC ${STB_INCLUDE_DIRS})
add_library(glforge::glforge ALIAS glforge)

if (MSVC)
    target_compile_options(glforge PRIVATE /W4 /WX)
else()
    target_compile_options(glforge PRIVATE -Wall -Wextra -Wpedantic)
endif()

add_subdirectory(examples)