#ifndef EDGE_H
#define EDGE_H

#include "entity.h"
#include "point.h"
#include "surface.h"

class Edge : public Entity {
    public:
        Edge(size_t start, Point &start_p, size_t end, Point &end_p) :
            startInd(start), startPoint(start_p),
            endInd(end), endPoint(end_p) {}

        void Move(double, double, double) const;
        void Rotate(double, double, double, Point) const;
        void Scale(double, double, double, Point) const;

        Surface &Lift(double, double, double);

    private:
        size_t startInd;
        size_t endInd;
        Point &startPoint;
        Point &endPoint;
};

#endif // EDGE_H