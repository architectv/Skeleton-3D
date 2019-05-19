#ifndef VECTOR4_H_
#define VECTOR4_H_

#include "vector3.h"

template <typename T>
class Vector4 : public Vector<4, T> {
 public:
  using typename Vector<4, T>::reference;
  using typename Vector<4, T>::const_reference;

  constexpr static Vector4 x_axis(T value = T(1));
  constexpr static Vector4 y_axis(T value = T(1));
  constexpr static Vector4 z_axis(T value = T(1));
  constexpr static Vector4 w_axis(T value = T(1));

  constexpr static Vector4 x_scale(T value = T(1));
  constexpr static Vector4 y_scale(T value = T(1));
  constexpr static Vector4 z_scale(T value = T(1));
  constexpr static Vector4 w_scale(T value = T(1));

  constexpr Vector4() noexcept;
  constexpr Vector4(std::initializer_list<T> list) noexcept;
  constexpr explicit Vector4(T value) noexcept;
  constexpr Vector4(T x, T y, T z, T w) noexcept;
  constexpr explicit Vector4(const Vector3<T>& xyz, T w = T{}) noexcept;
  constexpr explicit Vector4(const Vector2<T>& xy, T z = T{}, T w = T{}) noexcept;

  template <std::size_t other_size, typename U>
  constexpr explicit Vector4(const Vector<other_size, U>& other) noexcept;

  reference x();
  constexpr const_reference x() const;

  reference y();
  constexpr const_reference y() const;

  reference z();
  constexpr const_reference z() const;

  reference w();
  constexpr const_reference w() const;

  Vector3<T>& xyz();
  constexpr const Vector3<T> xyz() const;

  constexpr static Vector4 Plane(const Vector3<T>& p0, const Vector3<T>& p1, const Vector3<T>& p2);
  constexpr static Vector4 Plane(const Vector3<T>& normal, const Vector3<T>& point);
};

#include "impl/vector4.hpp"

#endif  // VECTOR4_H_
