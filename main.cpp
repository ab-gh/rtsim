#include <string>
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
    scn.addObject(new Sphere(Vector(.2, -.2, -1), .1, RGB(1, 0, 0), 0.3));
    scn.addObject(new Sphere(Vector(-1, 0, -3), .7, RGB(0, 1, 0), 1.0));
    scn.addObject(new InfinitePlane(Vector(0, -12, 0), Vector(0, 1, 0), RGB(1, 1, 1)));

    scn.addSource(new Source(Vector(0, 5, -1), 1));
    scn.addSource(new Source(Vector(7, -5, -1), .2));

    render(cam, scn);
    return 0;
}
