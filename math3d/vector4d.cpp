#include "vector4d.h"

Vector4D::Vector4D(const Vector2D& vector, float z, float w)
    : x_(vector.x()), y_(vector.y()), z_(z), w_(w) {}

Vector4D::Vector4D(const Vector3D& vector, float w)
    : x_(vector.x()), y_(vector.y()), z_(vector.z()), w_(w) {}

Vector4D Vector4D::Normalized() const {
  const double sqr_len = DoubleLengthSquared();
  if (FuzzyIsNull(sqr_len))
    return Vector4D();
  if (FuzzyIsNull(sqr_len - 1.0))
    return *this;
  const double len = std::sqrt(sqr_len);
  return {static_cast<float>(static_cast<double>(x_) / len),
          static_cast<float>(static_cast<double>(y_) / len),
          static_cast<float>(static_cast<double>(z_) / len),
          static_cast<float>(static_cast<double>(w_) / len)};
}

void Vector4D::Normalize() {
  const double sqr_len = DoubleLengthSquared();
  if (FuzzyIsNull(sqr_len) || FuzzyIsNull(sqr_len - 1.0))
    return;
  const double len = std::sqrt(sqr_len);
  x_ = static_cast<float>(static_cast<double>(x_) / len);
  y_ = static_cast<float>(static_cast<double>(y_) / len);
  z_ = static_cast<float>(static_cast<double>(z_) / len);
  w_ = static_cast<float>(static_cast<double>(w_) / len);
}

Vector2D Vector4D::ToVector2D() const {
  return {x_, y_};
}

Vector2D Vector4D::ToVector2DAffine() const {
  return ::IsNull(w_) ? Vector2D() : Vector2D(x_ / w_, y_ / w_);
}

Vector3D Vector4D::ToVector3D() const {
  return {x_, y_, z_};
}

Vector3D Vector4D::ToVector3DAffine() const {
  return ::IsNull(w_) ? Vector3D() : Vector3D(x_ / w_, y_ / w_, z_ / w_);
}

std::istream& operator>>(std::istream& is, Vector4D& vector) {
  is >> vector.x_ >> vector.y_ >> vector.z_ >> vector.w_;
  return is;
}

std::ostream& operator<<(std::ostream& os, const Vector4D& vector) {
  os << '('
     << vector.x() << ", "
     << vector.y() << ", "
     << vector.z() << ", "
     << vector.w()
     << ')';
  return os;
}
