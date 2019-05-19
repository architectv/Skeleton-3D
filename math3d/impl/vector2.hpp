template <typename T>
constexpr Vector2<T> Vector2<T>::x_axis(T value) {
  return {value, T{}};
}

template <typename T>
constexpr Vector2<T> Vector2<T>::y_axis(T value) {
  return {T{}, value};
}

template <typename T>
constexpr Vector2<T> Vector2<T>::x_scale(T value) {
  return {value, T(1)};
}

template <typename T>
constexpr Vector2<T> Vector2<T>::y_scale(T value) {
  return {T(1), value};
}

template <typename T>
constexpr Vector2<T>::Vector2() noexcept: Vector<2, T>() {}

template <typename T>
constexpr Vector2<T>::Vector2(const std::initializer_list<T>& list) noexcept: Vector<2, T>(list) {}

template <typename T>
constexpr Vector2<T>::Vector2(T value) noexcept: Vector<2, T>(value) {}

template <typename T>
constexpr Vector2<T>::Vector2(T x, T y) noexcept: Vector<2, T>{x, y} {}

template <typename T> template <std::size_t other_size, typename U>
constexpr Vector2<T>::Vector2(const Vector<other_size, U>& other) noexcept: Vector<2, T>(other) {}

template <typename T>
typename Vector2<T>::reference Vector2<T>::x() {
  return Vector<2, T>::data_[0];
}

template <typename T>
constexpr typename Vector2<T>::const_reference Vector2<T>::x() const {
  return Vector<2, T>::data_[0];
}

template <typename T>
typename Vector2<T>::reference Vector2<T>::y() {
  return Vector<2, T>::data_[1];
}

template <typename T>
constexpr typename Vector2<T>::const_reference Vector2<T>::y() const {
  return Vector<2, T>::data_[1];
}

template <typename T>
constexpr typename Vector2<T>::value_type Vector2<T>::SkewProduct(const Vector2<T> &v1, const Vector2<T> &v2) {
  return v1.x() * v2.y() - v1.y() * v2.x();
}

template <typename T>
constexpr Vector2<T> Vector2<T>::perpendicular() const {
  return {-y(), x()};
}

template <typename T> template <typename U>
std::enable_if_t<std::is_floating_point<U>::value, T> Vector2<T>::aspect_ratio() const {
  return x() / y();
}
