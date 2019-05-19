template <std::size_t size, typename T>
constexpr Matrix<size, T>::Matrix(T value) noexcept: RectMatrix<size, size, T>(value) {}

template <std::size_t size, typename T>
constexpr Matrix<size, T>::Matrix(IdentityInitT, T value) noexcept: RectMatrix<size, size, T>() {
for (std::size_t i = 0; i != size; ++i)
  RectMatrix<size, size, T>::data_[i][i] = value;
}

template <std::size_t size, typename T> template <typename... U>
constexpr Matrix<size, T>::Matrix(const Vector<size, T>& first, const U&... next) noexcept: RectMatrix<size, size, T>(first, next...) {}

template <std::size_t size, typename T> template <std::size_t cols, std::size_t rows, typename U>
constexpr Matrix<size, T>::Matrix(const RectMatrix<cols, rows, U>& other) noexcept: RectMatrix<size, size, T>(other) {}

template <std::size_t size, typename T>
bool Matrix<size, T>::IsOrtogonal() const {
  for (std::size_t i = 0; i != size; ++i)
    if (!RectMatrix<size, size, T>::data_[i].IsNormalized())
      return false;

  for (std::size_t i = 0; i != size - 1; ++i)
    for (std::size_t j = i + 1; j != size; ++j)
      if (Vector<size, T>::DotProduct(this->data_[i], this->data_[j]) > TypeTraits<T>::eps)
        return false;

  return true;
}

template <std::size_t size, typename T>
Matrix<size - 1, T> Matrix<size, T>::minor(std::size_t col, std::size_t row) const {
  Matrix<size - 1, T> result;

  for (std::size_t i = 0; i != size - 1; ++i)
    for (std::size_t j = 0; j != size - 1; ++j)
      result.data_[i].data_[j] = RectMatrix<size, size, T>::data_[i + (i >= col)].data_[j + (j >= row)];

  return result;
}

template <std::size_t size, typename T>
constexpr typename Matrix<size, T>::value_type  Matrix<size, T>::determinant() const {
  return MatrixDeterminant<size, T>(*this);
}

template <std::size_t size, typename T>
Matrix<size, T> Matrix<size, T>::inverted() const {
  Matrix<size, T> result;

  const T det = determinant();

  for (std::size_t col = 0; col != size; ++col)
    for (std::size_t row = 0; row != size; ++row)
      result.data_[col].data_[row] = ((row + col) & 1 ? -1 : 1) * minor(row, col).determinant() / det;

  return result;
}

template <std::size_t size, typename T>
Matrix<size, T> Matrix<size, T>::inverted_orthogonal() const {
  assert(IsOrtogonal());
  return RectMatrix<size, size, T>::transposed();
}

template <std::size_t size, typename T>
T MatrixDeterminant<size, T>::operator()(const Matrix<size, T>& m) {
  T result{};

  for (std::size_t col = 0; col != size; ++col)
    result += (col & 1 ? -1 : 1) * m.data_[col].data_[0] * m.minor(col, 0).determinant();

  return result;
}

template <typename T>
constexpr T MatrixDeterminant<1, T>::operator()(const Matrix<1, T>& m) {
  return m.data_[0].data_[0];
}

template <typename T>
constexpr T MatrixDeterminant<2, T>::operator()(const Matrix<2, T>& m) {
  return m.data_[0].data_[0] * m.data_[1].data_[1] - m.data_[1].data_[0] * m.data_[0].data_[1];
}
template <typename T>
constexpr T MatrixDeterminant<3, T>::operator()(const Matrix<3, T>& m) {
  return
    m.data_[0].data_[0] * (m.data_[1].data_[1] * m.data_[2].data_[2] - m.data_[2].data_[1] * m.data_[1].data_[2])
  - m.data_[0].data_[1] * (m.data_[1].data_[0] * m.data_[2].data_[2] - m.data_[2].data_[0] * m.data_[1].data_[2])
  + m.data_[0].data_[2] * (m.data_[1].data_[0] * m.data_[2].data_[1] - m.data_[2].data_[0] * m.data_[1].data_[1]);
}