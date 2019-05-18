#ifndef TRANSFORM_H_
#define TRANSFORM_H_

#include <cmath>
#include <initializer_list>
#include <istream>
#include <ostream>
#include "global.h"
#include "matrix.h"
#include "vector.h"

class Transform {
 public:
  constexpr Transform() noexcept;
  constexpr Transform(const std::initializer_list<float>& list) noexcept;

  constexpr Transform& Translate(const Vector3& delta);
  constexpr Transform& Scale(const Vector3& factor);
  Transform& RotateX(float angle);
  Transform& RotateY(float angle);
  Transform& RotateZ(float angle);

  constexpr Vector3 map(const Vector3& vector);

  friend std::istream& operator>>(std::istream& is, Transform& transform);
  friend std::ostream& operator<<(std::ostream& os, const Transform& transform);

 protected:
  Matrix4 matrix_;
};

constexpr Transform::Transform() noexcept: matrix_(Matrix4::identity()) {}

constexpr Transform::Transform(const std::initializer_list<float>& list) noexcept: matrix_(list) {}

constexpr Transform& Transform::Translate(const Vector3& delta) {
  matrix_ *= Matrix4({
    1, 0, 0, delta.x(),
    0, 1, 0, delta.y(),
    0, 0, 1, delta.z(),
    0, 0, 0,         1
  });
  return *this;
}

constexpr Transform& Transform::Scale(const Vector3& factor) {
  matrix_ *= Matrix4({
    factor.x(),          0,          0, 0,
             0, factor.y(),          0, 0,
             0,          0, factor.z(), 0,
             0,          0,          0, 1
  });
  return *this;
}

Transform& Transform::RotateX(float angle) {
  angle = ToRadians(angle);
  const float s = std::sin(angle);
  const float c = std::cos(angle);

  matrix_ *= Matrix4({
    1, 0,  0, 0,
    0, c, -s, 0,
    0, s,  c, 0,
    0, 0,  0, 1
  });

  return *this;
}

Transform& Transform::RotateY(float angle) {
  angle = ToRadians(angle);
  const float s = std::sin(angle);
  const float c = std::cos(angle);

  matrix_ *= Matrix4({
     c, 0, s, 0,
     0, 1, 0, 0,
    -s, 0, c, 0,
     0, 0, 0, 1
  });

  return *this;
}

Transform& Transform::RotateZ(float angle) {
  angle = ToRadians(angle);
  const float s = std::sin(angle);
  const float c = std::cos(angle);

  matrix_ *= Matrix4({
    c, -s, 0, 0,
    s,  c, 0, 0,
    0,  0, 1, 0,
    0,  0, 0, 1
  });

  return *this;
}

constexpr Vector3 Transform::map(const Vector3& vector) {
  return matrix_ * vector;
}

std::istream& operator>>(std::istream& is, Transform& transform) {
  is >> transform.matrix_;
  return is;
}

std::ostream& operator<<(std::ostream& os, const Transform& transform) {
  os << transform.matrix_;
  return os;
}

#endif  // TRANSFORM_H_
