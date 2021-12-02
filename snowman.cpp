#include <string>
#include <cmath>
#include "Render.h"
#include "Camera.h"
#include "Vector.h"
#include "Scene.h"
#include "Object.h"
#include "Source.h"
#include <time.h>

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
    // Arms
    scn.addObject(new Cone(Vector(-0.3, 0.1, -4), Vector(-1.3, -1.3, -4), 0.07, RGB(0.64, 0.16, 0.16), 0.06));
    scn.addObject(new Cone(Vector(0.3, 0.1, -4), Vector(1.3, -1.3, -4), 0.07, RGB(0.64, 0.16, 0.16), 0.06));

    /* TREE */
    scn.addObject(new Cone(Vector(-5, -0.5, -8), Vector(-5, -3, -8), 1.5, RGB(0, 0.3, 0), 0.2));
    scn.addObject(new Cone(Vector(-5, 0.6, -8), Vector(-5, -1.5, -8), 1.3, RGB(0, 0.35, 0), 0.2));
    scn.addObject(new Cone(Vector(-5, 1.3, -8), Vector(-5, -0.3, -8), 1, RGB(0, 0.4, 0), 0.2));
    scn.addObject(new Cone(Vector(-5, 2, -8), Vector(-5, 0.6, -8), 0.8, RGB(0, 0.45, 0), 0.2));
    // Star
    scn.addObject(new Sphere(Vector(-5, 2, -8), 0.2, RGB(1, 0.87, 0), 1));
    // Baubles
    scn.addObject(new Sphere(Vector(-5.3, -0.3, -7), 0.1, RGB(0.9, 0.1, 0.1), 0.6));
    scn.addObject(new Sphere(Vector(-4.7, 0.6, -7), 0.1, RGB(0.9, 0.1, 0.1), 0.6));
    scn.addObject(new Sphere(Vector(-4.2, -1.5, -6.9), 0.1, RGB(0.9, 0.1, 0.1), 0.6));
    /* SCENE */
    // Floor
    scn.addObject(new InfinitePlane(Vector(0, -3, 0), Vector(0, 1, 0), RGB(1, 1, 1), 0));
    // Sky
    scn.addObject(new InfinitePlane(Vector(0, 0, -30), Vector(0, 0, 1), RGB(0.3, 0.3, 1), 0));
    // Top
    scn.addSource(new Source(Vector(0, 5, -1), 0.7));
    // Side key
    scn.addSource(new Source(Vector(-4, 3, 0), 0.4));
    // Front key
    scn.addSource(new Source(Vector(0, -3, 5), 0.2));

    /* SNOW */

    srand (time(NULL));

    for (int i = 0; i < 200; i++) {
        auto x = -20 + (rand() % 41);
        auto y = -3 + (rand() % 41);
        scn.addObject(new Sphere(Vector(x, y, -15), 0.05, RGB(1, 1, 1), 0));
    }

    render(cam, scn, 1);
    return 0;
}
