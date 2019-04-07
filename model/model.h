#include <iostream>
#include <vector>
using std::vector;

struct Point {
  float x;
  float y;
  float z;
  int index;

  Point(float x_s, float y_s, float z_s, int index_s) :
      x(x_s), y(y_s), z(z_s), index(index_s)
      {}  
};

struct Edge {
  const Point &start;
  const Point &finish;

  Edge(Point &start_s, Point &finish_s) :
      start(start_s), finish(finish_s)
      {}
};

struct Surface {
  int numberEdges;
  vector<Edge> edges;

  Surface(vector<Edge> edges_s) :
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

  // get points
  const vector<Point&> GetPoints() const;

  //get edges
  const vector<Edge&> GetEdges() const;

  // get surfaces
  const vector<Surface&> GetSurfaces() const;

  // is point already in model
  const bool IsPointInModel(Point &pointCheck) const;

  // is edge alredy in model
  const bool IsEdgeInModel(Edge &edgeCheck) const;

  // is surface already in model
  const bool IsSurfaceInModel(Surface &surfaceCheck) const;

 private:
  // points
  vector<Point&> points;

  // edges
  vector<Edge&> edges;

  // surfaces
  vector<Surface&> surfaces;

  const bool isEqualCoords(float one, float two) const;
  const bool isEqualPoints(Point one, Point two) const;
  const bool isEqualEdges(Edge one, Edge two) const;
  const bool isEqualSurfaces(Surface one, Surface two) const;
};