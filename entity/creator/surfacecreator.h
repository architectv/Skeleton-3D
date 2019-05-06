#ifndef SURFACECREATOR_H
#define SURFACECREATOR_H

#include <entity.h>

class SurfaceCreator {
 public:
    ~SurfaceCreator() = default;
    
    Surface CreateRectPlane(Point, Point);
    Surface CreateDisc(Point, double, double);
    Surface CreatePolygonPlane(Point, double, int);
    Surface CreateCylinderSurface(Point, double, double);
    Surface CreateConeSurface(Point, double, double);
};

#endif // SURFACECREATOR_H
