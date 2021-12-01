# rtsim
C++ implementation of a ray tracing simulator

```cpp
// Initialise a scene and camera
Camera cam;
Scene scn;
// Add a floor
scn.addObject(new InfinitePlane(Vector(0, -2, 0), Vector(0, 1, 0), RGB(0.1, 0.1, 0.6), 0));
// Add some objects on the floor
scn.addObject(new Sphere(Vector(-1, -1, -4), 1, RGB(1, 0, 0), 0.2));
scn.addObject(new Sphere(Vector(0, -1.8, -3.9), 0.2, RGB(0, 1, 0), 0));
scn.addObject(new Cone(Vector(1, 0.5, -5.3), Vector(1, -2, -5.3), 1.3, RGB(0.3, 0.5, 0.7), 0.7));
// Add some background walls
scn.addObject(new InfinitePlane(Vector(-6, -6, -6), Vector(1.5, 0, 1), RGB(0.6, 0.6, 0.6), 0.1));
scn.addObject(new InfinitePlane(Vector(-10, -10, -10), Vector(0, 0, 1), RGB(0.6, 0.6, 0.6), 0.1));
// Add some walls behind the camera
scn.addObject(new InfinitePlane(Vector(25, 25, 25), Vector(-1.5, 0, -  1), RGB(0.3, 0.3, 0.3), 0));
scn.addObject(new InfinitePlane(Vector(25, 25, 25), Vector(0, 0, -1), RGB(0.3, 0.3, 0.3), 0));
// Add a shiny disk under the objects
scn.addObject(new Disc(Vector(0, -1.99, -4.5), Vector(0, 1, 0), 2.4, RGB(0.7, 0.7, 0.7), 0.1));
// Add a front and key light
scn.addSource(new Source(Vector(-1, 5, -2.5), 0.8));
scn.addSource(new Source(Vector(0, 0, 1), 0.01));
// Render the scene with a maximum reflection depth of 2
render(cam, scn, 2);
return 0;
```

![](https://raw.githubusercontent.com/ab-gh/rtsim/main/docs/demo.png)

## Features

- Objects
  - Spheres
  - Cones
  - Infinite Planes
  - Discs
- Materials
  - Colour
  - Reflectivity
- Light sources
  - Point light 
- Scene illumination types
  - Ambient (constant)
  - Diffuse
  - Specular
  - Reflection

## Roadmap
- [ ] More objects
  - [ ] Cylinders
  - [ ] Cuboids
  - [ ] Triangles for meshing
  - [ ] Shape file import
- [ ] Rendering
  - [ ] Specify file name
  - [ ] Scene file import
  - [ ] Free camera
  - [ ] DoF and focal distance
  - [ ] Anti-aliasing/supersampling
- [ ] Materials
  - [ ] Shadows
  - [ ] Refraction
  - [ ] Transparent/translucent
  - [ ] Emissive objects (volume lights)