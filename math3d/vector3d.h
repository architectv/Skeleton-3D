#ifndef VECTOR3D_H_
#define VECTOR3D_H_

#include <cassert>
#include <istream>
#include <ostream>
#include "global.h"
#include "vector2d.h"
#include "vector4d.h"

class Vector2D;
class Vector4D;

class Vector3D {
 public:
  constexpr Vector3D(float x = 0.0f, float y = 0.0f, float z = 0.0f);
  Vector3D(const Vector2D& vector, float z = 0.0f);
  explicit Vector3D(const Vector4D& vector);

  bool IsNull() const;

  constexpr float x() const;
  constexpr float y() const;
  constexpr float z() const;

  void set_x(float x);
  void set_y(float y);
  void set_z(float z);

  float& operator[](int i);
  float operator[](int i) const;

  constexpr float Length() const;
  constexpr float LengthSquared() const;
  constexpr double DoubleLengthSquared() const;

  Vector3D Normalized() const;
  void Normalize();

  Vector3D& operator+=(const Vector3D& vector);
  Vector3D& operator-=(const Vector3D& vector);
  Vector3D& operator*=(float factor);
  Vector3D& operator*=(const Vector3D& vector);
  Vector3D& operator/=(float divisor);
  inline Vector3D& operator/=(const Vector3D& vector);

  constexpr static float DotProduct(const Vector3D& v1, const Vector3D& v2);
  constexpr static Vector3D CrossProduct(const Vector3D& v1, const Vector3D& v2);

  static Vector3D Normal(const Vector3D& v1, const Vector3D& v2);
  static Vector3D Normal(const Vector3D& v1, const Vector3D& v2, const Vector3D& v3);

  float DistanceToPoint(const Vector3D& point) const;
  float DistanceToPlane(const Vector3D& plane, const Vector3D& normal) const;
  float DistanceToPlane(const Vector3D& plane1, const Vector3D& plane2, const Vector3D& plane3) const;
  float DistanceToLine(const Vector3D& point, const Vector3D& direction) const;

  constexpr friend inline bool operator==(const Vector3D& v1, const Vector3D& v2);
  constexpr friend inline bool operator!=(const Vector3D& v1, const Vector3D& v2);
  constexpr friend inline const Vector3D operator+(const Vector3D& v1, const Vector3D& v2);
  constexpr friend inline const Vector3D operator-(const Vector3D& v1, const Vector3D& v2);
  constexpr friend inline const Vector3D operator*(float factor, const Vector3D& vector);
  constexpr friend inline const Vector3D operator*(const Vector3D& vector, float factor);
  constexpr friend inline const Vector3D operator*(const Vector3D& v1, const Vector3D& v2);
  constexpr friend inline const Vector3D operator-(const Vector3D& vector);
  constexpr friend inline const Vector3D operator/(const Vector3D& vector, float divisor);
  constexpr friend inline const Vector3D operator/(const Vector3D& vector, const Vector3D& divisor);

  constexpr friend inline bool FuzzyCompare(const Vector3D& v1, const Vector3D& v2);

  friend std::istream& operator>>(std::istream& is, Vector3D& vector);
  friend std::ostream& operator<<(std::ostream& os, const Vector3D& vector);

  Vector2D ToVector2D() const;
  Vector4D ToVector4D() const;

 private:
  float x_, y_, z_;

  friend class Vector2D;
  friend class Vector4D;

//  friend Vector3D operator*(const Vector3D& vector, const Matrix4x4& matrix);
//  friend Vector3D operator*(const Matrix4x4& matrix, const Vector3D& vector);
};


constexpr inline Vector3D::Vector3D(float x, float y, float z) : x_(x), y_(y), z_(z) {}

inline bool Vector3D::IsNull() const {
  return ::IsNull(x_) && ::IsNull(y_) && ::IsNull(z_);
}

constexpr inline float Vector3D::x() const { return x_; }
constexpr inline float Vector3D::y() const { return y_; }
constexpr inline float Vector3D::z() const { return z_; }

inline void Vector3D::set_x(float x) { x_ = x; }
inline void Vector3D::set_y(float y) { y_ = y; }
inline void Vector3D::set_z(float z) { z_ = z; }

inline float& Vector3D::operator[](int i) {
  assert(static_cast<unsigned>(i) < 3u);
  return *(&x_ + i);
}

inline float Vector3D::operator[](int i) const {
  assert(static_cast<unsigned>(i) < 3u);
  return *(&x_ + i);
}

constexpr inline float Vector3D::Length() const {
  return static_cast<float>(std::sqrt(DoubleLengthSquared()));
}

constexpr inline float Vector3D::LengthSquared() const {
  return Sqr(x_) + Sqr(y_) + Sqr(z_);
}

constexpr inline double Vector3D::DoubleLengthSquared() const {
  return Sqr(static_cast<double>(x_))
       + Sqr(static_cast<double>(y_))
       + Sqr(static_cast<double>(z_));
}

inline Vector3D& Vector3D::operator+=(const Vector3D& vector) {
  x_ += vector.x_;
  y_ += vector.y_;
  z_ += vector.z_;
  return *this;
}

inline Vector3D& Vector3D::operator-=(const Vector3D& vector) {
  x_ -= vector.x_;
  y_ -= vector.y_;
  z_ -= vector.z_;
  return *this;
}

inline Vector3D& Vector3D::operator*=(float factor) {
  x_ *= factor;
  y_ *= factor;
  z_ *= factor;
  return *this;
}

inline Vector3D& Vector3D::operator*=(const Vector3D& vector) {
  x_ *= vector.x_;
  y_ *= vector.y_;
  z_ *= vector.z_;
  return *this;
}

inline Vector3D& Vector3D::operator/=(float divisor) {
  x_ /= divisor;
  y_ /= divisor;
  z_ /= divisor;
  return *this;
}

inline Vector3D& Vector3D::operator/=(const Vector3D& vector) {
  x_ /= vector.x_;
  y_ /= vector.y_;
  z_ /= vector.z_;
  return *this;
}

constexpr inline float Vector3D::DotProduct(const Vector3D& v1, const Vector3D& v2) {
  return v1.x_ * v2.x_ + v1.y_ * v2.y_ + v1.z_ * v2.z_;
}

constexpr inline Vector3D Vector3D::CrossProduct(const Vector3D& v1, const Vector3D& v2) {
  return {v1.y_ * v2.z_ - v1.z_ * v2.y_,
          v1.z_ * v2.x_ - v1.x_ * v2.z_,
          v1.x_ * v2.y_ - v1.y_ * v2.x_};
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wfloat-equal"

constexpr inline bool operator==(const Vector3D& v1, const Vector3D& v2) {
  return v1.x_ == v2.x_ && v1.y_ == v2.y_ && v1.z_ == v2.z_;
}

constexpr inline bool operator!=(const Vector3D& v1, const Vector3D& v2) {
  return v1.x_ != v2.x_ || v1.y_ != v2.y_ || v1.z_ != v2.z_;
}

#pragma GCC diagnostic pop

constexpr inline const Vector3D operator+(const Vector3D& v1, const Vector3D& v2) {
  return {v1.x_ + v2.x_, v1.y_ + v2.y_, v1.z_ + v2.z_};
}

constexpr inline const Vector3D operator-(const Vector3D& v1, const Vector3D& v2) {
  return {v1.x_ - v2.x_, v1.y_ - v2.y_, v1.z_ - v2.z_};
}

constexpr inline const Vector3D operator*(float factor, const Vector3D& vector) {
  return {vector.x_ * factor, vector.y_ * factor, vector.z_ * factor};
}

constexpr inline const Vector3D operator*(const Vector3D& vector, float factor) {
  return {vector.x_ * factor, vector.y_ * factor, vector.z_ * factor};
}

constexpr inline const Vector3D operator*(const Vector3D& v1, const Vector3D& v2) {
  return {v1.x_ * v2.x_, v1.y_ * v2.y_, v1.z_ * v2.z_};
}

constexpr inline const Vector3D operator-(const Vector3D& vector) {
  return {-vector.x_, -vector.y_, -vector.z_};
}

constexpr inline const Vector3D operator/(const Vector3D& vector, float divisor) {
  return {vector.x_ / divisor, vector.y_ / divisor, vector.z_ / divisor};
}

constexpr inline const Vector3D operator/(const Vector3D& vector, const Vector3D& divisor) {
  return {vector.x_ / divisor.x_, vector.y_ / divisor.y_, vector.z_ / divisor.z_};
}

constexpr inline bool FuzzyCompare(const Vector3D& v1, const Vector3D& v2) {
  return FuzzyCompare(v1.x_, v2.x_)
      && FuzzyCompare(v1.y_, v2.y_)
      && FuzzyCompare(v1.z_, v2.z_);
}

#endif  // VECTOR3D_H_
