# 7. Save images as PNG with LodePNG

## Context

The client needs to open rendered images in ordinary image viewers, and our tests need lossless pixel verification. PNG is lossless, compressed, and universally supported, but implementing PNG compression and CRC checksums ourselves would take days.

Alternatives considered:
- **libpng**: the reference C library. Its API is verbose and C-style, and it is not pre-installed in our dev container.
- **stb_image_write**: a single-header public-domain C library using raw pointers; its output files are larger than LodePNG's.
- **LodePNG**: one `.cpp` and one `.h` under the zlib licence, zero dependencies, clean C++ API using `std::vector`, though slower to encode than libpng.
- **Writing PPM ourselves**: no library needed, but most standard viewers cannot open PPM and files are far larger (hundreds of KB for small images).

## Decision

We save images as PNG using **LodePNG**, downloaded via CMake `FetchContent` (just like Catch2) and pinned to commit `7b2893e35891c0c85bee5595caafaf3c2044b409` since LodePNG does not publish tagged releases.

Only `src/output/` (and its test) includes `lodepng.h`. The rest of the codebase depends on our own abstract interface `ImageSaver`, with `PngSaver` acting as an Adapter/Strategy.

## Status

Proposed

## Consequences

- Rendered images can be opened directly in any standard viewer and verified losslessly in tests.
- No third-party source files are committed to the repository; CMake fetches the exact pinned commit.
- The first configure (or configure after `make clean`) requires internet access in both the dev container and CI.
- Upgrading LodePNG requires manually updating the pinned commit hash in `CMakeLists.txt`.
- LodePNG is slower at encoding than libpng, which is acceptable given its simple C++ API and our current focus.
- Changing libraries or adding new formats (such as EXR for film production) only requires adding a new class implementing `ImageSaver`.
- `ImageSaver` introduces an extra abstraction layer with a single implementation for now.
