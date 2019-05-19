#ifndef MATRIX_H_
#define MATRIX_H_

#include "rect_matrix.h"

template <std::size_t size, typename T>
struct MatrixDeterminant;

template <std::size_t size, typename T>
class Matrix : public RectMatrix<size, size, T> {
 public:
  using value_type = T;

  class IdentityInitT {};

  constexpr Matrix() noexcept = default;
  constexpr explicit Matrix(T value) noexcept;
  constexpr explicit Matrix(IdentityInitT, T value = T(1)) noexcept;

  template <typename... U>
  constexpr Matrix(const Vector<size, T>& first, const U&... next) noexcept;

  template <std::size_t cols, std::size_t rows, typename U>
  constexpr explicit Matrix(const RectMatrix<cols, rows, U>& other) noexcept;

  bool IsOrtogonal() const;

  Matrix<size - 1, T> minor(std::size_t col, std::size_t row) const;

  constexpr value_type determinant() const;

  Matrix inverted() const;
  Matrix inverted_orthogonal() const;

 private:
  friend struct MatrixDeterminant<size, T>;
};

template <std::size_t size, typename T>
struct MatrixDeterminant {
  T operator()(const Matrix<size, T>& m);
};

template <typename T>
struct MatrixDeterminant<1, T> {
  constexpr T operator()(const Matrix<1, T>& m);
};

template <typename T>
struct MatrixDeterminant<2, T> {
  constexpr T operator()(const Matrix<2, T>& m);
};

template <typename T>
struct MatrixDeterminant<3, T> {
  constexpr T operator()(const Matrix<3, T>& m);
};

#include "impl/matrix.hpp"

template <typename T>
using Matrix2x2 = Matrix<2, T>;

template <typename T>
using Matrix3x3 = Matrix<3, T>;

template <typename T>
using Matrix4x4 = Matrix<4, T>;


#endif  // MATRIX_H_
