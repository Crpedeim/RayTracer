# Ray Tracer in C++
![Final Render](https://github.com/user-attachments/assets/80918956-4ab1-4c8d-af35-253f926677ff)

A physically-based path tracer written from scratch in C++, following Peter Shirley's Ray Tracing in One Weekend. It renders photorealistic images with diffuse, metallic, and glass materials, depth of field, and antialiasing — entirely on the CPU, with no external graphics or math libraries. Every vector operation, intersection test, and light-transport bounce is hand-implemented.


How it works

The renderer traces rays from a virtual camera into the scene and recursively follows each ray as it bounces between surfaces, accumulating color via the rendering equation until it either escapes to the sky or exhausts its bounce budget:


For every pixel, it fires multiple jittered rays (stochastic sampling) and averages them — this is the antialiasing.
Each ray is intersected against the scene; on a hit, the surface material decides how the ray scatters, returning an attenuation color and a new ray.
ray_color() recurses on the scattered ray, multiplying attenuation at each bounce, up to max_depth. Rays that miss everything sample a blue-white sky gradient.


This is a Monte-Carlo path tracer: more samples per pixel → less noise → cleaner image.


Features

Material models (light scattering):


Lambertian (matte) — diffuse scatter using a random unit vector around the surface normal, with a degenerate-direction guard.
Metal (reflective) — mirror reflection about the normal, plus a configurable fuzz parameter that perturbs the reflected ray for brushed/glossy metal.
Dielectric (glass) — refraction via Snell's law, with total internal reflection handling and Schlick's approximation for angle-dependent Fresnel reflectance, so glass reflects at grazing angles like the real thing.


Camera & sampling:


Multisample antialiasing — configurable samples per pixel via sub-pixel jittering.
Defocus blur (depth of field) — a thin-lens model that samples ray origins over a defocus disk, with adjustable aperture (defocus_angle) and focus_dist.
Positionable camera — arbitrary lookfrom / lookat / vup, an orthonormal (u, v, w) camera basis, and adjustable vertical field of view.
Gamma correction — linear-to-gamma transform for accurate perceived brightness.


Geometry & core:


Analytic ray–sphere intersection (quadratic discriminant), with correct front/back-face normal orientation.
Hittable-object abstraction and a scene list for arbitrary object counts.
A hand-rolled vec3 math library (dot, cross, reflect, refract, random sampling) — no external math deps.



The final scene

A ground plane, three large showcase spheres — glass (dielectric), matte (Lambertian), and polished metal — surrounded by hundreds of randomly placed small spheres with randomized materials and colors. Rendered at 1200px wide (16:9), 100 samples/pixel, max bounce depth 50, with the camera at (13, 2, 3) looking at the origin through a 20° field of view and a 0.6° defocus angle.


Build & run

Requirements: CMake 3.10+, a C++17-compatible compiler.

bashgit clone https://github.com/Crpedeim/RayTracer.git
cd RayTracer/RayTracing

cmake -B build
cmake --build build --config release

# Render to a PPM image (redirect stdout)
./build/RayTracing > image.ppm

Open image.ppm in any image viewer that supports PPM, or convert it (e.g. pnmtopng image.ppm > image.png).


What I learned


How the rendering equation turns into a recursive bounce loop, and why more samples-per-pixel trades compute for less noise.
The physics of refraction — Snell's law, when light can't refract (total internal reflection), and why glass needs a Fresnel term (Schlick) to look right.
Building a small but complete linear-algebra toolkit (reflection, refraction, random sampling on disks/spheres) from the ground up.
How a thin-lens camera produces depth of field by sampling the aperture rather than treating the lens as a pinhole.


Possible extensions

Bounding-volume hierarchy (BVH) for faster intersection on large scenes, additional primitives (triangles / meshes), textures, lights and importance sampling, and multithreaded rendering.
