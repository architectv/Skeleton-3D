template <std::size_t cols, std::size_t rows, typename T>
constexpr RectMatrix<cols, rows, T>::RectMatrix(T value) noexcept {
  for (std::size_t i = 0; i != cols; ++i)
    std::fill(data_[i].begin(), data_[i].end(), value);
}

template <std::size_t cols, std::size_t rows, typename T> template <typename... U>
constexpr RectMatrix<cols, rows, T>::RectMatrix(const Vector<rows, T>& first, const U&... next) noexcept: data_{first, next...} {
  static_assert(sizeof...(next) + 1 == cols, "Wrong cols amount");
}

template <std::size_t cols, std::size_t rows, typename T> template <std::size_t cols_, std::size_t rows_, typename U>
constexpr RectMatrix<cols, rows, T>::RectMatrix(const RectMatrix<cols_, rows_, U>& other) noexcept: RectMatrix() {
  for (std::size_t i = 0; i != Min(cols, cols_); ++i)
    for (std::size_t j = 0; j != Min(rows, rows_); ++j)
      data_[i].data_[j] = other.data_[i].data_[j];
}

template <std::size_t cols, std::size_t rows, typename T>
typename RectMatrix<cols, rows, T>::pointer RectMatrix<cols, rows, T>::data() {
  return data_[0].data();
}

template <std::size_t cols, std::size_t rows, typename T>
constexpr typename RectMatrix<cols, rows, T>::const_pointer RectMatrix<cols, rows, T>::data() const {
  return data_[0].data();
}

template <std::size_t cols, std::size_t rows, typename T>
Vector<rows, T>& RectMatrix<cols, rows, T>::operator[](std::size_t col) {
  return data_[col];
}

template <std::size_t cols, std::size_t rows, typename T>
constexpr const Vector<rows, T>& RectMatrix<cols, rows, T>::operator[](std::size_t col) const {
  return data_[col];
}

template <std::size_t cols, std::size_t rows, typename T>
constexpr Vector<cols, T> RectMatrix<cols, rows, T>::row(std::size_t row) const {
  Vector<cols, T> result;

  for (std::size_t i = 0; i != cols; ++i)
    result[i] = data_[i].data_[row];

  return result;
}

template <std::size_t cols, std::size_t rows, typename T>
void RectMatrix<cols, rows, T>::set_row(std::size_t row, const Vector<cols, T>& data) {
  for (std::size_t i = 0; i != cols; ++i)
    data_[i].data_[row] = data.data_[i];
}

template <std::size_t cols, std::size_t rows, typename T>
constexpr Vector<RectMatrix<cols, rows, T>::DiagonalSize, T> RectMatrix<cols, rows, T>::diagonal() const {
  Vector<DiagonalSize, T> result;

  for (std::size_t i = 0; i != DiagonalSize; ++i)
    result[i] = data_[i].data_[i];

  return result;
}

template <std::size_t cols, std::size_t rows, typename T>
RectMatrix<cols, rows, T>& RectMatrix<cols, rows, T>::operator+=(const RectMatrix<cols, rows, T>& other) {
  for (std::size_t i = 0; i != cols; ++i)
    data_[i] += other.data_[i];

  return *this;
}

template <std::size_t cols, std::size_t rows, typename T>
RectMatrix<cols, rows, T>& RectMatrix<cols, rows, T>::operator-=(const RectMatrix<cols, rows, T>& other) {
  for (std::size_t i = 0; i != cols; ++i)
    data_[i] -= other.data_[i];

  return *this;
}

template <std::size_t cols, std::size_t rows, typename T> template <typename ArithmeticType>
std::enable_if_t<std::is_arithmetic<ArithmeticType>::value, RectMatrix<cols, rows, T>&> RectMatrix<cols, rows, T>::operator*=(ArithmeticType factor) {
  for (std::size_t i = 0; i != cols; ++i)
    data_[i] *= factor;

  return *this;
}

template <std::size_t cols, std::size_t rows, typename T> template <typename ArithmeticType>
std::enable_if_t<std::is_arithmetic<ArithmeticType>::value, RectMatrix<cols, rows, T>&> RectMatrix<cols, rows, T>::operator/=(ArithmeticType divisor) {
  for (std::size_t i = 0; i != cols; ++i)
    data_[i] /= divisor;

  return *this;
}

template <std::size_t cols, std::size_t rows, typename T>
RectMatrix<cols, rows, T> operator+(const RectMatrix<cols, rows, T>& m1, const RectMatrix<cols, rows, T>& m2) {
  return RectMatrix<cols, rows, T>(m1) += m2;
}

template <std::size_t cols, std::size_t rows, typename T>
RectMatrix<cols, rows, T> operator-(const RectMatrix<cols, rows, T>& m1, const RectMatrix<cols, rows, T>& m2) {
  return RectMatrix<cols, rows, T>(m1) -= m2;
}

template <std::size_t cols, std::size_t rows, typename T>
RectMatrix<cols, rows, T> operator+(const RectMatrix<cols, rows, T>& matrix) {
  return matrix;
}

template <std::size_t cols, std::size_t rows, typename T>
RectMatrix<cols, rows, T> operator-(const RectMatrix<cols, rows, T>& matrix) {
  return RectMatrix<cols, rows, T>() - matrix;
}

template <std::size_t cols, std::size_t rows, typename T, typename ArithmeticType>
std::enable_if_t<std::is_arithmetic<ArithmeticType>::value, RectMatrix<cols, rows, T>> operator*(const RectMatrix<cols, rows, T>& matrix, ArithmeticType factor) {
  return RectMatrix<cols, rows, T>(matrix) *= factor;
}

template <std::size_t cols, std::size_t rows, typename T, typename ArithmeticType>
std::enable_if_t<std::is_arithmetic<ArithmeticType>::value, RectMatrix<cols, rows, T>> operator/(const RectMatrix<cols, rows, T>& matrix, ArithmeticType divisor) {
  assert(divisor != ArithmeticType{});
  return RectMatrix<cols, rows, T>(matrix) /= divisor;
}

template <std::size_t cols, std::size_t rows, typename T, std::size_t size>
RectMatrix<size, rows, T> operator*(const RectMatrix<cols, rows, T>& m1, const RectMatrix<size, cols, T>& m2) {
  RectMatrix<size, rows, T> result;

  for (std::size_t col = 0; col != size; ++col)
    for (std::size_t row = 0; row != rows; ++row)
      for (std::size_t pos = 0; pos != cols; ++pos)
        result[col][row] += m1[pos][row] * m2[col][pos];

  return result;
}

template <std::size_t cols, std::size_t rows, typename T> template <std::size_t size>
std::enable_if_t<cols == rows && rows == size, RectMatrix<size, size, T>&> RectMatrix<cols, rows, T>::operator*=(const RectMatrix<size, size, T>& other) {
  return *this = *this * other;
}

template <std::size_t cols, std::size_t rows, typename T>
Vector<rows, T> operator*(const RectMatrix<cols, rows, T>& matrix, const Vector<cols, T>& vector) {
  return (matrix * RectMatrix<1, cols, T>(vector))[0];
}

template <std::size_t cols, std::size_t rows, typename T>
RectMatrix<rows, cols, T> RectMatrix<cols, rows, T>::transposed() const {
  RectMatrix<rows, cols, T> result;

  for (std::size_t col = 0; col != cols; ++col)
    for (std::size_t row = 0; row != rows; ++row)
      result.data_[row].data_[col] = data_[col].data_[row];

  return result;
}

template <std::size_t cols, std::size_t rows, typename T>
std::istream& operator>>(std::istream& is, RectMatrix<cols, rows, T>& matrix) {
  for (std::size_t i = 0; i != rows; ++i)
    is >> matrix[i];

  return is;
}

template <std::size_t cols, std::size_t rows, typename T>
std::ostream& operator<<(std::ostream& os, const RectMatrix<cols, rows, T>& matrix) {
  for (std::size_t i = 0; i != rows; ++i)
    os << (i ? ' ' : '(') << matrix[i] << (i == rows - 1 ? ")" : ",\n");

  return os;
}
