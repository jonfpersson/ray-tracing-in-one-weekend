# Ray Tracing in One Weekend

This repository contains my implementation and completion of the "Ray Tracing in One Weekend" series. The series, written by Peter Shirley, is a beginner-friendly guide to understanding the fundamentals of ray tracing and creating a very basic ray tracer from scratch. In this project, I followed the series and expanded upon it to deepen my understanding of computer graphics and rendering techniques.

## Table of Contents

- [Ray Tracing in One Weekend](#ray-tracing-in-one-weekend)
  - [Table of Contents](#table-of-contents)
  - [Introduction](#introduction)
  - [Features](#features)
  - [How to Run](#how-to-run)

## Introduction

Ray tracing is a rendering technique used to simulate how light interacts with objects in a virtual scene. Instead of rasterizing the scene like traditional raster graphics, ray tracing follows the path of light rays as they interact with surfaces to produce realistic images. This project is an educational journey where I implemented a basic ray tracer by sequentially working through the "Ray Tracing in One Weekend" series.

## Features

- **Sphere and Lambertian Diffuse Surfaces**: I implemented basic sphere rendering and Lambertian diffuse shading to simulate the interaction of light with different surfaces.
- **Ray-Sphere Intersection**: The ray tracer can determine if a ray intersects a sphere and calculate the point of intersection.
- **Antialiasing**: To improve the image quality, I added antialiasing to reduce jagged edges and create smoother images.
- **Metallic Surfaces**: I extended the ray tracer to handle metallic surfaces, simulating reflections.
- **Dielectric Materials**: The ray tracer can now handle transparent materials, like glass, to simulate refraction and transparency.

## How to Run

To run the ray tracer and generate images, follow these steps:

1. Clone this repository to your local machine.
2. Make sure you have a C++ compiler that supports C++11 or higher.
3. Compile the source code by running ```g++ main.cpp```
4. Execute the resulting binary
5. The ray tracer will render the scene and save the output as an ppm image file.