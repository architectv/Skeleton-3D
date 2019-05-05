#ifndef SURFACE_H
#define SURFACE_H

#include "edge.h"
#include <vector>
using std::vector;

class Model;
class Surface : public Entity {
    public:
        Surface(vector<size_t> edgesInd_s, vector<Edge *> edges_s);

        void Move(const double&, const double&, const double&);
        void Rotate(const double&, const double&, const double&, const Point&);
        void Scale(const double&, const double&, const double&, const Point&);

        Model &Lift(const double&);
    private:
        vector<size_t> edges_ind;
        vector<Edge *> edges;
};

Surface::Surface(vector<size_t> edgesInd_s, vector<Edge *> edges_s) {
    edges_ind = edgesInd_s;
    edges = edges_s;
}

#endif // SURFACE_H
