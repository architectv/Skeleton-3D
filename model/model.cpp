#include "model.h"

const bool Model::isEqualCoords(float one, float two) const {
  if (one - two < 1e-5) {
    return true;
  }
  return false;
}

const bool Model::isEqualPoints(Point one, Point two) const {
  if (isEqualCoords(one.x, two.x) &&
      isEqualCoords(one.y, two.y) &&
      isEqualCoords(one.z, two.z)) {
          return true;
      }
    return false;
}

const bool Model::isEqualEdges(Edge one, Edge two) const {
    if ( (isEqualPoints(one.start, two.start) && isEqualPoints(one.finish, two.finish)) ||
         (isEqualPoints(one.start, two.finish) && isEqualPoints(one.finish, two.start)) ) {
             return true;
         }
    return false;
}

const bool Model::isEqualSurfaces(Surface one, Surface two) const {
    if (one.edges.size() != two.edges.size()) {
        return false;
    } else {
        int size = one.numberEdges;
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (isEqualEdges(one.edges[i], two.edges[j])) {
                    break;
                }
            }
            return false;
        }
        return true;
    }
}

const vector<Point&> Model::GetPoints() const {
    return this->points;
}

const vector<Edge&> Model::GetEdges() const {
    return this->edges;
}

const vector<Surface&> Model::GetSurfaces() const {
    return this->surfaces;
}

void Model::AddPoint(Point &newPoint) {
    if (IsPointInModel(newPoint)) {
        return;
    }
    points.push_back(newPoint);
}

void Model::AddEdge(Edge &newEdge) {
    if (IsEdgeInModel(newEdge)) {
        return;
    }
    edges.push_back(newEdge);
}

void Model::AddSurface(Surface &newSurface) {
    if (IsSurfaceInModel(newSurface)) {
        return;
    }
    surfaces.push_back(newSurface);
}

const bool Model::IsPointInModel(Point &pointCheck) const {
    for (Point pointData: points) {
        if (isEqualPoints(pointData, pointCheck)) {
            return true;
        }
    }
    return false;
}

const bool Model::IsEdgeInModel(Edge &edgeCheck) const {
    for (Edge edgeData: edges) {
        if (isEqualEdges(edgeData, edgeCheck)) {
            return true;
        }
    }
    return false;
}

const bool Model::IsSurfaceInModel(Surface &surfaceCheck) const {
    for (Surface surfaceData: surfaces) {
        if (isEqualSurfaces(surfaceData, surfaceCheck)) {
            return true;
        }
    }
    return false;
}