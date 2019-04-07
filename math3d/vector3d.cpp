#include "vector3d.h"

Vector3D::Vector3D(const Vector2D& vector, float z) : x_(vector.x()), y_(vector.y()), z_(z) {}
Vector3D::Vector3D(const Vector4D& vector) : x_(vector.x()), y_(vector.y()), z_(vector.z()) {}

Vector3D Vector3D::Normalized() const {
  const double sqr_len = DoubleLengthSquared();
  if (FuzzyIsNull(sqr_len))
    return Vector3D();
  if (FuzzyIsNull(sqr_len - 1.0))
    return *this;
  const double len = std::sqrt(sqr_len);
  return {static_cast<float>(static_cast<double>(x_) / len),
          static_cast<float>(static_cast<double>(y_) / len),
          static_cast<float>(static_cast<double>(z_) / len)};
}

void Vector3D::Normalize() {
  const double sqr_len = DoubleLengthSquared();
  if (FuzzyIsNull(sqr_len) || FuzzyIsNull(sqr_len - 1.0))
    return;
  const double len = std::sqrt(sqr_len);
  x_ = static_cast<float>(static_cast<double>(x_) / len);
  y_ = static_cast<float>(static_cast<double>(y_) / len);
  z_ = static_cast<float>(static_cast<double>(z_) / len);
}

Vector3D Vector3D::Normal(const Vector3D& v1, const Vector3D& v2) {
  return CrossProduct(v1, v2).Normalized();
}

Vector3D Vector3D::Normal(const Vector3D& v1, const Vector3D& v2, const Vector3D& v3) {
  return CrossProduct(v2 - v1, v3 - v1).Normalized();
}

float Vector3D::DistanceToPoint(const Vector3D& point) const {
  return (*this - point).Length();
}

float Vector3D::DistanceToPlane(const Vector3D& plane, const Vector3D& normal) const {
  return DotProduct(*this - plane, normal);
}

float Vector3D::DistanceToPlane(const Vector3D& plane1, const Vector3D& plane2, const Vector3D& plane3) const {
  const Vector3D n = Normal(plane2 - plane1, plane3 - plane1);
  return DotProduct(*this - plane1, n);
}

float Vector3D::DistanceToLine(const Vector3D& point, const Vector3D& direction) const {
  if (direction.IsNull())
    return (*this - point).Length();
  const Vector3D p = point + DotProduct(*this - point, direction) * direction;
  return (*this - p).Length();
}

Vector2D Vector3D::ToVector2D() const {
  return {x_, y_};
}

Vector4D Vector3D::ToVector4D() const {
  return {x_, y_, z_, 0.0f};
}

std::istream& operator>>(std::istream& is, Vector3D& vector) {
  is >> vector.x_ >> vector.y_ >> vector.z_;
  return is;
}

std::ostream& operator<<(std::ostream& os, const Vector3D& vector) {
  os << '(' << vector.x() << ", " << vector.y() << ", " << vector.z() << ')';
  return os;
}
