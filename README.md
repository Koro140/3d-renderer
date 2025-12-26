# 3D Renderer in C

A simple 3D renderer written in **C**, using **SDL3** for window creation and pixel rendering.  
The project focuses on low-level, CPU-based rendering concepts.

## Features

- Software (CPU-based) 3D rendering
- Cross-platform support (Windows / Linux)
- Uses SDL3 for window management and input
- Minimal dependencies

## Requirements

- C compiler (GCC, Clang, or MSVC)
- CMake (3.16 or newer)
- SDL3 (included as a submodule)

## Installation

Clone the repository **with submodules**:

```bash
git clone --recurse-submodules https://github.com/Koro140/3d-renderer.git
cd 3d-renderer
```

Configure and build the project:

```bash
cmake -S . -B build
cmake --build build
```

After building, the executable will be located in the `build/` directory.

## Project Structure

```
3d-renderer/
├── src/        # Source files
├── include/    # Header files
├── external/   # SDL3 submodule
├── CMakeLists.txt
└── README.md
```

## Goals

- Learn the fundamentals of 3D graphics
- Implement a renderer without relying on GPU APIs
- Keep the codebase simple and readable

## License

This project is licensed under the MIT License.

