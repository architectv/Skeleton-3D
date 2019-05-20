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

template <std::size_t size, typename T>
class Vector {
  static_assert(size != 0, "Zero dimension vector does not exist");

 public:
  using value_type = T;
  using pointer = T*;
  using const_pointer = const T*;
  using reference = T&;
  using const_reference = const T&;
  using iterator = T*;
  using const_iterator = const T*;

  constexpr Vector() noexcept;
  explicit Vector(T value) noexcept;

  constexpr Vector(std::initializer_list<T> list) noexcept;

  template <typename... U, typename V = std::enable_if_t<sizeof...(U) + 1 == size, T>>
  constexpr explicit Vector(T first, U... next) noexcept;

  template <std::size_t other_size>
  constexpr explicit Vector(const Vector<other_size, T>& other) noexcept;

  template <std::size_t other_size, typename U>
  constexpr explicit Vector(const std::enable_if_t<std::is_convertible<U, T>::value, Vector<other_size, U>>& other) noexcept;

  constexpr Vector(const Vector&) noexcept = default;

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

  value_type length() const;
  constexpr value_type sum() const;
  constexpr value_type product() const;

  constexpr Vector& operator+=(const Vector& other);
  constexpr Vector& operator-=(const Vector& other);
  constexpr Vector& operator*=(const Vector& other);
  constexpr Vector& operator/=(const Vector& other);

  template <typename U>
  constexpr Vector& operator*=(U factor);

  template <typename U>
  constexpr Vector& operator/=(U divisor);


  constexpr bool IsNull() const;
  constexpr bool IsNormalized() const;

  constexpr static T DotProduct(const Vector& v1, const Vector& v2);

  template <typename U = T>
  std::enable_if_t<std::is_floating_point<U>::value, Vector> normalized() const;

  template <typename U = T>
  std::enable_if_t<std::is_floating_point<U>::value> normalize();

  template <typename U = T>
  std::enable_if_t<std::is_floating_point<U>::value, Vector> Projected(const Vector& line) const;

  template <typename U = T>
  std::enable_if_t<std::is_floating_point<U>::value, Vector> ProjectedOntoNormalized(const Vector& line) const;

 protected:
  T data_[size];
};

template <std::size_t size, typename T, typename U>
constexpr bool operator==(const Vector<size, T>& v1, const Vector<size, U>& v2);

template <std::size_t size, typename T, typename U>
constexpr bool operator!=(const Vector<size, T>& v1, const Vector<size, U>& v2);

template <std::size_t size, typename T, typename U>
constexpr std::enable_if_t<std::is_floating_point<std::common_type_t<T, U>>::value, bool> FuzzyCompare(const Vector<size, T>& v1, const Vector<size, U>& v2);

template <std::size_t size, typename T, typename U>
Vector<size, bool> operator<(const Vector<size, T>& v1, const Vector<size, U>& v2);

template <std::size_t size, typename T, typename U>
Vector<size, bool> operator<=(const Vector<size, T>& v1, const Vector<size, U>& v2);

template <std::size_t size, typename T, typename U>
Vector<size, bool> operator>(const Vector<size, T>& v1, const Vector<size, U>& v2);

template <std::size_t size, typename T, typename U>
Vector<size, bool> operator>=(const Vector<size, T>& v1, const Vector<size, U>& v2);

template <std::size_t size, typename T>
constexpr Vector<size, T> operator+(const Vector<size, T>& v1, const Vector<size, T>& v2);

template <std::size_t size, typename T>
constexpr Vector<size, T> operator+(const Vector<size, T>& vector);

template <std::size_t size, typename T>
constexpr Vector<size, T> operator-(const Vector<size, T>& v1, const Vector<size, T>& v2);

template <std::size_t size, typename T>
constexpr Vector<size, T> operator-(const Vector<size, T>& vector);

template <std::size_t size, typename T>
constexpr Vector<size, T> operator*(float factor, const Vector<size, T>& vector);

template <std::size_t size, typename T>
constexpr Vector<size, T> operator*(const Vector<size, T>& v1, const Vector<size, T>& v2);

template <std::size_t size, typename T, typename U>
constexpr Vector<size, T> operator*(const Vector<size, T>& vector, U factor);

template <std::size_t size, typename T, typename U>
constexpr Vector<size, T> operator/(const Vector<size, T>& vector, U divisor);

template <std::size_t size, typename T>
constexpr Vector<size, T> operator/(const Vector<size, T>& v1, const Vector<size, T>& v2);

template <std::size_t size, typename T>
std::istream& operator>>(std::istream& is, Vector<size, T>& vector);

template <std::size_t size, typename T>
std::ostream& operator<<(std::ostream& os, const Vector<size, T>& vector);

#include "impl/vector.hpp"

#endif  // VECTOR_H_
