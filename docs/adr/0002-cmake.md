# 2. CMake and CTest

## Context

A C++ project needs a build system that works across Linux, macOS, and Windows. Each platform has its own compiler and its own way to describe a build.

Alternatives considered:
- **Make** alone: works on Linux/macOS, not on Windows without extra tools.
- **Bazel**: powerful, but heavy and unfamiliar to most C++ developers.
- **CMake**: the de-facto standard for cross-platform C++ projects, with native support in VS Code, Zed, and most IDEs.

## Decision

We use CMake to describe the build, with CMake Presets to give each platform a named configuration. CTest, which comes with CMake, runs the tests.

## Status

Proposed

## Consequences

- The build works on Linux, macOS, and Windows from one `CMakeLists.txt`.
- Presets (`unix-debug`, `windows`, …) make the commands predictable.
- CMake is one more language to learn, on top of C++.
- CTest reports pass or fail per test case; for richer output, we use Catch2.
