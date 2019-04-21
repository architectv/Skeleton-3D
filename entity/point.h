#ifndef POINT_H
#define POINT_H

#include "entity.h"

class Point : public Entity {
    public:
        Point(float x_s, float y_s, float z_s) : x(x_s), y(y_s), z(z_s) {}
        void Move(double, double, double);
        void Rotate(double, double, double, Point);
        void Scale(double, double, double, Point);
    
    private:
        float x;
        float y;
        float z;
};

#endif // POINT_H