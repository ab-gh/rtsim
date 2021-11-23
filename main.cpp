#include "Object.h"
#include <string>
#include "RGB.h"
#include "Render.h"
#include "Camera.h"
#include "Ray.h"
#include "Vector.h"
#include "Scene.h"
#include "Object.h"
#include "Source.h"
using namespace std;

int main() {
    Camera cam;
    Scene scn;
    scn.addObject(new Sphere(Vector(0, 0, -1), 0.5, RGB(0, 0.5, 1)));
    scn.addSource(new Source(Vector(0, 2, 0), 1));

    render(cam, scn);
    return 0;
}
