# Ray Tracer in C++

![Final Render](./RayTracing/image.ppm)

A path tracer built from scratch in C++ following Peter Shirley's [Ray Tracing in One Weekend](https://raytracing.github.io/books/RayTracingInOneWeekend.html). Renders photorealistic images with diffuse, metallic, and glass materials, depth of field, and antialiasing — all computed on the CPU with no external graphics libraries.

## Features

- **Three material types** — Lambertian (matte), Metal (reflective with configurable fuzz), and Dielectric (glass with refraction and Schlick's approximation)
- **Antialiasing** — Multisampled rays per pixel for smooth edges
- **Defocus blur** — Simulated depth of field with configurable aperture and focus distance
- **Positionable camera** — Arbitrary camera placement with adjustable field of view
- **Gamma correction** — Accurate color output with gamma 2.0 correction

## The Final Scene

The rendered image features a ground plane, three large showcase spheres (glass, matte, and metal), and dozens of randomly placed smaller spheres with random materials. The camera is positioned at `(13, 2, 3)` looking at the origin with a 20° field of view, 100 samples per pixel, and a max ray bounce depth of 50.

## Build & Run

**Requirements:** CMake 3.10+, a C++11 compatible compiler.

```bash
# Clone the repo
git clone https://github.com/Crpedeim/RayTracer.git
cd RayTracing

# Build
cmake -B build
cmake --build build --config release

# Render (outputs PPM to stdout)
./build/RayTracing > output.ppm
```

The render takes a few minutes at 1200px width with 100 samples. To get a quick preview, you can lower `samples_per_pixel` and `image_width` in `main.cpp`.

> **Note:** The output is in PPM format. You can view it with tools like [IrfanView](https://www.irfanview.com/), [GIMP](https://www.gimp.org/), or convert it with ImageMagick: `convert output.ppm output.png`

## Project Structure

```
RayTracing/
├── CMakeLists.txt
└── src/
    ├── main.cpp           # Scene setup and entry point
    ├── headers.h          # Common includes, constants, utilities
    ├── vec3.cpp           # 3D vector class + math utilities (dot, cross, reflect, refract)
    ├── ray.cpp            # Ray class: origin + direction → point at t
    ├── sphere.cpp         # Sphere geometry with ray intersection (quadratic solver)
    ├── hittable.cpp       # Abstract base class for hittable objects + hit_record
    ├── hittable_list.cpp  # Collection of hittable objects
    ├── material.cpp       # Lambertian, Metal, and Dielectric materials
    ├── camera.cpp         # Camera with viewport, antialiasing, defocus blur, render loop
    ├── color.cpp          # Color output with gamma correction
    └── interval.cpp       # Numeric range utility for clamping and bounds checking
```

## How It Works

The ray tracer follows a simple loop: for each pixel, shoot rays from the camera into the scene, check what they hit, bounce them according to the hit material, and accumulate color. Each bounce loses energy based on the material's albedo. Rays that escape into the sky pick up a blue-white gradient. The result is averaged over many samples per pixel for a clean, antialiased image.

For a detailed breakdown of every class and how they work together, check out my blog post: **[I Built a Ray Tracer from Scratch in C++](https://byte-the-code.hashnode.dev/building_a_ray-tracer_from_scratch)**

## Render Settings

| Parameter | Value |
|---|---|
| Image width | 1200 px |
| Aspect ratio | 16:9 |
| Samples per pixel | 100 |
| Max bounce depth | 50 |
| Field of view | 20° |
| Defocus angle | 0.6° |
| Focus distance | 10.0 |

## Acknowledgments

Built following [Ray Tracing in One Weekend](https://raytracing.github.io/books/RayTracingInOneWeekend.html) by Peter Shirley, Trevor David Black, and Steve Hollasch.
