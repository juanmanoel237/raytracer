cmake_minimum_required(VERSION 3.25)
project(raytracer VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Warnings: one place, applied to our own targets only.
add_library(raytracer_warnings INTERFACE)
if(MSVC)
  target_compile_options(raytracer_warnings INTERFACE /W4)
else()
  target_compile_options(raytracer_warnings INTERFACE -Wall -Wextra -Wpedantic)
endif()

# LodePNG writes our PNG files. It has no CMake project of its own, so we build it here.
include(FetchContent)
FetchContent_Declare(
  lodepng
  GIT_REPOSITORY https://github.com/lvandeve/lodepng.git
  GIT_TAG        7b2893e35891c0c85bee5595caafaf3c2044b409
)
FetchContent_MakeAvailable(lodepng)
add_library(lodepng STATIC ${lodepng_SOURCE_DIR}/lodepng.cpp)
target_include_directories(lodepng PUBLIC ${lodepng_SOURCE_DIR})

# All real code lives in a library so that tests and the app share it.
add_library(raytracer_core
  src/math/vector.cpp
  src/colour/colour.cpp
  src/geometry/ray.cpp
  src/geometry/sphere.cpp
  src/image/image.cpp
  src/output/png_saver.cpp
  src/render/camera.cpp
  src/render/trace.cpp
)
target_include_directories(raytracer_core PUBLIC src)
target_link_libraries(raytracer_core PRIVATE raytracer_warnings lodepng)

add_executable(raytracer src/main.cpp)
target_link_libraries(raytracer PRIVATE raytracer_core raytracer_warnings)

# `run` target: builds the app if needed, then runs it.
add_custom_target(run COMMAND raytracer DEPENDS raytracer USES_TERMINAL)

# Tests
option(RAYTRACER_BUILD_TESTS "Build the unit tests" ON)
if(RAYTRACER_BUILD_TESTS)
  enable_testing()
  add_subdirectory(tests)
endif()
