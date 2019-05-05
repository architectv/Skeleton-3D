#ifndef EDGE_H_
#define EDGE_H_

#include "point.h"

class Surface;
class Edge : public Entity {
    public:
        Edge(size_t start, Point& start_p, size_t end, Point& end_p) :
            startInd(start), endInd(end),
            startPoint(&start_p), endPoint(&end_p) {}
        explicit Edge(const Edge&);

        void Move(const double&, const double&, const double&);
        void Rotate(const double&, const double&, const double&, const Point&);
        void Scale(const double&, const double&, const double&, const Point&);

        Surface &Lift(const double&, const double&, const double&);

    private:
        size_t startInd;
        size_t endInd;
        Point* startPoint;
        Point* endPoint;
};

Edge::Edge(const Edge& input) :
    startInd(input.startInd), endInd(input.endInd) {
    *startPoint = Point(input.startPoint);
    *endPoint = Point(input.endPoint);
}

void Edge::Move(const double& dx, const double& dy, const double& dz) {
    startPoint->Move(dx, dy, dz);
    endPoint->Move(dx, dy, dz);
}

void Edge::Rotate(const double& dx, const double& dy, const double& dz, const Point& center) {
    startPoint->Rotate(dx, dy, dz, center);
    endPoint->Rotate(dx, dy, dz, center);
}

void Edge::Scale(const double& dx, const double& dy, const double& dz, const Point& center) {
    startPoint->Scale(dx, dy, dz, center);
    endPoint->Scale(dx, dy, dz, center);
}

Surface& Edge::Lift(const double& dx, const double& dy, const double& dz) {
    /*
     * 01
     * 32

    Point p0 = startPoint;
    Point p1 = endPoint;
    Point p2 = Point(p1);
    p2.Move(dx, dy, dz);

    */
}

#endif // EDGE_H_
