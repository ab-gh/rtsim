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
    scn.addObject(new Sphere(Vector(0, -1, -4), 1, RGB(1, 0, 0), 0.05));
    scn.addObject(new InfinitePlane(Vector(0, -2, 0), Vector(0, 1, 0), RGB(1, 1, 1), 0.5));

    scn.addSource(new Source(Vector(0, 5, -1), 1));

    render(cam, scn, 1);
    return 0;
}
