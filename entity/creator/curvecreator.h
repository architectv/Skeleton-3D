#ifndef CURVECREATOR_H
#define CURVECREATOR_H

#include <edge.h>

class CurveCreator: public Edge {
 public:
    Edge CreateLine(Point, Point);
    vector<Edge> CreateRectangle(Point, Point);
    vector<Edge> CreateEllipse(Point, double, double);
    vector<Edge> CreatePolygon(Point, double, int);
};

#endif // CURVECREATOR_H
