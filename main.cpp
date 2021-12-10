#include <string>
#include "Render.h"
#include "Camera.h"
#include "Vector.h"
#include "Scene.h"
#include "Object.h"
#include "Source.h"

using namespace std;

int main() {
    // Initialise a scene and camera
    Camera cam;
    Scene scn;
    // Load an empty room scene file
    scn.read("room.scn");
    // Add some objects to the empty room
    scn.addObject(new Sphere(Vector(-1, -1, -4), 1, RGB(1, 0, 0), 0.2));
    scn.addObject(new Sphere(Vector(0, -1.8, -3.9), 0.2, RGB(0, 1, 0), 0));
    scn.addObject(new Cone(Vector(1, 0.5, -5.3), Vector(1, -2, -5.3), 1.3, RGB(0.3, 0.5, 0.7), 0.7));
    scn.addSource(new Source(Vector(0, 0, 1), 0.01));
    // Render the scene with a maximum reflection depth of 2
    render(cam, scn, 2);
    return 0;
}
