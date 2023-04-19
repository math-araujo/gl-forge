cmake_minimum_required(VERSION 3.25)

add_library(gl-forge STATIC
    application.hpp application.cpp
    window.hpp window.cpp
    camera.hpp camera.cpp
    shader.hpp shader.cpp
)

target_link_libraries(gl-forge PRIVATE glad::glad glfw glm::glm imgui::imgui)
target_compile_features(gl-forge PRIVATE cxx_std_20)
set_target_properties(gl-forge PROPERTIES CXX_EXTENSIONS OFF)
target_include_directories(gl-forge PUBLIC ${STB_INCLUDE_DIRS})
target_include_directories(gl-forge PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

if (MSVC)
    target_compile_options(gl-forge PRIVATE /W3)
else()
    target_compile_options(gl-forge PRIVATE -Wall -Wextra -Wpedantic)
endif()