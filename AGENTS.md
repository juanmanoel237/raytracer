# AGENTS.md

## Commands

Run these in a terminal **inside the dev container**:

```
make build   # configure and compile
make run     # build, then run
make test    # build, then run the tests
make clean   # delete the build folder
```

## Architecture decisions

All decisions are in `docs/adr/`. Read them before changing the build, the tools, or the test setup.

- Never go against an accepted ADR. To change a decision, write a new ADR with status Proposed and ask me.
- Never set an ADR to Accepted yourself.

## How we work

- **TDD**: write a failing test first, then only enough code to make it pass.
- Expected values in tests come from the maths, not from running the code. If a test fails, ask me before changing what it expects.
- One small step at a time. Do only what I ask for, nothing more.
- Keep the C++ simple. No advanced features unless I ask for them.
- Do not build or run anything on the host. The commands above run in the dev container.

## Source layout

New classes go in the folder of their concept, under `src/`, and their tests in the matching folder under `tests/`.

```
src/
  main.cpp
  math/       vector.h, vector.cpp
  colour/     colour.h, colour.cpp
  material/   material.h, material.cpp
  geometry/   hit.h, shape.h, ray.h, ray.cpp, sphere.h, sphere.cpp, plane.h, plane.cpp
  scene/      scene.h, scene.cpp
  image/      image.h, image.cpp
  output/     image_saver.h, png_saver.h, png_saver.cpp
  render/     camera.h, camera.cpp, trace.h, trace.cpp
tests/
  test_helpers.h, test_helpers.cpp
  math/       test_vector.cpp
  colour/     test_colour.cpp
  material/   test_material.cpp
  geometry/   test_ray.cpp, test_sphere.cpp, test_plane.cpp
  scene/      test_scene.cpp
  image/      test_image.cpp
  output/     test_png_saver.cpp
  render/     test_camera.cpp, test_trace.cpp
```
