#ifndef MATRIX4_H_
#define MATRIX4_H_

#include "matrix.h"
#include "vector4.h"

template <typename T>
class Matrix4: public Matrix4x4<T> {
 public:
  constexpr static Matrix4<T> translation(const Vector3<T>& vector);
  constexpr static Matrix4<T> scaling(const Vector3<T>& vector);

  template <typename FloatingPoint>
  static std::enable_if_t<std::is_floating_point<FloatingPoint>::value, Matrix4<T>> rotation(FloatingPoint angle, const Vector3<T>& normalized_axis);

  template <typename FloatingPoint>
  static std::enable_if_t<std::is_floating_point<FloatingPoint>::value, Matrix4<T>> rotation_x(FloatingPoint angle);

  template <typename FloatingPoint>
  static std::enable_if_t<std::is_floating_point<FloatingPoint>::value, Matrix4<T>> rotation_y(FloatingPoint angle);

  template <typename FloatingPoint>
  static std::enable_if_t<std::is_floating_point<FloatingPoint>::value, Matrix4<T>> rotation_z(FloatingPoint angle);

  static Matrix4<T> reflection(const Vector3<T>& normal);

  constexpr static Matrix4<T> shearing_xy(T amount_x, T amount_y);
  constexpr static Matrix4<T> shearing_xz(T amount_x, T amount_z);
  constexpr static Matrix4<T> shearing_yz(T amount_y, T amount_z);

  static Matrix4<T> orthographic_projection(const Vector2<T>& size, T near, T far);
  static Matrix4<T> perspective_projection(T fov, T aspect_ratio, T near, T far);
  static Matrix4<T> perspective_projection(const Vector2<T>& size, T near, T far);

  static Matrix4<T> look_at(const Vector3<T>& eye, const Vector3<T>& target, const Vector3<T>& up);

  constexpr static Matrix4<T> from(const Matrix3x3<T>& rotation_scaling, const Vector3<T>& translation);

  constexpr Matrix4() noexcept;
  constexpr explicit Matrix4(T value) noexcept;
  constexpr explicit Matrix4(typename Matrix<4, T>::IdentityInitT, T value = T(1)) noexcept;

  constexpr Matrix4(const Vector4<T>& first, const Vector4<T>& second, const Vector4<T>& third, const Vector4<T>& fourth) noexcept;

  template <std::size_t cols, std::size_t rows, typename U>
  constexpr explicit Matrix4(const RectMatrix<cols, rows, U>& other) noexcept;

  bool IsRigidTransformation() const;

  constexpr Matrix3x3<T> rotation_scaling() const;
  constexpr Matrix3x3<T> rotation_shear() const;
  Matrix3x3<T> rotation() const;
  Matrix3x3<T> rotation_normalized() const;
  Vector3<T> scaling_squared() const;
  Vector3<T> scaling() const;
  T uniform_scaling_squared() const;
  T uniform_scaling() const;

  Vector3<T>& right();
  constexpr Vector3<T> right() const;

  Vector3<T>& up();
  constexpr Vector3<T> up() const;

  Vector3<T>& backward();
  constexpr Vector3<T> backward() const;

  Vector3<T>& translation();
  constexpr Vector3<T> translation() const;

  Matrix4<T> inverted_rigid() const;

  Vector3<T> map_vector(const Vector3<T>& vector) const;
  Vector3<T> map_point(const Vector3<T>& vector) const;
};

#include "impl/matrix4.hpp"

using Matrix4f = Matrix4<float>;
using Matrix4i = Matrix4<int>;

#endif  // MATRIX4_H_
