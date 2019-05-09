#ifndef SURFACE_H
#define SURFACE_H

#include "entity.h"

Surface::Surface(vector<Edge*> edges_s, vector<size_t> edgesInd_s) {
    edges_ind = edgesInd_s;
    edges = edges_s;
}

Surface::Surface(const Surface& input) {
    edges_ind = input.edges_ind;
    edges.resize(edges_ind.size(), nullptr);

    for (size_t i = 0; i < input.edges.size(); ++i) {
        *edges[i] = *input.edges[i];
    }
}

bool Surface::operator==(const Surface& input) const {
    if (this->edges.size() != input.edges.size()) {
        return false;
    }

    size_t size = this->edges.size();
    for (size_t i = 0; i < size; ++i) {
        bool check = true;

        for (size_t j = 0; j < size && check; ++j) {
            if (this->edges[i] == input.edges[j]) {
                check = false;
            }
        }

        if (check) {
            return false;
        }
    }
    
    return true;
}

bool Surface::operator!=(const Surface& input) const {
    return !(*this == input);
}

vector<Point *> Surface::getPointsFromThis() const {
    vector<Point*> surfacePoints;
    for (int i = 0; i < edges.size(); ++i) {
        Edge *tmp = edges[i];
        bool p1st = true, p2st = true;
        for (int j = 0; j < surfacePoints.size() && (p1st || p2st); ++j) {
            if (*(tmp->startPoint) == *surfacePoints[j]) {
                p1st = false;
            }
            if (*(tmp->endPoint) == *surfacePoints[j]) {
                p2st = false;
            }
        }
        if (p1st) {
            surfacePoints.push_back(tmp->startPoint);
        }
        if (p2st) {
            surfacePoints.push_back(tmp->endPoint);
        }
    }
    return surfacePoints;
}

void Surface::Move(double dx, double dy, double dz) {
    vector<Point*> surfacePoints = getPointsFromThis();
    for (int i = 0; i < surfacePoints.size(); ++i) {
        Point *tmp = surfacePoints.at(i);
        tmp->Move(dx, dy, dz);
    }
}
void Surface::Rotate(const Point& center, double dx, double dy, double dz) {
    vector<Point*> surfacePoints = getPointsFromThis();
    for (int i = 0; i < surfacePoints.size(); ++i) {
        Point *tmp = surfacePoints.at(i);
        tmp->Rotate(center, dx, dy, dz);
    }
}
void Surface::Scale(const Point& center, double dx, double dy, double dz) {
    vector<Point*> surfacePoints = getPointsFromThis();
    for (int i = 0; i < surfacePoints.size(); ++i) {
        Point *tmp = surfacePoints.at(i);
        tmp->Scale(center, dx, dy, dz);
    }
}

#endif // SURFACE_H
