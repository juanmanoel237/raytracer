# Contributing

Thank you for contributing to the raytracer.

## Prerequisites

- [Docker Desktop](https://www.docker.com/products/docker-desktop/) (or Docker Engine on Linux), running.
- [VS Code](https://code.visualstudio.com/) with the [Dev Containers](https://marketplace.visualstudio.com/items?itemName=ms-vscode.remote-containers) extension, or [Zed](https://zed.dev/).

## Setting up

1. Clone the repository.
2. Open it in its dev container:
   - **VS Code**: run **Dev Containers: Reopen in Container** from the command palette.
   - **Zed**: accept the "Open in Dev Container" prompt.
3. The first start builds the Docker image and downloads Catch2. This takes a few minutes.

## Running the project

In a terminal **inside the container**:

```
make build   # configure and compile
make run     # build, then run
make test    # build, then run the tests
make clean   # delete the build folder
```

All tests must pass before you submit a pull request.

## How we work

- **TDD**: write a failing test before the code. Commit on green.
- Expected values in tests come from the maths, not from running the code.
- One small step at a time. Each commit should leave the tests green.
- Never compare doubles with `==`. Use `Catch::Matchers::WithinAbs` with a tolerance of `1e-9`.

## Architecture decisions

Decisions are recorded in [`docs/adr/`](docs/adr/). Read them before changing the build, the tools, or the structure. To change a decision, write a new ADR with status Proposed and open a pull request.

## Submitting a change

1. Fork the repository and create a branch from `main`.
2. Make your changes, with tests.
3. Push and open a pull request. The CI will run the build and tests.
4. The maintainer reviews and merges.
