#include <string>
#include <cmath>
#include "Render.h"
#include "Camera.h"
#include "Vector.h"
#include "Scene.h"
#include "Object.h"
#include "Source.h"

using namespace std;

int main() {
    Camera cam;
    Scene scn;
    /* SNOWMAN */
    // Body
    scn.addObject(new Sphere(Vector(0, -2, -4), 0.9, RGB(1, 1, 1), 0));
    scn.addObject(new Sphere(Vector(0, -0.55, -4), 0.7, RGB(1, 1, 1), 0));
    scn.addObject(new Sphere(Vector(0, 0.6, -4), 0.5, RGB(1, 1, 1), 0));
    // Nose
    scn.addObject(new Cone(Vector(0, 0.5, -3.5), Vector(0, 0.5, -3.2), 0.05, RGB(1, 0.5, 0), 0));
    // Eyes
    scn.addObject(new Sphere(Vector(-0.15, 0.7, -3.55), 0.06, RGB(0.1, 0.1, 0.1), 0.1));
    scn.addObject(new Sphere(Vector(0.15, 0.7, -3.55), 0.06, RGB(0.1, 0.1, 0.1), 0.1));
    // Mouth
    scn.addObject(new Sphere(Vector(0, 0.35, -3.55), 0.04, RGB(0.1, 0.1, 0.1), 0.1));
    scn.addObject(new Sphere(Vector(-0.06, 0.37, -3.55), 0.04, RGB(0.1, 0.1, 0.1), 0.1));
    scn.addObject(new Sphere(Vector(0.06, 0.37, -3.55), 0.04, RGB(0.1, 0.1, 0.1), 0.1));
    scn.addObject(new Sphere(Vector(-0.12, 0.39, -3.55), 0.04, RGB(0.1, 0.1, 0.1), 0.1));
    scn.addObject(new Sphere(Vector(0.12, 0.39, -3.55), 0.04, RGB(0.1, 0.1, 0.1), 0.1));


    /* SCENE */
    // Floor
    scn.addObject(new InfinitePlane(Vector(0, -3, 0), Vector(0, 1, 0), RGB(1, 1, 1), 0.4));
    // Top
    scn.addSource(new Source(Vector(0, 5, -1), 0.8));
    // Side key
    scn.addSource(new Source(Vector(-4, 3, 0), 0.4));

    render(cam, scn, 1);
    return 0;
}
