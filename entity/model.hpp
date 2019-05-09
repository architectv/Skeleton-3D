#ifndef MODEL_H
#define MODEL_H

#include "entity.h"

Model::~Model() {
    points.clear();
    edges.clear();
    surfaces.clear();
}

const vector<Point*>& Model::GetPoints() const {
    return this->points;
}

const vector<Edge*>& Model::GetEdges() const {
    return this->edges;
}

const vector<Surface*>& Model::GetSurfaces() const {
    return this->surfaces;
}

void Model::AddPoint(Point &newPoint) {
    if (IsPointInModel(newPoint)) {
        return;
    }
    points.push_back(&newPoint);
}

void Model::AddEdge(Edge &newEdge) {
    if (IsEdgeInModel(newEdge)) {
        return;
    }
    edges.push_back(&newEdge);
}

void Model::AddSurface(Surface &newSurface) {
    if (IsSurfaceInModel(newSurface)) {
        return;
    }
    surfaces.push_back(&newSurface);
}

bool Model::IsPointInModel(const Point &pointCheck) const {
    for (size_t i = 0; i < points.size(); i++) {
        if (*points[i] == pointCheck) {
            return true;
        }
    }
    return false;
}

bool Model::IsEdgeInModel(const Edge &edgeCheck) const {
    for (size_t i = 0; i < edges.size(); i++) {
        if (*edges[i] == edgeCheck) {
            return true;
        }
    }
    return false;
}

bool Model::IsSurfaceInModel(const Surface &surfaceCheck) const {
    for (size_t i = 0; i < surfaces.size(); i++) {
        if (*surfaces[i] == surfaceCheck) {
            return true;
        }
    }
    return false;
}

void Model::DeletePoint(const Point &delPoint) {
    for (size_t i = 0; i < points.size(); i++) {
        if (*points[i] == delPoint) {
            for (size_t j = 0; j < edges.size(); j++) {
                if (*points[edges[j]->endInd] == delPoint ||
                    *points[edges[j]->startInd] == delPoint) {
                          DeleteEdge(*edges[j]);
                    }
            }
            points.erase(points.begin() + i);

            for (size_t j = 0; j < edges.size(); j++) {
                if (edges[i]->startInd >= i) {
                    edges[i]->startInd -= 1;
                }
                if (edges[i]->endInd >= i) {
                    edges[i]->endInd -= 1;
                }
            }
            return;
        }
    }
}

void Model::DeleteEdge(const Edge &delEdge) {
    for (size_t i = 0; i < edges.size(); i++) {
        if (*edges[i] == delEdge) {
            for (size_t j = 0; j < surfaces.size(); j++) {
                bool flag = 1;
                for (size_t edge = 0; edge < surfaces[j]->edges.size() && flag; edge++) {
                    if (delEdge == *surfaces[j]->edges[edge] && flag) {
                        DeleteSurface(*surfaces[j]);
                        j--;
                        flag = 0;
                    }
                }
            }
            edges.erase(edges.begin() + i);

            for (size_t j = 0; j < surfaces.size(); j++) {
                for (size_t k = 0; k < surfaces[j]->edges.size(); k++) {
                    if (surfaces[j]->edges_ind[k] >= i) {
                        surfaces[j]->edges_ind[k] -= 1;
                    }
                }
            }
            return;
        }
    }
}

void Model::DeleteSurface(const Surface &delSurface) {
    for (size_t i = 0; i < surfaces.size(); i++) {
        if (*surfaces[i] == delSurface) {
            surfaces.erase(surfaces.begin() + i);
            return;
        }
    }
}

vector<Point *> Model::getPointsFromThis() const {
    vector<Point*> modelPoints;
    for (int i = 0; i < points.size(); ++i) {
        bool pSt = true;
        Point *tmp = points[i];
        for (int j = 0; j < modelPoints.size() && pSt; ++j) {
            if (*tmp == *modelPoints[j]) {
                pSt = false;
            }
        }
        if (pSt) {
            modelPoints.push_back(tmp);
        }
    }

    for (int i = 0; i < edges.size(); ++i) {
        Edge *tmp = edges[i];
        bool p1st = true, p2st = true;
        for (int j = 0; j < modelPoints.size() && (p1st || p2st); ++j) {
            if (*(tmp->startPoint) == *modelPoints[j]) {
                p1st = false;
            }
            if (*(tmp->endPoint) == *modelPoints[j]) {
                p2st = false;
            }
        }
        if (p1st) {
            modelPoints.push_back(tmp->startPoint);
        }
        if (p2st) {
            modelPoints.push_back(tmp->endPoint);
        }
    }
    for (int i = 0; i < surfaces.size(); ++i) {
        vector<Point*> pointsFromSurface = surfaces[i]->getPointsFromThis();
        for (int j = 0; j < pointsFromSurface.size(); ++j) {
            bool status = true;
            for (int k = 0; k < modelPoints.size() && status; ++k) {
                if (pointsFromSurface[j] == modelPoints[k]) {
                    status = false;
                }
            }
            if (status) {
                modelPoints.push_back(pointsFromSurface[j]);
            }
        }
    }
    return modelPoints;
}

void Model::Move(double dx, double dy, double dz) {
    vector<Point*> modelPoints = getPointsFromThis();
    for (int i = 0; i < modelPoints.size(); ++i) {
        Point *tmp = modelPoints.at(i);
        tmp->Move(dx, dy, dz);
    }
}
void Model::Rotate(const Point& center, double dx, double dy, double dz) {
    vector<Point*> modelPoints = getPointsFromThis();
    for (int i = 0; i < modelPoints.size(); ++i) {
        Point *tmp = modelPoints.at(i);
        tmp->Rotate(center, dx, dy, dz);
    }
}
void Surface::Scale(const Point& center, double dx, double dy, double dz) {
    vector<Point*> modelPoints = getPointsFromThis();
    for (int i = 0; i < modelPoints.size(); ++i) {
        Point *tmp = modelPoints.at(i);
        tmp->Scale(center, dx, dy, dz);
    }
}

/*
void Model::PrintData() const {
    printf("\n");
    printf("==================\n");
    printf("Points");
    for (size_t i = 0; i < points.size(); i++) {
        printf("\n%lu. x = %f; y = %f; z = %f;", i, points[i].x, points[i].y, points[i].z);
    }
    printf("\n");
    printf("==================\n");
    printf("Edges");
    for (size_t i = 0; i < edges.size(); i++) {
        printf("\n%lu. start = %d; end = %d;", i, edges[i].startInd, edges[i].endInd);
    }
    printf("\n");
    printf("==================\n");
    printf("Surfaces");
    for (size_t i = 0; i < surfaces.size(); i++) {
        printf("\n%lu.", i);
        for (size_t j = 0; j < surfaces[i].edges.size(); j++) {
            printf(" %d,", surfaces[i].edges[j]);
        }
    }
}*/

#endif // MODEL_H
