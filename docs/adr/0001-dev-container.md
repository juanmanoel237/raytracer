# 1. Dev container

## Context

The team works on different operating systems (macOS, Windows, Linux) with different processors (ARM, x86-64). Without a shared environment, each developer installs their own tools and versions. The result: "it works on my machine", broken tests, and slow onboarding.

We want the same compiler, the same tools, and the same build on every machine, from day one.

## Decision

We use a dev container: a Docker image that runs Linux and holds the compiler, CMake, and the other tools the project needs. VS Code and Zed open the project inside the container, and all commands run there.

The container specification lives in `.devcontainer/` and is committed to the repository.

## Status

Proposed

## Consequences

- Every developer and every CI run uses the same Linux, the same compiler (clang), and the same tools.
- The first start takes a few minutes while Docker builds the image.
- Everyone needs Docker Desktop (or Docker Engine on Linux) installed.
- The container runs Linux, so it does not test a native macOS or Windows build. Render times and pixel-exact output may differ between ARM and x86-64 hosts.
