#ifndef RECT_MATRIX_H_
#define RECT_MATRIX_H_

#include "vector.h"

template <std::size_t cols, std::size_t rows, typename T>
class RectMatrix {
  static_assert(cols != 0 && rows != 0, "Zero elements rectangular matrix does not exist");

  template <std::size_t, std::size_t, class>
  friend class RectMatrix;

 public:
  using pointer = T*;
  using const_pointer = const T*;

  enum: std::size_t {
    Cols = cols,
    Rows = rows,
    DiagonalSize = cols < rows ? cols : rows
  };

  constexpr RectMatrix() noexcept = default;
  constexpr explicit RectMatrix(T value) noexcept;

  template <typename... U>
  constexpr explicit RectMatrix(const Vector<rows, T>& first, const U&... next) noexcept;

  template <std::size_t cols_, std::size_t rows_, typename U>
  constexpr explicit RectMatrix(const RectMatrix<cols_, rows_, U>& other) noexcept;

  pointer data();
  constexpr const_pointer data() const;

  Vector<rows, T>& operator[](std::size_t col);
  constexpr const Vector<rows, T>& operator[](std::size_t col) const;

  constexpr Vector<cols, T> row(std::size_t row) const;
  void set_row(std::size_t row, const Vector<cols, T>& data);

  constexpr Vector<DiagonalSize, T> diagonal() const;

  RectMatrix& operator+=(const RectMatrix& other);
  RectMatrix& operator-=(const RectMatrix& other);

  template <typename ArithmeticType>
  std::enable_if_t<std::is_arithmetic<ArithmeticType>::value, RectMatrix&> operator*=(ArithmeticType factor);

  template <typename ArithmeticType>
  std::enable_if_t<std::is_arithmetic<ArithmeticType>::value, RectMatrix&> operator/=(ArithmeticType divisor);

  template <std::size_t size>
  std::enable_if_t<cols == rows && rows == size, RectMatrix<size, size, T>&> operator*=(const RectMatrix<size, size, T>& other);

  RectMatrix<rows, cols, T> transposed() const;

 protected:
  Vector<rows, T> data_[cols];
};

template <std::size_t cols, std::size_t rows, typename T>
RectMatrix<cols, rows, T> operator+(const RectMatrix<cols, rows, T>& m1, const RectMatrix<cols, rows, T>& m2);

template <std::size_t cols, std::size_t rows, typename T>
RectMatrix<cols, rows, T> operator-(const RectMatrix<cols, rows, T>& m1, const RectMatrix<cols, rows, T>& m2);

template <std::size_t cols, std::size_t rows, typename T>
RectMatrix<cols, rows, T> operator+(const RectMatrix<cols, rows, T>& matrix);

template <std::size_t cols, std::size_t rows, typename T>
RectMatrix<cols, rows, T> operator-(const RectMatrix<cols, rows, T>& matrix);

template <std::size_t cols, std::size_t rows, typename T, typename U>
RectMatrix<cols, rows, T> operator*(const RectMatrix<cols, rows, T>& matrix, U factor);

template <std::size_t cols, std::size_t rows, typename T, typename U>
RectMatrix<cols, rows, T> operator/(const RectMatrix<cols, rows, T>& matrix, U divisor);

template <std::size_t cols, std::size_t rows, typename T, std::size_t size>
RectMatrix<size, rows, T> operator*(const RectMatrix<cols, rows, T>& m1, const RectMatrix<size, cols, T>& m2);

template <std::size_t cols, std::size_t rows, typename T>
Vector<rows, T> operator*(const RectMatrix<cols, rows, T>& matrix, const Vector<cols, T>& vector);

template <std::size_t cols, std::size_t rows, typename T>
std::istream& operator>>(std::istream& is, RectMatrix<cols, rows, T>& matrix);

template <std::size_t cols, std::size_t rows, typename T>
std::ostream& operator<<(std::ostream& os, const RectMatrix<cols, rows, T>& matrix);

#include "impl/rect_matrix.hpp"

#endif  // RECT_MATRIX_H_
