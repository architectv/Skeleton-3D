#ifndef MATRIX_H_
#define MATRIX_H_

#include <initializer_list>
#include <istream>
#include <ostream>
#include "vector.h"

template <std::size_t rows, std::size_t cols>
class Matrix;

using Matrix3 = Matrix<3, 3>;
using Matrix4 = Matrix<4, 4>;

template <std::size_t rows, std::size_t cols>
class Matrix {
  static_assert(rows != 0 && cols != 0, "Zero dimension matrix does not exist");

 public:
  using row = Vector<rows>;
  using reference = row&;
  using const_reference = const row&;

  constexpr Matrix() noexcept = default;
  constexpr Matrix(const std::initializer_list<float>& list) noexcept;
  constexpr Matrix(float scalar);

  constexpr static Matrix identity() noexcept;

  reference operator[](std::size_t row);
  constexpr const_reference operator[](std::size_t row) const;

  reference at(std::size_t row);
  const_reference at(std::size_t row) const;

  constexpr Matrix& operator+=(const Matrix& other);
  constexpr Matrix& operator-=(const Matrix& other);

  template <std::size_t span>
  constexpr Matrix<rows, span>& operator*=(const Matrix<cols, span>& other);

  constexpr Matrix& operator*=(float scalar);

  template <std::size_t rows_, std::size_t cols_>
  friend constexpr Matrix<rows_, cols_> operator+(const Matrix<rows_, cols_>& m1, const Matrix<rows_, cols_>& m2);

  template <std::size_t rows_, std::size_t cols_>
  friend constexpr Matrix<rows_, cols_> operator-(const Matrix<rows_, cols_>& m1, const Matrix<rows_, cols_>& m2);

  template <std::size_t rows_, std::size_t cols_, std::size_t span_>
  friend constexpr Matrix<rows_, span_> operator*(const Matrix<rows_, cols_>& m1, const Matrix<cols_, span_>& m2);

  template <std::size_t rows_, std::size_t cols_>
  friend constexpr Matrix<rows_, cols_> operator*(const Matrix<rows_, cols_>& matrix, float scalar);

  template <std::size_t rows_, std::size_t cols_>
  friend constexpr Vector<rows_ - 1> operator*(const Matrix<rows_, cols_>& matrix, const Vector<rows_ - 1>& vector);

  template <std::size_t rows_, std::size_t cols_>
  friend std::istream& operator>>(std::istream& is, Matrix<rows_, cols_>& matrix);

  template <std::size_t rows_, std::size_t cols_>
  friend std::ostream& operator<<(std::ostream& os, const Matrix<rows_, cols_>& matrix);

 protected:
  row data_[cols];
};

template <std::size_t rows, std::size_t cols>
constexpr Matrix<rows, cols>::Matrix(const std::initializer_list<float>& list) noexcept: Matrix() {
  auto it = list.begin();
  for (std::size_t i = 0; i != rows; ++i)
    for (std::size_t j = 0; j != cols; ++j) {
      data_[i][j] = *it++;
      if (it == list.end())
        return;
    }
}

template <std::size_t rows, std::size_t cols>
constexpr Matrix<rows, cols>::Matrix(float scalar) {
  static_assert(rows == cols, "Must not be called on a rectangular matrix");
  for (std::size_t i = 0; i != rows; ++i)
    data_[i][i] = scalar;
}

template <std::size_t rows, std::size_t cols>
constexpr Matrix<rows, cols> Matrix<rows, cols>::identity() noexcept {
  Matrix<rows, cols> identify(1);
  return identify;
}

template <std::size_t rows, std::size_t cols>
typename Matrix<rows, cols>::reference Matrix<rows, cols>::operator[](std::size_t row) {
  assert(row < rows);
  return data_[row];
}

template <std::size_t rows, std::size_t cols>
constexpr typename Matrix<rows, cols>::const_reference Matrix<rows, cols>::operator[](std::size_t row) const {
  assert(row < rows);
  return data_[row];
}

template <std::size_t rows, std::size_t cols>
typename Matrix<rows, cols>::reference Matrix<rows, cols>::at(std::size_t row) {
  if (row >= rows)
    throw std::out_of_range("Out of range");
  return data_[row];
}

template <std::size_t rows, std::size_t cols>
typename Matrix<rows, cols>::const_reference Matrix<rows, cols>::at(std::size_t row) const {
  if (row >= rows)
    throw std::out_of_range("Out of range");
  return data_[row];
}

template <std::size_t rows, std::size_t cols>
constexpr Matrix<rows, cols>& Matrix<rows, cols>::operator+=(const Matrix<rows, cols>& other) {
  for (std::size_t i = 0; i != rows; ++i)
    data_[i] += other.data_[i];
  return *this;
}

template <std::size_t rows, std::size_t cols>
constexpr Matrix<rows, cols>& Matrix<rows, cols>::operator-=(const Matrix<rows, cols>& other) {
  for (std::size_t i = 0; i != rows; ++i)
    data_[i] -= other.data_[i];
  return *this;
}

template <std::size_t rows, std::size_t cols> template <std::size_t span>
constexpr Matrix<rows, span>& Matrix<rows, cols>::operator*=(const Matrix<cols, span>& other) {
  Matrix<rows, span> result;
  for (std::size_t i = 0; i != rows; ++i)
    for (std::size_t j = 0; j != span; ++j)
      for (std::size_t k = 0; k != cols; ++k)
        result.data_[i][j] += data_[i][k] * other.data_[k][j];
  return *this = result;
}

template <std::size_t rows, std::size_t cols>
constexpr Matrix<rows, cols>& Matrix<rows, cols>::operator*=(float scalar) {
  for (std::size_t i = 0; i != rows; ++i)
    data_[i] *= scalar;
  return *this;
}

template <std::size_t rows, std::size_t cols>
constexpr Matrix<rows, cols> operator+(const Matrix<rows, cols>& m1, const Matrix<rows, cols>& m2) {
  return Matrix<rows, cols>(m1) += m2;
}

template <std::size_t rows, std::size_t cols>
constexpr Matrix<rows, cols> operator-(const Matrix<rows, cols>& m1, const Matrix<rows, cols>& m2) {
  return Matrix<rows, cols>(m1) -= m2;
}

template <std::size_t rows, std::size_t cols, std::size_t span>
constexpr Matrix<rows, span> operator*(const Matrix<rows, cols>& m1, const Matrix<cols, span>& m2) {
  Matrix<rows, cols>(m1) *= m2;
}

template <std::size_t rows, std::size_t cols>
constexpr Matrix<rows, cols> operator*(const Matrix<rows, cols>& matrix, float scalar) {
  return Matrix<rows, cols>(matrix) *= scalar;
}

template <std::size_t rows, std::size_t cols>
constexpr Vector<rows - 1> operator*(const Matrix<rows, cols>& matrix, const Vector<rows - 1>& vector) {
  static_assert(rows > 1, "Must not be called on a vector");
  Vector<rows> w(vector);
  w.back() = 1.0f;

  Vector<rows - 1> result;
  for (std::size_t i = 0; i + 1 < rows; ++i)
    for (std::size_t k = 0; k != cols; ++k)
      result[i] += matrix[i][k] * w[k];

  return result;
}

template <std::size_t rows, std::size_t cols>
std::istream& operator>>(std::istream& is, Matrix<rows, cols>& matrix) {
  for (std::size_t i = 0; i != rows; ++i)
    is >> matrix.data_[i];
  return is;
}

template <std::size_t rows, std::size_t cols>
std::ostream& operator<<(std::ostream& os, const Matrix<rows, cols>& matrix) {
  for (std::size_t i = 0; i != rows; ++i) {
    os << (i ? ' ' : '(') << matrix.data_[i] << (i == rows - 1 ? ")" : ",\n");
  }
  return os;
}

#endif  // MATRIX_H_
