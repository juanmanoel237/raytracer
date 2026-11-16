# Discovery report

## Problem statement

A Los Angeles animation studio needs an open-source, deterministic, and extensible CPU ray tracer by January 5th to render a 90-minute 8K film within a two-month render window because commercial seat-based licenses exceed $2 million per year and previous in-house tools failed due to unmaintainable, undocumented code.

## Client interview summary

### Reliability and debugging

**Need:** The studio needs a deterministic renderer that always produces the same output for a given input and allows developers to diagnose visual bugs within a single day.

> **Q (Student):** "What specific failures forced you to replace your previous rendering tools?"
>
> **A:** "About 6 months ago, we had a big project to bring to publication, and we kept finding that there were black artifacts in the images that were produced, and the rendering time doubled. [...] Nobody could tell us why."

> **Q (Student):** "What will demonstrate that our solution fits your needs?"
>
> **A:** "One, it produces a reliable image. So if I give it some inputs, I can always expect the same output. And the second one is that if there is an image anomaly, we can figure out within the same day why there is an anomaly and what steps we can take to correct it."

**My conclusion:** Predictable execution, clear error reporting, and automated tests are just as important as rendering speed.

### Licensing costs and commercial limitations

**Need:** The studio wants to eliminate per-machine licensing fees (over $2 million last year) and avoid waiting months for commercial vendors like Maya to add custom features, staying within a $500,000 budget.

> **Q (Student):** "What did you spend on rendering licenses last year, and why not use commercial software?"
>
> **A:** "On licenses, we must have spent over $2 million. Remember, the license is seat-based, so we pay per machine, per artist, plus every single node in our render farm. [...] With Maya, if we want to add something specific, we have to go through an official channel, and either they just say no, or it will take 6 months or a year to add a feature. [...] We would like to spend no more than $500,000 on the budget."

**My conclusion:** Building our own engine removes per-node licensing costs on the 100-machine render farm and gives the studio full control over new features.

### Scope, workflow, and performance

**Need:** The renderer must run headless on CPUs without a GUI, read scene files exported from third-party tools, support fast low-resolution previews for artists (about 10 pre-renders per image), and render 8K production frames for a 90-minute animated film within 2 months. For January 5th, only spheres and planes are required.

> **Q (Student):** "Which rendering features are strictly required right now, and what is your workflow and hardware setup?"
>
> **A:** "For the moment, let's just say we need to be able to render spheres, planes. And that's it for that. [...] We don't have graphics cards, so everything must be rendered by the CPU. [...] On the render farm, we have up to 100 machines. [...] Typically, at least 10 different pre-renders per image before the final render. [...] Once the creative side is done, you don't want to spend any more than 2 months for final rendering. It's a 90-minute film at 8K. [...] The designer will use some third-party software to position the scene, save a file, and that file will be the input to your renderer. No interface at this point."

**My conclusion:** The tool must be a CLI black box taking a scene file and outputting image files, with configurable resolution and quality settings for previews versus final renders.

### Open-source governance and maintainability

**Need:** The entire codebase must be open-source so partner studios can contribute, and clean enough that the studio's 5-person development team can maintain it even if key developers leave. It also needs technical docs for developers and a user guide for artists.

> **Q (Student):** "Will all the code be open source, and what happened with your previous team?"
>
> **A:** "Currently, all is open source. We rely on partners to do the rendering for us, and these partners have the skill sets to contribute to this project as well. [...] What happened last time is that we had a team of 5 people. The key person wrote the code, and when they left, we had 5 people that didn't know how to debug it. [...] We expect some kind of user guide for the artists or the people setting up the scenes."

**My conclusion:** Clean architecture (SOLID, OOP), Architecture Decision Records (ADRs), and clear documentation are mandatory to avoid single-person dependencies.

### Open questions

- Which exact input file format (e.g., JSON, YAML, or custom scene format) will the artists' third-party software export?
- Which output image file format (e.g., PPM, PNG, EXR) is expected on disk?
- What is the target frame rate (e.g., 24 fps) for the 90-minute film?

## State of the art

| Solution | Maker | Licence | Pricing (checked 16 Nov 2026) | Capabilities | Sources |
|---|---|---|---|---|---|
| **Arnold** | Autodesk | Proprietary | Commercial subscription (per-seat / token-based; exact current pricing on Autodesk store) | Industry-standard CPU/GPU production ray tracer, handles massive scenes and complex lighting | https://www.autodesk.com/products/arnold/overview |
| **RenderMan** | Pixar | Proprietary | Commercial per-license fee (non-commercial free tier available; commercial pricing via Pixar) | Feature-film path tracer, distributed rendering support, deep pipeline integration | https://renderman.pixar.com/ |
| **Cycles** | Blender Foundation | Apache 2.0 (Open Source) | Free (checked 16 Nov 2026) | Production CPU/GPU path tracer, physically based shading, open-source community | https://www.cycles-renderer.org/ |
| **LuxCoreRender** | LuxCoreRender Team | Apache 2.0 (Open Source) | Free (checked 16 Nov 2026) | Physically based spectral ray tracer, CPU/OpenCL rendering, supports distributed network rendering | https://luxcorerender.org/ |
| **pbrt-v4** | Matt Pharr, Wenzel Jakob, Greg Humphreys | BSD 2-Clause (Open Source) | Free (checked 16 Nov 2026) | Reference physically based CPU/GPU renderer used for research and education, well-documented C++ codebase | https://pbrt.org/ |

Commercial renderers like Arnold and RenderMan meet feature-film quality standards, but their per-seat licensing model becomes too expensive across 100 render nodes and prevents the studio from modifying core features freely. Open-source engines like Cycles or pbrt are free, yet adapting a massive, general-purpose codebase to a custom pipeline with strict internal maintainability rules is harder for a small team than owning a clean, purpose-built C++ renderer.

## What is ray tracing?

Ray tracing is a 3D rendering technique that takes a scene description as input—including camera position, geometry (such as spheres and planes), materials, and light sources—and outputs a 2D pixel image. For each pixel in the image, the program shoots virtual rays from the camera into the 3D scene to find the closest object they hit. At each intersection point, it calculates the pixel's final color by checking direct visibility to light sources (shadows) and tracing secondary bounced rays to simulate optical effects like reflections and refractions.

**Sources:**
- Starter: *Ray Tracing in One Weekend* — https://raytracing.github.io/books/RayTracingInOneWeekend.html
- Reference: *Physically Based Rendering: From Theory To Implementation (pbrt)* — https://www.pbr-book.org/

## What is C++?

### Programming paradigms

C++ is a multi-paradigm, compiled language that supports procedural, object-oriented (OOP), generic (templates), and functional programming. Compared to managed languages like Java, C#, or Python, C++ compiles directly to native machine code without a virtual machine or garbage collector, giving direct control over CPU execution and memory layout.

### What to watch out for

Unlike garbage-collected languages, C++ leaves memory management and object lifetimes up to the developer. Classic traps include memory leaks, dangling pointers, out-of-bounds array access, and undefined behavior, which can easily cause random crashes or visual artifacts if raw pointers are misused. Modern C++ mitigates this through RAII (Resource Acquisition Is Initialization) and smart pointers (`std::unique_ptr`, `std::shared_ptr`).

### Shaping the domain model

Because the client needs to add new geometric shapes, materials, and lighting models without rewriting existing code, C++ OOP features like interfaces (abstract base classes with pure virtual functions), polymorphism, and composition fit naturally. Modeling core concepts (`Scene`, `Camera`, `Ray`, `Shape`, `Material`, `Light`) as decoupled classes will keep the codebase clean and extensible.

**Sources:**
- Starter: *Learn C++* — https://www.learncpp.com/
- Reference: *cppreference.com* — https://en.cppreference.com/