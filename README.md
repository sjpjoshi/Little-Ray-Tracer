# Little Ray Tracer

## Overview
Little Ray Tracer is a lightweight ray tracing engine written in C++ using SDL2, the STL library, and a custom-made linear algebra library. This project demonstrates essential ray tracing principles, including geometric transforms, lighting, and textures, optimized for efficient rendering.
This project is for educational purposes only, this is a learning experience for me. 

## Features
- **Geometric Primitives**: Supports rendering of spheres, planes, cylinders, boxes, and cones.
- **Camera Geometry**: Implements camera positioning, view direction, and perspective projection.
- **Lighting and Shadows**: Includes support for basic lighting models and shadow casting.
- **Materials**: Handles simple and refractive materials with various surface properties.
- **Textures**: Supports UV mapping, image textures, and procedural textures.
- **Noise**: Integrates both value noise and gradient noise for texture generation.
- **Normal Mapping**: Includes both texture-based and image-based normal mapping.
- **Rendering Optimizations**: Uses tile-based rendering and multithreading for improved performance.

## Examples
### 1. Refraction and Reflection
_Description_: Demonstrating light refraction and reflection on a refractive material.

![Refraction Example](https://github.com/sjpjoshi/Little-Ray-Tracer/blob/main/example1.png)
![Reflection Example](https://github.com/sjpjoshi/Little-Ray-Tracer/blob/main/Example4.png)

### 2. Numerous objects
_Description_: Cones, Cylinders, Spheres

![Refraction Example](https://github.com/sjpjoshi/Little-Ray-Tracer/blob/main/Example2.png)

### 3. UV Mapping and Image Textures
_Description_: Example showcasing UV space and image texture mapping on geometric shapes.

![UV Mapping Example](https://github.com/sjpjoshi/Little-Ray-Tracer/blob/main/Example3.png)

## How to Build

1. Ensure you have SDL2 and the STL library installed. You also need to include the custom-made linear algebra library provided in the repository.

2. Compile the project using your preferred C++ compiler. Example with `g++`:
   ```bash
   g++ -o raytracer main.cpp -lSDL2

3. Run the executable:
./raytracer

## Future Features
-Global Illumination
-Advanced camera effects (e.g., depth of field, motion blur)

## License
This project is licensed under the MIT License. See the LICENSE file for details.
