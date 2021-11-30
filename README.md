# rtsim
C++ implementation of a ray tracing simulator

```cpp
Camera cam;
Scene scn;
int recursion_depth = 5;

scn.addObject(new Sphere(Vector(-1, -1, -4), 1, RGB(1, 0, 0), 0.1));
scn.addObject(new Sphere(Vector(0, -1.8, -3.9), 0.2, RGB(0, 1, 0), 0.3));
scn.addObject(new Cone(Vector(1, 0.5, -5.3), Vector(1, -2, -5.3), 1.3, RGB(0.5, 0.7, 1), 0.9));

scn.addObject(new InfinitePlane(Vector(0, -2, 0), Vector(0, 1, 0), RGB(0.5, 0.6, 0.7), 0.1));

scn.addSource(new Source(Vector(-1, 5, -2.5), 0.8));
scn.addSource(new Source(Vector(0, 0, 1), 0.00001));

render(cam, scn, recursion_depth);
```

![](https://raw.githubusercontent.com/ab-gh/rtsim/main/docs/demo.png)

## Features

- [ ] Objects
  - [x] Spheres
  - [x] Planes
  - [ ] Triangles
  - [ ] Cuboids
  - [ ] Cylinders
  - [x] Cone
- [ ] Materials
  - [x] Reflectivity parameters
  - [ ] Emissive
  - [ ] Refractive
- [ ] Light sources
  - [x] Point light
  - [ ] Emissive
- [ ] Scene illumination
  - [x] Ambient (constant)
  - [x] Diffuse
  - [x] Specular
  - [x] Reflection
  - [ ] Refraction
  - [ ] Global Illumination
- [ ] Rendering
  - [ ] Free camera
  - [ ] Anti-aliasing
  - [ ] Specify file name

# TODO

- [x] Add a floor
- [ ] Add a room
- [x] Add reflectivity 
- [x] Factor out the intensity function
- [ ] Read in scene fies
