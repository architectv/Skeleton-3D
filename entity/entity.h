#ifndef ENTITY_H
#define ENTITY_H

#include "point.h"

class Entity {
    public:
        virtual void Move(double, double, double);
        virtual void Rotate(double, double, double, Point);
        virtual void Scale(double, double, double, Point);
};

#endif // ENTITY_H