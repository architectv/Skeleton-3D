#ifndef ENTITY_H
#define ENTITY_H

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
        Entity();
        virtual ~Entity();
        virtual void Move(const double&, const double&, const double&);
        virtual void Rotate(const double&, const double&, const double&, const Point&);
        virtual void Scale(const double&, const double&, const double&, const Point&);
};

class Point : public Entity {
    public:
        Point(double x_s, double y_s, double z_s) : x(x_s), y(y_s), z(z_s) {}
        Point(const Point&);
        Point(Point*);
        virtual ~Point();
        void Move(const double&, const double&, const double&);
        void Rotate(const double&, const double&, const double&, const Point&);
        void Scale(const double&, const double&, const double&, const Point&);

        bool operator ==(const Point& input) const;
        bool operator !=(const Point& input) const;

    private:
        double x;
        double y;
        double z;

        void rotateByX(const double& angle, const Point& center);
        void rotateByY(const double& angle, const Point& center);
        void rotateByZ(const double& angle, const Point& center);
        double scaleFormula(const double& coordinate, const double& factor, const double& center);
};

class Edge : public Entity {
    public:
        Edge(size_t start, Point& start_p, size_t end, Point& end_p) :
            startInd(start), endInd(end),
            startPoint(&start_p), endPoint(&end_p) {}
        Edge(const Edge&);
        Edge(const Edge*);

        void Move(const double&, const double&, const double&);
        void Rotate(const double&, const double&, const double&, const Point&);
        void Scale(const double&, const double&, const double&, const Point&);

        Surface Lift(const double&, const double&, const double&);

        bool operator ==(const Edge& input) const;
        bool operator !=(const Edge& input) const;

    private:
        size_t startInd;
        size_t endInd;
        Point* startPoint;
        Point* endPoint;
};

class Surface : public Entity {
    public:
        Surface(vector<size_t> edgesInd_s, vector<Edge *> edges_s);
        Surface(const Surface&);
        Surface(const Surface*);

        void Move(const double&, const double&, const double&);
        void Rotate(const double&, const double&, const double&, const Point&);
        void Scale(const double&, const double&, const double&, const Point&);

        Model &Lift(const double&);

        bool operator ==(const Surface& input) const;
        bool operator !=(const Surface& input) const;

    private:
        vector<size_t> edges_ind;
        vector<Edge *> edges;
};

class Model : public Entity {
    public:
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
        const std::vector<Point>& GetPoints() const;
        //get edges
        const std::vector<Edge>& GetEdges() const;
        // get surfaces
        const std::vector<Surface>& GetSurfaces() const;

        // is point already in model
        bool IsPointInModel(const Point &pointCheck) const;
        // is edge alredy in model
        bool IsEdgeInModel(const Edge &edgeCheck) const;
        // is surface already in model
        bool IsSurfaceInModel(const Surface &surfaceCheck) const;

        const std::string GetName() const;
        void SetName(std::string);

        void Move(const double&, const double&, const double&);
        void Rotate(const double&, const double&, const double&, const Point&);
        void Scale(const double&, const double&, const double&, const Point&);

        Model &Union(vector<Entity>);
        Model &Intersect(vector<Entity>);
        Model &Trim(vector<Entity>);

    private:
        std::string name;
        std::vector<Point> points;
        std::vector<Edge> edges;
        std::vector<Surface> surfaces;
        // glTexture texture;
};

#endif // ENTITY_H
