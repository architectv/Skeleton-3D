#ifndef VECTOR_H_
#define VECTOR_H_

#include <algorithm>
#include <cassert>
#include <cmath>
#include <initializer_list>
#include <istream>
#include <ostream>
#include <stdexcept>
#include "global.h"

template <std::size_t size>
class Vector;

using Vector2 = Vector<2>;
using Vector3 = Vector<3>;
using Vector4 = Vector<4>;

constexpr bool Is2or3or4(std::size_t size) { return size == 2 || size == 3 || size == 4; }
constexpr bool Is3or4(std::size_t size) { return size == 3 || size == 4; }
constexpr bool Is4(std::size_t size) { return size == 4; }

template <std::size_t size>
class Vector {
  static_assert(size != 0, "Zero dimension vector does not exist");

 public:
  using pointer = float*;
  using const_pointer = const float*;
  using reference = float&;
  using const_reference = const float&;
  using iterator = float*;
  using const_iterator = const float*;

  constexpr Vector() noexcept;
  constexpr Vector(const std::initializer_list<float>& list) noexcept;
  explicit Vector(float scalar) noexcept;

  template <std::size_t other_size>
  constexpr explicit Vector(const Vector<other_size>& other) noexcept;

  pointer data();
  constexpr const_pointer data() const;

  reference operator[](std::size_t index);
  constexpr const_reference operator[](std::size_t index) const;

  reference at(std::size_t index);
  const_reference at(std::size_t index) const;

  reference front();
  constexpr const_reference front() const;

  reference back();
  constexpr const_reference back() const;

  iterator begin();
  constexpr const_iterator begin() const;

  iterator end();
  constexpr const_iterator end() const;

  template <bool EnableBool = true> constexpr std::enable_if_t<Is2or3or4(size) && EnableBool, float> x() const;
  template <bool EnableBool = true> constexpr std::enable_if_t<Is2or3or4(size) && EnableBool, float> y() const;
  template <bool EnableBool = true> constexpr std::enable_if_t<Is3or4(size) && EnableBool, float> z() const;
  template <bool EnableBool = true> constexpr std::enable_if_t<Is4(size) && EnableBool, float> w() const;

  template <bool EnableBool = true> constexpr std::enable_if_t<Is2or3or4(size) && EnableBool> set_x(float x);
  template <bool EnableBool = true> constexpr std::enable_if_t<Is2or3or4(size) && EnableBool> set_y(float y);
  template <bool EnableBool = true> constexpr std::enable_if_t<Is3or4(size) && EnableBool> set_z(float z);
  template <bool EnableBool = true> constexpr std::enable_if_t<Is4(size) && EnableBool> set_w(float w);

  constexpr bool operator==(const Vector<size>& other) const;
  constexpr bool operator!=(const Vector<size>& other) const;
  constexpr bool static FuzzyCompare(const Vector<size>& v1, const Vector<size>& v2);

  constexpr bool IsNull() const;
  constexpr bool IsNormalized() const;

  float length() const;

  constexpr static float DotProduct(const Vector<size>& v1, const Vector<size>& v2);
  constexpr static double DoubleDotProduct(const Vector<size>& v1, const Vector<size>& v2);
  constexpr static Vector<size> CrossProduct(const Vector<size>& v1, const Vector<size>& v2) = delete;
  constexpr static float SkewProduct(const Vector<size>& v1, const Vector<size>& v2) = delete;

  Vector<size> Normalized() const;
  void Normalize();

  static Vector<size> Normal(const Vector<size>& v1, const Vector<size>& v2) = delete;
  static Vector<size> Normal(const Vector<size>& v1, const Vector<size>& v2, const Vector<size>& v3) = delete;

  constexpr float DistanceToPoint(const Vector<size>& point) const;
  constexpr float DistanceToLine(const Vector<size>& point, const Vector<size>& direction) const;
  constexpr float DistanceToPlane(const Vector<size>& plane, const Vector<size>& normal) const = delete;
  float DistanceToPlane(const Vector<size>& plane1, const Vector<size>& plane2, const Vector<size>& plane3) const = delete;

  constexpr Vector<size>& operator+=(const Vector<size>& other);
  constexpr Vector<size>& operator-=(const Vector<size>& other);
  constexpr Vector<size>& operator*=(float factor);
  constexpr Vector<size>& operator*=(const Vector<size>& other);
  constexpr Vector<size>& operator/=(float divisor);
  constexpr Vector<size>& operator/=(double divisor);
  constexpr Vector<size>& operator/=(const Vector<size>& other);

  template <std::size_t size_> friend std::istream& operator>>(std::istream& is, Vector<size_>& vector);
  template <std::size_t size_> friend std::ostream& operator<<(std::ostream& os, const Vector<size_>& vector);

 protected:
  float data_[size];
};

template <std::size_t size>
constexpr Vector<size>::Vector() noexcept: data_{} {}

template <std::size_t size>
constexpr Vector<size>::Vector(const std::initializer_list<float>& list) noexcept: data_{} {
  std::copy(list.begin(), list.end(), data_);
}

template <std::size_t size>
Vector<size>::Vector(float scalar) noexcept: data_{} {
  std::fill(data_, data_ + size, scalar);
}

template <std::size_t size> template <std::size_t other_size>
constexpr Vector<size>::Vector(const Vector<other_size>& other) noexcept: data_{} {
  if (size <= other_size)
    std::copy(other.begin(), other.begin() + size, data_);
  else
    std::copy(other.begin(), other.end(), data_);
}


template <std::size_t size>
typename Vector<size>::pointer Vector<size>::data() {
  return data_;
}

template <std::size_t size>
constexpr typename Vector<size>::const_pointer Vector<size>::data() const {
  return data_;
}

template <std::size_t size>
typename Vector<size>::reference Vector<size>::operator[](std::size_t index) {
  assert(index < size);
  return data_[index];
}

template <std::size_t size>
constexpr typename Vector<size>::const_reference Vector<size>::operator[](std::size_t index) const {
  assert(index < size);
  return data_[index];
}

template <std::size_t size>
typename Vector<size>::reference Vector<size>::at(std::size_t index) {
  if (index >= size)
    throw std::out_of_range("Out of range");
  return data_[index];
}

template <std::size_t size>
typename Vector<size>::const_reference Vector<size>::at(std::size_t index) const {
  if (index >= size)
    throw std::out_of_range("Out of range");
  return data_[index];
}

template <std::size_t size>
typename Vector<size>::reference Vector<size>::front() {
  return data_[0];
}

template <std::size_t size>
constexpr typename Vector<size>::const_reference Vector<size>::front() const {
  return data_[0];
}

template <std::size_t size>
typename Vector<size>::reference Vector<size>::back() {
  return data_[size - 1];
}

template <std::size_t size>
constexpr typename Vector<size>::const_reference Vector<size>::back() const {
  return data_[size - 1];
}

template <std::size_t size>
typename Vector<size>::iterator Vector<size>::begin() {
  return data_;
}

template <std::size_t size>
constexpr typename Vector<size>::const_iterator Vector<size>::begin() const {
  return data_;
}

template <std::size_t size>
typename Vector<size>::iterator Vector<size>::end() {
  return data_ + size;
}

template <std::size_t size>
constexpr typename Vector<size>::const_iterator Vector<size>::end() const {
  return data_ + size;
}

template <std::size_t size> template <bool EnableBool>
constexpr std::enable_if_t<Is2or3or4(size) && EnableBool, float> Vector<size>::x() const {
  return data_[0];
}

template <std::size_t size> template <bool EnableBool>
constexpr std::enable_if_t<Is2or3or4(size) && EnableBool, float> Vector<size>::y() const {
  return data_[1];
}

template <std::size_t size> template <bool EnableBool>
constexpr std::enable_if_t<Is3or4(size) && EnableBool, float> Vector<size>::z() const {
  return data_[2];
}

template <std::size_t size> template <bool EnableBool>
constexpr std::enable_if_t<Is4(size) && EnableBool, float> Vector<size>::w() const {
  return data_[3];
}

template <std::size_t size> template <bool EnableBool>
constexpr std::enable_if_t<Is2or3or4(size) && EnableBool> Vector<size>::set_x(float x) {
  data_[0] = x;
}

template <std::size_t size> template <bool EnableBool>
constexpr std::enable_if_t<Is2or3or4(size) && EnableBool> Vector<size>::set_y(float y) {
  data_[1] = y;
}

template <std::size_t size> template <bool EnableBool>
constexpr std::enable_if_t<Is3or4(size) && EnableBool> Vector<size>::set_z(float z) {
  data_[2] = z;
}

template <std::size_t size> template <bool EnableBool>
constexpr std::enable_if_t<Is4(size) && EnableBool> Vector<size>::set_w(float w) {
  data_[3] = w;
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wfloat-equal"

template <std::size_t size>
constexpr bool Vector<size>::operator==(const Vector<size>& other) const {
  for (std::size_t i = 0; i != size; ++i)
    if (data_[i] != other.data_[i])
      return false;
  return true;
}

template <std::size_t size>
constexpr bool Vector<size>::operator!=(const Vector<size>& other) const {
  return !(*this == other);
}

#pragma GCC diagnostic pop

template <std::size_t size>
constexpr bool Vector<size>::FuzzyCompare(const Vector<size>& v1, const Vector<size>& v2) {
  for (std::size_t i = 0; i != size; ++i)
    if (!::FuzzyCompare(v1.data_[i], v2.data_[i]))
      return false;
  return true;
}

template <std::size_t size>
constexpr bool Vector<size>::IsNull() const {
  for (std::size_t i = 0; i != size; ++i)
    if (data_[i] != 0.0f)
      return false;
  return true;
}

template <std::size_t size>
constexpr bool Vector<size>::IsNormalized() const {
  return FuzzyIsNull(DotProduct(*this, *this) - 1.0);
}

template <std::size_t size>
float Vector<size>::length() const {
  return std::sqrt(DotProduct(*this, *this));
}

template <std::size_t size>
constexpr float Vector<size>::DotProduct(const Vector<size>& v1, const Vector<size>& v2) {
  float result = 0.0f;
  for (std::size_t i = 0; i != size; ++i)
    result += v1.data_[i] * v2.data_[i];
  return result;
}

template <std::size_t size>
constexpr double Vector<size>::DoubleDotProduct(const Vector<size>& v1, const Vector<size>& v2) {
  double result = 0.0;
  for (std::size_t i = 0; i != size; ++i)
    result += static_cast<double>(v1.data_[i]) * static_cast<double>(v2.data_[i]);
  return result;
}

template <>
constexpr Vector<3> Vector<3>::CrossProduct(const Vector<3>& v1, const Vector<3>& v2) {
  return {
      v1.data_[1] * v2.data_[2] - v1.data_[2] * v2.data_[1],
      v1.data_[2] * v2.data_[0] - v1.data_[0] * v2.data_[2],
      v1.data_[0] * v2.data_[1] - v1.data_[1] * v2.data_[0]
  };
}

template <>
constexpr float Vector<2>::SkewProduct(const Vector<2>& v1, const Vector2 &v2) {
  return v1.data_[0] * v2.data_[1] - v1.data_[1] * v2.data_[0];
}

template <std::size_t size>
constexpr Vector<size>& Vector<size>::operator+=(const Vector<size>& other) {
  for (std::size_t i = 0; i != size; ++i)
    data_[i] += other.data_[i];
  return *this;
}

template <std::size_t size>
constexpr Vector<size>& Vector<size>::operator-=(const Vector<size>& other) {
  for (std::size_t i = 0; i != size; ++i)
    data_[i] -= other.data_[i];
  return *this;
}

template <std::size_t size>
constexpr Vector<size>& Vector<size>::operator*=(float factor) {
  for (std::size_t i = 0; i != size; ++i)
    data_[i] *= factor;
  return *this;
}

template <std::size_t size>
constexpr Vector<size>& Vector<size>::operator*=(const Vector<size>& other) {
  for (std::size_t i = 0; i != size; ++i)
    data_[i] *= other.data_[i];
  return *this;
}

template <std::size_t size>
constexpr Vector<size>& Vector<size>::operator/=(float divisor) {
  for (std::size_t i = 0; i != size; ++i)
    data_[i] /= divisor;
  return *this;
}

template <std::size_t size>
constexpr Vector<size>& Vector<size>::operator/=(double divisor) {
  for (std::size_t i = 0; i != size; ++i)
    data_[i] /= divisor;
  return *this;
}

template <std::size_t size>
constexpr Vector<size>& Vector<size>::operator/=(const Vector<size>& other) {
  for (std::size_t i = 0; i != size; ++i)
    data_[i] /= other.data_[i];
  return *this;
}

template <std::size_t size>
constexpr Vector<size> operator+(const Vector<size>& v1, const Vector<size>& v2) {
  return Vector<size>(v1) += v2;
}

template <std::size_t size>
constexpr Vector<size> operator+(const Vector<size>& vector) {
  return vector;
}

template <std::size_t size>
constexpr Vector<size> operator-(const Vector<size>& v1, const Vector<size>& v2) {
  return Vector<size>(v1) -= v2;
}

template <std::size_t size>
constexpr Vector<size> operator-(const Vector<size>& vector) {
  return Vector<size>() -= vector;
}

template <std::size_t size>
constexpr Vector<size> operator*(const Vector<size>& vector, float factor) {
  return Vector<size>(vector) *= factor;
}

template <std::size_t size>
constexpr Vector<size> operator*(float factor, const Vector<size>& vector) {
  return vector * factor;
}

template <std::size_t size>
constexpr Vector<size> operator*(const Vector<size>& v1, const Vector<size>& v2) {
  return Vector<size>(v1) *= v2;
}

template <std::size_t size>
constexpr Vector<size> operator/(const Vector<size>& vector, float divisor) {
  assert(divisor != 0.0f);
  return Vector<size>(vector) /= divisor;
}

template <std::size_t size>
constexpr Vector<size> operator/(const Vector<size>& vector, double divisor) {
  assert(divisor != 0.0f);
  return Vector<size>(vector) /= divisor;
}

template <std::size_t size>
constexpr Vector<size> operator/(const Vector<size>& v1, const Vector<size>& v2) {
  return Vector<size>(v1) /= v2;
}

template <std::size_t size>
Vector<size> Vector<size>::Normalized() const {
  const double sqr_len = DoubleDotProduct(*this, *this);
  if (FuzzyIsNull(sqr_len))
    return Vector<size>();
  if (FuzzyIsNull(sqr_len - 1.0))
    return *this;
  const double len = std::sqrt(sqr_len);
  return *this / len;
}

template <std::size_t size>
void Vector<size>::Normalize() {
  const double sqr_len = DoubleDotProduct(*this, *this);
  if (FuzzyIsNull(sqr_len) || (FuzzyIsNull(sqr_len - 1.0)))
    return;
  const double len = std::sqrt(sqr_len);
  *this /= len;
}

template <>
Vector<3> Vector<3>::Normal(const Vector<3>& v1, const Vector<3>& v2) {
  return CrossProduct(v1, v2).Normalized();
}

template <>
Vector<3> Vector<3>::Normal(const Vector<3>& v1, const Vector<3>& v2, const Vector<3>& v3) {
  return CrossProduct(v2 - v1, v3 - v1).Normalized();
}

template <std::size_t size>
constexpr float Vector<size>::DistanceToPoint(const Vector<size>& point) const {
  return (*this - point).length();
}

template <std::size_t size>
constexpr float Vector<size>::DistanceToLine(const Vector<size>& point, const Vector<size>& direction) const {
  if (direction.IsNull())
    return (*this - point).length();
  const Vector<size> p = point + DotProduct(*this - point, direction) * direction;
  return (*this - p).length();
}

template <>
constexpr float Vector<3>::DistanceToPlane(const Vector<3>& plane, const Vector<3>& normal) const {
  return DotProduct(*this - plane, normal);
}

template <>
float Vector<3>::DistanceToPlane(const Vector<3>& plane1, const Vector<3>& plane2, const Vector<3>& plane3) const {
  const Vector<3> n = Normal(plane2 - plane1, plane3 - plane1);
  return DotProduct(*this - plane1, n);
}

template <std::size_t size>
std::istream& operator>>(std::istream& is, Vector<size>& vector) {
  for (std::size_t i = 0; i != size; ++i)
    is >> vector.data_[i];
  return is;
}

template <std::size_t size>
std::ostream& operator<<(std::ostream& os, const Vector<size>& vector) {
  os << '(';
  for (std::size_t i = 0; i + 1 < size; ++i)
    os << vector.data_[i] << ", ";
  os << vector.back() << ')';
  return os;
}

#endif  // VECTOR_H_
