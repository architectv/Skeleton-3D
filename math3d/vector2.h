#ifndef VECTOR2_H_
#define VECTOR2_H_

#include "vector.h"

template <typename T>
class Vector2 : public Vector<2, T> {
 public:
  using typename Vector<2, T>::value_type;
  using typename Vector<2, T>::reference;
  using typename Vector<2, T>::const_reference;

  constexpr static Vector2 x_axis(T value = T(1));
  constexpr static Vector2 y_axis(T value = T(1));

  constexpr static Vector2 x_scale(T value = T(1));
  constexpr static Vector2 y_scale(T value = T(1));


  constexpr Vector2() noexcept;
  constexpr Vector2(const std::initializer_list<T>& list) noexcept;
  constexpr explicit Vector2(T value) noexcept;
  constexpr Vector2(T x, T y) noexcept;

  template <std::size_t other_size, typename U>
  constexpr Vector2(const Vector<other_size, U>& other) noexcept;

  reference x();
  constexpr const_reference x() const;

  reference y();
  constexpr const_reference y() const;

  constexpr static value_type SkewProduct(const Vector2& v1, const Vector2& v2);

  constexpr Vector2 perpendicular() const;

  template <typename U = T>
  std::enable_if_t<std::is_floating_point<U>::value, T> aspect_ratio() const;
};

#include "impl/vector2.hpp"

using Vector2f = Vector2<float>;
using Vector2i = Vector2<int>;

#endif  // VECTOR2_H_
