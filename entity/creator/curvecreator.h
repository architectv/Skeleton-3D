#ifndef CURVECREATOR_H
#define CURVECREATOR_H

#include <entity.h>

class CurveCreator {
 public:
    ~CurveCreator() = default;

    Edge CreateLine(Point, Point);
    vector<Edge> CreateRectangle(Point, Point);
    vector<Edge> CreateEllipse(Point, double, double);
    vector<Edge> CreatePolygon(Point, double, int);
};

#endif // CURVECREATOR_H
