# Raytracer

A CPU ray tracer in C++, built as a student project for HETIC.

## Getting started

Open this project in its dev container (VS Code: **Dev Containers: Reopen in Container**). Then use the short commands below, in a terminal inside the container.

## Commands

| Command | What it does |
|---|---|
| `make build` | Configure and compile |
| `make run` | Build, then run the program |
| `make test` | Build, then run the tests |
| `make clean` | Delete the build folder |

On Windows without the container, use the CMake presets directly (see `CMakePresets.json`).

## Architecture decisions

All decisions are recorded in [`docs/adr/`](docs/adr/). Read them before changing the build, the tools, or the test setup.

## Contributing

See [`CONTRIBUTING.md`](CONTRIBUTING.md) for how to set up the dev container, run the tests, and submit a change.
