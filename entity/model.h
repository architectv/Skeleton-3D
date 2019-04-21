#ifndef MODEL_H
#define MODEL_H

#include "entity.h"
#include "point.h"
#include "edge.h"
#include "surface.h"
#include <string>
#include <vector>
using std::string;
using std::vector;

class Model : public Entity {
    public:
        Model();
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
        
        const string GetName() const;
        void SetName(string);

        Model &Union(vector<Entity>);
        Model &Intersect(vector<Entity>);
        Model &Trim(vector<Entity>);

    private:
        string name;
        vector<Point> points;
        vector<Edge> edges;
        vector<Surface> surfaces;
        // glTexture texture;
};

#endif // MODEL_H