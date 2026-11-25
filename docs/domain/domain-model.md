# Domain model

## The algorithm (in the client's words)

> We have a camera: an eye and a screen in front of it. The screen is divided into pixels. For each pixel, the camera sends a ray from the eye through the centre of the pixel. A ray has an origin and a direction, and both are vectors. We ask the scene for the nearest hit among its shapes (spheres, planes). Each shape has a material that computes how it is shaded by the sun's light using the surface normal. If the ray hits something, the pixel takes the shaded colour; otherwise, it takes the background colour. When every pixel has a colour, we have an image, and a saver writes it to a file.

## Class diagram

```mermaid
classDiagram
    Camera "1" --> "*" Ray : sends
    Camera --> Image : renders
    Camera --> Scene : traces
    Scene "1" --> "*" Shape : owns
    Shape <|.. Sphere : implements
    Shape <|.. Plane : implements
    Shape --> Hit : returns optional
    Hit --> Material : carries
    Shape --> Material : has
    Material --> Colour : colour
    Image "1" --> "*" Colour : pixels
    ImageSaver --> Image : saves
    PngSaver --|> ImageSaver : implements
    Camera --> Vector : eye, screenCentre
    Ray --> Vector : origin, direction
    Hit --> Vector : point, normal
    Scene --> Vector : toLight
    Sphere --> Vector : centre
    Plane --> Vector : point, normal
    trace --> Ray : takes
    trace --> Scene : takes
    trace --> Colour : returns

    class Vector {
        x: double
        y: double
        z: double
        operator+()
        operator-()
        dot()
        length()
        normalised()
        operator*(double t, Vector v)
    }

    class Colour {
        r: double
        g: double
        b: double
        r()
        g()
        b()
        operator*(double t, Colour c)
    }

    class Material {
        colour: Colour
        colour()
        shade(normal, toLight) Colour
    }

    class Ray {
        origin: Vector
        direction: Vector
        origin()
        direction()
        at(t) Vector
    }

    class Hit {
        <<struct>>
        t: double
        point: Vector
        normal: Vector
        material: Material
    }

    class Shape {
        <<interface>>
        hit(Ray) optional~Hit~
    }

    class Sphere {
        centre: Vector
        radius: double
        material: Material
        hit(Ray) optional~Hit~
    }

    class Plane {
        point: Vector
        normal: Vector
        material: Material
        hit(Ray) optional~Hit~
    }

    class Scene {
        toLight: Vector
        shapes: unique_ptr~Shape~[]
        add(unique_ptr~Shape~)
        toLight() Vector
        nearestHit(Ray) optional~Hit~
    }

    class Camera {
        eye: Vector
        screenCentre: Vector
        screenWidth: double
        rayThroughPixel(col, row, w, h)
        render(Scene, w, h) Image
    }

    class Image {
        width: int
        height: int
        pixels: Colour[]
        width()
        height()
        pixel(col, row)
        setPixel(col, row, Colour)
    }

    class ImageSaver {
        <<interface>>
        save(Image, path)
    }

    class PngSaver {
        save(Image, path)
    }

    class trace {
        <<function>>
        trace(Ray, Scene) Colour
    }
```

## Folder dependencies

The arrows between folders go one way (acyclic dependencies):

```
output/ ──→ image/ ──→ colour/
render/ ──→ image/
render/ ──→ scene/ ──→ geometry/ ──→ material/ ──→ colour/
              │            │             │
              └────────────┴─────────────┴──→ math/
```

## Open questions / parked decisions

| Topic | Note |
|---|---|
| Single directional sun in `Scene` | A lamp (point light) would be a second kind of light: introduce a Light interface when needed. |
| Single `Material` law (Lambertian) | Reflective or refractive materials (mirrors, glass) will require a `Material` abstraction or variant. |
| Each `Shape` stores `_material` | Three lines of plumbing per shape; revisit with the third shape. |
| No shadows yet | Dark sides are black from `max(0, N·L)`; cast shadow rays when shadows are requested. |
| `Camera` has two reasons to change | Holds camera geometry and the render loop. Split when scenes or distributed rendering require it. |
| Colour outside `[0, 1]` | `toByte` assumes values in `[0, 1]`. Decide clamping/tone-mapping when multiple lights arrive. |
| Out-of-bounds pixels in `Image` | No bounds check yet. Decide policy when needed. |
