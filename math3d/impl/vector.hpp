template <std::size_t size, typename T>
constexpr Vector<size, T>::Vector() noexcept: data_{} {}

template <std::size_t size, typename T>
constexpr Vector<size, T>::Vector(std::initializer_list<T> list) noexcept: data_{} {
  std::copy(list.begin(), list.size() <= size ? list.end() : list.begin() + size, data_);
}

template <std::size_t size, typename T> template <typename... U, typename y>
constexpr Vector<size, T>::Vector(T first, U... next) noexcept: data_{first, next...} {}

template <std::size_t size, typename T>
Vector<size, T>::Vector(T value) noexcept: data_{} {
  std::fill(begin(), end(), value);
}

template <std::size_t size, typename T> template <std::size_t other_size>
constexpr Vector<size, T>::Vector(const Vector<other_size, T>& other) noexcept: data_{} {
  if (size <= other_size)
    std::copy(other.begin(), other.begin() + size, begin());
  else
    std::copy(other.begin(), other.end(), end());
}

template <std::size_t size, typename T> template <std::size_t other_size, typename U>
constexpr Vector<size, T>::Vector(const std::enable_if_t<std::is_convertible<U, T>::value, Vector<other_size, U>>& other) noexcept: data_{} {
  for (std::size_t i = 0; i != Min(size, other_size); ++i)
    data_[i] = other.data_[i];
}

template <std::size_t size, typename T>
typename Vector<size, T>::pointer Vector<size, T>::data() {
  return data_;
}

template <std::size_t size, typename T>
constexpr typename Vector<size, T>::const_pointer Vector<size, T>::data() const {
  return data_;
}

template <std::size_t size, typename T>
typename Vector<size, T>::reference Vector<size, T>::operator[](std::size_t index) {
  return data_[index];
}

template <std::size_t size, typename T>
constexpr typename Vector<size, T>::const_reference Vector<size, T>::operator[](std::size_t index) const {
  return data_[index];
}

template <std::size_t size, typename T>
typename Vector<size, T>::reference Vector<size, T>::at(std::size_t index) {
  if (index >= size)
    throw std::out_of_range("Out of range");
  return data_[index];
}

template <std::size_t size, typename T>
typename Vector<size, T>::const_reference Vector<size, T>::at(std::size_t index) const {
  if (index >= size)
    throw std::out_of_range("Out of range");
  return data_[index];
}

template <std::size_t size, typename T>
typename Vector<size, T>::reference Vector<size, T>::front() {
  return data_[0];
}

template <std::size_t size, typename T>
constexpr typename Vector<size, T>::const_reference Vector<size, T>::front() const {
  return data_[0];
}

template <std::size_t size, typename T>
typename Vector<size, T>::reference Vector<size, T>::back() {
  return data_[size - 1];
}

template <std::size_t size, typename T>
constexpr typename Vector<size, T>::const_reference Vector<size, T>::back() const {
  return data_[size - 1];
}

template <std::size_t size, typename T>
typename Vector<size, T>::iterator Vector<size, T>::begin() {
  return data_;
}

template <std::size_t size, typename T>
constexpr typename Vector<size, T>::const_iterator Vector<size, T>::begin() const {
  return data_;
}

template <std::size_t size, typename T>
typename Vector<size, T>::iterator Vector<size, T>::end() {
  return data_ + size;
}

template <std::size_t size, typename T>
constexpr typename Vector<size, T>::const_iterator Vector<size, T>::end() const {
  return data_ + size;
}

template <std::size_t size, typename T>
typename Vector<size, T>::value_type Vector<size, T>::length() const {
  return std::sqrt(DotProduct(*this, *this));
}

template <std::size_t size, typename T>
constexpr typename Vector<size, T>::value_type Vector<size, T>::sum() const {
  T result(data_[0]);

  for (std::size_t i = 1; i != size; ++i)
    result += data_[i];

  return result;
}

template <std::size_t size, typename T>
constexpr typename Vector<size, T>::value_type Vector<size, T>::product() const {
  T result(data_[0]);

  for (std::size_t i = 1; i != size; ++i)
    result *= data_[i];

  return result;
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wfloat-equal"

// TODO ::boost::is_equality_comparable
template <std::size_t size, typename T, typename U>
constexpr bool operator==(const Vector<size, T>& v1, const Vector<size, U>& v2) {
  for (std::size_t i = 0; i != size; ++i)
    if (v1[i] != v2[i])
      return false;
  return true;
}

template <std::size_t size, typename T, typename U>
constexpr bool operator!=(const Vector<size, T>& v1, const Vector<size, U>& v2) {
  return !(v1 == v2);
}

#pragma GCC diagnostic pop

template <std::size_t size, typename T, typename U>
constexpr std::enable_if_t<std::is_floating_point<std::common_type_t<T, U>>::value, bool> FuzzyCompare(const Vector<size, T>& v1, const Vector<size, U>& v2) {
  for (std::size_t i = 0; i != size; ++i)
    if (!FuzzyCompare(v1[i], v2[i]))
      return false;
  return true;
}

template <std::size_t size, typename T, typename U>
Vector<size, bool> operator<(const Vector<size, T>& v1, const Vector<size, U>& v2) {
  Vector<size, bool> result;

  for (std::size_t i = 0; i != size; ++i)
    result[i] = v1[i] < v2[i];

  return result;
}

template <std::size_t size, typename T, typename U>
Vector<size, bool> operator<=(const Vector<size, T>& v1, const Vector<size, U>& v2) {
  Vector<size, bool> result;

  for (std::size_t i = 0; i != size; ++i)
    result[i] = v1[i] <= v2[i];

  return result;
}

template <std::size_t size, typename T, typename U>
Vector<size, bool> operator>(const Vector<size, T>& v1, const Vector<size, U>& v2) {
  Vector<size, bool> result;

  for (std::size_t i = 0; i != size; ++i)
    result[i] = v1[i] > v2[i];

  return result;
}

template <std::size_t size, typename T, typename U>
Vector<size, bool> operator>=(const Vector<size, T>& v1, const Vector<size, U>& v2) {
  Vector<size, bool> result;

  for (std::size_t i = 0; i != size; ++i)
    result[i] = v1[i] >= v2[i];

  return result;
}

template <std::size_t size, typename T>
constexpr Vector<size, T>& Vector<size, T>::operator+=(const Vector<size, T>& other) {
  for (std::size_t i = 0; i != size; ++i)
    data_[i] += other.data_[i];
  return *this;
}

template <std::size_t size, typename T>
constexpr Vector<size, T>& Vector<size, T>::operator-=(const Vector<size, T>& other) {
  for (std::size_t i = 0; i != size; ++i)
    data_[i] -= other.data_[i];
  return *this;
}

template <std::size_t size, typename T>
constexpr Vector<size, T>& Vector<size, T>::operator*=(const Vector<size, T>& other) {
  for (std::size_t i = 0; i != size; ++i)
    data_[i] *= other.data_[i];
  return *this;
}

template <std::size_t size, typename T>
constexpr Vector<size, T>& Vector<size, T>::operator/=(const Vector<size, T>& other) {
  for (std::size_t i = 0; i != size; ++i)
    data_[i] /= other.data_[i];
  return *this;
}

template <std::size_t size, typename T> template <typename U>
constexpr Vector<size, T>& Vector<size, T>::operator*=(U factor) {
  for (std::size_t i = 0; i != size; ++i)
    data_[i] *= factor;
  return *this;
}

template <std::size_t size, typename T> template <typename U>
constexpr Vector<size, T>& Vector<size, T>::operator/=(U divisor) {
  for (std::size_t i = 0; i != size; ++i)
    data_[i] /= divisor;
  return *this;
}

template <std::size_t size, typename T>
constexpr Vector<size, T> operator+(const Vector<size, T>& v1, const Vector<size, T>& v2) {
  return Vector<size, T>(v1) += v2;
}

template <std::size_t size, typename T>
constexpr Vector<size, T> operator+(const Vector<size, T>& vector) {
  return vector;
}

template <std::size_t size, typename T>
constexpr Vector<size, T> operator-(const Vector<size, T>& v1, const Vector<size, T>& v2) {
  return Vector<size, T>(v1) -= v2;
}

template <std::size_t size, typename T>
constexpr Vector<size, T> operator-(const Vector<size, T>& vector) {
  return Vector<size, T>() -= vector;
}

template <std::size_t size, typename T>
constexpr Vector<size, T> operator*(float factor, const Vector<size, T>& vector) {
  return vector * factor;
}

template <std::size_t size, typename T>
constexpr Vector<size, T> operator*(const Vector<size, T>& v1, const Vector<size, T>& v2) {
  return Vector<size, T>(v1) *= v2;
}

template <std::size_t size, typename T, typename U>
constexpr Vector<size, T> operator*(const Vector<size, T>& vector, U factor) {
  return Vector<size, T>(vector) *= factor;
}

template <std::size_t size, typename T, typename U>
constexpr Vector<size, T> operator/(const Vector<size, T>& vector, U divisor) {
  assert(divisor != U{});
  return Vector<size, T>(vector) /= divisor;
}

template <std::size_t size, typename T>
constexpr Vector<size, T> operator/(const Vector<size, T>& v1, const Vector<size, T>& v2) {
  return Vector<size, T>(v1) /= v2;
}

template <std::size_t size, typename T>
constexpr bool Vector<size, T>::IsNull() const {
  for (std::size_t i = 0; i != size; ++i)
    if (!::IsNull(data_[i]))
      return false;
  return true;
}

template <std::size_t size, typename T>
constexpr bool Vector<size, T>::IsNormalized() const {
  return FuzzyIsNull(DotProduct(*this, *this) - 1.0);
}

template <std::size_t size, typename T>
constexpr T Vector<size, T>::DotProduct(const Vector<size, T>& v1, const Vector<size, T>& v2) {
  return (v1 * v2).sum();
}

template <std::size_t size, typename T> template <typename U>
std::enable_if_t<std::is_floating_point<U>::value, Vector<size, T>> Vector<size, T>::normalized() const {
  return *this * (T(1) / length());
}

template <std::size_t size, typename T> template <typename U>
std::enable_if_t<std::is_floating_point<U>::value> Vector<size, T>::normalize() {
  *this *= T(1) / length();
}

template <std::size_t size, typename T> template <typename U>
std::enable_if_t<std::is_floating_point<U>::value, Vector<size, T>> Vector<size, T>::Projected(const Vector<size, T>& line) const {
  return line * Vector<size, T>::DotProduct(*this, line) / Vector<size, T>::DotProduct(line, line);
}

template <std::size_t size, typename T> template <typename U>
std::enable_if_t<std::is_floating_point<U>::value, Vector<size, T>> Vector<size, T>::ProjectedOntoNormalized(const Vector<size, T>& line) const {
  assert(line.IsNormalized());
  return line * Vector<size, T>::DotProduct(*this, line);
}

template <std::size_t size, typename T>
std::istream& operator>>(std::istream& is, Vector<size, T>& vector) {
  for (std::size_t i = 0; i != size; ++i)
    is >> vector[i];

  return is;
}

template <std::size_t size, typename T>
std::ostream& operator<<(std::ostream& os, const Vector<size, T>& vector) {
  os << '(';

  for (std::size_t i = 0; i + 1 < size; ++i)
    os << vector[i] << ", ";

  os << vector.back() << ')';

  return os;
}
