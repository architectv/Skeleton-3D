#ifndef _MODEL_H
#define _MODEL_H

#include <iostream>
#include <vector>
#include <stdlib.h>
using std::vector;

typedef struct Point_t {
  float x;
  float y;
  float z;
  int index;

  Point_t(float x_s, float y_s, float z_s, int index_s) :
      x(x_s), y(y_s), z(z_s), index(index_s)
      {}  
} Point;

typedef struct Edge_t {
  const Point *start;
  const Point *finish;

  Edge_t(Point *start_s, Point *finish_s) :
      start(start_s), finish(finish_s)
      {}
} Edge;

typedef struct Surface_t {
  int numberEdges;
  vector<Edge *> edges;

  Surface_t(vector<Edge *> edges_s) :
          edges(edges_s)
          {}
} Surface;

class Model {
 public:
  // constructor
  Model();

  // destructor
  ~Model();

  // add point to model
  void AddPoint(Point *newPoint);

  // add edge to model
  void AddEdge(Edge *newEdge);

  // add surface to model
  void AddSurface(Surface *newSurface);

  // delete point from model
  void DeletePoint(const Point *delPoint);

  // delete Edge from model
  void DeleteEdge(const Edge *delEdge);

  // delete Surface from model
  void DeleteSurface(const Surface *delSurface);

  // get points
  const vector<Point *> GetPoints() const;

  //get edges
  const vector<Edge *> GetEdges() const;

  // get surfaces
  const vector<Surface *> GetSurfaces() const;

  // is point already in model
  const bool IsPointInModel(const Point *pointCheck) const;

  // is edge alredy in model
  const bool IsEdgeInModel(const Edge *edgeCheck) const;

  // is surface already in model
  const bool IsSurfaceInModel(const Surface *surfaceCheck) const;

 private:
  // points
  vector<Point *> points;

  // edges
  vector<Edge *> edges;

  // surfaces
  vector<Surface *> surfaces;

  const bool isEqualCoords(const float one, const float two) const;
  const bool isEqualPoints(const Point * one, const Point *two) const;
  const bool isEqualEdges(const Edge *one, const Edge *two) const;
  const bool isEqualSurfaces(const Surface *one, const Surface *two) const;
};

#endif // _MODEL_H