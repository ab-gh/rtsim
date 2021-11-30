# rtsim
C++ implementation of a ray tracing simulator

```cpp
Scene scn;
scn.addObject(new Sphere(Vector(.5, .5, -5 ), 2, RGB(0, 0, 1), 0.3));
scn.addObject(new Sphere(Vector(.2, -.2, -1), .1, RGB(1, 0, 0), 0.3));
scn.addObject(new Sphere(Vector(-1, 0, -3), .7, RGB(0, 1, 0), 1.0));

scn.addSource(new Source(Vector(0, 5, -1), 1));
scn.addSource(new Source(Vector(7, -5, -1), .2));

render(Camera cam, scn);
```

![](https://raw.githubusercontent.com/ab-gh/rtsim/main/docs/Screenshot%202021-11-24%20at%206.57.55%20pm.png)

## Features

- [ ] Objects
  - [x] Spheres
  - [ ] Planes
  - [ ] Triangles
  - [ ] Cuboids
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
  - [ ] Reflection
  - [ ] Refraction
  - [ ] Global Illumination
- [ ] Rendering
  - [ ] Free camera
  - [ ] Anti-aliasing
  - [ ] Specify file name
