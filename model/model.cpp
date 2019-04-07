#include "model.h"

Model::Model() {}

Model::~Model() {
    points.clear();
    edges.clear();
    surfaces.clear();
}
const bool Model::isEqualCoords(float one, float two) const {
  if (one - two < 1e-5) {
    return true;
  }
  return false;
}

const bool Model::isEqualPoints(const Point *one, const Point *two) const {
  if (isEqualCoords(one->x, two->x) &&
      isEqualCoords(one->y, two->y) &&
      isEqualCoords(one->z, two->z)) {
          return true;
    }
    return false;
}

const bool Model::isEqualEdges(const Edge *one, const Edge *two) const {
    if ( (isEqualPoints(one->start, two->start) && isEqualPoints(one->finish, two->finish)) ||
         (isEqualPoints(one->start, two->finish) && isEqualPoints(one->finish, two->start)) ) {
             return true;
         }
    return false;
}

const bool Model::isEqualSurfaces(const Surface *one, const Surface *two) const {
    if (one->edges.size() != two->edges.size()) {
        return false;
    } else {
        size_t size = one->numberEdges;
        for (size_t i = 0; i < size; i++) {
            for (size_t j = 0; j < size; j++) {
                if (isEqualEdges(one->edges[i], two->edges[j])) {
                    break;
                }
            }
            return false;
        }
        return true;
    }
}

const vector<Point *> Model::GetPoints() const {
    return this->points;
}

const vector<Edge *> Model::GetEdges() const {
    return this->edges;
}

const vector<Surface *> Model::GetSurfaces() const {
    return this->surfaces;
}

void Model::AddPoint(Point *newPoint) {
    if (IsPointInModel(newPoint)) {
        return;
    }
    points.push_back(newPoint);
}

void Model::AddEdge(Edge *newEdge) {
    if (IsEdgeInModel(newEdge)) {
        return;
    }
    edges.push_back(newEdge);
}

void Model::AddSurface(Surface *newSurface) {
    if (IsSurfaceInModel(newSurface)) {
        return;
    }
    surfaces.push_back(newSurface);
}

const bool Model::IsPointInModel(const Point *pointCheck) const {
    for (size_t i = 0; i < points.size(); i++) {
        if (isEqualPoints(points[i], pointCheck)) {
            return true;
        }
    }
    return false;
}

const bool Model::IsEdgeInModel(const Edge *edgeCheck) const {
    for (size_t i = 0; i < edges.size(); i++) {
        if (isEqualEdges(edges[i], edgeCheck)) {
            return true;
        }
    }
    return false;
}

const bool Model::IsSurfaceInModel(const Surface *surfaceCheck) const {
    for (size_t i = 0; i < surfaces.size(); i++) {
        if (isEqualSurfaces(surfaces[i], surfaceCheck)) {
            return true;
        }
    }
    return false;
}

void Model::DeletePoint(const Point *delPoint) {
    for (size_t i = 0; i < points.size(); i++) {
        if (isEqualPoints(points[i], delPoint)) {
            points.erase(points.begin() + i);
            return;
        }
    }
}

void Model::DeleteEdge(const Edge *delEdge) {
    for (size_t i = 0; i < edges.size(); i++) {
        if (isEqualEdges(edges[i], delEdge)) {
            edges.erase(edges.begin() + i);
            return;
        }
    }
}

void Model::DeleteSurface(const Surface *delSurface) {
    for (size_t i = 0; i < surfaces.size(); i++) {
        if (isEqualSurfaces(surfaces[i], delSurface)) {
            surfaces.erase(surfaces.begin() + i);
            return;
        }
    }
}
