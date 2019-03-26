#include "model.h"

const size_t Model::CountPoints() const {
    return this->numberPoints;
}

const size_t Model::CountEdges() const {
    return this->numberEdges;
}

const size_t Model::CountSurface() const {
    return this->numberSurface;
}