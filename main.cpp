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
    scn.addObject(new Sphere(Vector(1.3, -0.5, -3), 0.5, RGB(1, 0, 0), 0.8));
    scn.addObject(new InfinitePlane(Vector(0, -4, 0), Vector(0, 1, 0), RGB(1, 1, 1), 0.4));
    scn.addObject(new Cone(Vector(0, 2, -4), Vector(0, -1, -4), 1, RGB(1, 1, 1), 1));

    scn.addSource(new Source(Vector(0, 5, -1), 1));

    render(cam, scn);
    return 0;
}
