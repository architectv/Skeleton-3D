#ifndef EDGE_HPP
#define EDGE_HPP

#include "entity.h"

Edge::Edge(const Edge& input) :
    startInd(input.startInd), endInd(input.endInd) {
    *startPoint = Point(input.startPoint);
    *endPoint = Point(input.endPoint);
}

Edge::Edge(const Edge* input) :
    startInd(input->startInd), endInd(input->endInd) {
    *startPoint = Point(input->startPoint);
    *endPoint = Point(input->endPoint);
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

Surface Edge::Lift(const double& dx, const double& dy, const double& dz) {
    /*
     * 01     0 & 1 - 0; 1 & 2 - 1; 2 & 3 - 2; 3 & 0 - 3;
     * 32
    */

    Point p0 = startPoint;
    Point p1 = endPoint;
    Point p2 = Point(p1);
    p2.Move(dx, dy, dz);
    Point p3 = Point(p0);
    p3.Move(dx, dy, dz);

    Edge e0(0, p0, 1, p1);
    Edge e1(1, p1, 2, p2);
    Edge e2(2, p2, 3, p3);
    Edge e3(3, p3, 0, p0);

    std::vector<size_t> ind;
    for (size_t i = 0; i < 4; i++) {
        ind.push_back(i);
    }

    std::vector<Edge *> edges;
    edges.push_back(&e0);
    edges.push_back(&e1);
    edges.push_back(&e2);
    edges.push_back(&e3);

    Surface surf(ind, edges);
    return surf;
}

bool Edge::operator ==(const Edge& input) const {
    if (this->startPoint == input.startPoint && this->endPoint == input.endPoint) {
        return true;
    } else if (this->startPoint == input.endPoint && this->endPoint == input.startPoint) {
        return true;
    }
    return false;
}

bool Edge::operator !=(const Edge& input) const {
    if (*this == input) {
        return false;
    } else {
        return true;
    }
}

#endif // EDGE_H_
