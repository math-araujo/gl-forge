# gl-forge

Personal C++ OpenGL 4.6 framework, used as setup of graphics projects (rendering, animation, geometry).

## Build

```
git clone https://github.com/math-araujo/gl-forge.git

cd gl-forge

# Run `cmake --list-presets` to see all available presets

# On Windows + MSVC
cmake --preset=msvc

cmake --build build --config Release

# Or on Linux
cmake --preset=unix

cmake --build build
```

## Requirements

* C++20 compiler

* CMake $\geq$ 3.25

## Dependencies

[vcpkg](https://github.com/microsoft/vcpkg) is used as package manager for the external dependencies.  See `vcpkg.json` file for the list of dependencies.

This framework fetchs and builds `vcpkg` in [manifest mode](https://vcpkg.readthedocs.io/en/latest/users/manifests/) during the configuration step, so there's no need to manually download it. To remove the dependencies, just delete the `vcpkg` and `build` directories; nothing is installed system-wide.

## Usage

### FetchContent

It's possible to consume `gl-forge` in an external project by using CMake [FetchContent](https://cmake.org/cmake/help/latest/module/FetchContent.html). Because this framework uses `vcpkg`, it's necessary to fetch the framework **before** the first call to `project()` in the root CMakeLists.txt.

```
include(FetchContent)
FetchContent_Declare(gl-forge
    GIT_REPOSITORY https://github.com/math-araujo/gl-forge.git
    GIT_TAG 14434df9d2ca8270cc0d785043cc7e01526788c0 # master branch
)
FetchContent_MakeAvailable(gl-forge)
project(your-project LANGUAGES CXX)
```