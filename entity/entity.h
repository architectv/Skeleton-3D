#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>
#include <vector>
#include <string>

using std::vector;
using std::string;

class Model;
class Surface;
class Edge;
class Point;

class Entity {
 public:
    Entity() {}
    virtual ~Entity() {}

    virtual void Move(double, double, double) = 0;
    virtual void Rotate(const Point&, double, double, double) = 0;
    virtual void Scale(const Point&, double, double, double) = 0;
};

class Point: public Entity {
 public:
    Point();
    Point(double, double, double);
    Point(const Point&);
    Point(std::initializer_list<double>);

    virtual ~Point();

    void Move(double, double, double);
    void Rotate(const Point& center, double dx, double dy, double dz);
    void Scale(const Point& center, double dx, double dy, double dz);

    bool operator==(const Point&) const;
    bool operator!=(const Point&) const;

 private:
    double x = 0;
    double y = 0;
    double z = 0;

    void rotateByX(const Point& center, double angle);
    void rotateByY(const Point& center, double angle);
    void rotateByZ(const Point& center, double angle);

    double scaleFormula(double center, double coordinate, double factor);
};

class Edge: public Entity {
 public:
    friend class Surface;
    friend class Model;
    Edge(Point& start_p, Point& end_p, size_t start, size_t end);
    Edge(const Edge&);

    void Move(double, double, double);
    void Rotate(const Point& center, double dx, double dy, double dz);
    void Scale(const Point& center, double dx, double dy, double dz);

    Surface Lift(double, double, double);

    bool operator==(const Edge&) const;
    bool operator!=(const Edge&) const;

 private:
    size_t startInd;
    size_t endInd;

    Point* startPoint;
    Point* endPoint;
};

class Surface: public Entity {
 public:
    friend class Edge;
    friend class Model;
    Surface(vector<Edge*> edges_s, vector<size_t> edgesInd_s);
    Surface(const Surface&);

    void Move(double, double, double);
    void Rotate(const Point& center, double dx, double dy, double dz);
    void Scale(const Point& center, double dx, double dy, double dz);

    Model& Lift(double);

    bool operator==(const Surface& input) const;
    bool operator!=(const Surface& input) const;

 private:
    vector<size_t> edges_ind;
    vector<Edge*> edges;

    vector<Point *> getPointsFromThis() const;
};

class Model : public Entity {
 public:
    friend class Edge;
    friend class Surface;
    Model();

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
    const std::vector<Point*>& GetPoints() const;
    //get edges
    const std::vector<Edge*>& GetEdges() const;
    // get surfaces
    const std::vector<Surface*>& GetSurfaces() const;

    // is point already in model
    bool IsPointInModel(const Point &pointCheck) const;
    // is edge alredy in model
    bool IsEdgeInModel(const Edge &edgeCheck) const;
    // is surface already in model
    bool IsSurfaceInModel(const Surface &surfaceCheck) const;

    const std::string GetName() const;
    void SetName(std::string);

    void Move(double, double, double);
    void Rotate(const Point& center, double dx, double dy, double dz);
    void Scale(const Point& center, double dx, double dy, double dz);

    Model &Union(vector<Entity>);
    Model &Intersect(vector<Entity>);
    Model &Trim(vector<Entity>);

 private:
    std::string name;
    std::vector<Point*> points;
    std::vector<Edge*> edges;
    std::vector<Surface*> surfaces;
    vector<Point *> getPointsFromThis() const;
    // glTexture texture;
};

#endif // ENTITY_H
