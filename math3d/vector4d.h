#ifndef VECTOR4D_H_
#define VECTOR4D_H_

#include <cassert>
#include <istream>
#include <ostream>
#include "global.h"
#include "vector2d.h"
#include "vector3d.h"

class Vector2D;
class Vector3D;

class Vector4D {
 public:
  constexpr Vector4D(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 0.0f);
  Vector4D(const Vector2D& vector, float z = 0.0f, float w = 0.0f);
  Vector4D(const Vector3D& vector, float w = 0.0f);

  bool IsNull() const;

  constexpr float x() const;
  constexpr float y() const;
  constexpr float z() const;
  constexpr float w() const;

  void set_x(float x);
  void set_y(float y);
  void set_z(float z);
  void set_w(float w);

  float& operator[](int i);
  float operator[](int i) const;

  constexpr float Length() const;
  constexpr float LengthSquared() const;
  constexpr double DoubleLengthSquared() const;

  Vector4D Normalized() const;
  void Normalize();

  Vector4D& operator+=(const Vector4D& vector);
  Vector4D& operator-=(const Vector4D& vector);
  Vector4D& operator*=(float factor);
  Vector4D& operator*=(const Vector4D& vector);
  Vector4D& operator/=(float divisor);
  inline Vector4D& operator/=(const Vector4D& vector);

  constexpr static float DotProduct(const Vector4D& v1, const Vector4D& v2);

  constexpr friend inline bool operator==(const Vector4D& v1, const Vector4D& v2);
  constexpr friend inline bool operator!=(const Vector4D& v1, const Vector4D& v2);
  constexpr friend inline const Vector4D operator+(const Vector4D& v1, const Vector4D& v2);
  constexpr friend inline const Vector4D operator-(const Vector4D& v1, const Vector4D& v2);
  constexpr friend inline const Vector4D operator*(float factor, const Vector4D& vector);
  constexpr friend inline const Vector4D operator*(const Vector4D& vector, float factor);
  constexpr friend inline const Vector4D operator*(const Vector4D& v1, const Vector4D& v2);
  constexpr friend inline const Vector4D operator-(const Vector4D& vector);
  constexpr friend inline const Vector4D operator/(const Vector4D& vector, float divisor);
  constexpr friend inline const Vector4D operator/(const Vector4D& vector, const Vector4D& divisor);

  constexpr friend inline bool FuzzyCompare(const Vector4D& v1, const Vector4D& v2);

  friend std::istream& operator>>(std::istream& is, Vector4D& vector);
  friend std::ostream& operator<<(std::ostream& os, const Vector4D& vector);

  Vector2D ToVector2D() const;
  Vector2D ToVector2DAffine() const;
  Vector3D ToVector3D() const;
  Vector3D ToVector3DAffine() const;

 private:
  float x_, y_, z_, w_;

  friend class Vector2D;
  friend class Vector3D;

  // friend Vector4D operator*(const Vector4D& vector, const Matrix4x4& matrix);
  // friend Vector4D operator*(const Matrix4x4& matrix, const Vector4D& vector);
};

constexpr inline Vector4D::Vector4D(float x, float y, float z, float w)
    : x_(x), y_(y), z_(z), w_(w) {}

inline bool Vector4D::IsNull() const {
  return ::IsNull(x_) && ::IsNull(y_) && ::IsNull(z_) && ::IsNull(w_);
}

constexpr inline float Vector4D::x() const { return x_; }
constexpr inline float Vector4D::y() const { return y_; }
constexpr inline float Vector4D::z() const { return z_; }
constexpr inline float Vector4D::w() const { return w_; }

inline void Vector4D::set_x(float x) { x_ = x; }
inline void Vector4D::set_y(float y) { y_ = y; }
inline void Vector4D::set_z(float z) { z_ = z; }
inline void Vector4D::set_w(float w) { w_ = w; }

inline float& Vector4D::operator[](int i) {
  assert(static_cast<unsigned>(i) < 4u);
  return *(&x_ + i);
}

inline float Vector4D::operator[](int i) const {
  assert(static_cast<unsigned>(i) < 4u);
  return *(&x_ + i);
}

constexpr inline float Vector4D::Length() const {
  return static_cast<float>(std::sqrt(DoubleLengthSquared()));
}

constexpr inline float Vector4D::LengthSquared() const {
  return Sqr(x_) + Sqr(y_) + Sqr(z_) + Sqr(w_);
}

constexpr inline double Vector4D::DoubleLengthSquared() const {
  return Sqr(static_cast<double>(x_))
       + Sqr(static_cast<double>(y_))
       + Sqr(static_cast<double>(z_))
       + Sqr(static_cast<double>(w_));
}

inline Vector4D& Vector4D::operator+=(const Vector4D& vector) {
  x_ += vector.x_;
  y_ += vector.y_;
  z_ += vector.z_;
  w_ += vector.w_;
  return *this;
}

inline Vector4D& Vector4D::operator-=(const Vector4D& vector) {
  x_ -= vector.x_;
  y_ -= vector.y_;
  z_ -= vector.z_;
  w_ -= vector.w_;
  return *this;
}

inline Vector4D& Vector4D::operator*=(float factor) {
  x_ *= factor;
  y_ *= factor;
  z_ *= factor;
  w_ *= factor;
  return *this;
}

inline Vector4D& Vector4D::operator*=(const Vector4D& vector) {
  x_ *= vector.x_;
  y_ *= vector.y_;
  z_ *= vector.z_;
  w_ *= vector.w_;
  return *this;
}

inline Vector4D& Vector4D::operator/=(float divisor) {
  x_ /= divisor;
  y_ /= divisor;
  z_ /= divisor;
  w_ /= divisor;
  return *this;
}

constexpr inline float Vector4D::DotProduct(const Vector4D& v1, const Vector4D& v2) {
  return v1.x_ * v2.x_ + v1.y_ * v2.y_ + v1.z_ * v2.z_ + v1.w_ * v2.w_;
}

inline Vector4D& Vector4D::operator/=(const Vector4D& vector) {
  x_ /= vector.x_;
  y_ /= vector.y_;
  z_ /= vector.z_;
  w_ /= vector.w_;
  return *this;
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wfloat-equal"

constexpr inline bool operator==(const Vector4D& v1, const Vector4D& v2) {
  return v1.x_ == v2.x_ && v1.y_ == v2.y_ && v1.z_ == v2.z_ && v1.w_ == v2.w_;
}

constexpr inline bool operator!=(const Vector4D& v1, const Vector4D& v2) {
  return v1.x_ != v2.x_ || v1.y_ != v2.y_ || v1.z_ != v2.z_ || v1.w_ != v2.w_;
}

#pragma GCC diagnostic pop

constexpr inline const Vector4D operator+(const Vector4D& v1, const Vector4D& v2) {
  return {v1.x_ + v2.x_, v1.y_ + v2.y_, v1.z_ + v2.z_, v1.w_ + v2.w_};
}

constexpr inline const Vector4D operator-(const Vector4D& v1, const Vector4D& v2) {
  return {v1.x_ - v2.x_, v1.y_ - v2.y_, v1.z_ - v2.z_, v1.w_ - v2.w_};
}

constexpr inline const Vector4D operator*(float factor, const Vector4D& vector) {
  return {vector.x_ * factor, vector.y_ * factor, vector.z_ * factor, vector.w_ * factor};
}

constexpr inline const Vector4D operator*(const Vector4D& vector, float factor) {
  return {vector.x_ * factor, vector.y_ * factor, vector.z_ * factor, vector.w_ * factor};
}

constexpr inline const Vector4D operator*(const Vector4D& v1, const Vector4D& v2) {
  return {v1.x_ * v2.x_, v1.y_ * v2.y_, v1.z_ * v2.z_, v1.w_ * v2.w_};
}

constexpr inline const Vector4D operator-(const Vector4D& vector) {
  return {-vector.x_, -vector.y_, -vector.z_, -vector.w_};
}

constexpr inline const Vector4D operator/(const Vector4D& vector, float divisor) {
  return {vector.x_ / divisor, vector.y_ / divisor, vector.z_ / divisor, vector.w_ / divisor};
}

constexpr inline const Vector4D operator/(const Vector4D& vector, const Vector4D& divisor) {
  return {vector.x_ / divisor.x_, vector.y_ / divisor.y_, vector.z_ / divisor.z_, vector.w_ / divisor.w_};
}

constexpr inline bool FuzzyCompare(const Vector4D& v1, const Vector4D& v2) {
  return FuzzyCompare(v1.x_, v2.x_)
      && FuzzyCompare(v1.y_, v2.y_)
      && FuzzyCompare(v1.z_, v2.z_)
      && FuzzyCompare(v1.w_, v2.w_);
}

#endif  // VECTOR4D_H_
