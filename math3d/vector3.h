#ifndef VECTOR3_H_
#define VECTOR3_H_

#include "vector2.h"

template <typename T>
class Vector3 : public Vector<3, T> {
 public:
  using typename Vector<3, T>::reference;
  using typename Vector<3, T>::const_reference;

  constexpr static Vector3 x_axis(T value = T(1));
  constexpr static Vector3 y_axis(T value = T(1));
  constexpr static Vector3 z_axis(T value = T(1));

  constexpr static Vector3 x_scale(T value = T(1));
  constexpr static Vector3 y_scale(T value = T(1));
  constexpr static Vector3 z_scale(T value = T(1));

  constexpr Vector3() noexcept;
  constexpr Vector3(const std::initializer_list<T>& list) noexcept;
  constexpr explicit Vector3(T value) noexcept;
  constexpr Vector3(T x, T y, T z) noexcept;
  constexpr explicit Vector3(const Vector2<T>& xy, T z = T{}) noexcept;

  template <std::size_t other_size, typename U>
  constexpr explicit Vector3(const Vector<other_size, U>& other) noexcept;

  reference x();
  constexpr const_reference x() const;

  reference y();
  constexpr const_reference y() const;

  reference z();
  constexpr const_reference z() const;

  constexpr Vector2<T> xy() const;

  constexpr static Vector3 CrossProduct(const Vector3& v1, const Vector3& v2);
};

#include "impl/vector3.hpp"

using Vector3f = Vector3<float>;
using Vector3i = Vector3<int>;

#endif  // VECTOR3_H_
