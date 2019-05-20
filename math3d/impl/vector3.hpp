template <typename T>
constexpr Vector3<T> Vector3<T>::x_axis(T value) {
  return {value, T{}, T{}};
}

template <typename T>
constexpr Vector3<T> Vector3<T>::y_axis(T value) {
  return {T{}, value, T{}};
}

template <typename T>
constexpr Vector3<T> Vector3<T>::z_axis(T value) {
  return {T{}, T{}, value};
}

template <typename T>
constexpr Vector3<T> Vector3<T>::x_scale(T value) {
  return {value, T(1), T(1)};
}

template <typename T>
constexpr Vector3<T> Vector3<T>::y_scale(T value) {
  return {T(1), value, T(1)};
}

template <typename T>
constexpr Vector3<T> Vector3<T>::z_scale(T value) {
  return {T(1), T(1), value};
}

template <typename T>
constexpr Vector3<T>::Vector3() noexcept: Vector<3, T>() {}

template <typename T>
constexpr Vector3<T>::Vector3(const std::initializer_list<T>& list) noexcept: Vector<3, T>(list) {}

template <typename T>
constexpr Vector3<T>::Vector3(T value) noexcept: Vector<3, T>(value) {}

template <typename T>
constexpr Vector3<T>::Vector3(T x, T y, T z) noexcept: Vector<3, T>{x, y, z} {}

template <typename T>
constexpr Vector3<T>::Vector3(const Vector2<T>& xy, T z) noexcept: Vector<3, T>{xy[0], xy[1], z} {}

template <typename T> template <std::size_t other_size, typename U>
constexpr Vector3<T>::Vector3(const Vector<other_size, U>& other) noexcept: Vector<3, T>(other) {}

template <typename T>
typename Vector3<T>::reference Vector3<T>::x() {
  return Vector<3, T>::data_[0];
}

template <typename T>
constexpr typename Vector3<T>::const_reference Vector3<T>::x() const {
  return Vector<3, T>::data_[0];
}

template <typename T>
typename Vector3<T>::reference Vector3<T>::y() {
  return Vector<3, T>::data_[1];
}

template <typename T>
constexpr typename Vector3<T>::const_reference Vector3<T>::y() const {
  return Vector<3, T>::data_[1];
}

template <typename T>
typename Vector3<T>::reference Vector3<T>::z() {
  return Vector<3, T>::data_[2];
}

template <typename T>
constexpr typename Vector3<T>::const_reference Vector3<T>::z() const {
  return Vector<3, T>::data_[2];
}

template <typename T>
constexpr Vector2<T> Vector3<T>::xy() const {
  return {x(), y()};
}

template <typename T>
constexpr Vector3<T> Vector3<T>::CrossProduct(const Vector3<T> &v1, const Vector3<T> &v2) {
  return {
    v1.y() * v2.z() - v1.z() * v2.y(),
    v1.z() * v2.x() - v1.x() * v2.z(),
    v1.x() * v2.y() - v1.y() * v2.x()
  };
}
