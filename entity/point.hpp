#ifndef POINT_HPP
#define POINT_HPP

#include "entity.h"

#define _USE_MATH_DEFINES
#include <math.h>

Point::~Point() {}

Point::Point():
    x(0), y(0), z(0) {}

Point::Point(double x_s, double y_s, double z_s):
    x(x_s), y(y_s), z(z_s) {}

Point::Point(const Point& input) {
    x = input.x;
    y = input.y;
    z = input.z;
}

Point::Point(std::initializer_list<double> input) {
    if (input.size() != 3) {
        return;
    }

    x = *input.begin();
    y = *(input.begin() + 1);
    z = *input.end();
}

void Point::rotateByX(const Point& center, double angle) {
    const double a = y, b = z, c = center.y, d = center.z;
    const double cos_a = cos(angle), sin_a = sin(angle);

    const double new_a = c + (a - c) * cos_a + (b - d) * sin_a;
    const double new_b = d - (a - c) * sin_a + (b - d) * cos_a;

    y = new_a;
    z = new_b;
}

void Point::rotateByY(const Point& center, double angle) {
    const double a = x, b = z, c = center.x, d = center.z;
    const double cos_a = cos(angle), sin_a = sin(angle);

    const double new_a = c + (a - c) * cos_a + (b - d) * sin_a;
    const double new_b = d - (a - c) * sin_a + (b - d) * cos_a;

    x = new_a;
    z = new_b;
}

void Point::rotateByZ(const Point& center, double angle) {
    const double a = x, b = y, c = center.x, d = center.y;
    const double cos_a = cos(angle), sin_a = sin(angle);

    const double new_a = c + (a - c) * cos_a + (b - d) * sin_a;
    const double new_b = d - (a - c) * sin_a + (b - d) * cos_a;

    x = new_a;
    y = new_b;
}

void Point::Move(double dx, double dy, double dz) {
    x += dx;
    y += dy;
    z += dz;
}

void DegreesToRadian(double *coord) {
    *coord *= M_PI / 180;
}

void Point::Rotate(const Point& center, double dx, double dy, double dz) {
    DegreesToRadian(&dx);
    DegreesToRadian(&dy);
    DegreesToRadian(&dz);

    rotateByX(center, dx);
    rotateByY(center, dy);
    rotateByZ(center, dz); 
}

void Point::Scale(const Point& center, double dx, double dy, double dz) {
    x = scaleFormula(center.x, x, dx);
    y = scaleFormula(center.y, y, dy);
    z = scaleFormula(center.z, z, dz);
}

double Point::scaleFormula(double center, double coordinate, double factor) {
    return coordinate * factor + (1 - factor) * center;
}

bool Point::operator==(const Point& input) const {
    const double eps = 1e-05;

    if (fabs(x - input.x) < eps) {
        if (fabs(y - input.y) < eps) {
            if (fabs(z - input.z) < eps) {
                return true;
            }
        }
    }

    return false;
}

bool Point::operator!=(const Point& input) const {
    return !(*this == input);
}

#endif // POINT_H
