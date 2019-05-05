#ifndef MODEL_H
#define MODEL_H

#include "surface.h"
#include <string>
#include <vector>

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

        void Move(const double&, const double&, const double&) override;
        void Rotate(const double&, const double&, const double&, const Point&) override;
        void Scale(const double&, const double&, const double&, const Point&) override;

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

#endif // MODEL_H
