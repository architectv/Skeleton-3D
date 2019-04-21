#ifndef SURFACE_H
#define SURFACE_H

#include "entity.h"
#include "edge.h"
#include "model.h"
#include <vector>
using std::vector;

class Surface : public Entity {
    public:
        Surface(vector<size_t> edgesInd_s, vector<Edge *> edges_s) :
            edgesInd(edgesInd_s), edges(edges_s) {}

        void Move(double, double, double) const;
        void Rotate(double, double, double, Point) const;
        void Scale(double, double, double, Point) const;

        Model &Lift(double);
    private:
        vector<size_t> edges_ind;
        vector<Edge *> edges;
};

#endif // SURFACE_H