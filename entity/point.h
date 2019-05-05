#ifndef POINT_H
#define POINT_H

#include "entity.h"

#include <cmath>

class Point : public Entity {
    public:
        Point(float x_s, float y_s, float z_s) : x(x_s), y(y_s), z(z_s) {}
        void Move(const double&, const double&, const double&);
        void Rotate(const double&, const double&, const double&, const Point&);
        void Scale(const double&, const double&, const double&, const Point&);
    
    private:
        float x;
        float y;
        float z;

        void rotateByX(const double& angle, const Point& center);
        void rotateByY(const double& angle, const Point& center);
        void rotateByZ(const double& angle, const Point& center);
        double scaleFormula(const double& coordinate, const double& factor, const double& center);
};

void Point::rotateByX(const double& angle, const Point& center) {
    const double a = y, b = z, c = center.y, d = center.z;
    const double cos_a = cos(angle), sin_a = sin(angle);

    const double new_a = c + (a - c) * cos_a + (b - d) * sin_a;
    const double new_b = d - (a - c) * sin_a + (b - d) * cos_a;

    y = new_a;
    z = new_b;
}

void Point::rotateByY(const double& angle, const Point& center) {
    const double a = x, b = z, c = center.x, d = center.z;
    const double cos_a = cos(angle), sin_a = sin(angle);

    const double new_a = c + (a - c) * cos_a + (b - d) * sin_a;
    const double new_b = d - (a - c) * sin_a + (b - d) * cos_a;

    x = new_a;
    z = new_b;
}

void Point::rotateByZ(const double& angle, const Point& center) {
    const double a = x, b = y, c = center.x, d = center.y;
    const double cos_a = cos(angle), sin_a = sin(angle);

    const double new_a = c + (a - c) * cos_a + (b - d) * sin_a;
    const double new_b = d - (a - c) * sin_a + (b - d) * cos_a;

    x = new_a;
    y = new_b;
}

void Point::Move(const double& dx, const double& dy, const double& dz) {
    x += dx;
    y += dy;
    z += dz;
}

void Point::Rotate(const double& dx, const double& dy, const double& dz, const Point& center) {
    rotateByX(dx, center);
    rotateByY(dy, center);
    rotateByZ(dz, center); 
}

void Point::Scale(const double& dx, const double& dy, const double& dz, const Point& center) {
    x = scaleFormula(x, dx, center.x);
    y = scaleFormula(y, dy, center.y);
    z = scaleFormula(z, dz, center.z);
}

double Point::scaleFormula(const double& coordinate, const double& factor, const double& center) {
    return coordinate * factor + (1 - factor) * center;
}

#endif // POINT_H