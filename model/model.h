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
  void addPoint(Point &point);

  // add edge to model
  void addEdge(Edge &edge);

  // add surface to model
  void addSurface(Surface &surface);

  // get points
  const vector<Point&> getPoints() const;

  //get edges
  const vector<Edge&> getEdges() const;

  // get surfaces
  const vector<Surface&> getSurfaces() const;

 private:
  // points
  vector<Point&> points;

  // edges
  vector<Edge&> edges;

  // surfaces
  vector<Surface&> surfaces;
};