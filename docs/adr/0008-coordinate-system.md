# 8. Coordinate system and image grid

## Context

Turning a pixel's column and row into a 3D ray requires an explicit convention for both the 3D world axes and the 2D image grid. Without a written decision, the camera, shapes, and image saver can easily disagree on which direction is "up" or "forward".

Alternatives considered:
- **Right-handed (x right, y up, −z forward)**, as used in *Ray Tracing in One Weekend*.
- **Left-handed (x right, y up, +z forward)**, where objects in front of the camera have positive z coordinates.
- **Image origin at bottom-left** vs **top-left**: PNG and most image formats store pixels row by row from top to bottom.

## Decision

We use:
- **3D world coordinates (left-handed)**: `+x` to the right, `+y` up, and `+z` forward (away from the eye).
- **2D image coordinates**: `(column, row)` counted from the **top-left** corner `(0, 0)`, stored row by row in memory (`row * width + column`).
- **Pixel centres**: each ray passes through the centre of its pixel (`+ 0.5`), with `y` inverted so row `0` maps to the top of the screen (`+y`).

## Status

Proposed

## Consequences

- Positions in front of the camera use intuitive positive `z` values.
- Image memory layout matches PNG row order directly, avoiding vertical flips when saving.
- `Camera::rayThroughPixel` must invert the `y` axis when mapping `row` to world `y`.
- Readers comparing our code with *Ray Tracing in One Weekend* must remember our `+z` forward convention vs its `−z` convention.
