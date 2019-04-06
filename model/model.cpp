#include "model.h"

const vector<Point&> Model::getPoints() const {
    return this->points;
}

const vector<Edge&> Model::getEdges() const {
    return this->edges;
}

const vector<Surface&> Model::getSurfaces() const {
    return this->surfaces;
}

void Model::addPoint(Point &point) {
    points.push_back(point);
}

void Model::addEdge(Edge &edge) {
    edges.push_back(edge);
}

void Model::addSurface(Surface &surface) {
    surfaces.push_back(surface);
}