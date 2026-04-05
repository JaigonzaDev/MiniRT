*This project has been created as part of the 42 curriculum by jaigonza, rlobun.*

# miniRT

## Description
miniRT is a small ray tracer written in C as part of the 42 curriculum.

Its goal is to render a 3D scene described in a `.rt` file by implementing the core principles of ray tracing:
- camera projection
- ray-object intersections
- ambient and point lighting
- color computation per pixel

This implementation parses a scene file and renders it with MiniLibX.
It currently supports:
- scene properties: `A` (ambient), `C` (camera), `L` (light)
- objects: `sp` (sphere), `pl` (plane), `cy` (cylinder)

The project follows the miniRT constraints from the subject file in `docs/en.subject.pdf`.

## Features
- Scene parsing from text files (`.rt`, and currently also `.r` extensions)
- Multiple spheres, planes, and cylinders
- Basic light model (ambient + point light)
- Linux Makefile targeting MiniLibX for X11
- Integrated use of `Get_next_line` and MiniLibX

## Instructions
### Requirements
- C compiler (`cc`)
- `make`
- X11 development libraries: `libXext`, `libX11`, `libm`, `libbsd`

### Build
From the project root:

```bash
make
```

### Run
Use one scene file as argument:

```bash
./miniRT path/to/scene.rt
```

Examples available in `docs/tests/`.

### Useful Make targets
```bash
make clean     # remove MiniRT object files
make fclean    # remove MiniRT binary and run fclean on libraries when available
make re        # full rebuild
make info      # print build flags
make sani      # rebuild with sanitizers
```


## Scene Format Overview
A scene is made of one element per line. Empty lines and lines starting with `#` are ignored.

Mandatory unique elements:
- `A` ambient light
- `C` camera
- `L` light

Object elements (multiple allowed):
- `sp` sphere
- `pl` plane
- `cy` cylinder

Typical examples:

```text
A 0.2 255,255,255
C 0,0,0 0,0,1 70
L 10,10,10 0.7 255,255,255
sp 0,0,20 10 255,0,0
pl 0,-10,0 0,1,0 255,255,255
cy 20,0,20 0,1,0 6 15 0,255,0
```

For complete and official constraints, refer to the 42 subject.

## Project Structure
- `srcs/` core source code (parsing, math, intersections, render, mlx loop)
- `include/` headers
- `libs/Get_next_line/` line-by-line file reader library
- `libs/mlx_linux/` MiniLibX implementation for Linux/X11
- `docs/tests/` sample scenes

## Resources
Classic references:
- Ray Tracing in One Weekend, Peter Shirley
- Scratchapixel: Ray Tracing lessons
- PBRT (Physically Based Rendering) book and website
- MiniLibX documentation (42 resources and `libs/mlx_linux/`)
- 42 miniRT subject (`docs/en.subject.pdf`)

How AI was used in this project:
- Build tooling support: reviewing and improving Makefile clean/fclean behavior across root and libraries.
- Documentation support: drafting and structuring this README for clarity and compliance with the required sections.
- No blind code generation policy: any AI suggestion for build scripts or documentation was reviewed and adjusted before use.

## Notes
This README is an overview. The authoritative project rules are the 42 miniRT subject and your campus evaluation criteria.
