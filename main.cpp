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

    scn.addObject(new Sphere(Vector(-1, -1, -4), 1, RGB(1, 0, 0), 0.1));
    scn.addObject(new Sphere(Vector(0, -1.8, -3.9), 0.2, RGB(0, 1, 0), 0.3));
    //scn.addObject(new Cone(Vector(1, 0.5, -5.3), Vector(1, -2, -5.3), 1.3, RGB(0.5, 0.7, 1), 0.9));

    scn.addObject(new Cone(Vector(1.5, 0.5, -5.3), Vector(1.5, 0.5, -4), 1.3, RGB(0.5, 0.7, 1), 0.9));


    scn.addObject(new InfinitePlane(Vector(0, -2, 0), Vector(0, 1, 0), RGB(0.5, 0.6, 0.7), 0.1));
    //scn.addObject(new Disc(Vector(-1, -1.99, -4), Vector(0, 1, 0), 1.0, RGB(0.5, 0, 1), 0.1));
    scn.addObject(new Disc(Vector(-1, 0, -4), Vector(0, 0, 1), 1.0, RGB(0.5, 0, 1), 0.1));


    scn.addSource(new Source(Vector(-1, 5, -2.5), 0.8));
    scn.addSource(new Source(Vector(0, 0, 1), 0.00001));

    render(cam, scn, 1);
    return 0;
}
