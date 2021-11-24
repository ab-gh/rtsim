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
    scn.addObject(new Sphere(Vector(0, 0, -1), .5, RGB(1, 0, 0)));
    scn.addSource(new Source(Vector(0, 1, -1), 1));

    render(cam, scn);
    return 0;
}
