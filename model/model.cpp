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

const bool Model::isEqualPoints(const Point &one, const Point &two) const {
  if (isEqualCoords(one.x, two.x) &&
      isEqualCoords(one.y, two.y) &&
      isEqualCoords(one.z, two.z)) {
          return true;
    }
    return false;
}

const bool Model::isEqualEdges(const Edge &one, const Edge &two) const {
    if (one.startInd == two.startInd && one.endInd == two.startInd ||
        one.endInd == two.startInd && one.startInd == two.endInd) {
             return true;
        }
    return false;
}

const bool Model::isEqualSurfaces(const Surface &one, const Surface &two) const {
    if (one.edges.size() != two.edges.size()) {
        return false;
    } else {
        size_t size = one.edges.size();
        for (size_t i = 0; i < size; i++) {
            for (size_t j = 0; j < size; j++) {
                if (isEqualEdges(edges[one.edges[i]], edges[two.edges[j]])) {
                    break;
                }
            }
            return false;
        }
        return true;
    }
}

const vector<Point> Model::GetPoints() const {
    return this->points;
}

const vector<Edge> Model::GetEdges() const {
    return this->edges;
}

const vector<Surface> Model::GetSurfaces() const {
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

const bool Model::IsPointInModel(const Point &pointCheck) const {
    for (size_t i = 0; i < points.size(); i++) {
        if (isEqualPoints(points[i], pointCheck)) {
            return true;
        }
    }
    return false;
}

const bool Model::IsEdgeInModel(const Edge &edgeCheck) const {
    for (size_t i = 0; i < edges.size(); i++) {
        if (isEqualEdges(edges[i], edgeCheck)) {
            return true;
        }
    }
    return false;
}

const bool Model::IsSurfaceInModel(const Surface &surfaceCheck) const {
    for (size_t i = 0; i < surfaces.size(); i++) {
        if (isEqualSurfaces(surfaces[i], surfaceCheck)) {
            return true;
        }
    }
    return false;
}

void Model::DeletePoint(const Point &delPoint) {
    for (size_t i = 0; i < points.size(); i++) {
        if (isEqualPoints(points[i], delPoint)) {
            for (size_t j = 0; j < edges.size(); j++) {
                if ((isEqualPoints(points[edges[i].endInd], delPoint) ||
                      isEqualPoints(points[edges[i].startInd], delPoint))) {
                          DeleteEdge(edges[j]);
                    }
            }
            points.erase(points.begin() + i);

            for (size_t j = 0; j < edges.size(); j++) {
                if (edges[i].startInd >= i) {
                    edges[i].startInd -= 1;
                }
                if (edges[i].endInd >= i) {
                    edges[i].endInd -= 1;
                }
            }
            return;
        }
    }
}

void Model::DeleteEdge(const Edge &delEdge) {
    for (size_t i = 0; i < edges.size(); i++) {
        if (isEqualEdges(edges[i], delEdge)) {
            for (size_t j = 0; j < surfaces.size(); j++) {
                bool flag = 1;
                for (size_t edge = 0; edge < surfaces[j].edges.size() && flag; edge++) {
                    if (isEqualEdges(delEdge, surfaces[j].edges.at[edge]) && flag) {
                        DeleteSurface(surfaces[j]);
                        j--;
                        flag = 0;
                    }
                }
            }
            edges.erase(edges.begin() + i);

            for (size_t j = 0; j < surfaces.size(); j++) {
                for (size_t k = 0; k < surfaces[j].edges.size(); k++) {
                    if (surfaces[j].edges[k] >= i) {
                        surfaces[j].edges[k] -= 1;
                    }
                }
            }
            return;
        }
    }
}

void Model::DeleteSurface(const Surface &delSurface) {
    for (size_t i = 0; i < surfaces.size(); i++) {
        if (isEqualSurfaces(surfaces[i], delSurface)) {
            surfaces.erase(surfaces.begin() + i);
            return;
        }
    }
}
