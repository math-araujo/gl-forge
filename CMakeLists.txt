cmake_minimum_required(VERSION 3.25)
option(FETCH_VCPKG "Fetch vcpkg as dependency manager" FALSE)
if (${FETCH_VCPKG})
    message(STATUS "Populating vcpkg")
    include(cmake/fetchvcpkg.cmake)
else()
    message(STATUS "Building without vcpkg")
endif()

project(glforge LANGUAGES CXX)

message(STATUS "VCPKG DIR: ${vcpkg_SOURCE_DIR}")
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
add_library(glforge_glforge STATIC ${gl_forge_files})
target_include_directories(glforge_glforge PUBLIC include)

target_link_libraries(glforge_glforge PUBLIC glad::glad glfw glm::glm imgui::imgui)
target_compile_features(glforge_glforge PRIVATE cxx_std_20)
set_target_properties(glforge_glforge PROPERTIES CXX_EXTENSIONS OFF)
target_include_directories(glforge_glforge PUBLIC ${STB_INCLUDE_DIRS})

if (MSVC)
    target_compile_options(glforge_glforge PRIVATE /W4 /WX)
else()
    target_compile_options(glforge_glforge PRIVATE -Wall -Wextra -Wpedantic)
endif()

# Link to ALIAS glforge::glforge
add_library(glforge::glforge ALIAS glforge_glforge)

option(BUILD_GL_FORGE_EXAMPLES "Build examples directory" FALSE)
if (${BUILD_GL_FORGE_EXAMPLES})
    add_subdirectory(examples)
endif()