# 9. A shape has a material (composition over inheritance)

## Context

When adding lighting (Lambert's cosine law), every surface needs both geometry (how to intersect a ray and compute a normal) and appearance (how that surface reacts to light).

We also have multiple shapes (`Sphere`, `Plane`, and more to come) and will eventually have multiple materials (diffuse, mirror, glass).

Alternatives considered:
- **Inheritance (`LitSphere`, `MirrorSphere`, `LitPlane`, `MirrorPlane`, …)**: each combination of shape and material becomes its own subclass. With $N$ shapes and $M$ materials, the number of classes multiplies ($N \times M$), and shading code is duplicated across shapes.
- **Composition (`Shape` has a `Material`)**: `Material` is a separate concept responsible for shading (`shade(normal, toLight)`). Each shape holds a `Material` and passes it in its `Hit`, while shapes remain independent behind the `Shape` interface.

## Decision

We use **composition**: a shape *has a* `Material`, rather than *being* a lit/shaded subclass.

- `Material` lives in `src/material/` and computes surface colour from `normal` and `toLight` using Lambert's law ($\max(0, N \cdot L)$).
- `Shape` is an abstract interface returning `std::optional<Hit>`, where `Hit` bundles `t`, `point`, unit `normal`, and `material`.
- `Scene` owns a collection of `std::unique_ptr<Shape>` and `toLight`, and `trace` delegates shading to `hit->material.shade(hit->normal, scene.toLight())`.

## Status

Proposed

## Consequences

- Adding a new shape (such as a cylinder or triangle) only requires implementing `Shape::hit`; no existing rendering or shading code changes (Open/Closed and Dependency Inversion).
- Shading logic lives in one place (`Material`) instead of being duplicated in `Sphere` and `Plane`.
- Shapes and materials combine freely ($N + M$ classes instead of $N \times M$).
- `Material` is a concrete value type copied into `Hit`. When a second material kind (such as mirrors or glass) is added, `Material` will need its own abstraction or variant, and each `Shape` currently carries the three lines of `_material` plumbing.
