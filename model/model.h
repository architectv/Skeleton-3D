#ifndef _MODEL_H
#define _MODEL_H

#include <iostream>
#include <vector>
#include <stdlib.h>
#include <math.h>
using std::vector;

struct Point {
  float x;
  float y;
  float z;

  Point(float x_s, float y_s, float z_s) :
      x(x_s), y(y_s), z(z_s)
      {}  
};

struct Edge {
  int startInd;
  int endInd;

  Edge(int start, int end) :
      startInd(start), endInd(end)
      {}
};

struct Surface {
  vector<int> edges;

  Surface(vector<int> edges_s) :
          edges(edges_s)
          {}
};

class Model {
 public:
  // constructor
  Model();

  // destructor
  ~Model();

  // add point to model
  void AddPoint(Point &newPoint);

  // add edge to model
  void AddEdge(Edge &newEdge);

  // add surface to model
  void AddSurface(Surface &newSurface);

  // delete point from model
  void DeletePoint(const Point &delPoint);

  // delete Edge from model
  void DeleteEdge(const Edge &delEdge);

  // delete Surface from model
  void DeleteSurface(const Surface &delSurface);

  // get points
  const vector<Point> GetPoints() const;

  //get edges
  const vector<Edge> GetEdges() const;

  // get surfaces
  const vector<Surface> GetSurfaces() const;

  // is point already in model
  const bool IsPointInModel(const Point &pointCheck) const;

  // is edge alredy in model
  const bool IsEdgeInModel(const Edge &edgeCheck) const;

  // is surface already in model
  const bool IsSurfaceInModel(const Surface &surfaceCheck) const;

  // print data about model in terminal
  void PrintData() const;

 private:
  // points
  vector<Point> points;

  // edges
  vector<Edge> edges;

  // surfaces
  vector<Surface> surfaces;

  const bool isEqualCoords(const float one, const float two) const;
  const bool isEqualPoints(const Point &one, const Point &two) const;
  const bool isEqualEdges(const Edge &one, const Edge &two) const;
  const bool isEqualSurfaces(const Surface &one, const Surface &two) const;
};

#endif // _MODEL_H