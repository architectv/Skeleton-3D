#ifndef SURFACECREATOR_H
#define SURFACECREATOR_H

#include <entity/surface.h>

class SurfaceCreator: public Surface {
 public:
    Surface CreateRectPlane(Point, Point);
    Surface CreateDisc(Point, double, double);
    Surface CreatePolygonPlane(Point, double, int);
    Surface CreateCylinderSurface(Point, double, double);
    Surface CreateConeSurface(Point, double, double);
};

#endif // SURFACECREATOR_H
