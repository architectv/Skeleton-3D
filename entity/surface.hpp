#ifndef SURFACE_H
#define SURFACE_H

#include "entity.h"

#include <vector>
using std::vector;

Surface::Surface(vector<Edge*> edges_s, vector<size_t> edgesInd_s) {
    edges_ind = edgesInd_s;
    edges = edges_s;
}

Surface::Surface(const Surface& input) {
    edges_ind = input.edges_ind;
    edges.resize(edges_ind.size(), nullptr);

    for (size_t i = 0; i < input.edges.size(); ++i) {
        *edges[i] = *input.edges[i];
    }
}

bool Surface::operator==(const Surface& input) const {
    if (this->edges.size() != input.edges.size()) {
        return false;
    } else {
        size_t size = this->edges.size();
        for (size_t i = 0; i < size; i++) {
            bool check = true;
            for (size_t j = 0; j < size && check; j++) {
                if (this->edges[i] == input.edges[j]) {
                    check = false;
                }
            }
            if (check == true) {
                return false;
            }
        }
        return true;
    }
}

bool Surface::operator!=(const Surface& input) const {
    return !(*this == input);
}

#endif // SURFACE_H
