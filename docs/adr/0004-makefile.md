# 4. Makefile for short commands

## Context

The CMake commands are long and hard to remember:

```
cmake --preset unix-debug
cmake --build --preset unix-debug
./build/unix-debug/raytracer
ctest --preset unix-debug
```

Developers who know npm expect short commands like `npm run build`. We want the same brevity.

Alternatives considered:
- **npm scripts**: only available in Node.js projects.
- **shell aliases**: personal, not committed to the repository.
- **Makefile**: available in Linux, macOS, and the dev container; committed to the repository; short and memorable.

## Decision

We add a `Makefile` at the root of the project. It wraps the CMake commands behind four targets:

```
make build   # configure and compile
make run     # build, then run
make test    # build, then run the tests
make clean   # delete the build folder
```

The preset defaults to `unix-debug`. Pass `PRESET=unix-release` to override.

## Status

Proposed

## Consequences

- Day-to-day work needs only four short commands.
- `make` is not available on Windows by default. Windows users use the CMake presets directly (documented in the README).
- Makefile commands must be indented with a tab, not spaces. A wrong indent causes "missing separator" errors.
