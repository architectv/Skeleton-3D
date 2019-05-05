#ifndef EDGE_HPP
#define EDGE_HPP

#include "entity.h"

Edge::Edge(Point& start_p, Point& end_p, size_t start, size_t end):
    startInd(start), endInd(end),
    startPoint(&start_p), endPoint(&end_p) {}

Edge::Edge(const Edge& input):
    startInd(input.startInd), endInd(input.endInd) {
    *startPoint = *input.startPoint;
    *endPoint = *input.endPoint;
}

void Edge::Move(double dx, double dy, double dz) {
    startPoint->Move(dx, dy, dz);
    endPoint->Move(dx, dy, dz);
}

void Edge::Rotate(const Point& center, double dx, double dy, double dz) {
    startPoint->Rotate(center, dx, dy, dz);
    endPoint->Rotate(center, dx, dy, dz);
}

void Edge::Scale(const Point& center, double dx, double dy, double dz) {
    startPoint->Scale(center, dx, dy, dz);
    endPoint->Scale(center, dx, dy, dz);
}

Surface Edge::Lift(double dx, double dy, double dz) {
    /*
     * 01     0 & 1 - 0; 1 & 2 - 1; 2 & 3 - 2; 3 & 0 - 3;
     * 32
    */

    Point p0 = *startPoint;
    Point p1 = *endPoint;
    Point p2(p1);
    Point p3(p0);

    p2.Move(dx, dy, dz);
    p3.Move(dx, dy, dz);

    Edge e0(p0, p1, 0, 1);
    Edge e1(p1, p2, 1, 2);
    Edge e2(p2, p3, 2, 3);
    Edge e3(p3, p0, 3, 0);

    std::vector<size_t> ind;
    for (size_t i = 0; i < 4; i++) {
        ind.push_back(i);
    }

    std::vector<Edge*> edges;
    edges.push_back(&e0);
    edges.push_back(&e1);
    edges.push_back(&e2);
    edges.push_back(&e3);

    Surface surf(edges, ind);

    return surf;
}

bool Edge::operator==(const Edge& input) const {
    if (this->startPoint == input.startPoint && this->endPoint == input.endPoint) {
        return true;
    } else if (this->startPoint == input.endPoint && this->endPoint == input.startPoint) {
        return true;
    }

    return false;
}

bool Edge::operator!=(const Edge& input) const {
    return !(*this == input);
}

#endif // EDGE_H_
