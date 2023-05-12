cmake_minimum_required(VERSION 3.25)
project(glforge-examples LANGUAGES CXX)

# Initial executable as a test
add_executable(example main.cpp)
target_compile_features(example PRIVATE cxx_std_20)
target_link_libraries(example PRIVATE glforge::glforge)