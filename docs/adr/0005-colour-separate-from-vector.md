# 5. Colour as a separate class from Vector

## Context

A colour has three numbers (r, g, b), and so does a Vector (x, y, z). We could represent both with the same class. The domain model leaves this open.

Arguments for sharing:
- Less code: one class, not two.

Arguments against:
- Colours are mixed, clamped to [0, 1], and converted to [0, 255] for image files. A direction needs none of that.
- A colour has no use for `dot`, `normalised`, or `length`.
- With two classes, the compiler stops anyone from adding a colour to a position by mistake.
- DRY is about shared *knowledge*, not similar-looking code.

## Decision

Colour is a class of its own, separate from Vector. It holds three doubles _r, _g, _b (from 0 to 1) and exposes them through `r()`, `g()`, and `b()`.

## Status

Proposed

## Consequences

- The compiler prevents mixing colours and directions.
- There is some duplication between the two classes (three doubles, three getters, a constructor).
- When colours need operations (mixing, clamping, gamma correction), those will be added to Colour, not to Vector.
- If materials are added later, the colour may move out of Sphere.
