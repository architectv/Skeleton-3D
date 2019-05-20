#ifndef MATRIX3_H_
#define MATRIX3_H_

#include "matrix.h"
#include "vector3.h"

template <typename T> class Matrix3: public Matrix3x3<T> {
 public:
  constexpr static Matrix3<T> translation(const Vector2<T>& vector);
  constexpr static Matrix3<T> scaling(const Vector2<T>& vector);

  template <typename FloatingPoint>
  static std::enable_if_t<std::is_floating_point<FloatingPoint>::value, Matrix3<T>> rotation(FloatingPoint angle);

  static Matrix3<T> reflection(const Vector2<T>& normal);

  constexpr static Matrix3<T> shearing_x(T amount);
  constexpr static Matrix3<T> shearing_y(T amount);

  static Matrix3<T> projection(const Vector2<T>& size);

  constexpr static Matrix3<T> from(const Matrix2x2<T>& rotation_scaling, const Vector2<T>& translation);
  
  constexpr Matrix3() noexcept;
  constexpr explicit Matrix3(T value) noexcept;
  constexpr explicit Matrix3(typename Matrix<3, T>::IdentityInitT, T value = T(1)) noexcept;
  constexpr Matrix3(const Vector3<T>& first, const Vector3<T>& second, const Vector3<T>& third) noexcept;

  template <std::size_t cols, std::size_t rows, typename U>
  constexpr explicit Matrix3(const RectMatrix<cols, rows, U>& other) noexcept;

  bool IsRigidTransformation() const;

  constexpr Matrix2x2<T> rotation_scaling() const;
  Matrix2x2<T> rotation_shear() const;
  Matrix2x2<T> rotation() const;
  Matrix2x2<T> rotation_normalized() const;

  Vector2<T> scaling_squared() const;
  Vector2<T> scaling() const;

  T uniform_scaling_squared() const;
  T uniform_scaling() const;

  Vector2<T>& right();
  constexpr Vector2<T> right() const;

  Vector2<T>& up();
  constexpr Vector2<T> up() const;

  Vector2<T>& translation();
  constexpr Vector2<T> translation() const;

  Matrix3<T> inverted_rigid() const;

  Vector2<T> map_vector(const Vector2<T>& vector) const;
  Vector2<T> map_point(const Vector2<T>& vector) const;

};

#include "impl/matrix3.hpp"

using Matrix3f = Matrix3<float>;
using Matrix3i = Matrix3<int>;

#endif  // MATRIX3_H_
