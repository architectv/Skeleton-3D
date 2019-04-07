#include "vector2d.h"

Vector2D::Vector2D(const Vector3D& vector) : x_(vector.x()), y_(vector.y()) {}
Vector2D::Vector2D(const Vector4D& vector) : x_(vector.x()), y_(vector.y()) {}

Vector2D Vector2D::Normalized() const {
  const double sqr_len = DoubleLengthSquared();
  if (FuzzyIsNull(sqr_len))
    return Vector2D();
  if (FuzzyIsNull(sqr_len - 1.0))
    return *this;
  const double len = std::sqrt(sqr_len);
  return {static_cast<float>(static_cast<double>(x_) / len),
          static_cast<float>(static_cast<double>(y_) / len)};
}

void Vector2D::Normalize() {
  const double sqr_len = DoubleLengthSquared();
  if (FuzzyIsNull(sqr_len) || FuzzyIsNull(sqr_len - 1.0))
    return;
  const double len = std::sqrt(sqr_len);
  x_ = static_cast<float>(static_cast<double>(x_) / len);
  y_ = static_cast<float>(static_cast<double>(y_) / len);
}

float Vector2D::DistanceToPoint(const Vector2D& point) const {
  return (*this - point).Length();
}

float Vector2D::DistanceToLine(const Vector2D& point, const Vector2D& direction) const {
  if (direction.IsNull())
    return (*this - point).Length();
  const Vector2D p = point + DotProduct(*this - point, direction) * direction;
  return (*this - p).Length();
}

constexpr inline Vector3D Vector2D::ToVector3D() const {
  return {x_, y_, 0.0f};
}

constexpr inline Vector4D Vector2D::ToVector4D() const {
  return {x_, y_, 0.0f, 0.0f};
}

std::istream& operator>>(std::istream& is, Vector2D& vector) {
  is >> vector.x_ >> vector.y_;
  return is;
}

std::ostream& operator<<(std::ostream& os, const Vector2D& vector) {
  os << '(' << vector.x() << ", " << vector.y() << ')';
  return os;
}
