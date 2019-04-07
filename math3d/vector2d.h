#ifndef VECTOR2D_H_
#define VECTOR2D_H_

#include <cassert>
#include <istream>
#include <ostream>
#include "global.h"
#include "vector3d.h"
#include "vector4d.h"

class Vector3D;
class Vector4D;

class Vector2D {
 public:
  constexpr Vector2D(float x = 0.0f, float y = 0.0f);
  explicit Vector2D(const Vector3D& vector);
  explicit Vector2D(const Vector4D& vector);

  bool IsNull() const;

  constexpr float x() const;
  constexpr float y() const;

  void set_x(float x);
  void set_y(float y);

  float& operator[](int i);
  float operator[](int i) const;

  constexpr float Length() const;
  constexpr float LengthSquared() const;
  constexpr double DoubleLengthSquared() const;

  Vector2D Normalized() const;
  void Normalize();

  float DistanceToPoint(const Vector2D& point) const;
  float DistanceToLine(const Vector2D& point, const Vector2D& direction) const;

  Vector2D& operator+=(const Vector2D& vector);
  Vector2D& operator-=(const Vector2D& vector);
  Vector2D& operator*=(float factor);
  Vector2D& operator*=(const Vector2D& vector);
  Vector2D& operator/=(float divisor);
  inline Vector2D& operator/=(const Vector2D& vector);

  constexpr static float DotProduct(const Vector2D& v1, const Vector2D& v2);
  constexpr static float SkewProduct(const Vector2D& v1, const Vector2D& v2);

  constexpr friend inline bool operator==(const Vector2D& v1, const Vector2D& v2);
  constexpr friend inline bool operator!=(const Vector2D& v1, const Vector2D& v2);
  constexpr friend inline const Vector2D operator+(const Vector2D& v1, const Vector2D& v2);
  constexpr friend inline const Vector2D operator-(const Vector2D& v1, const Vector2D& v2);
  constexpr friend inline const Vector2D operator*(float factor, const Vector2D& vector);
  constexpr friend inline const Vector2D operator*(const Vector2D& vector, float factor);
  constexpr friend inline const Vector2D operator*(const Vector2D& v1, const Vector2D& v2);
  constexpr friend inline const Vector2D operator-(const Vector2D& vector);
  constexpr friend inline const Vector2D operator/(const Vector2D& vector, float divisor);
  constexpr friend inline const Vector2D operator/(const Vector2D& vector, const Vector2D& divisor);

  constexpr friend inline bool FuzzyCompare(const Vector2D& v1, const Vector2D& v2);

  friend std::istream& operator>>(std::istream& is, Vector2D& vector);
  friend std::ostream& operator<<(std::ostream& os, const Vector2D& vector);

  constexpr Vector3D ToVector3D() const;
  constexpr Vector4D ToVector4D() const;

 private:
  float x_, y_;

  friend class Vector3D;
  friend class Vector4D;
};


constexpr inline Vector2D::Vector2D(float x, float y): x_(x), y_(y) {}

inline bool Vector2D::IsNull() const {
  return ::IsNull(x_) && ::IsNull(y_);
}

constexpr inline float Vector2D::x() const { return x_; }
constexpr inline float Vector2D::y() const { return y_; }

inline void Vector2D::set_x(float x) { x_ = x; }
inline void Vector2D::set_y(float y) { y_ = y; }

inline float& Vector2D::operator[](int i) {
  assert(static_cast<unsigned>(i) < 2u);
  return *(&x_ + i);
}

inline float Vector2D::operator[](int i) const {
  assert(static_cast<unsigned>(i) < 2u);
  return *(&x_ + i);
}

constexpr inline float Vector2D::Length() const {
  return static_cast<float>(std::sqrt(DoubleLengthSquared()));
}

constexpr inline float Vector2D::LengthSquared() const {
  return Sqr(x_) + Sqr(y_);
}

constexpr inline double Vector2D::DoubleLengthSquared() const {
  return Sqr(static_cast<double>(x_))
       + Sqr(static_cast<double>(y_));
}

inline Vector2D& Vector2D::operator+=(const Vector2D& vector) {
  x_ += vector.x_;
  y_ += vector.y_;
  return *this;
}

inline Vector2D& Vector2D::operator-=(const Vector2D& vector) {
  x_ -= vector.x_;
  y_ -= vector.y_;
  return *this;
}

inline Vector2D& Vector2D::operator*=(float factor) {
  x_ *= factor;
  y_ *= factor;
  return *this;
}

inline Vector2D& Vector2D::operator*=(const Vector2D& vector) {
  x_ *= vector.x_;
  y_ *= vector.y_;
  return *this;
}

inline Vector2D& Vector2D::operator/=(float divisor) {
  x_ /= divisor;
  y_ /= divisor;
  return *this;
}

inline Vector2D& Vector2D::operator/=(const Vector2D& vector) {
  x_ /= vector.x_;
  y_ /= vector.y_;
  return *this;
}

constexpr inline float Vector2D::DotProduct(const Vector2D& v1, const Vector2D& v2) {
  return v1.x_ * v2.x_ + v1.y_ * v2.y_;
}

constexpr inline float Vector2D::SkewProduct(const Vector2D& v1, const Vector2D& v2) {
  return v1.x_ * v2.y_ - v1.y_ * v2.x_;
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wfloat-equal"

constexpr inline bool operator==(const Vector2D& v1, const Vector2D& v2) {
  return v1.x_ == v2.x_ && v1.y_ == v2.y_;
}

constexpr inline bool operator!=(const Vector2D& v1, const Vector2D& v2) {
  return v1.x_ != v2.x_ || v1.y_ != v2.y_;
}

#pragma GCC diagnostic pop

constexpr inline const Vector2D operator+(const Vector2D& v1, const Vector2D& v2) {
  return {v1.x_ + v2.x_, v1.y_ + v2.y_};
}

constexpr inline const Vector2D operator-(const Vector2D& v1, const Vector2D& v2) {
  return {v1.x_ - v2.x_, v1.y_ - v2.y_};
}

constexpr inline const Vector2D operator*(float factor, const Vector2D& vector) {
  return {vector.x_ * factor, vector.y_ * factor};
}

constexpr inline const Vector2D operator*(const Vector2D& vector, float factor) {
  return {vector.x_ * factor, vector.y_ * factor};
}

constexpr inline const Vector2D operator*(const Vector2D& v1, const Vector2D& v2) {
  return {v1.x_ * v2.x_, v1.y_ * v2.y_};
}

constexpr inline const Vector2D operator-(const Vector2D& vector) {
  return {-vector.x_, -vector.y_};
}

constexpr inline const Vector2D operator/(const Vector2D& vector, float divisor) {
  return {vector.x_ / divisor, vector.y_ / divisor};
}

constexpr inline const Vector2D operator/(const Vector2D& vector, const Vector2D& divisor) {
  return {vector.x_ / divisor.x_, vector.y_ / divisor.y_};
}

constexpr inline bool FuzzyCompare(const Vector2D& v1, const Vector2D& v2) {
  return FuzzyCompare(v1.x_, v2.x_) && FuzzyCompare(v1.y_, v2.y_);
}

#endif  // VECTOR2D_H_
